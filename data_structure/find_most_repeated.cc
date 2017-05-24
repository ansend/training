#include <stdio.h>
#include <unistd.h>
#include <stdint.h>

//删除数组中出现次数超过一半的整数
#define MAX_LEN  1024
int array[MAX_LEN];

void find_most_repeated()
{
   int just_you;
   int exist_times = 0;
   for(int i = 0; i < MAX_LEN; i++)
   {
      if(exist_times == 0)
         {
            just_you = array[i];
              exist_times ++;
              
         }else{
            
               if(just_you == array[i])
                  exist_times ++;
               else
                  exist_times --;
              
         }
         
   }
   printf("it's just you %d \n", just_you);
}

int main(int argc, char** argv)
{
   for(int i = 0 ; i < 450; i++)
   {
       array[i] = i;
   }

   for(int i = 450 ; i < 1024; i++)
   {
       array[i] = 1000;
   }

   find_most_repeated();
  
}

