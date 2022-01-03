#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <string.h>
#include "DoubleLinkedListExtension.h"

DoubleStringElement NewDoubleStringItem(const char* string)
{
	DoubleStringElement item = malloc(sizeof(DoubleStringItem));
	if (!item)
	{
		return NULL;
	}
	item->string = string;
	return item;
}

DoubleStringElement M_Clone(DoubleListHead originalHead)
{
	DoubleStringElement cHead = NULL;
	DoubleListElement currentNode = *originalHead;
	while (currentNode)
	{
		DoubleStringElement clonedNode = (DoubleStringElement)malloc(sizeof(DoubleStringElement));
		if (clonedNode)
		{
			memcpy(clonedNode, currentNode, sizeof(DoubleStringItem));
			M_AppendToDoubleList((DoubleListHead)&cHead, (DoubleListElement)clonedNode);
			currentNode = currentNode->next;
		}
		else
			return NULL;
	}
	return cHead;
}