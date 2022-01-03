#pragma once
typedef struct SDoubleNodeList
{
	struct SDoubleNodeList* prev;
	struct SDoubleNodeList* next;
} DoubleNodeList;

#define DoubleListElement DoubleNodeList*
#define DoubleListHead DoubleNodeList**

#define AppendToDoubleList(head, item) M_AppendToDoubleList((DoubleListHead)&head, (DoubleListElement)item)
#define RemoveFromDoubleList(head, item) M_RemoveFromDoubleList((DoubleListHead)&head, (DoubleListElement)item)
#define InsertIntoDoubleListAfterElement(head, itemToAdd, afterItem) M_InsertIntoDoubleListAfterElement((DoubleListHead)&head, (DoubleListElement)itemToAdd, (DoubleListElement)afterItem)
#define InsertIntoDoubleListBeforeElement(head, itemToAdd, beforeItem) M_InsertIntoDoubleListBeforeElement((DoubleListHead)&head, (DoubleListElement)itemToAdd, (DoubleListElement)beforeItem)
#define GetDoubleElementAt(head, index) M_GetDoubleElementAt((DoubleListHead)&head, index)
#define Length(head) M_Length((DoubleListHead)&head)
#define Shuffle(head) M_Shuffle((DoubleListHead)&head)

DoubleListElement GetDoubleListTail(DoubleListHead head);
DoubleListElement M_AppendToDoubleList(DoubleListHead head, DoubleListElement item);
DoubleListElement M_RemoveFromDoubleList(DoubleListHead head, DoubleListElement item);
DoubleListElement M_InsertIntoDoubleListAfterElement(DoubleListHead head, DoubleListElement itemToAdd, DoubleListElement afterItem);
DoubleListElement M_InsertIntoDoubleListBeforeElement(DoubleListHead head, DoubleListElement itemToAdd, DoubleListElement beforeItem);
DoubleListElement M_GetDoubleElementAt(DoubleListHead head, int index);
int M_Length(DoubleListHead head);
void M_Shuffle(DoubleListHead head);