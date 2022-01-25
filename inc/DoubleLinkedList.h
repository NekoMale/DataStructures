#pragma once
typedef struct S_NodeDoubleList
{
	void* data;
	struct S_NodeDoubleList* prev;
	struct S_NodeDoubleList* next;
} T_NodeDoubleList;

typedef  T_NodeDoubleList* NodeDoubleList;
typedef NodeDoubleList* HeadDoubleList;

typedef struct S_DoubleList
{
	HeadDoubleList head;
	HeadDoubleList tail;
	size_t elementSize;
	size_t capacity;
	size_t length;
} T_DoubleList;

typedef T_DoubleList* DoubleList;

#define DoubleList_New(elementType) M_DoubleList_New(sizeof(elementType))
#define DoubleList_Append(doubleList, value) M_DoubleList_Append((DoubleList)doubleList, value)
#define DoubleList_RemoveAt(doubleList, index) M_DoubleList_RemoveAt((DoubleList)doubleList, index)
#define DoubleList_GetAt(doubleList, index) M_DoubleList_GetAt((DoubleList)doubleList, index)
#define DoubleList_Shuffle(doubleList) M_DoubleList_Shuffle((DoubleList)doubleList)
#define DoubleList_SwitchElements(doubleList, index1, index2) M_DoubleList_SwitchElements((DoubleList)doubleList, index1, index2)
#define DoubleList_Clone(originalDoubleList) M_DoubleList_Clone((DoubleList)originalDoubleList)
#define DoubleList_InsertAfter(doubleList, valueToInsert, valueToCheck) M_DoubleList_InsertAfter((DoubleList)doubleList, valueToInsert, valueToCheck)
#define DoubleList_InsertBefore(doubleList, valueToInsert, valueToCheck) M_DoubleList_InsertBefore((DoubleList)doubleList, valueToInsert, valueToCheck)
#define DoubleList_IncreaseCapacity(doubleList, capacity) M_DoubleList_IncreaseCapacity((DoubleList)doubleList, capacity)

DoubleList M_DoubleList_New(const size_t elementSize);
int M_DoubleList_Append(DoubleList doubleList, void* value);
int M_DoubleList_RemoveAt(DoubleList doubleList, int index);
void* M_DoubleList_GetAt(DoubleList doubleList, int index);
DoubleList M_DoubleList_Shuffle(DoubleList doubleList);
void M_DoubleList_SwitchElements(DoubleList doubleList, int index1, int index2);
DoubleList M_DoubleList_Clone(DoubleList originalDoubleList);
int M_DoubleList_InsertAfter(DoubleList doubleList, void* valueToInsert, void* valueToCheck);
int M_DoubleList_InsertBefore(DoubleList doubleList, void* valueToInsert, void* valueToCheck);
int M_DoubleList_IncreaseCapacity(DoubleList doubleList, int capacityDelta);