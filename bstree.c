#include "bstree.h"

/* 
 * node_new - allocates an new node structure, and initialize.
 *
 * @item: item to be inserted in the new node created.
 */
static NODE *node_new(ITEM *item);


/*
 * node_free -frees the memory used by @node.
 *
 */
static void node_free(NODE **node);


/*
 * node_insert: performs the algorithm of insertion.
 *
 * @root: node used as parameter to find the right location of insertion.
 * @new_node: the new node which will be inserted in the tree.
 *
 *  node_insert is an auxiliary function to bstree_insert function.
 *  actually, its here where the real insertion happens.
 */
static int node_insert(NODE **root, NODE *new_node);


/*
 * node_remove: an given node.
 *
 * @bst: source from remotion.
 * @root: node that will be constuled
 * @key: the parameter for remotion.
 *
 * this function verifies if @root has the @key parameter, if so
 *     then verify the number of children of @root.
 *     if @root is an leaf node, then call remove_leaf_node.
 *     else if @root have only the left child, then call the promote_left_child function.
 *     else if @root have only the right child, then call the promote_right_child function.
 *     else if @root have two children, then call promote_max_predecessor fucntion.
 *
 * else, performs an traditional search algorithm on the tree, untill find the node.
 */
static int node_remove(BSTREE *bst, NODE **root, int key);


/*
 * node_search: auxiliary function for lookup.
 *
 * @root: root which will be consulted.
 * @key: parameter for the search.
 *
 * this function verifies if @root corresponds to the @key parameter.
 * if yes, return the information stores at @root node.
 * else if key is smaller than the key of @root, search at left subtree.
 * else, search at right subtree.
 */
static ITEM *node_search(NODE *root, int key);


/*
 * detect_children - informs the number of children of an given  @node, 
 * 		     used for remotion algorithm.
 *
 * return LEAF_NODE, if have no children.
 * return ONLY_LCHILD, if have only the left child.
 * return ONLY_RCHILD, if have only the right child,
 * return return BOTH_CHILD, if @node has the left child and right child.
 */
static int detect_children(NODE *node);


/*
 * bstree_free_aux - auxiliary function for remotion. frees the tree,
 *                   starting by an given @node.
 */
static int bstree_free_aux(NODE **node);

/* set of auxiliary functions for the main traversal functions */
static void traversePreOrder(NODE *node);                    // |
static void traverseEndOrder(NODE *node);                    // |
static void traversePostOrder(NODE *node);                   // |
/*-------------------------------------------------------------*/

/*
 * remove_leaf_node - cut an leaf node from the tree.
 *
 *  @root: node that will be removed.
 * 
 *  this function is called by, and only by,  node_remove function.
 *  which means that @root is an leaf node and it needs to be erased.
 *  WARNING: DO NOT call this function from another parts of the code.
 */
static int remove_leaf_node(NODE **root);

/*
 * promote_left_child - promotes the left child of an given node.
 *
 * @root: node which have to be removed, and your left child have
 * 	  to be promoted.
 *
 *  promote_left_child is called by, and only by, node_remove function.
 *  which means that @root is an node that have to be removed but have
 *  only an left child (ONLY_LCHILD). Note that we cannot simply cut @root
 *  from the tree because we will lose the reference to the left child.
 *  WARNING: DO NOT call this function from another parts of the code. 
 */
static int promote_left_child(NODE **root);


/*
 * promote_right_child - promotes the right child of an given node.
 *
 * @root: node which have to be removed, and your right child have
 * 	  to be promoted.
 *
 *  promote_right_child is called by, and only by, node_remove function.
 *  which means that @root is an node that have to be removed but have
 *  only an right child (ONLY_RCHILD). Note that we cannot simply cut @root
 *  from the tree because we will lose the reference to the right child.
 *  WARNING: DO NOT call this function from another parts of the code. 
 */

static int promote_right_child(NODE **root);


/*
 * promote_max_predecessor - replace an given node by the maximum 
 * 			     predecessor on the tree.
 *
 * @root: node which have to be removed but have the both children.
 *
 *  promote_max_predecessor is called by, and only by, node_remove function.
 *  which means that @root is an node that have to be removed but have
 *  the both children (BOTH_CHILD). Note that we cannot simply cut @root
 *  from the tree because we will lose the reference to the children.
 *  so, we find the max predecessor (e.g.: the node which key is immediately smaller), which is
 *  an leaf node, cut it from the tree, and put it in the place of @root.
 *  WARNING: DO NOT call this function from another parts of the code. 
 */
