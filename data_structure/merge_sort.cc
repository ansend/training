#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


void Merge(int *a, int left, int mid, int right)  
{  
      int n1 = mid-left+1;  
     int n2 = right-mid;  
    // int *L = new int[n1+1];  
    // int *R = new int[n2+1];  
     int *L = new int[n1];  
     int *R = new int[n2];  
     
     int i, j, k;  
       
     for (i=0; i<n1; i++){  
         L[i] = a[left+i];  
     }  
     for (j=0; j<n2; j++){  
         R[j] = a[mid+j+1];  
     }  
     //L[n1] = 0x7fffffff;  
     //R[n2] = 0x7fffffff;  
  /* 
     for (i=0, j=0, k=left; k<=right; k++)  
     {  
         if (L[i]<=R[j])  
         {  
             a[k] = L[i];  
             i++;
	     if(i == n1)
	      break;
         }else{  
             a[k] = R[j];  
             j++;  
	     if(j == n2)
	     break;
         }  
     } 
   */  
    i = 0;
    j = 0;
    k = left;
  
    while(k <= right)
    {
       if(i == n1)
       {
          a[k++] = R[j++];
	  continue;
       }
     
       if(j == n2)
       {
         a[k++]= L[i++];
	 continue;
       }

       if(L[i] <= R[j])
       {
          a[k++] = L[i++];
       }else{

          a[k++] = R[j++];
       }

    }

     delete []L;  
     delete []R;  
 }  
   
 void MergeSort1(int *a, int left, int right)  
 {  
     if (left<right)  
     {  
         int mid = (left+right)/2;  
         MergeSort1(a, left, mid);  
         MergeSort1(a, mid+1, right);  
         Merge(a, left, mid, right);  
     }  
 }


int main(int argc, char** argv)
{
   
   int array[] = {13, 32, 43, 56, 67, 89,39,29,89,31,56};
   for(int i =0; i< 10; i++)
	   printf("array %d ", array[i]);
   printf("\n");
   MergeSort1(array, 0, 9);
   for(int i =0; i< 10; i++)
	   printf("array %d ", array[i]);
   printf("\n");


}
