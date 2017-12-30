#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_new(int element_size, free_func_t free_func)
{
    list_t *list = calloc(1, sizeof(list_t));
    list->element_size = element_size;
    list->free_func = free_func;
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void list_destroy(list_t *list)
{
  list_node_t *next, *curr = list->head;
  while(curr)
  {
    next = curr->next;
    list->free_func(curr->data);
    free(curr->data);
    free(curr);
    curr = next;
  }

  list->head = NULL;
  list->tail = NULL;
}

list_node_t *create_node(list_t *list, void *element)
{
  list_node_t *node = calloc(1, sizeof(list_node_t));
  node->data = calloc(1, list->element_size);
  memcpy(node->data, element, list->element_size);
  return node;
}

void list_prepend(list_t *list, void *element)
{
  list_node_t *node = create_node(list, element);
  node->prev = NULL;
  node->next = list->head;
  list->head = node;

  if(!list->tail)
    list->tail = node;
  else
  {
    node->next->prev = node;
  }
  list->length++;
}
void list_append(list_t *list, void *element)
{
  list_node_t *node = create_node(list, element);
  node->prev = list->tail;
  node->next = NULL;

  if(list->tail)
  {
    list->tail->next = node;
    list->tail = node;
  }
  else
  {
    list->head = node;
    list->tail = node;
  }

  list->length++;
}

int list_size(list_t *list)
{
  return list->length;
}

void list_for_each(list_t *list, list_iterator_t iterator, void *args)
{
  list_node_t *curr = list->head;
  bool result = TRUE;
  while(curr)
  {
    if(args)
    {
      iter_args_t iter_arg = {curr->data, args};
      result = iterator(&iter_arg);
    }
    else
      result = iterator(curr->data);
    if(!result) remove_node(list, curr);
    curr = curr->next;
  }
}

void remove_node(list_t *list, list_node_t *node)
{
  list->length--;
  if(node == list->head && node->next)
  {
    list->head = node->next;
    list->head->prev = NULL;
  }
  else if(node == list->tail && node->prev)
  {
    list->tail = node->prev;
    list->tail->next = NULL;
  }
  else if(node == list->head && node == list->head)
  {
    list->head = NULL;
    list->tail = NULL;
  }
  else
  {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
}
