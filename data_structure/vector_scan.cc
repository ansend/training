#include <stdio.h>
#include <unistd.h>


int vector[] ={31, -41, 59, 26, -53, 58, 97, -93, -23, 84};


void algrithom1()
{
   printf("sizeof vector is %lu\n", sizeof(vector)/sizeof(int));

   int num = sizeof(vector) / sizeof(int);

   int maxsofar = 0;

   int i, j, k;
   for( i =0; i < num; i++)
   {
       for (j=i ; j< num; j++)
       {
          int  sum = 0;
          for ( k = i; k <= j; k++)
	  {
             sum += vector[k];
	  }

          maxsofar = maxsofar > sum ? maxsofar : sum;
          printf("i, j, max: %d, %d, %d\n", i, j, maxsofar);
       }


   }

   printf(" max sofar is %d \n", maxsofar);

}


void algrithom()
{

   printf("sizeof vector is %lu\n", sizeof(vector)/sizeof(int));

   int num = sizeof(vector) / sizeof(int);

   int maxsofar = 0;

   int i, j;
   for( i =0; i < num; i++)
   {
       int sum = 0;
       for (j=i ; j< num; j++)
       {
          sum += vector[j];

          maxsofar = maxsofar > sum ? maxsofar : sum;
          printf("i, j, max: %d, %d, %d\n", i, j, maxsofar);
       }


   }

   printf(" max sofar is %d \n", maxsofar);




}

int main(int argc, char ** argv)
{

  algrithom();

}
