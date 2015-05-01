#ifndef ITEM_H
#define ITEM_H

/*
 * struct item
 *
 * @key: primary key of the item
 * @value: basic information sored. (could be an (void *) pointer to an struct)
 *
 */
typedef struct item ITEM;
struct item {
	int key;
	int value;
};

/*
 * item_new: returns a pointer to an struct item
 *
 */
ITEM *item_new(int key, int value);

/*
 * item_free: frees the memory pointed by item pointer.
 */
void item_free(ITEM **item);

/* 
 * item_copy: returns an pointer to an allocated item which contains the same
 *            informations stored in the @item
 * 
 * @item: pointer which will be copied.
 */
ITEM *item_copy(const ITEM *item);

/*
 * item_print: print at standard output the fields of @item
 *
 * @item: the item to be printed
 */
void item_print(const ITEM *item);

#endif /* ITEM_H */
