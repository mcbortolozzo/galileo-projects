/*
  raid.c: River Raid, using galileo as controller inputs

  Copyright (c) 2017 Marcelo Cardoso Bortolozzo <mcbortolozzo@inf.ufrgs.br>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.
*/

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "raid.h"
#include "interface.h"
#include "raid_list.h"

#ifdef GALILEO
#include <fcntl.h>
#include <unistd.h>
#include <galileo2io.h>
#endif

int start_game(options_t *game_options)
{
  ship_t *player = new_ship(game_options);
  int score = 0;

  while(player->hp > 0)
  {
    player->x_pos = DEFAULT_X_POS;
    map_t *map = new_map();
    list_t *bullet_list = new_bullet_list();
    list_t *enemy_list = new_enemy_list();
    int cycles = 0;
    int map_speed = get_map_speed(game_options);
#ifdef GALILEO
    map_speed /= 10;
#endif
    while(1)
    {
      move_args_t args = {map, enemy_list};
      list_for_each(bullet_list, move_bullet, &args);
      if(cycles == map_speed)
      {
        cycles = 0;
        list_for_each(enemy_list, move_enemy, NULL);
        move_map_step(map, game_options);
        generate_enemies(enemy_list, game_options, map);
      }
      draw_map(map, player, bullet_list, enemy_list);
      if(check_player_collision(map, player, enemy_list) == COLLISION)
      {
        player->hp--;
        restart_match(map, bullet_list, enemy_list);
        if(player->hp) show_continue(player->hp);
        break;
      }
      move_player(player, bullet_list);
#ifndef GALILEO
      usleep(100000);
#endif
      cycles++;
    }
  }
  show_defeat(score);
  return score;
}

//**** OBJECT INITIZALIZATION ****//

ship_t *new_ship(options_t* game_options)
{
  ship_t *ship = calloc(1, sizeof(ship_t));
  ship->x_pos = DEFAULT_X_POS;
  ship->y_pos = DEFAULT_Y_POS;
  switch (game_options->difficulty) {
    case EASY:    ship->hp = EASY_HP; break;
    case NORMAL:  ship->hp = NORMAL_HP; break;
    case HARD:    ship->hp = HARD_HP; break;
    case LUNATIC: ship->hp = LUNATIC_HP; break;
  }
  ship->weapon = new_weapon();
#ifdef GALILEO
  if((ship->button_file=open("/sys/class/gpio/gpio6/value",O_RDONLY)) < 0)
  {
    printf("Opening /sys/class/gpio/gpio6/value");
    exit(-1);
  }
  if((ship->control_file=open("/sys/bus/iio/devices/iio:device0/in_voltage0_raw",O_RDONLY)) < 0)
  {
          perror("Opening in_voltage0raw:");
          exit(-1);
  }
  char data_str[80];
  pgets(data_str,sizeof data_str,"/sys/bus/iio/devices/iio:device0/in_voltage0_scale");
  ship->scale=atof(data_str)/1000.0;
#endif
  return ship;
}

weapon_t *new_weapon()
{
  weapon_t *weapon = calloc(1, sizeof(weapon_t));
  weapon->type = WEAPON_DEFAULT;
  weapon->reload_time = RELOAD_DEFAULT;
  weapon->curr_reload = 0;
  return weapon;
}

bullet_t *new_bullet(ship_t *player_ship)
{
  bullet_t *bullet = calloc(1, sizeof(bullet_t));
  bullet->x_pos = player_ship->x_pos;
  bullet->y_pos = player_ship->y_pos - 1;
  bullet->type = player_ship->weapon->type;
  bullet->move_delay = 0;
  return bullet;
}

enemy_t *new_enemy()
{
  enemy_t *enemy = calloc(1, sizeof(enemy_t));

  return enemy;
}

map_t *new_map()
{
  int i;
  map_t *map = calloc(1, sizeof(map_t));
  map->grid = calloc(WINDOW_LENGTH, sizeof(char*));
  map->draw_grid = calloc(WINDOW_LENGTH, sizeof(char*));

  for(i = 0; i < WINDOW_LENGTH; i++)
  {
    map->grid[i] = calloc(WINDOW_WIDTH, sizeof(char));
    map->draw_grid[i] = calloc(WINDOW_WIDTH, sizeof(char));
  }

  clear_map(map);
  return map;
}

options_t *new_options()
{
    options_t *options = calloc(1, sizeof(options_t));
    options->difficulty = DEFAULT_DIFFICULTY;
    return options;
}

//***** MAP ******//

int get_map_speed(options_t *game_options)
{
    switch (game_options->difficulty) {
      case EASY:    return EASY_SPEED;
      case NORMAL:  return NORMAL_SPEED;
      case HARD:    return HARD_SPEED;
      case LUNATIC: return LUNATIC_SPEED;
    }
    return EASY_SPEED;
}

