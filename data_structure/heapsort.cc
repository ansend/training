#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

/*
1.堆
  堆实际上是一棵完全二叉树，其任何一非叶节点满足性质：
  Key[i]<=key[2i+1]&&Key[i]<=key[2i+2] 其中 i=0,1,2, ...n    最小堆
  Key[i]>=Key[2i+1]&&key[i]>=key[2i+2] 其中 i=0,1,2, ...n    最大堆
  即任何一非叶节点的关键字不大于或者不小于其左右孩子节点的关键字。
  堆分为大顶堆和小顶堆，满足Key[i]>=Key[2i+1]&&key>=key[2i+2]称为大顶堆，满足 Key[i]<=key[2i+1]&&Key[i]<=key[2i+2]称为小顶堆。
  由上述性质可知大顶堆的堆顶的关键字肯定是所有关键字中最大的，小顶堆的堆顶的关键字是所有关键字中最小的。

  2.堆排序的思想
   利用大顶堆(小顶堆)堆顶记录的是最大关键字(最小关键字)这一特性，使得每次从无序中选择最大记录(最小记录)变得简单。
    其基本思想为(大顶堆)：
    1)将初始待排序关键字序列(R1,R2....Rn)构建成大顶堆，此堆为初始的无序区；
    2)将堆顶元素R[1]与最后一个元素R[n]交换，此时得到新的无序区(R1,R2,......Rn-1)和新的有序区(Rn),且满足R[1,2...n-1]<=R[n]; 
    3)由于交换后新的堆顶R[1]可能违反堆的性质，因此需要对当前无序区(R1,R2,......Rn-1)调整为新堆，然后再次将R[1]与无序区
	  最后一个元素交换，得到新的无序区(R1,R2....Rn-2)和新的有序区(Rn-1,Rn)。不断重复此过程直到有序区的元素个数为n-1，
	  则整个排序过程完成。
    操作过程如下：
     1)初始化堆：将R[1..n]构造为堆；
     2)将当前无序区的堆顶元素R[1]同该区间的最后一个记录交换，然后将新的无序区调整为新的堆。
    因此对于堆排序，最重要的两个操作就是构造初始堆和调整堆，其实构造初始堆事实上也是调整堆的过程，
	只不过构造初始堆是对所有的非叶节点都进行调整。

*/

void swap(int * a, int * b)
{
   int tmp = *a;
   *a = *b;
   *b = tmp;
}


void adjust_heap(int * array, int size, int pos)
{

     int left = 2*pos + 1;
     int right = 2*pos + 2;
     
     int largest = pos;

     if( (left < size) && (array[left] > array[largest]))
         largest = left;
   
     if((right < size) && (array[right] > array[largest]))
         largest = right;


     if(largest == right){
            
         swap(array+pos, array+right);
         adjust_heap(array, size, right);  
     }else if(largest == left){

         swap(array+pos, array+left);
         adjust_heap(array, size , left);

     }
     // if the current pos is alreay the largest, do nothing.

}

void build_heap(int * array, int size)
{

   int last_parent = size/2 -1; // considering, size ==3, the only one parent index is actually 0.
   for (int i =last_parent ; i>=0; i--)
   {
       adjust_heap(array, size , i);
   }

}

void heap_sort(int * array, int size)
{

   build_heap(array, size);

   for(int i=size ; i > 1 ; i--)
   {
      swap(array+i-1 , array);
      adjust_heap(array, i-1, 0);
   }
   
}


int main(int argc, char ** argv)
{

  int array[] = {9, 8, 3, 4, 5, 6 ,0, 1, 7, 2};


  int size = sizeof(array) / sizeof(int);
  for(int i=0; i<size; i++)
	printf("%d", array[i]);
  printf("\n");

  heap_sort(array, 10);
 
  for(int i =0; i<size; i++)
	printf("%d", array[i]);
  printf("\n");







}
