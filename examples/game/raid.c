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

int start_game(options_t *game_options)
{
  ship_t player = new_ship(game_options);
}

//**** OBJECT INITIZALIZATION ****//

ship_t *new_ship(options_t* game_options)
{
  ship_t *new_ship = calloc(1, sizeof(ship_t));
  new_ship->x_pos = DEFAULT_X_POS;
  new_ship->y_pos = DEFAULT_Y_POS;
  new_ship->hp = STARTING_HP;
  return new_ship;
}

bullet_t *new_bullet(ship_t *player_ship)
{
  bullet_t *new_bullet = calloc(1, sizeof(bullet_t));
  new_bullet->x_pos = player_ship->x_pos;
  new_bullet->y_pos = player_ship->y_pos - 1;
  return new_bullet;
}

enemy_t *new_enemy()
{
  enemy_t *new_enemy = calloc(1, sizeof(enemy_t));

  return new_enemy;
}

//****  END OBJECT INITIZALIZATION ****//

int main(int argc, char* argv[])
{
  int menu_option = 0;
  options_t game_options; //TODO default options
  do {
    menu_option = show_menu()
    switch (menu_option) {
      case MENU_START:    start_game(); break;
      case MENU_OPTIONS:  show_options(game_options); break;
      case MENU_EXIT:     break;
    }
  } while(selected_option != MENU_EXIT);
}
