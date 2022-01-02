#include <stddef.h> // required for NULL
#include "LinkedList.h"

ListElement GetListTail(ListHead head)
{
	ListElement currentNode = *head;
	ListElement lastNode = NULL;
	while (currentNode)
	{
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return lastNode;
}

ListElement AppendToList(ListHead head, ListElement item)
{
	ListElement tail = GetListTail(head);
	if (!tail)
	{
		*head = item;
	}
	else
	{
		tail->next = item;
	}
	item->next = NULL;
	return item;
}

ListElement PopFromList(ListHead head)
{
	ListElement currentHead = *head;
	if (!currentHead)
	{
		return NULL;
	}
	*head = (*head)->next;
	currentHead->next = NULL;
	return currentHead;
}

ListElement RemoveLastFromList(ListHead head) 
{
	ListElement previousNode = NULL;
	ListElement lastNode = NULL;
	ListElement currentNode = *head;
	while (currentNode) 
	{
		if(lastNode) 
		{
			previousNode = lastNode;
		}
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	if (previousNode)
		previousNode->next = NULL;
	else
		*head = NULL;
	return lastNode;
}

ListElement RemoveItemFromList(ListHead head, ListElement item)
{
	ListElement lastNode = NULL;
	ListElement currentNode = *head;
	while (currentNode) 
	{
		if (currentNode == item) 
		{
			if (lastNode) 
			{
				lastNode->next = currentNode->next;
			}
			else {
				*head = currentNode->next;
			}
			item->next = NULL;
			return item;
		}
		else 
		{
			lastNode = currentNode;
			currentNode = currentNode->next;
		}
	}
	return NULL;
}

void ReverseList(ListHead head) {
	ListElement newHead = NULL;
	ListElement lastElement = RemoveLastFromList(head);
	while (lastElement) 
	{
		AppendToList((ListHead)&newHead, lastElement);
		lastElement = RemoveLastFromList(head);
	}
	*head = newHead;
}