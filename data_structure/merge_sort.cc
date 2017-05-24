#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


void Merge(int *a, int p, int q, int r)  
{  
      int n1 = q-p+1;  
     int n2 = r-q;  
     int *L = new int[n1+1];  
     int *R = new int[n2+1];  
     int i, j, k;  
       
     for (i=0; i<n1; i++){  
         L[i] = a[p+i];  
     }  
     for (j=0; j<n2; j++){  
         R[j] = a[q+j+1];  
     }  
     L[n1] = 10000000;  
     R[n2] = 10000000;  
   
     for (i=0, j=0, k=p; k<=r; k++)  
     {  
         if (L[i]<=R[j])  
         {  
             a[k] = L[i];  
             i++;  
         }else{  
             a[k] = R[j];  
             j++;  
         }  
     }  
   
     delete []L;  
     delete []R;  
 }  
   
 void MergeSort1(int *a, int p, int r)  
 {  
     if (p<r)  
     {  
         int q = (p+r)/2;  
         MergeSort1(a, p, q);  
         MergeSort1(a, q+1, r);  
         Merge(a, p, q, r);  
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
