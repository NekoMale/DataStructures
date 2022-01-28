#define CLOVE_SUITE_NAME LinkedListSuite
#include "..\inc\clove.h"
#include "..\..\inc\LinkedList.h"

NG_List list;

static int Compare_Ints(const void* v1, const void* v2) {
	int i1 = *(int*)v1;
	int i2 = *(int*)v2;

	if (i1 < i2) return -1;
	else if (i1 > i2) return 1;
	else return 0;
}

CLOVE_SUITE_SETUP()
{
	list = NG_List_New(int, Compare_Ints);
}

CLOVE_TEST(ListInitialization)
{
	CLOVE_NOT_NULL(list);
	CLOVE_NOT_NULL(list->nodes);
}

CLOVE_TEST(ListIncreaseCapacity)
{
	NG_List_Increase_Capacity(list, 5);
	CLOVE_INT_EQ(list->capacity, 10);
}

CLOVE_TEST(ListAddOneElement)
{
	int a = 1;
	CLOVE_INT_EQ(NG_List_Add(list, &a), 0);
	CLOVE_INT_EQ(list->length, 1);
	CLOVE_INT_EQ(*(int*)((*list->nodes)->data), 1);
}

CLOVE_TEST(ListGetFirstElement)
{
	int a = 1;
	NG_List_Add(list, &a);
	CLOVE_INT_EQ(*(int*)(NG_List_GetAt(list, 0)), 1);
}

CLOVE_TEST(ListGetElementOutOfRange)
{
	int a = 1;
	NG_List_Add(list, &a);
	CLOVE_NULL(NG_List_GetAt(list, -1));
	CLOVE_NULL(NG_List_GetAt(list, 1));
	CLOVE_NULL(NG_List_GetAt(list, 2));
}

CLOVE_TEST(ListReverse)
{
	int a = 1;
	int b = 2; 
	int c = 3;
	NG_List_Add(list, &a);
	NG_List_Add(list, &b);
	NG_List_Add(list, &c);
	NG_List reversed_list = NG_List_Reverse(list);
	CLOVE_INT_EQ(*(int*)((*reversed_list->nodes)->data), 3);
	CLOVE_INT_EQ(*(int*)((*reversed_list->nodes)->next->data), 2);
	CLOVE_INT_EQ(*(int*)((*reversed_list->nodes)->next->next->data), 1);
}

CLOVE_TEST(ListGetLastElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	NG_List_Add(list, &a);
	NG_List_Add(list, &b);
	NG_List_Add(list, &c);
	CLOVE_INT_EQ(*(int*)NG_List_GetLast(list), 3);
}

CLOVE_TEST(ListRemoveFirstElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	NG_List_Add(list, &a);
	NG_List_Add(list, &b);
	NG_List_Add(list, &c);
	CLOVE_INT_EQ(NG_List_RemoveFirst(list), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_INT_EQ(*(int*)((*list->nodes)->data), 2);
}

CLOVE_TEST(ListRemoveSecondElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	NG_List_Add(list, &a);
	NG_List_Add(list, &b);
	NG_List_Add(list, &c);
	CLOVE_INT_EQ(NG_List_RemoveAt(list, 1), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_INT_EQ(*(int*)((*list->nodes)->next->data), 3);
}

CLOVE_TEST(ListRemoveLastElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	NG_List_Add(list, &a);
	NG_List_Add(list, &b);
	NG_List_Add(list, &c);
	CLOVE_INT_EQ(NG_List_RemoveLast(list), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_NULL((*list->nodes)->next->next);
}

CLOVE_TEST(ListRemoveElementOutOfRange)
{
	int a = 1;
	NG_List_Add(list, &a);
	CLOVE_INT_EQ(NG_List_RemoveAt(list, -1), -1);
	CLOVE_INT_EQ(NG_List_RemoveAt(list, 1), -1);
	CLOVE_INT_EQ(NG_List_RemoveAt(list, 2), -1);
}

CLOVE_TEST(ListRemoveValue)
{
	int a = 1;
	int b = 2;
	int c = 3;
	NG_List_Add(list, &a);
	NG_List_Add(list, &b);
	NG_List_Add(list, &c);
	CLOVE_INT_EQ(NG_List_Remove(list, &b), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_INT_NE(*(int*)((*list->nodes)->next->data), 2);
}