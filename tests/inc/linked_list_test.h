#define CLOVE_SUITE_NAME LinkedListSuite
#include "..\inc\clove.h"
#include "..\..\inc\linked_list.h"

ng_list list;

static int compare_ints(const void* v1, const void* v2) {
	int i1 = *(int*)v1;
	int i2 = *(int*)v2;

	if (i1 < i2) return -1;
	else if (i1 > i2) return 1;
	else return 0;
}

CLOVE_SUITE_SETUP()
{
	list = ng_list_new(int, compare_ints);
}

CLOVE_TEST(ListInitialization)
{
	CLOVE_NOT_NULL(list);
	CLOVE_NOT_NULL(list->nodes);
}

CLOVE_TEST(ListIncreaseCapacity)
{
	ng_list_increase_capacity(list, 5);
	CLOVE_INT_EQ(list->capacity, 10);
}

CLOVE_TEST(ListAddOneElement)
{
	int a = 1;
	CLOVE_INT_EQ(ng_list_add(list, &a), 0);
	CLOVE_INT_EQ(list->length, 1);
	CLOVE_INT_EQ(*(int*)((*list->nodes)->data), 1);
}

CLOVE_TEST(ListGetFirstElement)
{
	int a = 1;
	ng_list_add(list, &a);
	CLOVE_INT_EQ(*(int*)(ng_list_get_at(list, 0)), 1);
}

CLOVE_TEST(ListGetElementOutOfRange)
{
	int a = 1;
	ng_list_add(list, &a);
	CLOVE_NULL(ng_list_get_at(list, -1));
	CLOVE_NULL(ng_list_get_at(list, 1));
	CLOVE_NULL(ng_list_get_at(list, 2));
}

CLOVE_TEST(ListReverse)
{
	int a = 1;
	int b = 2; 
	int c = 3;
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	ng_list reversed_list = ng_list_reverse(list);
	CLOVE_INT_EQ(*(int*)((*reversed_list->nodes)->data), 3);
	CLOVE_INT_EQ(*(int*)((*reversed_list->nodes)->next->data), 2);
	CLOVE_INT_EQ(*(int*)((*reversed_list->nodes)->next->next->data), 1);
}

CLOVE_TEST(ListGetLastElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	CLOVE_INT_EQ(*(int*)ng_list_get_last(list), 3);
}

CLOVE_TEST(ListRemoveFirstElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	CLOVE_INT_EQ(ng_list_remove_first(list), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_INT_EQ(*(int*)((*list->nodes)->data), 2);
}

CLOVE_TEST(ListRemoveSecondElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	CLOVE_INT_EQ(ng_list_remove_at(list, 1), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_INT_EQ(*(int*)((*list->nodes)->next->data), 3);
}

CLOVE_TEST(ListRemoveLastElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	CLOVE_INT_EQ(ng_list_remove_last(list), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_NULL((*list->nodes)->next->next);
}

CLOVE_TEST(ListRemoveElementOutOfRange)
{
	int a = 1;
	ng_list_add(list, &a);
	CLOVE_INT_EQ(ng_list_remove_at(list, -1), -1);
	CLOVE_INT_EQ(ng_list_remove_at(list, 1), -1);
	CLOVE_INT_EQ(ng_list_remove_at(list, 2), -1);
}

CLOVE_TEST(ListRemoveValue)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	CLOVE_INT_EQ(ng_list_remove(list, &b), 0);
	CLOVE_INT_EQ(list->length, 2);
	CLOVE_INT_NE(*(int*)((*list->nodes)->next->data), 2);
}