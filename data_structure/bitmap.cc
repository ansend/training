#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


//求两个数组中数据的交集
#define REAL_SIZE 1000

#define SHIFT 3          //uint8_t map to 3, and uint32_t map to 5
#define MOD_MASK 0x7     // equal to %8,   mask 0x1F equals to %32 

#define MAX_SIZE  REAL_SIZE/(sizeof(uint8_t) * 8) + 1

uint8_t bitmap[MAX_SIZE];

void set_bm(uint32_t bit)
{
    printf("the bitmap index is %u \n", bit >> SHIFT);
    bitmap[bit >> SHIFT] |= uint8_t(1 << (bit & MOD_MASK));
}

bool test_bm(uint32_t bit)
{
   return bitmap[bit >> SHIFT] & uint8_t(1<<(bit & MOD_MASK));
}

void clean_bm(uint32_t bit)
{
   bitmap[bit >> SHIFT] &= uint8_t(1 << (bit & MOD_MASK));
}


int main (int argc, char ** argv)
{

	printf("max len is %lu \n", MAX_SIZE);
        int array1[255] = {0};
	int array2[255] = {0};
	
	array1[1] = 200;
	array2[3] = 200;
	array1[2] = 100;
	array2[4] = 150;

	for(int i=0; i<255; i++)
	{
           set_bm(array1[i]);	
	}
	
	for(int i=0; i<255; i++)
	{
	   if (test_bm(array2[i]))
	      printf("repeated num %d \n", array2[i]);
	   else
	      printf("not repeated num %d \n", array2[i]);
	}

}
