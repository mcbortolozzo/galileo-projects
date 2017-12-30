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

#include "list.h"

#define DEFAULT_X_POS 30
#define DEFAULT_Y_POS 22

#define MAP_BLOCK     'T'
#define MAP_WATER     ' '

#define COLLISION     10
#define NO_COLLISION  11

typedef struct weapon
{
  int type;
  int reload_time;
  int curr_reload;
} weapon_t;

typedef struct ship
{
  int hp;
  int x_pos;
  int y_pos;
  weapon_t *weapon;
} ship_t;

#define WEAPON_DEFAULT  30

#define RELOAD_DEFAULT  50

typedef struct map
{
  char **grid;
  char **draw_grid;
} map_t;

#define BULLET_SPEED_DEFAULT 10

typedef struct bullet
{
  int x_pos;
  int y_pos;
  int type;
  int move_delay;
} bullet_t;

typedef struct move_args
{
  map_t *map;
  list_t* enemy_list;
} move_args_t;

typedef struct enemy
{
  int hp;
  int x_pos;
  int y_pos;
  int type;
} enemy_t;

#define EASY        25
#define NORMAL      26
#define HARD        27
#define LUNATIC     28

#define DEFAULT_DIFFICULTY NORMAL

#define EASY_HP     5
#define NORMAL_HP   4
#define HARD_HP     3
#define LUNATIC_HP  1

#define EASY_WIDTH    15
#define NORMAL_WIDTH  10
#define HARD_WIDTH    6
#define LUNATIC_WIDTH 2

#define EASY_SPEED    70;
#define NORMAL_SPEED  50;
#define HARD_SPEED    30;
#define LUNATIC_SPEED 10;

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
weapon_t *new_weapon();
bullet_t *new_bullet(ship_t *player_ship);
enemy_t *new_enemy(); //TODO include stuff to configure this
map_t *new_map();
options_t* new_options();

void generate_map_line(char *next_line, char* prev_line, options_t *options);
void get_probability_mode(char *prev_line, prob_gen_t* p_gen);
void move_map_step(map_t *map, options_t *options);
int get_passage_width(options_t* options);
int get_map_speed(options_t *game_options);
void clear_map(map_t *map);

void move_player(ship_t *player, list_t *bullet_list);
int check_player_collision(map_t *map, ship_t *player, list_t *enemies);
int check_defeat(map_t *map, ship_t *player, int score);
void restart_match(map_t *map, list_t *bullets, list_t *enemies);

bool move_bullet(void *args);
bool bullet_collision(void *args);
bool move_enemy(void *e);
void generate_enemies(list_t *enemy_list, options_t *options, map_t *map);

#endif
