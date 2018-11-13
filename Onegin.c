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
char CorrectLetter(int numb, const StringContainer* string);

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
  WriteToFile(filetowrite, newstrings, stringcount);
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
  int numb1 = 0, numb2 = 0;
  for (;;)
  {
    if ((string1->pointer[numb1] == 0) && (string2->pointer[numb2] == 0))
      return 0;
    if (string1->pointer[numb1] == 0)
      return -1;
    if (string2->pointer[numb2] == 0)
      return 1;
    while ((string1->pointer[numb1]) < 65 || ((string1->pointer[numb1]) > 90 && (string1->pointer[numb1]) < 97) || ((string1->pointer[numb1]) > 122))
    {
      numb1++;
      if (numb1 == string1->charnum)
        return 1;
    }
    while ((string2->pointer[numb2]) < 65 || ((string2->pointer[numb2]) > 90 && (string2->pointer[numb2]) < 97) || (string2->pointer[numb2]) > 122)
    {
      numb2++;
      if (numb2 == string2->charnum)
        return -1;
    }

    letter1 = CorrectLetter(numb1, string1);
    letter2 = CorrectLetter(numb2, string2);
    if (letter1 > letter2)
      return 1;
    if (letter1 < letter2)
      return -1;
    numb1++;
    numb2++;
  }
}

int compbackward(const StringContainer* string1, const StringContainer* string2)
{

  char letter1 = 0, letter2 = 0;
  int numb1 = string1->charnum, numb2 = string2->charnum;
  for (;;)
  {
    while ((string1->pointer[numb1]) < 65 || ((string1->pointer[numb1]) > 90 && (string1->pointer[numb1]) < 97) || ((string1->pointer[numb1]) > 122))
    {
      numb1--;
    }
    while ((string2->pointer[numb2]) < 65 || ((string2->pointer[numb2]) > 90 && (string2->pointer[numb2]) < 97) || (string2->pointer[numb2]) > 122)
    {
      numb2--;
    }
    letter1 = CorrectLetter(numb1, string1);
    letter2 = CorrectLetter(numb2, string2);
    if (letter1 > letter2)
      return 1;
    if (letter1 < letter2)
      return -1;
    if ((numb1 == 0) && (numb2 == 0))
      return 0;
    if (numb1 == 0)
      return -1;
    if (numb2 == 0)
      return 1;
    numb1--;
    numb2--;
  }
}
char CorrectLetter(int numb, const StringContainer* string)
{
  char letter = 0;
  if (((string->pointer[numb]) >= 65) && (string->pointer[numb] <= 90))
  {
    letter = (string->pointer[numb]) + 32;
  }
  if ((string->pointer[numb] >= 97) && (string->pointer[numb] <= 122))
  {
    letter = string->pointer[numb];
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
