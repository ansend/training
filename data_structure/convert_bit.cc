#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


//把四个字节中的001 转换成 011 然后输出数字

void revert(uint32_t i)
{
   uint32_t orig = i;
   
   uint32_t mask = 7;
   
   int target = 1;
   int replace = 3;
   int shift= 0;
   
   while(shift < 29)
   {
          if ((mask & orig ) == target)
	   {
	      printf("mask : %x, target: %x, replace %x, orig: %x\n", mask, target, replace, orig);
	       orig |= replace;
               printf("orig is %x \n", orig);
		   mask <<= 3;
		   target <<= 3;
		   replace <<= 3;
		   shift += 3;
	   }else{
	   
	           printf("mask : %x, target: %x, replace %x, orig: %x\n", mask, target, replace, orig);
                   printf("left move 1\n");
	           mask <<= 1;
		   target <<= 1;
		   replace <<= 1;
		   shift += 1;
	   }
   }
   printf("final result is \n");
   printf("orig is %x \n", i);
   printf("target is %x \n", orig);
}

int main(int argc, char** argv)
{
   revert(0x01010101);
}
