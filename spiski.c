#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
int const sum = 1;
typedef struct node
{
  int canary1;
  int checksum;
  int val;
  struct node* prev;
  struct node* next;
  int canary2;
}node;
node* readnode(node* last, int count, int* counter);
node* findnode(node* last, int* number, int* findingcounter);
int interface();
int main()
{
  long long int* breaker = (long long int*) calloc (1, sizeof(long long int*));
  // int state = interface();
  node* first = NULL;
  printf("Введите число узлов\n");
  int count = 0;
  scanf("%d", &count);
  int counter = 1;
  printf("Введите значения узлов\n");
  node* lastnode;
  lastnode = readnode(first, count, &counter);
  for (int i = 0; i < 1000; i++)
    breaker[i] = i * 100;
  printf("%d\n", lastnode->val);
  int findingcounter = 0;
  int number = 0;
  node* exactnode = findnode(lastnode, &number, &findingcounter);
  printf("%d\n", exactnode->val);
  return 0;
}

// int interface()
// {
//   printf("Введите 1, если необходимо создать список, 2, если необходимо найти узел, 3, если необходимо добавить узел (в конец), 4, если необходимо завершить программу");
//   int d = 0;
//   scanf("%d", &d);
//   return d;
// }
node* readnode(node* last, int count, int* counter)
{
  node* ret = (node*) calloc (1, sizeof(node));
  ret->prev = last;
  ret->next = NULL;
  int val_ = 0;
  scanf("%d", &val_);
  ret->val = val_;
  ret->canary1 = val_;
  // if (*counter != 1)
  //   ret->canary2 = last->val + val_;
  if (*counter != count)
  {
    *counter += 1;
    return readnode(ret, count, counter);
  }
  else
    return ret;
}
node* findnode(node* last, int* number, int* findingcounter)
{
  if (*number == 0)
  {
    printf("Введите номер узла с конца\n");
    int temp;
    scanf("%d", &temp);
    *number = temp - 1;
  }
  if (*findingcounter == *number)
    return last;
  if(last->prev == NULL)
  {
    printf("выход за пределы памяти, вывод первого узла\n");
    return last;
  }
  assert(last->prev->canary1 != last->val);
  if (*findingcounter != *number)
  {
    *findingcounter += 1;
    node* prev_ = last->prev;
    return findnode(prev_, number, findingcounter);
  }
}
