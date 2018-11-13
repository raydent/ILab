#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
typedef struct strct
{
  char* pointer;
  int charnum;
  int stringnum;
}StringContainer;
char ReadToString(FILE* filetoread, char* giantstring, int filesize);
int Symbolamount(FILE* filetoread);
int ReadToNewStrings(char *giantstring, StringContainer* newstrings, int filesize);
int comp(const StringContainer*, const StringContainer*);

int main()
{
  FILE* filetoread= fopen ("original.txt", "r");
  FILE* filetowrite = fopen ("rework.txt", "w");
  if (!filetoread)
    printf("can't read file");
  if (!filetowrite)
    printf("can't write in file");
  int filesize = Symbolamount(filetoread);
  char* giantstring = (char*) calloc (filesize, sizeof(char*));
  StringContainer* newstrings = (StringContainer*) calloc (filesize, sizeof(StringContainer));
  ReadToString(filetoread, giantstring, filesize);
  int stringcount = ReadToNewStrings(giantstring, newstrings, filesize);
  printf("biba\n");
  qsort(newstrings, stringcount, sizeof(StringContainer), (int(*) (const void *, const void *)) comp);
  for (int i = 0; i <= stringcount; i++)
  {
    //printf("%s %d\n", newstrings[i].pointer, newstrings[i].charnum);
    fwrite(newstrings[i].pointer, sizeof(char), newstrings[i].charnum, filetowrite);
    fprintf(filetowrite, "\n");
  }
  return stringcount;
}

int Symbolamount(FILE* filetoread)
{
  struct stat st = {};
  stat ("original.txt", &st);
  int symbolamount = 0;
  symbolamount = (int)st.st_size;
  printf("количество символов = %d\n", symbolamount);
  return symbolamount;
}

char ReadToString(FILE* filetoread, char* giantstring, int filesize)
{
  fread(giantstring, sizeof(char), filesize, filetoread);
}

int ReadToNewStrings(char *giantstring, StringContainer* newstrings, int filesize)
{
  newstrings[0].pointer = &giantstring[0];
  int stringcount = 0;
  int ilast = 0;
  for (int i = 0; i < filesize; i++)
  {
    if (giantstring[i] == '\n')
    {
      giantstring[i] = '\0';
      if (stringcount == 0)
        newstrings[stringcount].charnum = i + 1;
      else
        newstrings[stringcount].charnum = i - ilast;
      ilast = i;
      stringcount++;
      if (giantstring[i + 1] == '\n')
      {
        while (giantstring[i + 1] == '\n')
        {
          i++;
        }
      }
      newstrings[stringcount].pointer = &giantstring[i + 1];
    }
  }
  // printf("%d\n", stringcount);
  // for (int i = 0; i <= stringcount; i++)
  // {
  //   printf("%s %d\n", newstrings[i].pointer, newstrings[i].charnum);
  // }
  return stringcount;
}
int comp(const StringContainer* string1, const StringContainer* string2)
{
  // int max = 0;
  // if (string1->charnum > string2->charnum)
  //   max = string1->charnum;
  // else
  //   max = string2->charnum;
  // for (int i = 0; i < max; i++)
  // {
  // if (string1->pointer[i] > string2->pointer[i])
  //   return 1;
  // if (string1->pointer[i] < string2->pointer[i])
  //   return -1;
  // }
  int ncharmax = 0;
  if (string2->charnum > string1->charnum)
    ncharmax = string2->charnum;
  else
    ncharmax = string1->charnum;
  int letter1 = 0, letter2 = 0;
  int i1 = 0, i2 = 0;
  for (;;)
  {
    if (((int)string1->pointer[i1] == 0) && ((int)string2->pointer[i2] == 0))
      return 0;
    if ((int)string1->pointer[i1] == 0)
      return -1;
    if ((int)string2->pointer[i2] == 0)
      return 1;
    if (((int)(string1->pointer[i1]) >= 65) && ((int)string1->pointer[i1] <= 90))
    {
      letter1 = ((int)string1->pointer[i1]) + 32;
    }
    if (((int)string1->pointer[i1] >= 97) && ((int)string1->pointer[i1] <= 122))
    {
      letter1 = (int)string1->pointer[i1];
    }
    else
    {
      while (((int)string1->pointer[i1]) < 65 || (((int)string1->pointer[i1]) > 90 && ((int)string1->pointer[i1]) < 97) || (((int)string1->pointer[i1]) > 122))
      {
        i1++;
      }
      letter1 = (int)string1->pointer[i1];
    }
    if (((int)(string2->pointer[i2]) >= 65) && ((int)string2->pointer[i2] <= 90))
    {
      letter2 = ((int)string2->pointer[i2]) + 32;
    }
    if (((int)string2->pointer[i2] >= 97) && ((int)string2->pointer[i2] <= 122))
    {
      letter2 = (int)string2->pointer[i2];
    }
    else
    {
      while (((int)string2->pointer[i2]) < 65 || (((int)string2->pointer[i2]) > 90 && ((int)string2->pointer[i2]) < 97) || ((int)string2->pointer[i2]) > 122)
      {
        i2++;
      }
      letter2 = (int)string2->pointer[i2];
    }
    if (letter1 > letter2)
      return 1;
    if (letter1 < letter2)
      return -1;
    i1++;
    i2++;
  }
}
