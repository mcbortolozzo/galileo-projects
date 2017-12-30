#ifndef __LIST_H
#define __LIST_H

typedef void (*free_func_t)(void *);

typedef enum { FALSE, TRUE } bool;

typedef bool (*list_iterator_t)(void *);

typedef struct list_node {
  void *data;
  struct list_node *next;
  struct list_node *prev;
} list_node_t;

typedef struct list{
  int length;
  int element_size;
  list_node_t *head;
  list_node_t *tail;
  free_func_t free_func;
} list_t;

typedef struct iter_args {
  void *data;
  void *args;
} iter_args_t;

list_t *list_new(int element_size, free_func_t free_func);
void list_destroy(list_t *list);

void list_prepend(list_t *list, void *element);
void list_append(list_t *list, void *element);
int list_size(list_t *list);

void list_for_each(list_t *list, list_iterator_t iterator, void *args);
void remove_node(list_t *list, list_node_t *node);

#endif
