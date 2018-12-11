#include <stdio.h>

#include "hashtable.h"
int main() {
  int n = 1;
  list** table = (struct list**) calloc (1, sizeof(list*));
  table[0] = ListConstr();
  FILE* f = fopen("source.dat", "r");
  table = FillList(table, f, &n, hash4);
  collisioncount(table, n);
  fwrite(table[n - 1] -> head -> name, sizeof(char), 20, stdout);
  AddElem(table, &n, hash4);
  fwrite(table[n - 1] -> head -> name, sizeof(char), 20, stdout);
  Finder(table, n, hash4);
  deleteHash(table, &n);
  // printf("%d\n", table[0] -> num);
  fclose (f);
  return 1;
}
