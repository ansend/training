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

    print_list(&root);

    Lnode * revroot =  reverseList(&root);

    print_list(revroot);
   
}
