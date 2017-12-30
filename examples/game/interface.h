/*
  interface.h: Text Interface elements

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

#ifndef INTERFACE_H
#define INTERFACE_H

#include "raid.h"

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define cursor_disable() fputs("\e[?25l", stdout);
#define cursor_enable() fputs("\e[?25h", stdout);

#define MENU_START    10
#define MENU_OPTIONS  11
#define MENU_EXIT     12

#define WINDOW_WIDTH  60
#define WINDOW_LENGTH 43

#define KEY_ENTER     10
#define KEY_ARROW     27
#define KEY_UP        65
#define KEY_DOWN      66

void init_interface();

/**
 * Enters the menu Interface
 * @return selected option from the menu
 */
int show_menu();
void print_menu(int selected_option);
void print_menu_option(const char *str, int y_pos, int is_selected);
void print_menu_title();
int prev_menu(int selected_option);
int next_menu(int selected_option);

void draw_map(map_t *map);

/**
 * Shows Game options
 */
void show_options(options_t *game_options);

void print_center_x(const char *str, int y_pos);
void print_at(const char *str, int x_pos, int y_pos);
void print_char_at(const char c, int x_pos, int y_pos);

void set_stdin_echo(int enable);
int get_key();


#endif
