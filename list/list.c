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
}list;
node* NodeConstruct();
list* ListConstr(list* list_);
void ListDestruct(list* list_);
node* PushHead(list* list_, int val_);
node* PushTail(list* list_, int val_);
node* Replace(node* node_, int val_);
node* Insert(node* node_, int val_, int state);
node* PopHead(list* list_);
node* PopTail(list* list_);
node* Delete(node* node_, list* list_);
node* FindNode(list* list_, int num_);
void Erase();
void PrintList(list* list_);
void CheckNode(node* node_);
int main() {
  list* list_ = (struct list*) calloc (1, sizeof(list));
  // list* list_;
  list_ = ListConstr(list_);
  PushHead(list_, 9);
  PushHead(list_, 7);
  PushHead(list_, 5);
  PushHead(list_, 3);
  PrintList(list_);
  printf("\n");
  Replace(FindNode(list_, 2), 1);
  PrintList(list_);
  printf("\n");
  PopHead(list_);
  PrintList(list_);
  printf("\n");
  PopTail(list_);
  PrintList(list_);
  printf("\n");
  // printf("%d\n", list_ -> head -> val);
  free(list_);
  return 1;
}

list* ListConstr(list* list_) {
  list_ -> head = NULL;
  list_ -> tail = NULL;
  list_ -> num = 0;
  return list_;
}
node* NodeConstruct() {
  node* node_ = (struct node*) calloc(1, sizeof(node));
  node_ -> prev = NULL;
  node_ -> next = NULL;
  node_ -> canary1 = OK;
  node_ -> canary2 = OK2;
  return node_;
}
node* PushHead(list* list_, int val_) {
  node* node_ = NodeConstruct();
  node_ -> val = val_;
  node_ -> checksum = val_ * CHECK;
  if (list_ -> num == 0) {
    list_ -> head = node_;
    list_ -> tail = node_;
    list_ -> num = 1;
  }
  else {
    list_ -> num += 1;
    node_ -> next = list_ -> head;
    list_ -> head = node_;
    node_ -> next -> prev = node_;
    node_ -> prev = NULL;
  }
  return node_;
}
node* PushTail(list* list_, int val_) {
  node* node_ = NodeConstruct();
  node_ -> val = val_;
  node_ -> checksum = val_ * CHECK;
  if (list_ -> num == 0) {
    list_ -> head = node_;
    list_ -> tail = node_;
    (list_ -> num) = 1;
  }
  else {
    (list_ -> num) += 1;
    node_ -> prev = list_ -> tail;
    list_ -> tail = node_;
    node_ -> prev -> next = node_;
    node_ -> next = NULL;
  }
  return node_;
}
node* FindNode(list* list_, int num_) {
  if (num_ < 1){
    printf("WRONG NUMBER");
    exit(0);
  }
  if (num_ > list_ -> num){
    printf("WRONG NUMBER");
    exit(0);
  }
  if (num_ == 1) {
    return list_->head;
  }
  if (num_ == list_->num) {
    return list_->tail;
  }
  if (num_ > (list_ -> num / 2)){
    CheckNode(list_ -> tail);
    node* node1 = list_ -> tail;
    for (int i = 1; i < (list_ -> num - num_ + 1); i++){
      node1 = node1 -> prev;
    }
    return node1;
  }
  else{
    CheckNode(list_ -> head);
    node* node2 = list_ -> head;
    for (int i = 1; i < num_; i++){
      node2 = node2 -> next;
    }
    return node2;
  }
}
node* Replace(node* node_, int val_) {
  CheckNode(node_);
  node_ -> val = val_;
};
node* Insert(node* node_, int val_, int state) {// state = -1 - сзади, 1 - спереди
  CheckNode(node_);
  struct node* node1 = NodeConstruct();
  node1 -> checksum = val_ * CHECK;
  if (state == -1) {
    node1 -> prev = node_ -> prev;
    node_ -> prev -> next = node1;
    node_ -> prev = node1;
    node1 -> next = node_;
  }
  if (state == 1) {
    node1 -> next = node_ -> prev;
    node_ -> next -> prev = node1;
    node_ -> next = node1;
    node1 -> prev = node_;
  }
  else {
    printf("WRONG STATE");
    exit(0);
  }
}
node* PopHead(list* list_){
  CheckNode(list_ -> head);
  list_ -> head = list_ -> head -> next;
  free(list_ -> head -> prev);
  list_ -> head -> prev = NULL;
  list_ -> num -= 1;
}
node* PopTail(list* list_){
  CheckNode(list_ -> tail);
  list_ -> tail = list_ -> tail -> prev;
  free(list_ -> tail -> next);
  list_ -> tail -> next = NULL;
  list_ -> num -= 1;
}
node* Delete(node* node_, list* list_){
  CheckNode(node_);
  node_ -> next -> prev = node_ -> prev;
  node_ -> prev -> next = node_ -> next;
  // free(node_);
  list_ -> num -= 1;
}
void Erase(list* list_){
  if (list_ -> num != 0){
    PopHead(list_);
    Erase(list_);
  }
}
void PrintList(list* list_){
  node* node_ = list_ -> head;
  for (int i = 1; i <= list_ -> num; i++){
    printf("%d\n", node_ -> val);
    node_ = node_ -> next;
  }
}
void CheckNode(node* node_){
  if (node_ -> canary1 != OK){
    printf("BROKEN NODE");
    exit(0);
  }
  if (node_ -> canary2 != OK2){
    printf("BROKEN NODE");
    exit(0);
  }
  if (node_ -> checksum != node_ -> val * CHECK){
    printf("BROKEN NODE");
    exit(0);
  }
}
