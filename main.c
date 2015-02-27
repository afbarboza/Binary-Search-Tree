#include "bstree.h"

int main(void)
{
	BSTREE *my_tree = bstree_new();
	bstree_insert(my_tree, item_new(6, 6));
	bstree_insert(my_tree, item_new(4, 4));
	bstree_insert(my_tree, item_new(8, 8));
	bstree_insert(my_tree, item_new(2, 2));
	bstree_insert(my_tree, item_new(5, 5));
	bstree_insert(my_tree, item_new(10, 10));
	printf("\n\n---> initial: \n");
	preOrderPrint(my_tree);
	bstree_remove(my_tree, 6);
	printf("\n\n---> final: \n");
	preOrderPrint(my_tree);
	printf("\nsearch for key <<5>>:\n");
	ITEM *lookup = bstree_search(my_tree, 5);
	if (lookup != NULL) {
		item_print(lookup);
	} else {
		printf("key not found.\n");
	}
	bstree_free(&my_tree);
	return 0;
}
