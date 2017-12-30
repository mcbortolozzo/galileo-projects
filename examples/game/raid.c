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

int start_game(options_t *game_options)
{
  ship_t *player = new_ship(game_options);
  map_t *map = new_map();
  while(1)
  {
    draw_map(map);
    usleep(250000);
    move_map_step(map);
  }
}

//**** OBJECT INITIZALIZATION ****//

ship_t *new_ship(options_t* game_options)
{
  ship_t *ship = calloc(1, sizeof(ship_t));
  ship->x_pos = DEFAULT_X_POS;
  ship->y_pos = DEFAULT_Y_POS;
  ship->hp = STARTING_HP;
  return ship;
}

bullet_t *new_bullet(ship_t *player_ship)
{
  bullet_t *bullet = calloc(1, sizeof(bullet_t));
  bullet->x_pos = player_ship->x_pos;
  bullet->y_pos = player_ship->y_pos - 1;
  return bullet;
}

enemy_t *new_enemy()
{
  enemy_t *enemy = calloc(1, sizeof(enemy_t));

  return enemy;
}

map_t *new_map()
{
  int i, j;
  map_t *map = calloc(1, sizeof(map_t));
  map->grid = calloc(WINDOW_LENGTH, sizeof(char*));

  for(i = 0; i < WINDOW_LENGTH; i++)
  {
    map->grid[i] = calloc(WINDOW_WIDTH, sizeof(char));
    for(j= 0; j < WINDOW_WIDTH; j++)
    {
      if(j == 0 || j == WINDOW_WIDTH - 1)
        map->grid[i][j] = MAP_BLOCK;
      else
        map->grid[i][j] = MAP_WATER;
    }
  }

  return map;
}

#define MIN_PASSAGE_WIDTH 8

void generate_map_line(char* next_line, char* prev_line)
{
  int x_pos = 0;
  int counting = 0;
  int passage_begin = -1;
  prob_gen_t p_gen;
  get_probability_mode(prev_line, &p_gen);
  strncpy(next_line, prev_line, WINDOW_WIDTH);
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

      if(r < p_gen.island && passage_width > 2*MIN_PASSAGE_WIDTH + 1) // island
      {
        int pos = rand() % (passage_width - 2*MIN_PASSAGE_WIDTH);
        next_line[passage_begin + pos + MIN_PASSAGE_WIDTH] = MAP_BLOCK;
      }
      else if(r < p_gen.close_left && passage_width > MIN_PASSAGE_WIDTH + 1) //inc left
      {
        next_line[passage_begin + 1] = MAP_BLOCK;
      }
      else if(r < p_gen.close_right && passage_width > MIN_PASSAGE_WIDTH + 1) // inc right
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

void move_map_step(map_t *map)
{
  int y;
  for(y = WINDOW_LENGTH - 1; y > 0; y--)
    strncpy(map->grid[y], map->grid[y-1], WINDOW_WIDTH);

  generate_map_line(map->grid[0], map->grid[1]);
}

//****  END OBJECT INITIZALIZATION ****//

int main(int argc, char* argv[])
{
  srand(time(NULL));
  init_interface();

  int menu_option = 0;
  options_t *game_options; //TODO default options
  do {
    menu_option = show_menu();
    switch (menu_option) {
      case MENU_START:    start_game(game_options); break;
      case MENU_OPTIONS:  show_options(game_options); break;
      case MENU_EXIT:     break;
    }
  } while(menu_option != MENU_EXIT);

  return 0;
}
