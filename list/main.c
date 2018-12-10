#include <stdio.h>
#include "list.h"
int main() {
  list* list_ = (struct list*) calloc (1, sizeof(list));
  // list* list_;
  ListConstr(list_);
  PushHead(list_, 9);
  PushHead(list_, 7);
  PushHead(list_, 5);
  PushHead(list_, 3);
  PrintList(list_);
  printf("\n");
  Replace(list_, 4, 1);
  PrintList(list_);
  printf("\n");
  PopHead(list_);
  PrintList(list_);
  printf("\n");
  PopTail(list_);
  PrintList(list_);
  printf("\n");
  Erase(list_);
  PushHead(list_, 3);
  PrintList(list_);
  PopTail(list_);
  // PopTail(list_);
  // printf("%d\n", list_ -> head -> val);
  ListDestruct(list_);
  // PrintList(list_);
  return 1;
}
