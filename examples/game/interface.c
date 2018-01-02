/*
  interface.c: Text Interface elements

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
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "interface.h"

#ifdef GALILEO
#include <fcntl.h>
#include <unistd.h>
#include <galileo2io.h>
#include <errno.h>
#endif

const char title[]    = "RIVER RAID";
const char start[]    = "START GAME";
const char options_text[]  = "OPTIONS";
const char exit_game[]= "EXIT GAME";
const char defeat[]   = "GAME OVER";
const char difficulty[] = "Difficulty";
const char confirm[]  = "Confirm";

void init_interface()
{
  /*clear();
  cursor_disable();
  set_stdin_echo(0);*/
}

void reset_interface()
{
  clear();
  cursor_enable();
  set_stdin_echo(1);
}

//***** MENU *****//

int show_menu()
{
  int selected_option = MENU_START;

#ifdef GALILEO
  int fd;
  if((fd=open("/sys/class/gpio/gpio6/value",O_RDONLY)) < 0)
  {
    printf("%d\n", errno);
    printf("Opening /sys/class/gpio/gpio6/value");
    exit(-1);
  }
  while(1)
  {
    print_menu(selected_option);
    usleep(1000);
    char s;
    lseek(fd,0,SEEK_SET);
    read(fd,&s,sizeof s);
    if(s == '1') return MENU_START;

    /*int fd2 = player->control_file;
    char data_str[80];
    lseek(fd2,0,SEEK_SET);
    read(fd2,data_str,sizeof data_str);
    int pos = atoi(data_str) * player->scale;
    player->x_pos = (WINDOW_WIDTH - 2) * pos / MAX_VOLTAGE;*/
  }
  close(fd);
#else
  char key = 0;
  get_key();
  do {
    print_menu(selected_option);
    key = get_key();
    switch (key) {
      case KEY_ENTER: return selected_option;
      case KEY_ARROW:
        get_key(); //skip this one ([)
        key = get_key();
        if(key == KEY_UP)
          selected_option = prev_menu(selected_option);
        else if(key == KEY_DOWN)
          selected_option = next_menu(selected_option);
        break;
      default: if(key != -1) printf("%d", key);
    }
  } while(key != 10);
#endif
  return 0;
}

void print_menu(int selected_option)
{
  clear();
  print_frame(title, 5);
  print_menu_option(start, 10, selected_option == MENU_START);
  print_menu_option(options_text, 15, selected_option == MENU_OPTIONS);
  print_menu_option(exit_game, 20, selected_option == MENU_EXIT);
}

void print_menu_option(const char *str, int y_pos, int is_selected)
{
  char option[30];
  if(is_selected)
    sprintf(option, "->%s<-", str);
  else
    sprintf(option, "%s", str);

  print_center_x(option, y_pos);
}

int next_menu(int selected_option)
{
  if(selected_option == MENU_EXIT)
    return MENU_START;
  else
    return selected_option + 1;
}

int prev_menu(int selected_option)
{
  if(selected_option == MENU_START)
    return MENU_EXIT;
  else
    return selected_option - 1;
}

//****** OPTIONS ******//

void show_options(options_t *game_options)
{
  int selected_option = MENU_DIFFICULTY;
  char key = 0;
  get_key();
  do {
    print_options(selected_option, game_options);
    key = get_key();
    switch (key) {
      case KEY_ENTER: if(selected_option == MENU_CONFIRM) return;
      case KEY_ARROW:
        get_key(); //skip this one ([)
        key = get_key();
        switch (key) {
          case KEY_UP:    selected_option = prev_option(selected_option); break;
          case KEY_DOWN:  selected_option = next_option(selected_option); break;
          case KEY_LEFT:  left_option(selected_option, game_options); break;
          case KEY_RIGHT: right_option(selected_option, game_options); break;
        }
        break;
      default: if(key != -1) printf("%d", key);
    }
  } while(1);
}

void print_options(int selected_option, options_t *options)
{
    char opt_str[80];
    clear();
    print_frame(options_text, 5);
    print_menu_option(difficulty, 10, selected_option == MENU_DIFFICULTY);
    get_difficulty_options(opt_str, options);
    print_center_x(opt_str, 15);
    print_menu_option(confirm, 20, selected_option == MENU_CONFIRM);
}

void get_difficulty_options(char *str, options_t *options)
{
  str[0] = 0;
  sprintf(str, "              "); // Padding to compensate special codes
  print_option_value(str, "EASY", options->difficulty == EASY);
  print_option_value(str, "NORMAL", options->difficulty == NORMAL);
  print_option_value(str, "HARD", options->difficulty == HARD);
  print_option_value(str, "LUNATIC", options->difficulty == LUNATIC);
}

void print_option_value(char *str, char* option, int is_selected)
{
  if(is_selected)
    sprintf(str, "%s" SEL_OPTION " %s " RESET, str, option);
  else
    sprintf(str, "%s %s ", str, option);
}


int prev_option(int selected_option)
{
  if(selected_option == MENU_DIFFICULTY)
    return MENU_CONFIRM;
  else
    return selected_option - 1;
}

