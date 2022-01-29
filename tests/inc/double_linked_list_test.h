#define CLOVE_SUITE_NAME DoubleLinkedListSuite
#include "..\inc\clove.h"
#include "..\..\inc\double_linked_list.h"

ng_double_list double_list;

int n = 0;
static int fake_rand()
{
	if (n == 2)
	{
		n = 0;
	}
	return n++;
}

static int Compare_Ints(const void* v1, const void* v2) {
	int i1 = *(int*)v1;
	int i2 = *(int*)v2;

	if (i1 < i2) return -1;
	else if (i1 > i2) return 1;
	else return 0;
}

CLOVE_SUITE_SETUP()
{
	double_list = ng_double_list_new(int, Compare_Ints);
}

CLOVE_TEST(DoubleListInitialization)
{
	CLOVE_NOT_NULL(double_list);
	CLOVE_NOT_NULL(double_list->head);
	CLOVE_NOT_NULL(double_list->tail);
}

CLOVE_TEST(DoubleListIncreaseCapacity)
{
	CLOVE_INT_EQ(ng_double_list_increase_capacity(double_list, 10), 0);
	CLOVE_INT_EQ(double_list->capacity, 15);
}

CLOVE_TEST(DoubleListIncreaseCapacityBy0)
{
	ng_double_list_increase_capacity(double_list, 0);
	CLOVE_INT_EQ(double_list->capacity, 5);
}

CLOVE_TEST(DoubleListIncreaseCapacityByNegativeNumber)
{
	CLOVE_INT_EQ(ng_double_list_increase_capacity(double_list, -5), -1);
	CLOVE_INT_EQ(double_list->capacity, 5);
}

CLOVE_TEST(DoubleListAddOneElement)
{
	int a = 1;
	CLOVE_INT_EQ(ng_double_list_add(double_list, &a), 0);
	CLOVE_INT_EQ(*(int*)(*double_list->head)->data, 1);
	CLOVE_INT_EQ(*(int*)(*double_list->tail)->data, 1);
}

CLOVE_TEST(DoubleListAddTwoElement)
{
	int a = 1;
	int b = 2;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	CLOVE_INT_EQ(*(int*)(*double_list->head)->data, 1);
	CLOVE_INT_EQ(*(int*)(*double_list->tail)->data, 2);
}

CLOVE_TEST(DoubleListRemoveFirstElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_remove_at(double_list, 0);
	CLOVE_INT_EQ(*(int*)(*double_list->head)->data, 2);
	CLOVE_INT_EQ(double_list->length, 2);
}

CLOVE_TEST(DoubleListRemoveLastElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_remove_at(double_list, 2);
	CLOVE_INT_EQ(*(int*)(*double_list->tail)->data, 2);
	CLOVE_INT_EQ(double_list->length, 2);
}

CLOVE_TEST(DoubleListRemoveElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_remove_at(double_list, 1);
	CLOVE_INT_EQ(*(int*)(*double_list->head)->data, 1);
	CLOVE_INT_EQ(*(int*)(*double_list->tail)->data, 3);
	CLOVE_INT_EQ(*(int*)(*double_list->head)->next->data, 3);
	CLOVE_INT_EQ(*(int*)(*double_list->tail)->prev->data, 1);
	CLOVE_INT_EQ(double_list->length, 2);
}

CLOVE_TEST(DoubleListInsertAfterElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	int d = 4;
	ng_double_list_add_after(double_list, &d, &b);
	CLOVE_INT_EQ(*(int*)(*double_list->head)->next->next->data, 4);
	CLOVE_INT_EQ(*(int*)(*double_list->tail)->prev->data, 4);
	CLOVE_INT_EQ(double_list->length, 4);
}

CLOVE_TEST(DoubleListInsertAfterTail)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	int d = 4;
	ng_double_list_add_after(double_list, &d, &c);
	CLOVE_INT_EQ(4, *(int*)(*double_list->head)->next->next->next->data);
	CLOVE_INT_EQ(4, *(int*)(*double_list->tail)->data);
	CLOVE_INT_EQ(4, double_list->length);
}

CLOVE_TEST(DoubleListInsertBeforeElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	int d = 4;
	ng_double_list_add_before(double_list, &d, &b);
	CLOVE_INT_EQ(4, *(int*)(*double_list->head)->next->data);
	CLOVE_INT_EQ(4, *(int*)(*double_list->tail)->prev->prev->data);
	CLOVE_INT_EQ(4, double_list->length);
}

