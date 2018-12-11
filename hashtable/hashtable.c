#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
long long int hash(long long int number){
  long long int val = 0;
  // val = (number % hash2) + ((number % hash1) * (number % hash3));
  val = number % 3;
  return val;
}

int FindList(list** table, long long int number, int n){
  long long int def = hash(number);
  list* list_ = NULL;
  for (int i = 0; i < n; i++){
    if (table[i] -> hashsum == def)
      return i;
  }
  return -1;
}

list* AddContact(list* list_, long long int number, int n, char* word){
  PushHead(list_, number);
  list_ -> head -> name = (char*) calloc(20, sizeof(char*));
  strcpy(list_ -> head -> name, word);
  list_ -> hashsum = hash(number);
}

list** FillList(list** table, FILE* f, int* n){
  long long int number = 0;
  printf("hash(num) = %lld\n", hash(number));
  char* word = (char*) calloc (20, sizeof(char*));
  for (;;){
    printf("n = %d\n", *n);
    if (fscanf(f,"%lld", &number) == EOF){
      break;
    }
    printf("hash(num) = %lld\n", hash(number));
    if (number == 0){
      break;
    }
    fgets(word, 20, f);
    if (table[0] -> head == NULL){
      AddContact(table[0], number, *n, word);
      // printf("%lld\n", hash(number));
    }
    else{
      int num = FindList(table, number, *n);
      if (num == -1){
        *n += 1;
        table = (list**) realloc(table, (*n) * sizeof(list**));
        table[*n - 1] = ListConstr();
        AddContact(table[*n - 1], number, *n, word);
        // table[*n - 1] -> num -= 1;
      }
      if (num != -1){
        AddContact(table[num], number, *n, word);
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
node* Finder(list** table, int n){
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
  FILE* xls = fopen("collisin.txt", "w");
  for (int i = 0; i < n; i++){
    node* node_ = table[i] -> head;
    fprintf(xls, "%d\n ", table[i] -> num);
    }
    fclose(xls);

}