int next_option(int selected_option)
{
  if(selected_option == MENU_CONFIRM)
    return MENU_DIFFICULTY;
  else
    return selected_option + 1;
}

void left_option(int selected_option, options_t *options)
{
  switch (selected_option) {
    case MENU_DIFFICULTY:
      if(options->difficulty == EASY)
        options->difficulty = LUNATIC;
      else
        options->difficulty--;
  }
}
void right_option(int selected_option, options_t *options)
{
  switch (selected_option) {
    case MENU_DIFFICULTY:
      if(options->difficulty == LUNATIC)
        options->difficulty = EASY;
      else
        options->difficulty++;
  }
}

//****** MAP ******//

void draw_map(map_t *map, ship_t *player, list_t *bullets, list_t* enemies)
{
  int x, y;
  gen_draw_map(map, player, bullets, enemies);
  for(y = 0; y < WINDOW_LENGTH; y++)
    for(x = 0; x < WINDOW_WIDTH; x++)
    {
      switch (map->draw_grid[y][x]) {
        case MAP_BLOCK:     printf(BLOCK_COLOR); break;
        case MAP_WATER:     printf(WATER_COLOR); break;
        case SHIP_SYMBOL:   printf(SHIP_COLOR); break;
        case BULLET_SYMBOL: printf(BULLET_COLOR); break;
        case ENEMY_SYMBOL:  printf(ENEMY_COLOR); break;
      }
      print_char_at(map->draw_grid[y][x], x+1, y+1);
      printf(RESET);
    }
}

void gen_draw_map(map_t *map, ship_t *player, list_t *bullets, list_t* enemies)
{
  int y;
  for(y = 0; y < WINDOW_LENGTH; y++)
    strncpy(map->draw_grid[y], map->grid[y], WINDOW_WIDTH);

  list_node_t *curr = bullets->head;
  while (curr)
  {
    bullet_t *b = (bullet_t *) curr->data;
    map->draw_grid[b->y_pos][b->x_pos] = BULLET_SYMBOL;
    curr = curr->next;
  }

  curr = enemies->head;
  while(curr)
  {
    enemy_t *e = (enemy_t *) curr->data;
    map->draw_grid[e->y_pos][e->x_pos] = ENEMY_SYMBOL;
    curr = curr->next;
  }
  map->draw_grid[player->y_pos][player->x_pos] = SHIP_SYMBOL;
}


void show_defeat(int score)
{
  char str[80];
  clear();
  print_frame(defeat, 5);
  sprintf(str, "Your Score: %d", score);
  print_center_x(str, 10);

  print_center_x("Press Any Key To Continue", 20);
  wait_key();
}

void show_continue(int lives)
{
  clear();
  print_frame("YOUR SHIP EXPLODED", 5);
  char str[80];
  sprintf(str, "Remaining Lives: %d", lives);
  print_center_x(str, 10);
  print_center_x("Press Any Key To Continue", 20);
  wait_key();
}

//***** MISC ******//

void print_frame(const char *str, int y_pos)
{
  int i;
  char text[80];
  sprintf(text, "| %s |", str);

  char frame[80];
  frame[0] = 0;
  for(i = 0; i < strlen(text); i++)
    sprintf(frame, "%s-", frame);

  print_center_x(frame, y_pos - 1);
  print_center_x(text, y_pos);
  print_center_x(frame, y_pos + 1);
}

void print_center_x(const char *str, int y_pos)
{
  int len = strlen(str);
  print_at(str, (WINDOW_WIDTH - len)/2, y_pos);
}

void print_at(const char *str, int x_pos, int y_pos)
{
  gotoxy(x_pos, y_pos);
  printf("%s", str);
}

void print_char_at(const char c, int x_pos, int y_pos)
{
  gotoxy(x_pos, y_pos);
  printf("%c", c);
}

void set_stdin_echo(int enable)
{
  struct termios tty;
  tcgetattr(STDIN_FILENO, &tty);
  if( !enable )
      tty.c_lflag &= ~ECHO;
  else
      tty.c_lflag |= ECHO;

  (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int get_key()
{
  int c;
  struct termios orig_term_attr;
  struct termios new_term_attr;

  tcgetattr(fileno(stdin), &orig_term_attr);
  memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
  new_term_attr.c_lflag &= ~(ECHO|ICANON);
  new_term_attr.c_cc[VTIME] = 0;
  new_term_attr.c_cc[VMIN] = 0;
  tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);

  c = fgetc(stdin);

  tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

  return c;
}

void wait_key()
{
#ifdef GALILEO
int fd;
if((fd=open("/sys/class/gpio/gpio6/value",O_RDONLY)) < 0)
{
  printf("%d\n", errno);
  printf("Opening /sys/class/gpio/gpio6/value");
  exit(-1);
}
while(1)
{
  char s;
  lseek(fd,0,SEEK_SET);
  read(fd,&s,sizeof s);
  if(s == '1') return;
}
#else
  int key;
  do {
    key = get_key();
  } while(key == -1);
#endif
}