CLOVE_TEST(DoubleListInsertBeforeHead)
{
	int a = 1;
	int b = 2;
	int c = 3;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	int d = 4;
	ng_double_list_add_before(double_list, &d, &a);
	CLOVE_INT_EQ(4, *(int*)(*double_list->head)->data);
	CLOVE_INT_EQ(4, *(int*)(*double_list->tail)->prev->prev->prev->data);
	CLOVE_INT_EQ(4, double_list->length);
}

CLOVE_TEST(DoubleListFakeShuffle)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_add(double_list, &d);
	ng_double_list shuffled_double_list = ng_double_list_shuffle_pick_function(double_list, 1, fake_rand);
	CLOVE_INT_EQ(1, *(int*)(*double_list->head)->data);
	CLOVE_INT_EQ(2, *(int*)(*double_list->head)->next->data);
	CLOVE_INT_EQ(2, *(int*)(*shuffled_double_list->head)->data);
	CLOVE_INT_EQ(1, *(int*)(*shuffled_double_list->head)->next->data);
}

CLOVE_TEST(DoubleListRealShuffle)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_add(double_list, &d);
	ng_double_list shuffled_double_list = ng_double_list_shuffle(double_list);
	CLOVE_NOT_NULL(shuffled_double_list);
	CLOVE_INT_EQ(double_list->length, shuffled_double_list->length);
}

CLOVE_TEST(DoubleListGetFirstElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_add(double_list, &d);
	int element = *(int*)ng_double_list_get_at(double_list, 0);
	CLOVE_INT_EQ(1, element);
}

CLOVE_TEST(DoubleListGetLastElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_add(double_list, &d);
	int element = *(int*)ng_double_list_get_at(double_list, 3);
	CLOVE_INT_EQ(4, element);
}

CLOVE_TEST(DoubleListGetElement)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_add(double_list, &d);
	ng_double_list_add(double_list, &e);
	int element = *(int*)ng_double_list_get_at(double_list, 3);
	CLOVE_INT_EQ(4, element);
}

CLOVE_TEST(DoubleListGetElementOutOfRange)
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	ng_double_list_add(double_list, &a);
	ng_double_list_add(double_list, &b);
	ng_double_list_add(double_list, &c);
	ng_double_list_add(double_list, &d);
	CLOVE_NULL(ng_double_list_get_at(double_list, 4));
	CLOVE_NULL(ng_double_list_get_at(double_list, 5));
}


