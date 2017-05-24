#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


bool find_binary_array(int* array, int min, int max, int x)
{
   if(min > max)
      return false;
         
   int mid = (min + max)/2;
   if(array[mid] == x)
      return true;
   else if(x < array[mid]){
      return find_binary_array(array, min, mid -1, x);
         
   }else{
      return find_binary_array(array, mid+1, max, x);
   }

}

bool find_rotate_array(int*array , int min, int max , int x)
{
   int low = min;
   int high = max;
   
   if(min > max)
      return false;
   int mid =  (low+high)/2;
    
   if (array[mid] == x)
       return true;
   else if(x < array[mid]){                          
        if(array[low] <= array[mid])// enter sorted range of the array     // 5, 6, 7, 8 , 1, 2, 3, 4 , find 7 
        {
            return find_binary_array(array, low, mid, x);
        }
        else if (array[low] > array[mid])          // still in rotate array
        {
            return find_rotate_array(array, low, mid, x);
        }
   
   }else{
   
        if(array[mid] <= array[high])      // enter sorted range of the array     // 5, 6, 7, 8 , 1, 2, 3, 4 , find 7 
        {
            return find_binary_array(array, low, mid, x);
        }
        else if (array[mid] > array[high]){          // still in rotate array
        
            return find_rotate_array(array, low, mid, x);
        }
   }
}

int main(int argc, char** argv)
{

    int list[] = {6,7,8,9,10,1,2,3,4};

    bool found =  find_rotate_array(list, 0, 8, 17);

    if(found)
       printf("found the num \n");
    else
       printf("no found the num\n");

}
