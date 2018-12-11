#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
const long long int constnum = 79000000000;
void writer(int num, FILE* f);
long long int numgen(int* array, int* counter);
int main(){
  int num = 0;
  int seed = time (NULL);
  srand(seed);
  printf("Введите число номеров");
  scanf("%d", &num);
  FILE* f = fopen ("source.dat", "w");
  assert(f);
  writer(num, f);
  fclose(f);
}
void writer(int n, FILE* f){
  long long int number = 0;
  int key = 0;
  int* array = (int*) calloc (n, sizeof (int*));
  int counter = 0;
  int state = 1;
  for (int i = 0; i < n; i++){
     // number = constnum + (abs(rand () % 100000) * 10000) + abs(rand () % 10000);
    number = numgen (array, &counter);
    fprintf(f,"%lld ", number);
    key = rand() % 19 + 1;
    for (int k = 0; k < key; k++){
      fprintf(f,"%c", ('A' + (char)(rand() % 26)));
    }
    fprintf(f, "\n");
  }
}
long long int numgen(int* array, int* counter){
  long long int number;
  number = constnum + abs((rand () % 100000) * 10000) + abs(rand () % 10000);
  // printf("%d\n", number);
  for (int i = 0; i < *counter + 1; i++){
    if (array[i] == number){
      printf("1\n");
      return numgen(array, counter);
    }
  }
  array[*counter] = number;
  *counter++;
  return number;
}
