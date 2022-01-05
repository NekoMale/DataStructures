#pragma once
#include <stdint.h>

typedef struct S_NodeList
{
	void* data;
	struct S_NodeList* next;
} T_NodeList;

#define NodeList T_NodeList*
#define HeadList NodeList*

typedef struct S_List
{
	HeadList nodes;
	size_t elementSize;
	size_t capacity;
	size_t length;
} T_List;

#define List T_List*


#define List_RemoveValueFromList(list, value) \
	_Generic((value), \
	int: M_List_RemoveIntFromList, \
	char*: M_List_RemoveStringFromList, \
	float: M_List_RemoveFloatFromList) \
	(list, value);

#define List_New(elementType) M_List_New(sizeof(elementType))
#define List_GetTail(list) M_List_GetTail((List) list)
#define List_Append(list, value) M_List_Append((List) list, value)
#define List_GetAt(list, index) M_List_GetAt((List) list, index)
#define List_RemoveFirst(list) M_List_RemoveFirst((List) list)
#define List_RemoveAt(list, index) M_List_RemoveAt((List) list, index)
#define List_RemoveLast(list) M_List_RemoveLast((List) list)
#define List_Reverse(list) M_List_Reverse((List) list)

List M_List_New(const size_t elementSize);
void* M_List_GetTail(List list);
int M_List_Append(List list, void* value);
void* M_List_GetAt(List list, int index);
int M_List_RemoveFirst(List list);
int M_List_RemoveAt(List list, int index);
int M_List_RemoveLast(List list);
void M_List_Reverse(List list);

int M_List_RemoveIntFromList(List list, int value);
int M_List_RemoveFloatFromList(List list, float value);
int M_List_RemoveStringFromList(List list, char* value);