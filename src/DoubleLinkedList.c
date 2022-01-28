#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <time.h>
#include "..\inc\DoubleLinkedList.h"

int M_DoubleList_IncreaseCapacity(DoubleList doubleList, int capacityDelta)
{
	if (capacityDelta < 1)
		return -1;

	HeadDoubleList newHead = (HeadDoubleList)realloc(doubleList->head, (doubleList->capacity + capacityDelta) * sizeof(T_NodeDoubleList) * doubleList->elementSize);
	if (!newHead)
		return -1;
	
	HeadDoubleList newTail = (HeadDoubleList)realloc(doubleList->tail, (doubleList->capacity + capacityDelta) * sizeof(T_NodeDoubleList) * doubleList->elementSize);
	if (!newTail)
	{
		free(newHead);
		return -1;
	}
	doubleList->head = newHead;
	doubleList->tail = newTail;

	doubleList->capacity += capacityDelta;
	return 0;
}

NodeDoubleList I_DoubleList_NewNode(const size_t elementSize, void* value)
{
	NodeDoubleList newElement = malloc(sizeof(T_NodeDoubleList) * elementSize);
	if (!newElement) return NULL;
	newElement->data = value;
	return newElement;
}

NodeDoubleList I_DoubleList_GetAt(DoubleList doubleList, int index)
{
	if (doubleList->length == 0)
		return NULL;
	if (index < 0 || index >= doubleList->length)
		return NULL;

	if (index == 0)
		return (*doubleList->head);
	if (index == doubleList->length - 1)
		return (*doubleList->tail);
	NodeDoubleList currentNode;
	if (index > (int)(doubleList->length * 0.5f))
	{
		currentNode = *doubleList->tail;
		for (int i = doubleList->length - 1; i > index; --i)
		{
			currentNode = currentNode->prev;
		}
	}
	else
	{
		currentNode = *doubleList->head;
		for (int i = 0; i < index; ++i)
		{
			currentNode = currentNode->next;
		}
	}
	return currentNode;
}

int I_DoubleList_InsertFirst(DoubleList doubleList, void* value)
{
	NodeDoubleList newElement = I_DoubleList_NewNode(doubleList->elementSize, value);
	if (!newElement)
		return -1;
	(*doubleList->head)->prev = newElement;
	newElement->next = (*doubleList->head);
	newElement->prev = NULL;
	(*doubleList->head) = newElement;
	++doubleList->length;
	if (doubleList->length > (int)(doubleList->capacity * 0.5f))
		M_DoubleList_IncreaseCapacity(doubleList, doubleList->capacity);
	return 0;
}

int I_DoubleList_InsertLast(DoubleList doubleList, void* value)
{
	NodeDoubleList newElement = I_DoubleList_NewNode(doubleList->elementSize, value);
	if (!newElement)
		return -1;
	newElement->prev = (*doubleList->tail);
	newElement->next = NULL;
	(*doubleList->tail)->next = newElement;
	(*doubleList->tail) = newElement;
	++doubleList->length;
	if (doubleList->length > (int)(doubleList->capacity * 0.5f))
		M_DoubleList_IncreaseCapacity(doubleList, doubleList->capacity);
	return 0;
}

int I_DoubleList_InsertBefore(DoubleList doubleList, NodeDoubleList currentNode, void* value)
{
	NodeDoubleList newElement = I_DoubleList_NewNode(doubleList->elementSize, value);
	if (!newElement)
		return -1;
	newElement->next = currentNode;
	newElement->prev = currentNode->prev;
	newElement->prev->next = newElement;
	currentNode->prev = newElement;
	++doubleList->length;
	if (doubleList->length > (int)(doubleList->capacity * 0.5f))
		M_DoubleList_IncreaseCapacity(doubleList, doubleList->capacity);
	return 0;
}

int I_DoubleList_InsertAfter(DoubleList doubleList, NodeDoubleList currentNode, void* value)
{
	NodeDoubleList newElement = I_DoubleList_NewNode(doubleList->elementSize, value);
	if (!newElement)
		return -1;
	newElement->prev = currentNode;
	newElement->next = currentNode->next;
	newElement->next->prev = newElement;
	currentNode->next = newElement;
	++doubleList->length;
	if (doubleList->length > (int)(doubleList->capacity * 0.5f))
		M_DoubleList_IncreaseCapacity(doubleList, doubleList->capacity);
	return 0;
}

int M_DoubleList_InsertBefore(DoubleList doubleList, void* valueToInsert, void* valueToCheck)
{
	if (doubleList->length == 0)
		return -1;
	if ((*doubleList->head)->data == valueToCheck)
	{
		return I_DoubleList_InsertFirst(doubleList, valueToInsert);
	}
	else
	{
		if ((*doubleList->tail)->data == valueToCheck)
		{
			return I_DoubleList_InsertBefore(doubleList, (*doubleList->tail), valueToInsert);
		}
		NodeDoubleList currentNode = (*doubleList->head)->next;
		while (currentNode)
		{
			if (currentNode->data == valueToCheck)
			{
				return I_DoubleList_InsertBefore(doubleList, currentNode, valueToInsert);
			}
		}
	}
	return -1;
}

