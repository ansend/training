#include <stdio.h>
#include <stdint.h>
#include <vector>


void insert_vec(){

  int array[10] = {0, 1, 2, 3,4,5,6,7,8,9};

  std::vector<int> intvec(array, array+10); //notice here, the iterator is [0,10), 

  //intvec.pop_front();  notice ****, vector not support pop_front, only list and queue support it.
  intvec.pop_back();
  std::vector<int>::iterator it = intvec.begin();

  intvec.erase(it,it);


  it = intvec.begin();
   while(it != intvec.end())
   {
        printf(" it value is %d \n", *it);

	it=intvec.insert(it, 20);

	it++; //it will return the newly added element, so advance 2 will move to the element behind
	     // the original value.
	it++;

   }
 
   printf("show the final result\n");
   for(it = intvec.begin(); it != intvec.end(); it++)
   {
       printf(" value: %d \n", *it);
   }
    
}
int main(int argc, char** argv)
{
   int i = 10LLU;
   printf("i is %d\n", i);
 
   printf("LLU size is %d\n", sizeof(10LLU));
   printf("int size is %d\n", sizeof(10));

   int yy =0x09;

   insert_vec();
}
