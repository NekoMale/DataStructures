#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <time.h>
#include "DoubleLinkedList.h"

DoubleListElement GetDoubleListTail(DoubleListHead head) 
{
	DoubleListElement currentNode = *head;
	if (currentNode)
	{
		while (currentNode->next)
		{
			currentNode = currentNode->next;
		}
	}
	return currentNode;
}

DoubleListElement M_AppendToDoubleList(DoubleListHead head, DoubleListElement item)
{
	DoubleListElement tail = GetDoubleListTail(head);
	if (!tail)
	{
		*head = item;
	}
	else
	{
		tail->next = item;
	}
	item->prev = tail;
	item->next = NULL;
	return item;
}

DoubleListElement M_RemoveFromDoubleList(DoubleListHead head, DoubleListElement item)
{
	DoubleListElement prev = item->prev;
	DoubleListElement next = item->next;
	if(prev)
		prev->next = next;
	if(next)
		next->prev = prev;
	item->prev = NULL;
	item->next = NULL;
	return item;
}

DoubleListElement M_InsertIntoDoubleListAfterElement(DoubleListHead head, DoubleListElement itemToAdd, DoubleListElement afterItem)
{
	DoubleListElement next = afterItem->next;
	afterItem->next = itemToAdd;
	itemToAdd->prev = afterItem;
	itemToAdd->next = next;
	if (next)
		next->prev = itemToAdd;
	return itemToAdd;
}

DoubleListElement M_InsertIntoDoubleListBeforeElement(DoubleListHead head, DoubleListElement itemToAdd, DoubleListElement beforeItem)
{
	DoubleListElement prev = beforeItem->prev;
	beforeItem->prev = itemToAdd;
	itemToAdd->next = beforeItem;
	itemToAdd->prev = prev;
	if (prev)
		prev->next = itemToAdd;
	else 
		*head = itemToAdd;
	return itemToAdd;
}

DoubleListElement M_GetDoubleElementAt(DoubleListHead head, int index)
{
	if (index < 0) return NULL;
	DoubleListElement currentNode = *head;
	for (int i = 0; i < index; i++)
	{
		if (!currentNode) return NULL;
		currentNode = currentNode->next;
	}
	return currentNode;
}

int M_Length(DoubleListHead head) {
	int length = 0;
	DoubleListElement currentNode = *head;
	while (currentNode)
	{
		length++;
		currentNode = currentNode->next;
	}
	return length;
}

void M_Shuffle(DoubleListHead head)
{
	srand(time(NULL));
	int max = M_Length(head);
	DoubleListElement currentNode = *head;
	int timesToShuffle = ((rand() % max) + 1) * 2;

	for (int i = 0; i < timesToShuffle; i++)
	{
		int random1 = rand() % max;
		int random2;
		do {
			random2 = rand() % max;
		} while (random2 == random1);

		DoubleListElement element1 = M_GetDoubleElementAt(head, random1);
		DoubleListElement element2 = M_GetDoubleElementAt(head, random2);

		DoubleListElement prev1 = element1->prev;
		DoubleListElement next1 = element1->next;

		DoubleListElement prev2 = element2->prev;
		DoubleListElement next2 = element2->next;

		if (random1 == random2 - 1)
		{
			next1 = element1;
			prev2 = element2;
		}
		else if (random1 == random2 + 1)
		{
			prev1 = element1;
			next2 = element2;
		}
		element1->prev = prev2;
		element1->next = next2;
		element2->prev = prev1;
		element2->next = next1;
		
		if (prev1)
			prev1->next = element2;
		else
			*head = element2;
		
		if (next1)
			next1->prev = element2;
		
		if (prev2)
			prev2->next = element1;
		else
			*head = element1;
		
		if (next2)
			next2->prev = element1;
	}
}