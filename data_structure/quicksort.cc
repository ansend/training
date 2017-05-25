#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#define LEN 10;
int array[10]={3,4,5,8,9,0,6,7,2,10};

void quick_sort(int* array, int left, int right)
{
    if(left > right)
      return;
    int low = left;
    int high= right;
    int key = array[left];
    printf("key %d\n left %d \n right %d", key, left, right);
    while(low < high)
    {

        while(low < high && array[high] > key)
	     high --;

	array[low] = array[high];

        while(low < high && array[low] < key)
	     low ++;

	array[high] = array[low];
    }

    array[low] = key;

    quick_sort(array, left, low-1);
    quick_sort(array, low+1, right);
}


int main(int argc, char** argv)
{
   for(int i=0 ; i< 10; i++)
   printf("array %d \n", array[i]);

   quick_sort(array, 0, 9);
   
   for(int i=0 ; i< 10; i++)
   printf("array %d \n", array[i]);


}
