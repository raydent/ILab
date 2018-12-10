#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
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
void CheckList(list* list_){
  if (!list_){
    printf("NO LIST");
    exit(0);
  }
  if (list_ -> canary1 != list_ -> num * OK){
    printf("LIST IS BROKEN");
    exit(0);
  }
  if (list_ -> head == NULL && list_ -> num != 0){
    printf("LIST IS BROKEN");
    exit(0);
  }
  if (list_ -> tail == NULL && list_ -> num != 0){
    printf("LIST IS BROKEN");
    exit(0);
  }
  if (list_ -> head != NULL){
    if (list_ -> head -> next == NULL && list_ -> num != 1){
      printf("LIST IS BROKEN");
      exit(0);
    }
  }
  if (list_ -> tail != NULL){
    if (list_ -> tail -> prev == NULL && list_ -> num != 1){
      printf("LIST IS BROKEN");
      exit(0);
    }
  }
  // if (list_ -> checksumh != (int)(list_ -> head -> prev) + (int)(list_ -> head -> next)){
  //   printf("LIST IS BROKEN");
  //   exit(0);
  // }
  // if (list_ -> checksumt != (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next)){
  //   printf("LIST IS BROKEN");
  //   exit(0);
  // }
}

list* ListConstr(list* list_) {
  list_ -> head = NULL;
  list_ -> tail = NULL;
  list_ -> num = 0;
  list_ -> canary1 = OK * list_ -> num;
  //list_ -> checksumh = (int)(list_ -> head -> prev) + (int)(list_ -> head -> next);
  //list_ -> checksumt = (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next);
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
  list_ -> canary1 += OK;
  if (list_ -> num == 0) {
    list_ -> head = node_;
    list_ -> tail = node_;
    list_ -> num = 1;
    //list_ -> checksumh = (int)(list_ -> head -> prev) + (int)(list_ -> head -> next);
  }
  else {
    list_ -> num += 1;
    node_ -> next = list_ -> head;
    list_ -> head = node_;
    node_ -> next -> prev = node_;
    node_ -> prev = NULL;
    //list_ -> checksumh = (int)(list_ -> head -> prev) + (int)(list_ -> head -> next);
  }
  return node_;
}
node* PushTail(list* list_, int val_) {
  node* node_ = NodeConstruct();
  node_ -> val = val_;
  node_ -> checksum = val_ * CHECK;
  list_ -> canary1 += OK;
  if (list_ -> num == 0) {
    list_ -> head = node_;
    list_ -> tail = node_;
    (list_ -> num) = 1;
    //list_ -> checksumt = (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next);
  }
  else {
    (list_ -> num) += 1;
    node_ -> prev = list_ -> tail;
    list_ -> tail = node_;
    node_ -> prev -> next = node_;
    node_ -> next = NULL;
    //list_ -> checksumt = (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next);
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
      if (node1 -> prev == NULL){
        printf("BROKEN LIST");
        exit(0);
      }
      node1 = node1 -> prev;
    }
    return node1;
  }
  else{
    CheckNode(list_ -> head);
    node* node2 = list_ -> head;
    for (int i = 1; i < num_; i++){
      if (node2 -> prev == NULL){
        printf("BROKEN LIST");
        exit(0);
      }
      node2 = node2 -> next;
    }
    return node2;
  }
}
node* Replace(list* list_, int num_, int val_){
  CheckList(list_);
  node* node_ = FindNode(list_, num_);
  CheckNode(node_);
  node_ -> val = val_;
  node_ -> checksum = val_ * CHECK;
};
node* Insert(list* list_, int num_, int val_, int state) {// state = -1 - сзади, 1 - спереди
  CheckList(list_);
  node* node_ = FindNode(list_, num_);
  CheckNode(node_);
  struct node* node1 = NodeConstruct();
  node1 -> checksum = val_ * CHECK;
  // if (num_ == list_ -> num)
    //list_ -> checksumt = (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next);
  // if (num_ == 1)
    //list_ -> checksumh = (int)(list_ -> head -> prev) + (int)(list_ -> head -> next);
  if (state == -1) {
    if (node1-> prev == NULL && num_ != 1){
      printf("BROKEN LIST");
      exit(0);
    }
    if (num_ == 1){
      PushHead(list_, val_);
    }
    node1 -> prev = node_ -> prev;
    node_ -> prev -> next = node1;
    node_ -> prev = node1;
    node1 -> next = node_;
    list_ -> canary1 += OK;
  }
  if (state == 1) {
    if (node1-> next == NULL && num_ != list_ -> num){
      printf("BROKEN LIST");
      exit(0);
    }
    if (num_ == list_ -> num){
      PushTail(list_, val_);
    }
    node1 -> next = node_ -> prev;
    node_ -> next -> prev = node1;
    node_ -> next = node1;
    node1 -> prev = node_;
    list_ -> canary1 += OK;
  }
  else {
    printf("WRONG STATE");
    exit(0);
  }
}
node* PopHead(list* list_){
  if (list_ -> num == 0){
    printf("NOTHING TO POP\n");
    exit(0);
  }
  CheckList(list_);
  CheckNode(list_ -> head);
  if (list_ -> num == 1){
    free(list_ -> head);
    list_ -> head = NULL;
    list_ -> tail = NULL;
    list_ -> canary1 = 0;
    list_ -> num -= 1;
    return NULL;
  }
  list_ -> head = list_ -> head -> next;
  free(list_ -> head -> prev);
  list_ -> head -> prev = NULL;
  list_ -> num -= 1;
  list_ -> canary1 -= OK;
  //list_ -> checksumh = (int)(list_ -> head -> prev) + (int)(list_ -> head -> next);
}
node* PopTail(list* list_){
  if (list_ -> num == 0){
    printf("NOTHING TO POP\n");
    exit(0);
  }
  CheckList(list_);
  CheckNode(list_ -> tail);
  if (list_ -> num == 1){
    free(list_ -> head);
    list_ -> head = NULL;
    list_ -> tail = NULL;
    list_ -> canary1 = 0;
    list_ -> num -= 1;
    return NULL;
  }
  list_ -> tail = list_ -> tail -> prev;
  free(list_ -> tail -> next);
  list_ -> tail -> next = NULL;
  list_ -> num -= 1;
  list_ -> canary1 -= OK;
  //list_ -> checksumt = (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next);
}
node* Delete(int num_, list* list_){
  node* node_ = FindNode(list_, num_);
  CheckNode(node_);
  if (list_ -> num == 0){
    printf("NOTHING TO POP\n");
    exit(0);
  }
  node_ -> next -> prev = node_ -> prev;
  node_ -> prev -> next = node_ -> next;
  // free(node_);
  list_ -> num -= 1;
  list_ -> canary1 -= OK;
  // if (num_ == 1)
    //list_ -> checksumh = (int)(list_ -> head -> prev) + (int)(list_ -> head -> next);
  // if (num_ == list_ -> num)
    //list_ -> checksumt = (int)(list_ -> tail -> prev) + (int)(list_ -> tail -> next);
}
void Erase(list* list_){
  CheckList(list_);
  if (list_ -> num != 0){
    PopHead(list_);
    Erase(list_);
  }
  else if (list_ -> num == 0){
    list_ -> head = NULL;
    list_ -> tail = NULL;
  }
}
void PrintList(list* list_){
  CheckList(list_);
  node* node_ = list_ -> head;
  for (int i = 1; i <= list_ -> num; i++){
    if (node_ -> next == NULL && i != list_ -> num){
      printf("BROKEN LIST");
      exit(0);
    }
    printf("%d\n", node_ -> val);
    node_ = node_ -> next;
  }
}
void ListDestruct(list* list_){
  CheckList(list_);
  Erase(list_);
  free(list_);
}
