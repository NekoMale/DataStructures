#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

#pragma region Internal
NodeList I_List_GetTail(List list)
{
	if (list->length == 0) return NULL;
	NodeList lastNode = NULL;
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return lastNode;
}

NodeList I_List_GetAt(List list, int index)
{
	if (index < list->length)
	{
		NodeList currentNode = *(list->nodes);
		for (int i = 0; i < index; ++i)
		{
			currentNode = currentNode->next;
		}
		return currentNode;
	}
	return NULL;
}

int I_List_IncreaseSize(List list)
{
	list->capacity *= 2;
	HeadList newNodes = (HeadList)realloc(list->nodes, list->capacity * sizeof(T_NodeList) * list->elementSize);
	if (newNodes)
	{
		list->nodes = newNodes;
		return 0;
	}
	return 1;
}
#pragma endregion Internal

List M_List_New(const size_t elementSize)
{
	List list = malloc(sizeof(T_List));
	if (!list) return NULL;
	list->elementSize = elementSize;
	list->capacity = 5;
	list->length = 0;
	list->nodes = (HeadList)calloc(list->capacity, sizeof(T_NodeList) * elementSize);
	if (!list->nodes) 
	{
		free(list);
		return NULL;
	}
	return list;
}

void* M_List_GetTail(List list)
{
	NodeList node = I_List_GetTail(list);
	if (node) return node->data;
	return NULL;
}

int M_List_Append(List list, void* value)
{
	NodeList element = malloc(sizeof(T_NodeList) * list->elementSize);
	if (!element) return 1;
	element->data = value;
	NodeList tail = I_List_GetTail(list);
	if (!tail)
	{
		*(list->nodes) = element;
	}
	else
	{
		tail->next = element;
	}
	element->next = NULL;
	++list->length;
	if (list->length > list->capacity - 2)
		I_List_IncreaseSize(list);
	return 0;
}

void* M_List_GetAt(List list, int index)
{
	NodeList node = I_List_GetAt(list, index);
	if (node) return node->data;
	return NULL;
}

int M_List_RemoveFirst(List list)
{
	NodeList currentHead = *(list->nodes);
	if (currentHead)
	{
		*(list->nodes) = currentHead->next;
		currentHead->next = NULL;
		--list->length;
		return 0;
	}
	return 1;
}

int M_List_RemoveLast(List list)
{
	if (list->length == 0) return 1;
	NodeList previousNode = NULL;
	NodeList lastNode = NULL;
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		previousNode = lastNode;
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	if (previousNode)
	{
		previousNode->next = NULL;
	}
	else {
		list->nodes = NULL;
		list->nodes = (HeadList)calloc(list->capacity, sizeof(T_NodeList) * list->elementSize);
	}
	--list->length;
	return 0;
}

int M_List_RemoveAt(List list, int index)
{
	if (index == 0)
		return M_List_RemoveFirst(list);
	else if (index < list->length) 
	{
		NodeList lastNode = *(list->nodes);
		NodeList currentNode = lastNode->next;
		for (int i = 1; i < index; ++i)
		{
			lastNode = currentNode;
			currentNode = currentNode->next;
		}
		lastNode->next = currentNode->next;
		currentNode->next = NULL;
		--list->length;
		return 0;
	}
	return 1;
}

void M_List_Remove(List list, NodeList lastNode, NodeList currentNode)
{
	if (lastNode)
	{
		lastNode->next = currentNode->next;
	}
	else {
		*(list->nodes) = currentNode->next;
	}
	currentNode->next = NULL;
	--list->length;
}

int M_List_RemoveIntFromList(List list, int value)
{
	NodeList lastNode = NULL;
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		if (value == *((int*)currentNode->data))
		{
			M_List_Remove(list, lastNode, currentNode);
			return 0;
		}
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return 1;
}

int M_List_RemoveFloatFromList(List list, float value)
{
	NodeList lastNode = NULL;
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		if (value == *((float*)currentNode->data))
		{
			M_List_Remove(list, lastNode, currentNode);
			return 0;
		}
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return 1;
}

int M_List_RemoveStringFromList(List list, char* value)
{
	NodeList lastNode = NULL;
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		if (strcmp(value, (char*)(currentNode->data)) == 0)
		{
			M_List_Remove(list, lastNode, currentNode);
			return 0;
		}
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return 1;
}

void M_List_Reverse(List list) 
{
	List newList = M_List_New(list->elementSize);
	for (int i = list->length - 1; i > -1 ; --i)
	{
		M_List_Append(newList, M_List_GetAt(list, i));
	}
	*(list->nodes) = *(newList->nodes);
}