void generate_map_line(char* next_line, char* prev_line, options_t *options)
{
  int x_pos = 0;
  int counting = 0;
  int passage_begin = -1;
  prob_gen_t p_gen;
  get_probability_mode(prev_line, &p_gen);
  strncpy(next_line, prev_line, WINDOW_WIDTH);
  int min_passage_width = get_passage_width(options);

  while(x_pos < WINDOW_WIDTH)
  {
    if(prev_line[x_pos] != MAP_BLOCK && !counting)
    {
      counting = 1;
      passage_begin = x_pos-1;
    }
    else if(prev_line[x_pos] == MAP_BLOCK && counting && passage_begin != -1)
    {
      counting = 0;
      int passage_width = x_pos - passage_begin;
      int r = rand() % 100;

      if(r < p_gen.island && passage_width > 2*min_passage_width + 1) // island
      {
        int pos = rand() % (passage_width - 2*min_passage_width);
        next_line[passage_begin + pos + min_passage_width] = MAP_BLOCK;
      }
      else if(r < p_gen.close_left && passage_width > min_passage_width + 1) //inc left
      {
        next_line[passage_begin + 1] = MAP_BLOCK;
      }
      else if(r < p_gen.close_right && passage_width > min_passage_width + 1) // inc right
      {
        next_line[x_pos - 1] = MAP_BLOCK;
      }
      else if(r < p_gen.open_left && passage_begin > 0)  // dec left
      {
        next_line[passage_begin] = MAP_WATER;
      }
      else if(r < p_gen.open_right && x_pos < WINDOW_WIDTH - 1) //dec rigth
      {
        next_line[x_pos] = MAP_WATER;
      }
    }
    x_pos++;
  }
}

int get_passage_width(options_t *options)
{
  switch (options->difficulty) {
    case EASY:    return EASY_WIDTH;
    case NORMAL:  return NORMAL_WIDTH;
    case HARD:    return HARD_WIDTH;
    case LUNATIC: return LUNATIC_WIDTH;
  }
  return EASY_WIDTH;
}

void get_probability_mode(char *prev_line, prob_gen_t* p_gen) //TODO adapt according to difficulty
{
  int x;
  int w_blocks = 0;
  int island_count = 0;
  int counting = -1;
  for(x = 1; x < WINDOW_WIDTH - 1; x++)
  {
    if(prev_line[x] == MAP_WATER)
    {
      if(counting == 1) island_count++;
      counting = 0;
      w_blocks++;
    }
    if(counting == 0 && prev_line[x] == MAP_BLOCK)
    {
      counting = 1;
    }
  }

  if(w_blocks < 30)
  {
    p_gen->island       = island_count ? 0 : 5;
    p_gen->close_left   = 15 - p_gen->island / 2;
    p_gen->close_right  = 25;
    p_gen->open_left    = 50;
    p_gen->open_right   = 75;
  }
  else if(w_blocks < 50)
  {
    p_gen->island       = island_count > 1 ? 0 : 10;
    p_gen->close_left   = 30 - p_gen->island / 2;
    p_gen->close_right  = 50;
    p_gen->open_left    = 70;
    p_gen->open_right   = 90;
  }
  else
  {
    p_gen->island       = island_count > 2 ? 0 : 20;;
    p_gen->close_left   = 50 - p_gen->island / 2;
    p_gen->close_right  = 80;
    p_gen->open_left    = 85;
    p_gen->open_right   = 90;
  }
}

void move_map_step(map_t *map, options_t *options)
{
  int y;
  for(y = WINDOW_LENGTH - 1; y > 0; y--)
    strncpy(map->grid[y], map->grid[y-1], WINDOW_WIDTH);

  generate_map_line(map->grid[0], map->grid[1], options);
}

void clear_map(map_t *map)
{
  int x,y;
  for(y = 0; y < WINDOW_LENGTH; y++)
    for(x = 0; x < WINDOW_WIDTH; x++)
    {
      if(x == 0 || x == WINDOW_WIDTH - 1)
        map->grid[y][x] = MAP_BLOCK;
      else
        map->grid[y][x] = MAP_WATER;
    }
}

//***** PLAYER *****//

void fire_weapon(ship_t *player, list_t *bullets)
{
  if(!player->weapon->curr_reload)
  {
    player->weapon->curr_reload = player->weapon->reload_time;
    list_append(bullets, new_bullet(player));
  }
}

void move_player(ship_t *player, list_t* bullet_list)
{
  if(player->weapon->curr_reload) player->weapon->curr_reload--;
#ifdef GALILEO
  int fd = player->button_file;
  char s;
  lseek(fd,0,SEEK_SET);
  read(fd,&s,sizeof s);
  if(s == '1') fire_weapon(player, bullet_list);

  int fd2 = player->control_file;
  char data_str[80];
  lseek(fd2,0,SEEK_SET);
  read(fd2,data_str,sizeof data_str);
  float pos = atoi(data_str) * player->scale;
  player->x_pos = (WINDOW_WIDTH - 2) * pos / MAX_VOLTAGE + 1;
  printf("%f %d %d",pos, MAX_VOLTAGE, player->x_pos);
  //exit(0);
#else
  char key = 0;
  key = get_key();
  switch (key) {
    case KEY_SPACE:
      fire_weapon(player->weapon, bullet_list);
     break;
    case KEY_ARROW:
      get_key(); //skip this one ([)
      key = get_key();
      if(key == KEY_LEFT)
        player->x_pos--;
      else if(key == KEY_RIGHT)
        player->x_pos++;
      break;
  }
#endif
}

