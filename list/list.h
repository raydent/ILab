#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
const int OK = 123451;
const int OK2 = 223597;
const int CHECK = 2;
typedef struct node {
  int canary1;
  int canary2;
  int checksum;
  int val;
  struct node* prev;
  struct node* next;
}node;
typedef struct list {
  node* head;
  node* tail;
  int num;
  int checksumh;
  int checksumt;
  int canary1;
}list;
void CheckNode(node* node_);
void CheckList(list* list_);
list* ListConstr(list* list_);
node* NodeConstruct();
node* PushHead(list* list_, int val_);
node* PushTail(list* list_, int val_);
node* FindNode(list* list_, int num_);
node* Replace(list* list_, int num_, int val_);
node* Insert(list* list_, int num_, int val_, int state);
node* PopHead(list* list_);
node* PopTail(list* list_);
node* Delete(int num_, list* list_);
void Erase(list* list_);
void PrintList(list* list_);
void ListDestruct(list* list_);
#include "list.c"
