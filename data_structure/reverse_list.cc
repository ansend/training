#include <stdio.h>
#include <stdint.h>
#include <unistd.h>


struct Lnode{
   int data;
   struct Lnode * next;

   Lnode(int d):data(d), next(NULL){}
};


Lnode * reverseList(Lnode * root)
{
    if ( NULL == root)
           return root;
              
       Lnode * revs_root = root;
       Lnode * p_node = root->next;
       Lnode * tmp_node = NULL;
       
       revs_root->next = NULL;
       while(p_node != NULL)
       {
         tmp_node = p_node->next;
              p_node->next = revs_root;
              revs_root = p_node;
              p_node = tmp_node;
       
       }
       
       return revs_root;
}
//merge 2 sequnced list into a one sequencetail list
// one condition is there is no extra new memory allocation.
Lnode * mergeList(Lnode * root1, Lnode* root2)
{
     if (root1 == NULL)
          return root2; 
     if (root2 == NULL)
          return root1;

     Lnode * newroot = NULL;
     Lnode * iroot1 = root1;
     Lnode * iroot2 = root2 ;

     if(iroot1->data <= iroot2->data){

         newroot= iroot1;
	 iroot1 = iroot1->next;
             printf(" ansen ddata  is %d \n", iroot1->data);
	 newroot->next = NULL;
           //  printf(" ansen ddata  is %d \n", iroot1->data);
     }else{

         newroot = iroot2;
	 iroot2 = iroot2->next;
	 newroot->next = NULL;

     }

     Lnode * inewroot = newroot;

    //         printf(" data  is %d \n", iroot1->data);
             printf(" ansen ddata  is %d \n", iroot2->data);

     while(iroot1 != NULL && iroot2 != NULL)
     {
         if(iroot1->data <= iroot2->data){
             printf(" data  is %d \n", iroot1->data);
	     inewroot->next = iroot1;
             iroot1 = iroot1->next;
	     inewroot = inewroot->next;
	     inewroot->next = NULL;
	 }else{
             inewroot->next = iroot2;
             printf(" data  is %d \n", iroot2->data);
             iroot2 = iroot2->next;
	     inewroot = inewroot->next;
	     inewroot->next = NULL;
	 }

     }

     if(iroot1 == NULL)
        inewroot->next = iroot2;
     else
        inewroot->next = iroot1;

     return newroot;
}

void print_list(Lnode * root)
{
    Lnode* cur_node = root;
    while(cur_node)
    {
       printf(" data is %d\n", cur_node->data);
       cur_node = cur_node->next;
    }
}



int main(int argc, char** argv)
{
    Lnode root(0);
    Lnode n1(1);
    root.next = &n1;
    Lnode n2(2);
    n1.next = &n2;
    Lnode n3(3);
    n2.next = &n3;    

    Lnode root2(5);
    Lnode nt1(6);
    root2.next = &nt1;
    Lnode nt2(7);
    nt1.next = &nt2;
    Lnode nt3(8);
    nt2.next = &nt3;    



    print_list(&root);
    print_list(&root2);

    //Lnode * revroot =  reverseList(&root);

    //print_list(revroot);
   
    
    Lnode * mergeroot = mergeList(&root, &root2);
    printf("print the merged list\n");
    print_list(mergeroot);
}