int M_DoubleList_InsertAfter(DoubleList doubleList, void* valueToInsert, void* valueToCheck)
{
	if (doubleList->length == 0)
		return -1;
	if ((*doubleList->tail)->data == valueToCheck)
	{
		return I_DoubleList_InsertLast(doubleList, valueToInsert);
	}
	else
	{
		if ((*doubleList->head)->data == valueToCheck)
		{
			return I_DoubleList_InsertAfter(doubleList, (*doubleList->head), valueToInsert);
		}
		NodeDoubleList currentNode = (*doubleList->head)->next;
		while (currentNode)
		{
			if (currentNode->data == valueToCheck)
			{
				return I_DoubleList_InsertAfter(doubleList, currentNode, valueToInsert);
			}
		}
	}
	return -1;
}

DoubleList M_DoubleList_New(const size_t elementSize)
{
	DoubleList doubleList = malloc(sizeof(T_DoubleList));
	if (!doubleList)
		return NULL;
	doubleList->elementSize = elementSize;
	doubleList->capacity = 5;
	doubleList->length = 0;
	doubleList->head = (HeadDoubleList)calloc(doubleList->capacity, sizeof(T_NodeDoubleList) * elementSize);
	if (!doubleList->head)
	{
		free(doubleList);
		return NULL;
	}
	doubleList->tail = (HeadDoubleList)calloc(doubleList->capacity, sizeof(T_NodeDoubleList) * elementSize);
	if (!doubleList->tail)
	{
		free(doubleList->head);
		free(doubleList);
		return NULL;
	}
	return doubleList;
}

void* M_DoubleList_GetAt(DoubleList doubleList, int index)
{
	NodeDoubleList node = I_DoubleList_GetAt(doubleList, index);
	if (!node) return NULL;
	return node->data;
}

int M_DoubleList_Append(DoubleList doubleList, void* value)
{
	if (doubleList->length == 0)
	{
		NodeDoubleList element = I_DoubleList_NewNode(doubleList->elementSize, value);
		if (!element)
			return -1;
		*(doubleList->head) = element;
		*(doubleList->tail) = element;
		element->prev = NULL;
		element->next = NULL;
		++(doubleList->length);
		if (doubleList->length > (int)(doubleList->capacity * 0.5f))
			M_DoubleList_IncreaseCapacity(doubleList, doubleList->capacity);
	}
	else {
		return I_DoubleList_InsertLast(doubleList, value);
	}
	return 0;
}

void M_DoubleList_SwitchElements(DoubleList doubleList, int index1, int index2)
{
	NodeDoubleList node1 = I_DoubleList_GetAt(doubleList, index1);
	NodeDoubleList node2 = I_DoubleList_GetAt(doubleList, index2);
	void* app = node1->data;
	node1->data = node2->data;
	node2->data = app;
}

DoubleList M_DoubleList_Clone(DoubleList originalDoubleList)
{
	DoubleList clonedDoubleList = M_DoubleList_New(originalDoubleList->elementSize);
	NodeDoubleList currentNode = (*originalDoubleList->head);

	while (currentNode)
	{
		M_DoubleList_Append(clonedDoubleList, currentNode->data);
		currentNode = currentNode->next;
	}

	return clonedDoubleList;
}

DoubleList M_DoubleList_Shuffle(DoubleList doubleList)
{
	DoubleList shuffledDoubleList = M_DoubleList_Clone(doubleList);

	srand(time(NULL));
	int max = doubleList->length;
	int timesToShuffle = (int)(doubleList->length * 0.5f);

	for (int i = 0; i < timesToShuffle; ++i) 
	{
		int random1 = rand() % max;
		int random2;
		do
		{
			random2 = rand() % max;
		} while (random1 == random2);

		M_DoubleList_SwitchElements(shuffledDoubleList, random1, random2);
	}
	return shuffledDoubleList;
}

int M_DoubleList_RemoveAt(DoubleList doubleList, int index)
{
	if (doubleList->length == 0)
		return -1;
	if (index < 0 || index >= doubleList->length)
		return -1;

	if (doubleList->length == 1)
	{
		*doubleList->head = NULL;
		*doubleList->tail = NULL;
	}
	else 
	{
		NodeDoubleList currentNode;
		if (index == 0)
		{
			currentNode = *doubleList->head;
			*doubleList->head = currentNode->next;
		}
		else if (index == doubleList->length - 1) 
		{
			currentNode = *doubleList->tail;
			*doubleList->tail = currentNode->prev;
		}
		else
		{
			NodeDoubleList lastNode = *doubleList->head;
			currentNode = lastNode->next;
			for (int i = 1; i < index; ++i)
			{
				lastNode = currentNode;
				currentNode = currentNode->next;
			}
			lastNode->next = currentNode->next;
			currentNode->next->prev = lastNode;
		}
		currentNode->next = NULL;
		currentNode->prev = NULL;
	}
	--doubleList->length;
	return 0;
}