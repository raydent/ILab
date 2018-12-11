#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
long long int hash1(long long int number){
  long long int val = 0;
  val = (number % HASH2) + ((number % HASH1) * (number % HASH3));
  return val;
}
long long int hash2(long long int number){
  long long int val = 0;
  val = (number % 10) + (number % 100) + (number % 1000) + (number % 10000) + (number / 1000 % 10000);
  return val;
}
long long int hash3(long long int number){
  long long int val = 0;
  val = (number << KEY) >> (4 * KEY);
  return val;
}
long long int hash4(long long int number){
  long long int val = 0;
  long long int num = number;
  val = (number / HASH1) % CONSTDIV;
}

int FindList(list** table, long long int number, int n, long long int (*hash) (long long int)){
  long long int def = hash(number);
  list* list_ = NULL;
  for (int i = 0; i < n; i++){
    if (table[i] -> hashsum == def)
      return i;
  }
  return -1;
}
list* AddContact(list* list_, long long int number, int n, char* word, long long int (*hash) (long long int)){
  if (list_ -> head != NULL){
    if (list_ -> head -> val == number){
      return NULL;
    }
  }
  PushHead(list_, number);
  list_ -> head -> name = (char*) calloc(20, sizeof(char*));
  strcpy(list_ -> head -> name, word);
  list_ -> hashsum = hash(number);
}
list** AddElem(list** table, int* n, long long int (*hash) (long long int)){
  long long int number = 0;
  printf("Введите число и имя\n");
  scanf("%lld", &number);
  char* word = (char*) calloc (20, sizeof (char*));
  fgets(word, 20, stdin);
  int num = FindList(table, number, *n, hash);
  node* node_ = NULL;
  if (num == -1){
    *n += 1;
    table = (list**) realloc(table, (*n) * sizeof(list**));
    table[*n - 1] = ListConstr();
    if (AddContact(table[*n - 1], number, *n, word, hash) == NULL)
      printf("Wrong number\n");
  }
  if (num != -1){
    node_ = table[num] -> head;
    for (int i = 0; i <= (table[num] -> num); i++){
      if (node_ -> val == number){
        printf("Wrong number\n");
        return NULL;
      }
      node_ = node_ -> next;
    }
    if(AddContact(table[num], number, *n, word, hash) == NULL)
      printf("Wrong number\n");
  }
}
list** FillList(list** table, FILE* f, int* n, long long int (*hash) (long long int)){
  long long int number = 0;
  char* word = (char*) calloc (20, sizeof(char*));
  for (;;){
    if (fscanf(f,"%lld", &number) == EOF){
      break;
    }
    if (number == 0){
      break;
    }
    fgets(word, 20, f);
    if (table[0] -> head == NULL){
      AddContact(table[0], number, *n, word, hash);
    }
    else{
      int num = FindList(table, number, *n, hash);
      if (num == -1){
        *n += 1;
        table = (list**) realloc(table, (*n) * sizeof(list**));
        table[*n - 1] = ListConstr();
        AddContact(table[*n - 1], number, *n, word, hash);
      }
      if (num != -1){
        AddContact(table[num], number, *n, word, hash);
      }
    }
  }
  return table;
}
int Printer(list** table, int n){
  for (int i = 0; i < n; i++){
      printf("%lld\n", table[i] -> hashsum);
      PrintList(table[i]);
      printf("\n \n \n");
  }
}
node* Finder(list** table, int n, long long int (*hash) (long long int)){
  printf("Введите номер");
  long long int number = 0;
  scanf("%lld", &number);
  int def = hash(number);
  for (int i = 0; i < n; i++){
    if (table[i] -> hashsum == def){
      node* node_ = table[i] -> head;
      for (;;){
        if (node_ -> val == number){
          fwrite(node_ -> name, sizeof(char), 20, stdout);
          return node_;
        }
        else if (node_ -> next != NULL){
          node_ = node_ -> next;
        }
        else if (node_ -> next == NULL){
          printf("Нет такого номера\n");
          return NULL;
        }
      }
    }
  }
  printf("Нет такого номера\n");
}

int collisioncount(list** table, int n){
  int counter = 1;
  long long int* corr = (long long int*) calloc (n, sizeof(long long int*));
  FILE* xls = fopen("collisin.txt", "w");
  for (int i = 0; i < n; i++){
    corr[i] = table[i] -> hashsum;
    fprintf(xls, "%d\n ", table[i] -> num);
    }
    fclose(xls);
}
void deleteHash(list** table, int* n){
  for (int i = 0; i < *n; i++){
    ListDestruct(table[i]);
  }
  free(table);
  *n = 0;
}
