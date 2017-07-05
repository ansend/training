#include <stdio.h>
#include <stdarg.h>

int vaprint(int num, ...)
{
   int j = num;
   va_list va;
   va_start(va, num);  // the second argument is the previous arg before the variable args.
   while (j >0)
   {
      int aa =  va_arg(va, int);
      printf("the %d index is %d\n", j , aa);
      j--;
   }

}

int main(int argc,  char ** argv)
{
    vaprint(2, 10, 20);
    vaprint(3, 10, 20, 30);

}
