#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

#define LEN 10;
int array[10]={3,4,5,8,9,0,6,7,2,10};

void quick_sort(int* array, int left, int right)
{
    if(left >= right)
      return;
    int low = left;
    int high= right;
    int key = array[left];
    printf("key %d\n left %d \n right %d", key, left, right);
    while(low < high)
    {
        /*而寻找结束的条件就是，1，找到一个小于或者大于key的数（大于或小于取决于你想升
         *序还是降序）2，没有符合条件1的，并且i与j的大小没有反转*/ 
        while(low < high && array[high] >= key)
	     high --; /*向前寻找*/

        /*找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
        *a[left]，那么就是给key）*/
	array[low] = array[high]; 

        /*这是i在当组内向后寻找，同上，不过注意与key的大小关系停止循环和上面相反，
         *因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反*/
        while(low < high && array[low] <= key)
	     low ++;

	array[high] = array[low];
    }

    array[low] = key; /*当在当组内找完一遍以后就把中间数key回归*/

    quick_sort(array, left, low-1); /*最后用同样的方式对分出来的左边的小组进行同上的做法*/
    quick_sort(array, low+1, right);/*用同样的方式对分出来的右边的小组进行同上的做法*/
}


int main(int argc, char** argv)
{
   for(int i=0 ; i< 10; i++)
   printf("array %d \n", array[i]);

   quick_sort(array, 0, 9);
   
   for(int i=0 ; i< 10; i++)
   printf("array %d \n", array[i]);


}
