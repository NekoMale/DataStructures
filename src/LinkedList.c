#include <stddef.h> // required for NULL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "..\inc\LinkedList.h"

NG_List __NG_List_New(const size_t elementSize, int(*compare_function)(const void* v1, const void* v2))
{
	NG_List list = malloc(sizeof(NG_T_List));
	if (!list) return NULL;
	list->elementSize = elementSize;
	list->capacity = 5;
	list->length = 0;
	list->compare_function = compare_function;
	list->nodes = (NG_HeadList)calloc(list->capacity, sizeof(NG_T_NodeList) * elementSize);
	if (!list->nodes) 
	{
		free(list);
		return NULL;
	}
	return list;
}

int __NG_List_Increase_Capacity(NG_List list, const size_t capacity_increase_amount)
{
	list->capacity += capacity_increase_amount;
	NG_HeadList newNodes = (NG_HeadList)realloc(list->nodes, list->capacity * sizeof(NG_T_NodeList) * list->elementSize);
	if (!newNodes)
	{
		return -1;
	}
	list->nodes = newNodes;
	return 0;
}

int __NG_List_Add(NG_List list, void* value)
{
	NG_NodeList element = malloc(sizeof(NG_T_NodeList) * list->elementSize);
	if (!element) return -1;
	element->data = value;
	NG_NodeList tail = *(list->nodes);
	if (!tail)
	{
		*(list->nodes) = element;
	}
	else
	{
		while (tail->next)
		{
			tail = tail->next;
		}
		tail->next = element;
	}
	element->next = NULL;
	++list->length;
	if (list->length > list->capacity - 2)
		__NG_List_Increase_Capacity(list, list->capacity);
	return 0;
}

void* __NG_List_GetAt(NG_List list, int index)
{
	if (index < 0 || index >= list->length)
	{
		return NULL;
	}

	NG_NodeList currentNode = *(list->nodes);
	for (int i = 0; i < index; ++i)
	{
		currentNode = currentNode->next;
	}
	return currentNode->data;
}

void* __NG_List_GetLast(NG_List list)
{
	return __NG_List_GetAt(list, list->length - 1);
}

int __NG_List_RemoveAt(NG_List list, int index)
{
	if (index < 0 || index >= list->length)
	{
		return -1;
	}
	
	NG_NodeList last_node = *list->nodes;
	if (index == 0)
	{
		*list->nodes = last_node->next;
		last_node->next = NULL;
	}
	else
	{
		NG_NodeList current_node = last_node->next;
		for (int i = 1; i < index; ++i)
		{
			last_node = current_node;
			current_node = current_node->next;
		}
		last_node->next = current_node->next;
		current_node->next = NULL;
	}
	--(list->length);
	return 0;
}

int __NG_List_RemoveFirst(NG_List list)
{
	return __NG_List_RemoveAt(list, 0);
}

int __NG_List_RemoveLast(NG_List list)
{
	return __NG_List_RemoveAt(list, list->length - 1);
}

int __NG_List_Remove(NG_List list, void* value_to_remove)
{
	NG_NodeList last_node;
	NG_NodeList current_node = *list->nodes;
	while (current_node)
	{
		if (list->compare_function(value_to_remove, current_node->data) == 0)
		{
			if (last_node)
			{
				last_node->next = current_node->next;
			}
			else
			{
				*list->nodes = current_node->next;
			}
			current_node->next = NULL;
			--(list->length);
			return 0;
		}
		last_node = current_node;
		current_node = current_node->next;
	}
	return -1;
}

NG_List __NG_List_Reverse(NG_List list) 
{
	NG_List reversed_list = __NG_List_New(list->elementSize, list->compare_function);
	for (int i = list->length - 1; i > -1 ; --i)
	{
		__NG_List_Add(reversed_list, __NG_List_GetAt(list, i));
	}
	return reversed_list;
}