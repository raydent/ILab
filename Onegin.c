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
int compforward(const StringContainer*, const StringContainer*);
int compbackward(const StringContainer*, const StringContainer*);
void WriteToFile(FILE* filetowrite, StringContainer*   newstrings, int stringcount);
char CorrectLetter(int i, const StringContainer* string);

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
  qsort(newstrings, stringcount, sizeof(StringContainer), (int(*) (const void *, const void *)) compforward);
  // WriteToFile(filetowrite, newstrings, stringcount);
  qsort(newstrings, stringcount, sizeof(StringContainer), (int(*) (const void *, const void *)) compbackward);
  WriteToFile(filetowrite, newstrings, stringcount);
  fclose(filetoread);
  fclose(filetowrite);
}

int Symbolamount(FILE* filetoread)
{
  struct stat st = {};
  stat ("original.txt", &st);
  int symbolamount = 0;
  symbolamount = st.st_size;
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
  return stringcount;
}

int compforward(const StringContainer* string1, const StringContainer* string2)
{
  char letter1 = 0, letter2 = 0;
  int i1 = 0, i2 = 0;
  for (;;)
  {
    if ((string1->pointer[i1] == 0) && (string2->pointer[i2] == 0))
      return 0;
    if (string1->pointer[i1] == 0)
      return -1;
    if (string2->pointer[i2] == 0)
      return 1;
    while ((string1->pointer[i1]) < 65 || ((string1->pointer[i1]) > 90 && (string1->pointer[i1]) < 97) || ((string1->pointer[i1]) > 122))
    {
      i1++;
    }
    while ((string2->pointer[i2]) < 65 || ((string2->pointer[i2]) > 90 && (string2->pointer[i2]) < 97) || (string2->pointer[i2]) > 122)
    {
      i2++;
    }
    letter1 = CorrectLetter(i1, string1);
    letter2 = CorrectLetter(i2, string2);
    if (letter1 > letter2)
      return 1;
    if (letter1 < letter2)
      return -1;
    i1++;
    i2++;
  }
}

int compbackward(const StringContainer* string1, const StringContainer* string2)
{

  char letter1 = 0, letter2 = 0;
  int i1 = string1->charnum, i2 = string2->charnum;
  for (;;)
  {
    while ((string1->pointer[i1]) < 65 || ((string1->pointer[i1]) > 90 && (string1->pointer[i1]) < 97) || ((string1->pointer[i1]) > 122))
    {
      i1--;
    }
    while ((string2->pointer[i2]) < 65 || ((string2->pointer[i2]) > 90 && (string2->pointer[i2]) < 97) || (string2->pointer[i2]) > 122)
    {
      i2--;
    }
    letter1 = CorrectLetter(i1, string1);
    letter2 = CorrectLetter(i2, string2);
    if (letter1 > letter2)
      return 1;
    if (letter1 < letter2)
      return -1;
    if ((i1 == 0) && (i2 == 0))
      return 0;
    if (i1 == 0)
      return -1;
    if (i2 == 0)
      return 1;
    i1--;
    i2--;
  }
}
char CorrectLetter(int i, const StringContainer* string)
{
  char letter = 0;
  if (((string->pointer[i]) >= 65) && (string->pointer[i] <= 90))
  {
    letter = (string->pointer[i]) + 32;
  }
  if ((string->pointer[i] >= 97) && (string->pointer[i] <= 122))
  {
    letter = string->pointer[i];
  }
  return letter;
}
void WriteToFile(FILE* filetowrite, StringContainer* newstrings, int stringcount)
{
  for (int i = 0; i <= stringcount; i++)
  {
    fprintf(filetowrite, "%s", newstrings[i].pointer);
    fprintf(filetowrite, "\n");
  }
}
