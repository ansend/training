#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

int binary_search(int* array, int max, int key)
{
      
   int low  = 0;
   int high = max;
   int mid;       
   while (low <= high)
   {
       mid = (low + high)/2;
       if(array[mid] == key){
           return mid; 
       }else if(key < array[mid]){
           high = mid - 1;
       }else{
           low = mid + 1;
       }
   }
   return -1;
}



int find_binary_array(int* array, int min, int max, int x)
{

   printf("bianry search ::  low: %d, high:%d ,  mid:%d \n", min , max, (min + max)/2);
   if(min > max)
      return -1;
         
   int mid = (min + max)/2;
   if(array[mid] == x)
      return mid;
   else if(x < array[mid]){
      return find_binary_array(array, min, mid -1, x);
         
   }else{
      return find_binary_array(array, mid+1, max, x);
   }

}

int find_rotate_array(int*array , int min, int max , int x)
{
   int low = min;
   int high = max;
   
   printf("rotate search  ::   low: %d, high:%d ,  mid:%d \n", min , max, (low+high)/2);
   if(min > max)
      return -1;
   int mid =  (low+high)/2;
    
   if (array[mid] == x)
       return mid;
   else if(array[low] < array[mid]){                          
        if(array[low] <= x && x < array[mid] )// enter sorted range of the array     // 5, 6, 7, 8 , 1, 2, 3, 4 , find 7 
        {
            return find_binary_array(array, low, mid-1, x);
        }
        else          // still in rotate array
        {
            return find_rotate_array(array, mid+1, high, x);
        }
   
   }else{
   
        if((array[mid] < x) && (x <= array[high]))      // enter sorted range of the array     // 5, 6, 7, 8 , 1, 2, 3, 4 , find 7 
        {
            return find_binary_array(array, mid+1, high, x);
        }
        else {          // still in rotate array
            return find_rotate_array(array, low, mid-1, x);
        }
   }
}




int rotate_array_search(int*array , int min, int max , int val)
{
   int low = min;
   int high = max;
   int mid;
   if(min > max)
      return -1;

   while ( low <= high)
   {
       mid = (low+high)/2;
       if (array[mid] == val)
           return mid;
       else if(array[low] < array[mid]){                          
           if(array[low] <= val && val < array[mid] )// enter sorted range of the array     // 5, 6, 7, 8 , 1, 2, 3, 4 , find 7 
           {
               high = mid -1;
           }
           else          // still in rotate array
           {
               low = mid +1;    
           }
       
       }else{
       
           if((array[mid] < val) && (val <= array[high]))      // enter sorted range of the array     // 5, 6, 7, 8 , 1, 2, 3, 4 , find 7 
           {
               low = mid + 1;         
           }
           else {          // still in rotate array
               high = mid - 1;
	   }
       }
    
    }

    return -1;

}




int main(int argc, char** argv)
{

    int list[] = {6,7,8,9,10,1,2,3,4};

    int inx = 0;
    for (inx; inx< 9; inx++)
    {
        printf(" key is : %d\n", list[inx]);
        int found = find_rotate_array(list, 0, 8, list[inx]);
        if(found != -1)
           printf("found the num %d \n", found);
        else
           printf("no found the num %d \n", found);
	
	printf("\n\n");
    }
}
