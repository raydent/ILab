#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
long long int hash(long long int number){
  long long int val = 0;
  val = (number % hash2) + ((number % hash1) * (number % hash3));
}
list* FindList(list** table, int number, int n){
  long long int def = hash(number);
  list* list_ = NULL;
  for (int i = 0; i < n; i++){
    if (table[i] -> hashsum == def)
      return table[i];
  }
  return NULL;
}

list** AddElem(list** table, FILE* f, int* n){
  long long int number = 0;
  char* word = (char*) calloc (20, sizeof(char*));
  for (;;){
    printf("n = %d\n", *n);
    if (fscanf(f,"%lld", &number) == EOF){
      break;
    }
    if (number == 0){
      break;
    }
    fgets(word, 20, f);
    if (table[0] -> head == NULL){
      PushHead(table[0], number);
      table[0] -> head -> name = (char*) calloc(20, sizeof(char*));
      strcpy(table[0] -> head -> name, word);
      table[0] -> hashsum = hash(number);
      printf("%lld\n", hash(number));
    }
    else{
      int state = 0;
      long long int def = hash(number);
      for (int i = 0; i < *n + 1; i++){
        if (table[i] -> hashsum == def){
            PushHead(table[i], number);
            // table[i] -> num += 1;
            table[i] -> head -> name = (char*) calloc(20, sizeof(char*));
            strcpy(table[i] -> head -> name, word);
            // *n -= 1;
            printf("%lld\n", def);
            state = 1;
            break;
        }
      }
      if (state != 1){
        *n += 1;
        table = (list**) realloc(table, (*n + 1) * sizeof(list**));
        table[*n] = ListConstr();
        PushHead(table[*n], number);
        table[*n] -> head -> name = (char*) calloc(20, sizeof(char*));
        strcpy(table[*n] -> head -> name, word);
        table[*n] -> hashsum = def;
        printf("%lld\n", def);
      }
      if (state == 1){
        state = 0;
        continue;
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
  for (int i = 0; i < n + 1; i++){
    node* node_ = table[i] -> head;
    fprintf(xls, "%d\n ", table[i] -> num);
    }
    fclose(xls);

}
