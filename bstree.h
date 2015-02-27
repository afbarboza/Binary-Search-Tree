#ifndef BSTREE_H
#define BSTREE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "item.h"

/**
* DOC: Binary Search Tree basics
* BSTs are a class of data structures used to implement lookup tables and dynamic sets. 
* They store data items, known as keys, and allow fast insertion and deletion of such keys, 
* as well as checking whether a key is present in a tree.
*
* BSTs are implementd using binary trees, which means that the basic structure of this kind of tree
* is an node, that contains an pointer to an left and right child, beyond a pointer to the 
* information that this node contains.
* In BST, the key stored at the left child of any given node is smaller than the parent and the 
* key stored at the right child of any given node is bigger than the parent. Such rules allows
* operations as insertion, deletion and searching in O(log n).
*
* For more informations about BS Trees, please visit:http://en.wikipedia.org/wiki/Binary_search_tree.
*
*/

typedef struct node NODE;
typedef struct bstree BSTREE;

/*
 * struct node - the basic structure of the tree
 *
 * @item: information stored in the node (key and value).
 * @leftChild: pointer to the node which contains an key immediately smaller
 * 	       than the the actually key of (struct node *) being manipulated.
 * @rightChild: pointer to the node which containt an key immediately bigger
 * 		than the actually key of (struct node *) being manipulated.
 *
 */
struct node {
	ITEM *item;
	struct node *leftChild;
	struct node *rightChild;
};

/*
 * struct bstree - the root of the tree
 *
 * @root: pointer to an (struct node *) which have no parent.
 */
struct bstree {
	NODE *root;
};



/*
 * bstree_new: return an allocated tree with null pointer for the root.
 */
BSTREE *bstree_new(void);


/*
 * bstree_free: frees the memory used.
 *
 * @bstree: pointer to the tree that will be freed. 
 *          No more free calls are necessary, after called this function.
 */
void bstree_free(BSTREE **bstree);


/*
 * bstree_insert - operation of insertion of the tree.
 *
 * @bstree: tree that will receive an new node.
 * @item: the new information to be inserted.
 *
 * This function performs an search operation to find the right position
 * for insertion. Then, allocates an new node and insert at @bstree.
 */
int bstree_insert(BSTREE *bstree, ITEM *item);


/*
 * bstree_remove - operation of remotion of the tree.
 *
 * @bstree: tree that will lose an node.
 * @key: key that pretends to be removed from the tree
 *
 * This function performs an search operation to find the node which contains
 * the @key parameter. Then, remove it from the @bstree.
 */
int bstree_remove(BSTREE *bstree, int key);


/*
 * bstree_search: lookup an given key in an given tree.
 *
 * @bstree: tree used as source of searching.
 * @key: value to be searched int the tree.
 *
 *  This function performs the basic recursive algorithm of search in the tree:
 *  if the actually node contains the @key, return it.
 *  else if key is smaller than the actually node, search at left subtree.
 *  else, search at right subtree.
 *
 *  returns NULL if not found or the item pointer, otherwise.
 */
ITEM *bstree_search(BSTREE *bstree, int key);


/*
 * is_empty - checks whether the tree is empty.
 *
 * returns true if @bstree is empty, false otherwise.
 */
bool is_empty(BSTREE *bstree);


/************************************************************************************
 * Those tree functions: preOrderPrint, postOrderPrint and enOrderPrint	            *
 * are inspired by Knuth algorithms for traversing binary trees.                    *
 *                                                                                  *
 * For more informations, see:                                                      *
 * The Art Of Computer Programming, vol. 1 "Fundamental Algorithms", section 2.3.1  *
 ***********************************************************************************/

/*
 * preOrderPrint - performs the pre-order traversal algorithm
 *
 * @bstree: tree to be printed at standard output.
 * 
 * first, prints the root.
 * then, visit the left subtree.
 * finally, visit the right subtree.
 */
void preOrderPrint(BSTREE *bstree);

/*
 * postOrderPrint - performs the portorder traversal algorithm
 *
 * @bstree: tree to be printed at standard output.
 *
 * first, visit the left subtree,
 * then, prints the root.
 * finally, visit the right subtree.
 */
void postOrderPrint(BSTREE *bstree);

/*
 * enOrderPrint - performs the endorder traversal algorithm
 *
 * @bstree: tree to be printed at standard output.
 *
 * first, visit the left subtree.
 * then, visit the right subtree.
 * finally, prints the root.
 */
void enOrderPrint(BSTREE *bstree);

#endif
