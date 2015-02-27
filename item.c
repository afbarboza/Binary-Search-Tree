#include "item.h"

#include <stdlib.h>
#include <stdio.h>

ITEM *item_new(int key, int value)
{
	ITEM *item = (ITEM *) malloc(sizeof(item));
	if (item == NULL)
		return NULL;
	item->key = key;
	item->value = value;
	return item;
}

void item_free(ITEM **item)
{
	if (item == NULL || *item == NULL)
		return;
	free(*item);
	*item = NULL;
}

ITEM *item_copy(const ITEM *item)
{
	if (item == NULL)
		return NULL;
	return item_new(item->key, item->value);
}

void item_print(const ITEM *item)
{
	if (item == NULL)
		return;
	printf("{key: %d, value: %d}\n", item->key, item->value);
}
