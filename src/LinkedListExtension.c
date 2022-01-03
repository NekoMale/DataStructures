#include <stddef.h> // required for NULL
#include <stdlib.h>
#include "LinkedListExtension.h"

StringElement NewStringItem(const char* string)
{
	StringElement item = malloc(sizeof(StringItem));
	if (!item)
	{
		return NULL;
	}
	item->string = string;
	return item;
}
