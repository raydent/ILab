#include <stdio.h>

#include "hashtable.h"
int main() {
  int n = 1;
  list** table = (struct list**) calloc (1, sizeof(list*));
  table[0] = ListConstr();
  FILE* f = fopen("source.dat", "r");
  table = FillList(table, f, &n);
  collisioncount(table, n);

  fclose (f);
  return 1;
}