static int promote_max_predecessor(NODE **root);

enum {
	ERROR = -1,
	LEAF_NODE = 0,
	ONLY_LCHILD = 1,
	ONLY_RCHILD = 2,
	BOTH_CHILD = 3
};

BSTREE *bstree_new(void)
{
	BSTREE *new_bstree = (BSTREE *) malloc(sizeof(BSTREE));
	if (new_bstree == NULL) {
		fprintf(stderr, "ERROR: nout enough memory.\n");
		return NULL;
	}

	new_bstree->root = NULL;
	return new_bstree;
}

void bstree_free(BSTREE **bstree)
{
	bstree_free_aux(&((*bstree)->root));
	free(*bstree);
	*bstree = NULL;
}

int bstree_insert(BSTREE *bstree, ITEM *item)
{
	if (bstree == NULL || item == NULL) {
		return 1;
	}

	NODE *new_node = node_new(item);
	return node_insert(&(bstree->root), new_node);
}

int bstree_remove(BSTREE *bstree, int key)
{
	return node_remove(bstree, &(bstree->root), key);
}

ITEM *bstree_search(BSTREE *bstree, int key)
{
	return node_search(bstree->root, key);
}

bool is_empty(BSTREE *bstree)
{
	if (bstree == NULL) {
		fprintf(stderr, "ERROR: null pointer.\n");
		return true;
	}

	return (bstree->root == NULL) ? true : false;
}

void preOrderPrint(BSTREE *bstree)
{
	traversePreOrder(bstree->root);
}

void postOrderPrint(BSTREE *bstree)
{
	traversePostOrder(bstree->root);
}

void enOrderPrint(BSTREE *bstree)
{
	traverseEndOrder(bstree->root);
}

static NODE *node_new(ITEM *item)
{
	if (item == NULL) {
		return NULL;
	}

	NODE *new_node = (NODE *) malloc(sizeof(NODE));
	if (new_node == NULL) {
		fprintf(stderr, "ERROR: not enought memory.\n");
		return NULL;
	}

	new_node->item = item;
	new_node->leftChild = NULL;
	new_node->rightChild = NULL;
	return new_node;
}

static int node_insert(NODE **root, NODE *new_node)
{
	if (root == NULL || new_node == NULL) {
		fprintf(stderr, "ERROR: null pointer.\nat: node_insert.\n");
		return 0;
	}

	if (*root == NULL) {
		*root = new_node;
		return 0;
	} else {
		if (new_node->item->key < (*root)->item->key) {
			return node_insert((&(*root)->leftChild), new_node);
		} else {
			return node_insert((&(*root)->rightChild), new_node);
		}
	}
}

static void traversePreOrder(NODE *node)
{
	if (node == NULL)
		return;

	item_print(node->item);
	traversePreOrder(node->leftChild);
	traversePreOrder(node->rightChild);
}

static void traverseEndOrder(NODE *node)
{
	if (node == NULL)
		return;

	traverseEndOrder(node->leftChild);
	traverseEndOrder(node->rightChild);
	item_print(node->item);
}

static void traversePostOrder(NODE *node)
{
	if (node == NULL)
		return;

	traversePostOrder(node->leftChild);
	item_print(node->item);
	traversePostOrder(node->rightChild);
}

static int node_remove(BSTREE *bst, NODE **root, int key)
{
	if (bst == NULL || root == NULL) {
		fprintf(stderr, "ERROR: null pointer.\n");
		return 1;
	}

	if (*root == NULL) {
		fprintf(stderr, "WARNING: key not found for remotion.\n");
		return 1;
	}

	if (key == (*root)->item->key) {
		int nchildren = detect_children(*root);
		switch(nchildren) {
			case LEAF_NODE:
				remove_leaf_node(root);
				break;
			case ONLY_LCHILD:
				promote_left_child(root);
				break;
			case ONLY_RCHILD:
				promote_right_child(root);
				break;
			case BOTH_CHILD:
				promote_max_predecessor(root);
				break;
		}
		return 0;
	} else if (key < (*root)->item->key) {
		return node_remove(bst, &((*root)->leftChild), key);
	} else {
		return node_remove(bst, &((*root)->rightChild), key);
	}
}