//CLOVE_TEST(DoubleListAutoIncreaseCapacity)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//
//	CLOVE_INT_EQ(doubleList->capacity, 10);
//
//	int d = 4;
//	DoubleList_Append(doubleList, &d);
//
//	CLOVE_INT_EQ(doubleList->capacity, 10);
//}
//#pragma endregion IncreaseCapacity
//
//#pragma region Append
//CLOVE_TEST(DoubleListAddNotFail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	CLOVE_INT_EQ(DoubleList_Append(doubleList, &a), 0);
//}
//
//CLOVE_TEST(DoubleListAddOneElementHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a);
//	void* value = (*doubleList->head)->data;
//	CLOVE_INT_EQ(*(int*)((*doubleList->head)->data), 1);
//}
//
//CLOVE_TEST(DoubleListAddOneElementTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a);
//	CLOVE_INT_EQ(*(int*)(*doubleList->tail)->data, 1);
//}
//
//CLOVE_TEST(DoubleListAddTwoElementHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	CLOVE_INT_EQ(*(int*)(*doubleList->head)->data, 1);
//}
//
//CLOVE_TEST(DoubleListAddTwoElementTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	CLOVE_INT_EQ(*(int*)(*doubleList->tail)->data, 2);
//}
//
//CLOVE_TEST(DoubleListAddFourElementsCheckThird)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	int thirdValue = *(int*)(*doubleList->head)->next->next->data;
//	CLOVE_INT_EQ(thirdValue, 3);
//}
//#pragma endregion Append
//
//#pragma region Remove
//CLOVE_TEST(DoubleListRemoveFromEmptyList)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 0), -1);
//}
//
//CLOVE_TEST(DoubleListRemoveAtNegativeIndex)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a);
//	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, -1), -1);
//}
//
//CLOVE_TEST(DoubleListRemoveAtLengthAsIndex)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a);
//	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 1), -1);
//}
//
//CLOVE_TEST(DoubleListRemoveAtIndexGreaterThenLength)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a);
//	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 2), -1);
//}
//
//CLOVE_TEST(DoubleListRemoveUniqueElementSucceeded)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a);
//	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 0), 0);
//}
//
//CLOVE_TEST(DoubleListRemoveUniqueElementHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a); 
//	DoubleList_RemoveAt(doubleList, 0);
//	CLOVE_NULL((*doubleList->head));
//}
//
//CLOVE_TEST(DoubleListRemoveUniqueElementTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	DoubleList_Append(doubleList, &a); 
//	DoubleList_RemoveAt(doubleList, 0);
//	CLOVE_NULL((*doubleList->tail));
//}
//
//CLOVE_TEST(DoubleListRemoveHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_RemoveAt(doubleList, 0);
//	CLOVE_INT_EQ(*(int*)(*doubleList->head)->data, 2);
//}
//
//CLOVE_TEST(DoubleListRemoveTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_RemoveAt(doubleList, 3);
//	CLOVE_INT_EQ(*(int*)(*doubleList->tail)->data, 3);
//}
//#pragma endregion Remove
//
//#pragma region Retrieving
//CLOVE_TEST(DoubleListGetFirstElement)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 0), 1);
//}
//
//CLOVE_TEST(DoubleListGetLastElement)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 4), 5);
//}
//
//CLOVE_TEST(DoubleListGetLowerHalfElement)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 2);
//}
//
//CLOVE_TEST(DoubleListGetUpperHalfElement)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 3), 4);
//}
//
//CLOVE_TEST(DoubleListGetHalfElement)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 2), 3);
//}
//#pragma endregion Retrieving
//
//#pragma region Shuffle & Cloning
//CLOVE_TEST(DoubleListCloning)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//
//	ng_double_list shuffledList = DoubleList_Clone(doubleList);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 1);
//}
//
//CLOVE_TEST(DoubleListTwoElementsSwitchingElements)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	ng_double_list shuffledList = DoubleList_Clone(doubleList);
//	DoubleList_SwitchElements(shuffledList, 0, 1);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 2);
//}
//
//CLOVE_TEST(DoubleListSwitchingElements)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//
//	ng_double_list shuffledList = DoubleList_Clone(doubleList);
//	DoubleList_SwitchElements(shuffledList, 0, 3);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 4);
//}
//
//CLOVE_TEST(DoubleListDoubleSwitchingElements)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	int c = 3;
//	int d = 4;
//	int e = 5;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//	DoubleList_Append(doubleList, &c);
//	DoubleList_Append(doubleList, &d);
//	DoubleList_Append(doubleList, &e);
//
//	ng_double_list shuffledList = DoubleList_Clone(doubleList);
//	DoubleList_SwitchElements(shuffledList, 0, 3);
//	DoubleList_SwitchElements(shuffledList, 3, 0);
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 1);
//}
//#pragma endregion Shuffle & Cloning
//
//#pragma region InsertAfter
//CLOVE_TEST(DoubleListInsertAfterHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertAfter(doubleList, &c, &a);
//	
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 3);
//}
//
//CLOVE_TEST(DoubleListInsertAfterHeadCheckHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertAfter(doubleList, &c, &a);
//	
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 0), 1);
//}
//
//CLOVE_TEST(DoubleListInsertAfterTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertAfter(doubleList, &c, &b);
//
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 2), 3);
//}
//
//CLOVE_TEST(DoubleListInsertAfterTailCheckOldTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertAfter(doubleList, &c, &b);
//
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 2);
//}
//
//CLOVE_TEST(DoubleListInsertBeforeHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertBefore(doubleList, &c, &a);
//
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 0), 3);
//}
//
//CLOVE_TEST(DoubleListInsertBeforeHeadCheckOldHead)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertBefore(doubleList, &c, &a);
//
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 1);
//}
//
//CLOVE_TEST(DoubleListInsertBeforeTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertBefore(doubleList, &c, &b);
//
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 3);
//}
//
//CLOVE_TEST(DoubleListInsertBeforeTailCheckTail)
//{
//	ng_double_list doubleList = ng_double_list_new(int);
//	int a = 1;
//	int b = 2;
//	DoubleList_Append(doubleList, &a);
//	DoubleList_Append(doubleList, &b);
//
//	int c = 3;
//	DoubleList_InsertBefore(doubleList, &c, &b);
//
//	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 2), 2);
//}
//#pragma endregion InsertAfter