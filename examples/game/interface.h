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

#define MENU_START    10
#define MENU_EXIT     11
#define MENU_OPTIONS  12

/**
 * Enters the menu Interface
 * @return selected option from the menu
 */
int show_menu();

/**
 * Shows Game options
 */
void show_options(options_t *game_options);

void print

#endif