static ITEM *node_search(NODE *root, int key)
{
	if (root == NULL) {
		fprintf(stderr, "WARNING: key not found.\n");
		return NULL;
	}

	if (key == root->item->key) {
		return root->item;
	} else if (key < root->item->key) {
		return node_search(root->leftChild, key);
	} else {
		return node_search(root->rightChild, key);
	}
}

static void node_free(NODE **node)
{
	if (node == NULL || *node == NULL) {
		return;
	}

	(*node)->leftChild = NULL;
	(*node)->rightChild = NULL;
	item_free(&((*node)->item));
	free(*node);
	*node = NULL;
}
static int detect_children(NODE *node)
{
	if (node == NULL) {
		return ERROR;
	}

	if (node->leftChild == NULL && node->rightChild == NULL)
		return LEAF_NODE;
	else if (node->leftChild != NULL && node->rightChild == NULL)
		return ONLY_LCHILD;
	else if (node->leftChild == NULL && node->rightChild != NULL)
		return ONLY_RCHILD;
	else
		return BOTH_CHILD;
}

static int remove_leaf_node(NODE **root)
{
	node_free(root);
	return 0;
}

static int promote_left_child(NODE **root)
{
	if (root == NULL || *root == NULL) {
		fprintf(stderr, "ERROR: null pointer.\n");
		return 1;
	}
	/*copying parameters from left child node*/
	ITEM *itemcpy = (*root)->leftChild->item;
	NODE *leftnodeptr = (*root)->leftChild->leftChild;
	NODE *rightnodeptr = (*root)->leftChild->rightChild;

	/*invalidating pointers*/
	(*root)->leftChild->leftChild = NULL;
	(*root)->leftChild->rightChild = NULL;
	free((*root)->leftChild);
	(*root)->leftChild = NULL;

	/*pasting paramers to the root node*/
	item_free(&((*root)->item));
	(*root)->item = itemcpy;
	(*root)->leftChild = leftnodeptr;
	(*root)->rightChild = rightnodeptr;
	return 0;
}

static int promote_right_child(NODE **root)
{
	if (root == NULL || *root == NULL) {
		fprintf(stderr, "ERROR: null pointer.\n");
		return 1;
	}
	
	ITEM *itemcpy = (*root)->rightChild->item;
	NODE *leftnodeptr = (*root)->rightChild->leftChild;
	NODE *rightnodeptr = (*root)->rightChild->rightChild;

	(*root)->rightChild->leftChild = NULL;
	(*root)->rightChild->rightChild = NULL;
	free((*root)->rightChild);
	(*root)->rightChild = NULL;

	item_free(&((*root)->item));
	(*root)->item = itemcpy;
	(*root)->leftChild = leftnodeptr;
	(*root)->rightChild = rightnodeptr;
	return 0;
}

static int promote_max_predecessor(NODE **root)
{
	if (root == NULL || *root == NULL) {
		fprintf(stderr, "ERROR: null pointer.\n");
		return 1;
	}

	NODE *parent_max_predecessor, *max_predecessor;
	parent_max_predecessor = *root;
	max_predecessor = (*root)->leftChild;

	while(max_predecessor->rightChild != NULL) {
		parent_max_predecessor = max_predecessor;
		max_predecessor = max_predecessor->rightChild;
	}

	item_free(&((*root)->item));
	(*root)->item = max_predecessor->item;
	if (parent_max_predecessor != *root) {
		parent_max_predecessor->rightChild = max_predecessor->leftChild;
		free(max_predecessor);
		return 0;
	} else {
		free((*root)->leftChild);
		(*root)->leftChild = NULL;
		return 0;
	}
}

static int bstree_free_aux(NODE **node)
{
	if (node == NULL) {
		fprintf(stderr, "ERROR: null pointer.\n");
		return 1;
	} else if (*node == NULL) {
		return 0;
	} else {
		bstree_free_aux(&((*node)->leftChild));
		bstree_free_aux(&((*node)->rightChild));
		node_free(node);
		return 0;
	}
}
