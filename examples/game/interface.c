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

const char title[]    = "| RIVER RAID |";
const char start[]    = "START GAME";
const char options[]  = "OPTIONS";
const char exit_game[]= "EXIT GAME";

void init_interface()
{
  clear();
  cursor_disable();
}

//***** MENU *****//

int show_menu()
{
  int selected_option = MENU_START;
  char key;
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
  return 0;
}

void print_menu(int selected_option)
{
  clear();
  print_menu_title();
  print_menu_option(start, 10, selected_option == MENU_START);
  print_menu_option(options, 15, selected_option == MENU_OPTIONS);
  print_menu_option(exit_game, 20, selected_option == MENU_EXIT);
}

void print_menu_title()
{
  int i;
  char frame[80];
  frame[0] = 0;
  for(i = 0; i < strlen(title); i++)
    sprintf(frame, "%s-", frame);

  print_center_x(frame, 4);
  print_center_x(title, 5);
  print_center_x(frame, 6);
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

void show_options(options_t *game_options)
{
  //TODO
}

//****** MAP ******//

void draw_map(map_t *map)
{
  int x, y;
  for(y = 0; y < WINDOW_LENGTH; y++)
    for(x = 0; x < WINDOW_WIDTH; x++)
    {
      print_char_at(map->grid[y][x], x+1, y+1);
    }
}


//***** MISC ******//
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
