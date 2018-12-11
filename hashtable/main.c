#include <stdio.h>

#include "hashtable.h"
int main() {
  int n = 1;
  list** table = (struct list**) calloc (1, sizeof(list*));
  table[0] = ListConstr();
  FILE* f = fopen("source.dat", "r");
  table = FillList(table, f, &n);
  // printf("%lld %lld\n", hash(79505224087), hash(79870799549));
  collisioncount(table, n);
  printf("h1 = %lld\n", table[0] -> hashsum);
  printf("h2 = %lld\n", table[1] -> hashsum);
  printf("tail = %d\n", table[1] -> num);
    printf("tail = %d\n", table[0] -> num);
  // printf("h3 = %lld\n", table[2] -> hashsum);
  // printf("n = %d", n);
  // Printer(table, n);
  // Finder(table, n);
  // collisioncount(table, n);
  // fwrite(table[18] -> head -> name, sizeof(char), 20, stdout);
  // fwrite(table[19] -> head -> name, sizeof(char), 20, stdout);
  // printf("hash = %lld\n", table[19] -> hashsum);
  // printf("hash = %lld\n", table[16] -> hashsum);
  // PrintList(table[19]);
  fclose (f);
  return 1;
}
