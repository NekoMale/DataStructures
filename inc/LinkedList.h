#pragma once
#include <stdint.h>

typedef struct NG_S_NodeList
{
	void* data;
	struct NG_S_NodeList* next;
} NG_T_NodeList;

typedef NG_T_NodeList* NG_NodeList;
typedef NG_NodeList* NG_HeadList;

typedef struct NG_S_List
{
	NG_HeadList nodes;
	size_t elementSize;
	size_t capacity;
	size_t length;
	int(*compare_function)(const void*, const void*);
} NG_T_List;

typedef NG_T_List* NG_List;

#define NG_List_New(elementType, compare_function) __NG_List_New(sizeof(elementType), compare_function)
#define NG_List_Increase_Capacity(list, capacity_increase_amount) __NG_List_Increase_Capacity((NG_List)list, capacity_increase_amount)
#define NG_List_Add(list, value) __NG_List_Add((NG_List) list, value)
#define NG_List_GetAt(list, index) __NG_List_GetAt((NG_List) list, index)
#define NG_List_Reverse(list) __NG_List_Reverse((NG_List) list)
#define NG_List_GetLast(list) __NG_List_GetLast((NG_List) list)
#define NG_List_RemoveFirst(list) __NG_List_RemoveFirst((NG_List) list)
#define NG_List_RemoveAt(list, index) __NG_List_RemoveAt((NG_List) list, index)
#define NG_List_RemoveLast(list) __NG_List_RemoveLast((NG_List) list)
#define NG_List_Remove(list, value_to_remove) __NG_List_Remove((NG_List) list, value_to_remove)


NG_List __NG_List_New(const size_t elementSize, int(*compare_function)(const void* v1, const void* v2));
int __NG_List_Increase_Capacity(NG_List list, const size_t capacity_increase_amount);
int __NG_List_Add(NG_List list, void* value);
void* __NG_List_GetAt(NG_List list, int index);
NG_List __NG_List_Reverse(NG_List list);
void* __NG_List_GetLast(NG_List list);
int __NG_List_RemoveFirst(NG_List list);
int __NG_List_RemoveAt(NG_List list, int index);
int __NG_List_RemoveLast(NG_List list);
int __NG_List_Remove(NG_List list, void* value_to_remove);