int check_player_collision(map_t *map, ship_t *player, list_t *enemies)
{
  switch (map->grid[player->y_pos][player->x_pos]) {
    case MAP_BLOCK: return COLLISION;
  }

  list_node_t *curr = enemies->head;
  while(curr)
  {
    enemy_t *e = curr->data;
    if(e->x_pos == player->x_pos && e->y_pos == player->y_pos)
      return COLLISION;
    curr = curr->next;
  }
  return NO_COLLISION;
}

void restart_match(map_t *map, list_t *bullets, list_t *enemies)
{
  free(map->grid); free(map->draw_grid); free(map);
  list_destroy(bullets); list_destroy(enemies);
}

int check_defeat(map_t *map, ship_t *player, int score)
{
  player->hp--;
  if(player->hp > 0)
  {

    return 0;
  }
  else
  {
    show_defeat(score);
    return 1;
  }
}

//***** BULLETS ******//

bool move_bullet(void *args)
{
  iter_args_t *iter_arg = (iter_args_t *) args;
  bullet_t *bullet = (bullet_t *) iter_arg->data;
  move_args_t *move_args = (move_args_t *) iter_arg->args;
  map_t *map = (map_t *) move_args->map;
  list_t *enemy_list = (list_t *) move_args->enemy_list;

  switch (map->grid[bullet->y_pos][bullet->x_pos]) {
    case MAP_BLOCK: return FALSE;
    case MAP_WATER: break;
  }

  if((--bullet->move_delay) < 1)
  {
    switch (bullet->type) {
      case WEAPON_DEFAULT:
        if(bullet->y_pos == 0)
          return FALSE;
        else
        {
          bullet->y_pos--;
          bullet->move_delay = BULLET_SPEED_DEFAULT;
        }
        break;
    }
  }

  list_node_t *curr = enemy_list->head;
  while(curr)
  {
    enemy_t *e = curr->data;
    if(bullet->y_pos == e->y_pos && bullet->x_pos == e->x_pos)
    {
      remove_node(enemy_list, curr);
      return FALSE;
    }
    curr = curr->next;
  }

  return TRUE;
}

bool bullet_collision(void *args)
{
  iter_args_t *iter_args = (iter_args_t *) args;
  enemy_t *enemy = (enemy_t *) iter_args->data;
  bullet_t *bullet = (bullet_t *) iter_args->args;

  if(bullet->x_pos == enemy->x_pos && bullet->y_pos == enemy->y_pos)
  {
    return FALSE;
  }
  else
    return TRUE;
}

bool move_enemy(void *e)
{
  enemy_t *enemy = (enemy_t *) e;
  enemy->y_pos++;
  if(enemy->y_pos >= WINDOW_LENGTH)
    return FALSE;
  else
    return TRUE;
}

void generate_enemies(list_t *enemy_list, options_t *options, map_t *map)
{
  int max_enemies = 0;
  switch (options->difficulty) {
    case EASY:    max_enemies = 1; break;
    case NORMAL:  max_enemies = 3; break;
    case HARD:    max_enemies = 5; break;
    case LUNATIC: max_enemies = 10; break;
  }
  int enemies = rand() % max_enemies;
  int i, j;
  int positions[enemies];
  for(i = 0; i < enemies; i++)
  {
    enemy_t *e = new_enemy();
    e->y_pos = 0;
    int position = 1 + rand() % (WINDOW_WIDTH - 2);
    bool valid_position = TRUE;
    for(j = 0; j < i; j++)
      if(positions[j] == position) valid_position = FALSE;

    if(map->grid[e->y_pos][position] != MAP_WATER
        || map->grid[e->y_pos][position - 1] != MAP_WATER
        || map->grid[e->y_pos][position + 1] != MAP_WATER)
      valid_position = FALSE;

    if(valid_position)
    {
      e->x_pos = position;
      positions[i] = position;
      list_append(enemy_list, e);
    }
  }

}

int main(int argc, char* argv[])
{
  srand(time(NULL));
  //init_interface();

  int menu_option = 0;
  options_t *game_options = new_options();
  do {
    menu_option = show_menu();
    switch (menu_option) {
      case MENU_START:    start_game(game_options); break;
      case MENU_OPTIONS:  show_options(game_options); break;
      case MENU_EXIT:     break;
    }
  } while(menu_option != MENU_EXIT);

  reset_interface();
  return 0;
}
