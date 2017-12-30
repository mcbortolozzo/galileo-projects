/*
  raid.h: River Raid, using galileo as controller inputs

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

#ifndef RAID_H
#define RAID_H

#define DEFAULT_X_POS 40
#define DEFAULT_Y_POS 20
#define STARTING_HP   5 //TODO different hp according to difficulty

#define MAP_BLOCK     'T'
#define MAP_WATER     ' '

typedef struct ship
{
  int hp;
  int x_pos;
  int y_pos;
} ship_t;

typedef struct map
{
  char **grid;
} map_t;

typedef struct bullet
{
  int x_pos;
  int y_pos;
} bullet_t;

typedef struct enemy
{
  int hp;
  int x_pos;
  int y_pos;
  int type;
} enemy_t;

typedef struct options
{
  int difficulty;
} options_t;

typedef struct prob_gen
{
  int island;
  int close_left;
  int close_right;
  int open_left;
  int open_right;
} prob_gen_t;

int start_game(options_t *game_options);

// Object Initialization
ship_t *new_ship(options_t* game_options);
bullet_t *new_bullet(ship_t *player_ship);
enemy_t *new_enemy(); //TODO include stuff to configure this
map_t *new_map();
void generate_map_line(char *next_line, char* prev_line);
void get_probability_mode(char *prev_line, prob_gen_t* p_gen);
void move_map_step(map_t *map);

#endif
