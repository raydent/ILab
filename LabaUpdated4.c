#include <stdio.h>
#include <stdlib.h>
#include <math.h>
const float D = 0.36, Pi = 3.14;
const int L1 = 20, L2 = 30, L3 = 50;
const int L[] = {20, 30, 50};
double deltaL = 0.2, deltaD = 0.01;
const int Npoints = 100;
const int WireAmount = 3;
void CalculateLaba(double meas1[], double meas2[], int nMeas, double measfin[]);
int ReadData(double meas1[] , double meas2[]);
void WriteLaba (double measfin[], int nMeas, double Disp);
void Delta (double meas1[], double meas2[], int nMeas, double* delta);
void laba1calculations(double* psumm, double meas1[], double meas2[], double measfin[], int n, int nWire);
double Disp(double meas[], int nMeas);
double cov (double meas1[], double meas2[], int nMeas, double* measavg);
int main()
{
  double meas1[Npoints];
  double meas2[Npoints];
  double measfin[Npoints];
  for (int i = 0; i <= Npoints; i++)
  {
    meas1[i] = 0;
    meas2[i] = 0;
    measfin[i] = 0;
  }
  ReadData (meas1 , meas2);
  int nMeas = ReadData (meas1 , meas2);
  if (nMeas <= 0)
  {
	   printf("Can't read file");
     return 1;
  }
  CalculateLaba(meas1, meas2, nMeas, measfin);
  for (int k = 0; k < nMeas; k++)
  if (measfin[k++] == 0)
  {
    printf("can't calculate measfin[%d]", k );
    return(0);
  }
  double delta = 0;
  Delta (meas1, meas2, nMeas, &delta);
  WriteLaba(measfin, nMeas, delta);
  return (0);
}
 int ReadData (double meas1[], double meas2[])
{
  FILE* file = fopen ("lab1.txt", "r");
  if (!file)
	{
	   printf ("Cannot open lab1.txt");
	   return -1;
	}
  int line = 0;
  for (;;)
  {
    int res = fscanf (file, "%lg %lg", &meas1[line], &meas2[line]);
    if (res == EOF) break;
    line++;
  }
  fclose (file);
  return line;
}
 void CalculateLaba (double meas1[],double meas2[],int nMeas, double measfin[])
{
  double meassum = 0, meas1sum = 0, meas2sum = 0, meas1max = 0, meas2max = 0, meas1min = meas1[0], meas2min = meas2[0];
  for (int n = 0; n < nMeas; n++)
  {
    if (meas1[n] >= meas1max)
      meas1max = meas1[n];
    if (meas2[n] >= meas2max)
      meas2max = meas2[n];
    if (meas1[n] <= meas1min)
        meas1min = meas1[n];
    if (meas2[n] <= meas2min)
        meas2min = meas2[n];
  }
  for (int n = 0; n < nMeas; n++)
  {
    if ((meas1[n] != meas1max) && (meas1[n] != meas1min))
      meas1sum += meas1[n];
    if ((meas2[n] != meas2max) && (meas2[n] != meas2min))
      meas2sum += meas2[n];
  }
  double meas1last = meas1sum / nMeas - 2;
  double meas2last = meas2sum / nMeas - 2;
  for (int n = 0; n < nMeas; n++)
  {
    if ((meas1[n] >= 20 * meas1last) || (meas1[n] <= meas1last / 20))
      printf ("global error for measurement 1, №%d \n", n+1);
    else meas1last = meas1[n];
    if ((meas2[n] >= 20 * meas2last) || (meas2[n] <= meas2last / 20))
      printf ("global error for measurement 2, №%d \n", n +1);
    else meas2last = meas2[n];
  }
  for (int nWire = 0; nWire < WireAmount; nWire++)
  {
    for (int k = (nWire * nMeas / WireAmount); k < ((nWire + 1) * nMeas / WireAmount); k++)
    {
      laba1calculations(&meassum, meas1, meas2, measfin, k, nWire);
    }
  }
}
 void WriteLaba (double measfin[], int nMeas, double delta)
{
  int n = 0; //n здесь и далее - счетчик номеров переменных в массиве
  double psumm = 0;
  FILE * labres = fopen ("labres.txt", "w");
  for (n = 0; n <= nMeas - 1; n++)
  {
    fprintf (labres, "p[%d]=%0.03lg +- %0.02lg \n", n+1, measfin[n], measfin[n] * delta);
    psumm += measfin[n];
  }
  fprintf (labres, "pavg = %0.03lg +- %0.02lg \n", (psumm/nMeas), (psumm / nMeas * delta));
  fclose (labres);
}
 void Delta (double meas1[], double meas2[], int nMeas, double* delta)
{
  double Disp1 = Disp(meas1, nMeas);
  double Disp2 = Disp(meas2, nMeas);
  double measavg = 0;
  double covar = cov (meas1, meas2, nMeas, &measavg);
  double delta0 = sqrt((((Disp1 / Disp2) - (covar / Disp1) * (covar / Disp1))) / (nMeas - 2));
  *delta = sqrt ((delta0 / measavg) *(delta0 / measavg) + (deltaL / L[2]) * (deltaL / L[2]) + (deltaD / D) * (deltaD / D));
}
 void laba1calculations(double* psumm, double meas1[], double meas2[], double measfin[], int n, int nWire)
{
  double p = 0;
  p = ((meas1[n] / meas2[n]) * (D*D) * Pi) / (4 * L[nWire]) * 100;
  measfin[n] = p;
  *psumm = *psumm + p;
}
 double cov (double meas1[], double meas2[], int nMeas, double* measavg)
{
  double meas1summ = 0, meas2summ = 0, meas12summ;
  for (int n =0; n < nMeas; n++)
  {
    meas1summ += meas1[n];
    meas2summ += meas2[n];
    meas12summ += meas1[n] * meas2[n];
  }
  *measavg = (meas1summ / meas2summ);
  double meas1avg = meas1summ / nMeas;
  double meas2avg = meas2summ / nMeas;
  double meas12avg = meas12summ / nMeas;
  return (meas12avg - (meas1avg * meas2avg));
}
 double Disp(double meas[], int nMeas)
{
  double meassum = 0, dispsumm = 0;
  for (int n = 0; n < nMeas; n++)
  {
    meassum += meas[n];
  }
  for (int n = 0; n < nMeas; n++)
  {
    dispsumm += (meas[n] - (meassum / nMeas)) * (meas[n] - (meassum / nMeas));
  }
  return (dispsumm/nMeas);
}
