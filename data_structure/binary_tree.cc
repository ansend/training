#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

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

bi_tree_node *  btree_find(struct bi_tree_node * tree, int value)
{
   if(tree == NULL)
      return NULL;
   if(tree->value == value)
       return tree;
   else if(value < tree->value)
       return btree_find(tree->left, value);
    else
       return btree_find(tree->right, value);

}




bi_tree_node * find_min_sub_tree(struct bi_tree_node * root, int left, int right)
{
   if(root == NULL) // normal should not be here.
     return NULL;
   if(left < root->value && right < root->value)

     return find_min_sub_tree(root->left, left, right);
   else if(left > root->value && right > root->value)
    return find_min_sub_tree(root->right, left, right);

   else
    return root;
}

int main(int argc, char ** argv)
{
    
    bi_tree_node * root = create_bnode(5);
    bi_tree_node * left = create_bnode(3);
    root->left = left;

    bi_tree_node * right = create_bnode(8);
    root->right = right;

    bi_tree_node * subtree = create_bnode(3);
   
    bi_tree_node * target = btree_find(root, 3);

    
    bool find = is_sub_tree(target, subtree);

    if(find)
     printf("the target is subtree of root\n");
     else
     printf("the target is not subtree of root\n");

}



