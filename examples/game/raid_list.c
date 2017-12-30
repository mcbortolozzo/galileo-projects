#include <stdlib.h>

#include "raid_list.h"
#include "raid.h"

void free_bullet(void * bullet)
{
  bullet_t *b = (bullet_t*) bullet;
  //free(b);
}

list_t *new_bullet_list()
{
  list_t *list = list_new(sizeof(bullet_t), free_bullet);
  return list;
}

void free_enemy(void *enemy)
{
  enemy_t *e = (enemy_t *) enemy;
  //free(e);
}

list_t *new_enemy_list()
{
  list_t *list = list_new(sizeof(enemy_t), free_enemy);
  return list;
}
