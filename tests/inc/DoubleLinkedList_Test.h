#include "..\inc\clove.h"
#include "..\..\inc\DoubleLinkedList.h"

#pragma region Initialization
CLOVE_TEST(DoubleListNotNULL)
{
	CLOVE_NOT_NULL(DoubleList_New(int));
}

CLOVE_TEST(DoubleListLength0)
{
	DoubleList doubleList = DoubleList_New(int);
	CLOVE_INT_EQ(doubleList->length, 0);
}
#pragma endregion Initialization

#pragma region IncreaseCapacity
CLOVE_TEST(DoubleListIncreaseCapacityByZero)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	CLOVE_INT_EQ(DoubleList_IncreaseCapacity(doubleList, 0), -1);
}

CLOVE_TEST(DoubleListIncreaseCapacityByNegativeNumber)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	CLOVE_INT_EQ(DoubleList_IncreaseCapacity(doubleList, -1), -1);
}

CLOVE_TEST(DoubleListIncreaseCapacityEmptyList)
{
	DoubleList doubleList = DoubleList_New(int);
	DoubleList_IncreaseCapacity(doubleList, 1);
	CLOVE_INT_EQ(doubleList->capacity, 6);
}

CLOVE_TEST(DoubleListIncreaseCapacityNotEmptyList)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	DoubleList_IncreaseCapacity(doubleList, 1);
	CLOVE_INT_EQ(doubleList->capacity, 6);
}

CLOVE_TEST(DoubleListAutoIncreaseCapacity)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);

	CLOVE_INT_EQ(doubleList->capacity, 10);

	int d = 4;
	DoubleList_Append(doubleList, &d);

	CLOVE_INT_EQ(doubleList->capacity, 10);
}
#pragma endregion IncreaseCapacity

#pragma region Append
CLOVE_TEST(DoubleListAddNotFail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	CLOVE_INT_EQ(DoubleList_Append(doubleList, &a), 0);
}

CLOVE_TEST(DoubleListAddOneElementHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a);
	void* value = (*doubleList->head)->data;
	CLOVE_INT_EQ(*(int*)((*doubleList->head)->data), 1);
}

CLOVE_TEST(DoubleListAddOneElementTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a);
	CLOVE_INT_EQ(*(int*)(*doubleList->tail)->data, 1);
}

CLOVE_TEST(DoubleListAddTwoElementHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	CLOVE_INT_EQ(*(int*)(*doubleList->head)->data, 1);
}

CLOVE_TEST(DoubleListAddTwoElementTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	CLOVE_INT_EQ(*(int*)(*doubleList->tail)->data, 2);
}

CLOVE_TEST(DoubleListAddFourElementsCheckThird)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	int thirdValue = *(int*)(*doubleList->head)->next->next->data;
	CLOVE_INT_EQ(thirdValue, 3);
}
#pragma endregion Append

#pragma region Remove
CLOVE_TEST(DoubleListRemoveFromEmptyList)
{
	DoubleList doubleList = DoubleList_New(int);
	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 0), -1);
}

CLOVE_TEST(DoubleListRemoveAtNegativeIndex)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a);
	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, -1), -1);
}

CLOVE_TEST(DoubleListRemoveAtLengthAsIndex)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a);
	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 1), -1);
}

CLOVE_TEST(DoubleListRemoveAtIndexGreaterThenLength)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a);
	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 2), -1);
}

CLOVE_TEST(DoubleListRemoveUniqueElementSucceeded)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a);
	CLOVE_INT_EQ(DoubleList_RemoveAt(doubleList, 0), 0);
}

CLOVE_TEST(DoubleListRemoveUniqueElementHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a); 
	DoubleList_RemoveAt(doubleList, 0);
	CLOVE_NULL((*doubleList->head));
}

CLOVE_TEST(DoubleListRemoveUniqueElementTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	DoubleList_Append(doubleList, &a); 
	DoubleList_RemoveAt(doubleList, 0);
	CLOVE_NULL((*doubleList->tail));
}

CLOVE_TEST(DoubleListRemoveHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_RemoveAt(doubleList, 0);
	CLOVE_INT_EQ(*(int*)(*doubleList->head)->data, 2);
}

CLOVE_TEST(DoubleListRemoveTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_RemoveAt(doubleList, 3);
	CLOVE_INT_EQ(*(int*)(*doubleList->tail)->data, 3);
}
#pragma endregion Remove

#pragma region Retrieving
CLOVE_TEST(DoubleListGetFirstElement)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 0), 1);
}

CLOVE_TEST(DoubleListGetLastElement)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 4), 5);
}

CLOVE_TEST(DoubleListGetLowerHalfElement)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 2);
}

