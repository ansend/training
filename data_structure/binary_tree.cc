#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


struct bi_tree_node{

	int value;
	struct bi_tree_node * left;
	struct bi_tree_node * right;
};

bi_tree_node * create_bnode(int value)
{
    struct bi_tree_node * tmp = (bi_tree_node*)malloc(sizeof(bi_tree_node));
    tmp->value = value;
    tmp->left = tmp->right = NULL;
    return tmp;
}


bool is_sub_tree(struct bi_tree_node * ptree, struct bi_tree_node * stree)
{

     if(ptree == NULL && stree == NULL)
         return true;

     if(ptree != NULL && stree != NULL){
         if(ptree-> value == stree->value){
            
             return (is_sub_tree(ptree->left, stree->right) && is_sub_tree(ptree->left, stree->right));
         }else

             return false; // value not equal;       
     }
     else  // one is null and another not
         return false;


}

bool btree_find(struct bi_tree_node * tree, int value)
{

   


}

