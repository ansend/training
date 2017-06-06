#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX(a, b)  (a > b ? a : b)
#define HEIGHT(node) (node == NULL? 0 : node->height)

typedef struct avl_node {
   int height;
   int value;
   int count;
   struct avl_node * left;
   struct avl_node * right;
} * avl_tree;


avl_node * create_node(int value)
{
   avl_node * temp = (avl_node*) malloc(sizeof(avl_node));
   temp->height = 0;
   temp->value = value;
   temp->count = 1;
   temp->left = temp->right = NULL;
   return temp;
}

avl_node * ll_rotate(avl_node * node)
{       
     avl_node * old_root = node;
     avl_node * new_root = old_root->left;
     old_root->left = new_root->right;
                                                                                            
     new_root->right = old_root;

     new_root->height = MAX(new_root->left->height, new_root->right->height) + 1;
     old_root->height = MAX(old_root->left->height, old_root->right->height) + 1;

     return new_root;
}
avl_node * rr_rotate(avl_node * node)
{
     avl_node * old_root = node;
     avl_node * new_root = old_root->right;
     old_root->right = new_root->left;
     new_root->left = old_root;

     new_root->height = MAX(new_root->left->height, new_root->right->height) + 1;
     old_root->height = MAX(old_root->left->height, old_root->right->height) + 1;

     return new_root;

}

avl_node * lr_rotate(avl_node * node)
{
     node->left = rr_rotate(node->left);
     return ll_rotate(node);
}

avl_node * rl_rotate(avl_node * node)
{
     node->right = ll_rotate(node->right);
     return rr_rotate(node);
}

avl_node * avl_insert(int value, struct avl_node * node)
{
     if ( node == NULL){
         
         node = create_node(value);

     }else if( value < node->value){ //left sub tree insert

         node->left = avl_insert(value, node->left);
         if(HEIGHT(node->left) - HEIGHT(node->right) == 2){

             if(value < node->left->value)
		   node = ll_rotate(node);
	     else
		   node = lr_rotate(node);
	 }

     }else if( value > node->value){//right sub tree insert
        
        node->right = avl_insert(value, node->right);
        if(HEIGHT(node->right) - HEIGHT(node->left) == 2){

             if(value > node->right->value)
		   node = rr_rotate(node);
	     else
		   node = rl_rotate(node);
        }

     }else { // exist value in current avl tree

        node->count ++;              
 
     }

     node->height = MAX(node->left->height, node->right->height) + 1;
     return node;

}

// build a sequence tree from a sequence array
// 有序数组构建成二叉搜索树 

struct bi_tree_node{

	int value;
	struct bi_tree_node * left;
	struct bi_tree_node * right;
};

bi_tree_node * create_bnode(int value)
{
    bi_tree_node * tmp = (bi_tree_node*)malloc(sizeof(bi_tree_node));
    tmp->value = value;
    tmp->left = tmp->right = NULL;
    return tmp;
}

bi_tree_node * build_bitree(int * array, int start, int end)
{
      if(start > end)
	      return NULL;

      int mid = (start + end) /2;

      bi_tree_node * tmp = create_bnode(array[mid]);

      tmp->left = build_bitree(array, start, mid-1);
      tmp->right = build_bitree(array, mid+1, end);

      return tmp;
}