CLOVE_TEST(DoubleListGetUpperHalfElement)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 3), 4);
}

CLOVE_TEST(DoubleListGetHalfElement)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 2), 3);
}
#pragma endregion Retrieving

#pragma region Shuffle & Cloning
CLOVE_TEST(DoubleListCloning)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);

	DoubleList shuffledList = DoubleList_Clone(doubleList);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 1);
}

CLOVE_TEST(DoubleListTwoElementsSwitchingElements)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	DoubleList shuffledList = DoubleList_Clone(doubleList);
	DoubleList_SwitchElements(shuffledList, 0, 1);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 2);
}

CLOVE_TEST(DoubleListSwitchingElements)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);

	DoubleList shuffledList = DoubleList_Clone(doubleList);
	DoubleList_SwitchElements(shuffledList, 0, 3);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 4);
}

CLOVE_TEST(DoubleListDoubleSwitchingElements)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int e = 5;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);
	DoubleList_Append(doubleList, &c);
	DoubleList_Append(doubleList, &d);
	DoubleList_Append(doubleList, &e);

	DoubleList shuffledList = DoubleList_Clone(doubleList);
	DoubleList_SwitchElements(shuffledList, 0, 3);
	DoubleList_SwitchElements(shuffledList, 3, 0);
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(shuffledList, 0), 1);
}
#pragma endregion Shuffle & Cloning

#pragma region InsertAfter
CLOVE_TEST(DoubleListInsertAfterHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertAfter(doubleList, &c, &a);
	
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 3);
}

CLOVE_TEST(DoubleListInsertAfterHeadCheckHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertAfter(doubleList, &c, &a);
	
	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 0), 1);
}

CLOVE_TEST(DoubleListInsertAfterTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertAfter(doubleList, &c, &b);

	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 2), 3);
}

CLOVE_TEST(DoubleListInsertAfterTailCheckOldTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertAfter(doubleList, &c, &b);

	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 2);
}

CLOVE_TEST(DoubleListInsertBeforeHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertBefore(doubleList, &c, &a);

	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 0), 3);
}

CLOVE_TEST(DoubleListInsertBeforeHeadCheckOldHead)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertBefore(doubleList, &c, &a);

	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 1);
}

CLOVE_TEST(DoubleListInsertBeforeTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertBefore(doubleList, &c, &b);

	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 1), 3);
}

CLOVE_TEST(DoubleListInsertBeforeTailCheckTail)
{
	DoubleList doubleList = DoubleList_New(int);
	int a = 1;
	int b = 2;
	DoubleList_Append(doubleList, &a);
	DoubleList_Append(doubleList, &b);

	int c = 3;
	DoubleList_InsertBefore(doubleList, &c, &b);

	CLOVE_INT_EQ(*(int*)DoubleList_GetAt(doubleList, 2), 2);
}
#pragma endregion InsertAfter

CLOVE_SUITE(DoubleLinkedListSuite)
{
	CLOVE_SUITE_TESTS(
		DoubleListNotNULL,
		DoubleListLength0,
		DoubleListIncreaseCapacityByZero,
		DoubleListIncreaseCapacityByNegativeNumber,
		DoubleListIncreaseCapacityEmptyList,
		DoubleListIncreaseCapacityNotEmptyList,
		DoubleListAutoIncreaseCapacity,
		DoubleListAddOneElementHead,
		DoubleListAddOneElementTail,
		DoubleListAddTwoElementHead,
		DoubleListAddTwoElementTail,
		DoubleListAddFourElementsCheckThird,
		DoubleListRemoveFromEmptyList,
		DoubleListRemoveAtNegativeIndex,
		DoubleListRemoveAtLengthAsIndex,
		DoubleListRemoveAtIndexGreaterThenLength,
		DoubleListRemoveUniqueElementSucceeded,
		DoubleListRemoveUniqueElementHead,
		DoubleListRemoveUniqueElementTail,
		DoubleListRemoveHead,
		DoubleListRemoveTail,
		DoubleListGetFirstElement,
		DoubleListGetLastElement,
		DoubleListGetLowerHalfElement,
		DoubleListGetUpperHalfElement,
		DoubleListGetHalfElement,
		DoubleListCloning,
		DoubleListTwoElementsSwitchingElements,
		DoubleListSwitchingElements,
		DoubleListDoubleSwitchingElements,
		DoubleListInsertAfterHead,
		DoubleListInsertAfterHeadCheckHead,
		DoubleListInsertAfterTail,
		DoubleListInsertAfterTailCheckOldTail,
		DoubleListInsertBeforeHead,
		DoubleListInsertBeforeHeadCheckOldHead,
		DoubleListInsertBeforeTail,
		DoubleListInsertBeforeTailCheckTail
	);
}