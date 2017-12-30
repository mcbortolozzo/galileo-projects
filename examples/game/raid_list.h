
#ifndef RAID_LIST_H
#define RAID_LIST_H

#include <list.h>

list_t *new_bullet_list();
void free_bullet(void *bullet);

list_t *new_enemy_list();
void free_enemy(void *bullet);

#endif
