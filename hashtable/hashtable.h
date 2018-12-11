#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
const int OK = 123451;
const int OK2 = 223597;
const int CHECK = 2;
const int hash1 = 132145;
const int hash2 = 23125;
const int hash3 = 9881;
typedef struct node {
  int canary1;
  int canary2;
  int checksum;
  long long  int val;
  char* name;
  struct node* prev;
  struct node* next;
}node;
typedef struct list {
  node* head;
  node* tail;
  int num;
  int checksumh;
  int checksumt;
  long long int hashsum;
  int canary1;
}list;
void CheckNode(node* node_);
void CheckList(list* list_);
list* ListConstr();
node* NodeConstruct();
node* PushHead(list* list_, long long int val_);
node* PushTail(list* list_, long long int val_);
node* FindNode(list* list_, int num_);
node* Replace(list* list_, int num_, long long int val_);
node* Insert(list* list_, int num_, long long int val_, int state);
node* PopHead(list* list_);
node* PopTail(list* list_);
node* Delete(int num_, list* list_);
void Erase(list* list_);
void PrintList(list* list_);
void ListDestruct(list* list_);
long long int hash(long long int number);
list** FillList(list** table, FILE* f, int* n);
int Printer(list** table, int n);
node* Finder(list** table, int n);
int collisioncount(list** table, int n);
list** FillTable(list** table, FILE* file, int* n);
int FindList(list** table, long long int number, int n);
#include "list.c"
#include "hashtable.c"
