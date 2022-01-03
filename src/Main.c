#include <stddef.h> // required for NULL
#include <stdio.h>
#include "LinkedListExtension.h"
#include "DoubleLinkedListExtension.h"

void PrintNewSection()
{
	printf("------------------------\n");
}

void PrintList(StringElement linkedList)
{
	StringElement stringItem = linkedList;
	while (stringItem)
	{
		printf("%s\n", stringItem->string);
		stringItem = (StringElement)stringItem->node.next;
	}
}

void PrintDoubleList(DoubleStringElement doubleLinkedList)
{
	DoubleStringElement stringItem = doubleLinkedList;
	while (stringItem)
	{
		DoubleStringElement prev = (DoubleStringElement)stringItem->node.prev;
		if (prev) {
			printf("%s -> ", prev->string);
		}
		printf("%s\n", stringItem->string);
		stringItem = (DoubleStringElement)stringItem->node.next;
	}
}

int main()
{
	StringElement linkedList = NULL;
	ListElement element1 = AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Hello World"));
	ListElement element2 = AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Test001"));
	ListElement element3 = AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Test002"));
	ListElement element4 = AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Last Item of the Linked List"));
	PrintList(linkedList);
	PrintNewSection();

	ReverseList((ListHead)&linkedList);
	PrintList(linkedList);
	PrintNewSection();
	
	RemoveItemFromList((ListHead)&linkedList, element2);
	PrintList(linkedList);
	PrintNewSection();

	RemoveLastFromList((ListHead)&linkedList);
	PrintList(linkedList);
	PrintNewSection();

	DoubleStringElement doubleLinkedList = NULL;
	DoubleListElement dElement1 = AppendToDoubleList(doubleLinkedList, NewDoubleStringItem("Hello World"));
	DoubleListElement dElement2 = AppendToDoubleList(doubleLinkedList, NewDoubleStringItem("Test 001"));
	DoubleListElement dElement3 = AppendToDoubleList(doubleLinkedList, NewDoubleStringItem("Test 002"));
	DoubleListElement dElement4 = AppendToDoubleList(doubleLinkedList, NewDoubleStringItem("Last Item of the Double Linked List"));
	PrintDoubleList(doubleLinkedList);
	PrintNewSection();

	RemoveFromDoubleList(doubleLinkedList, dElement2);
	PrintDoubleList(doubleLinkedList);
	PrintNewSection();

	DoubleListElement dElement5 = InsertIntoDoubleListAfterElement(doubleLinkedList, NewDoubleStringItem("Test 003"), dElement3);
	PrintDoubleList(doubleLinkedList);
	PrintNewSection();

	DoubleListElement dElement7 = InsertIntoDoubleListBeforeElement(doubleLinkedList, NewDoubleStringItem("Test 005"), dElement3);
	PrintDoubleList(doubleLinkedList);
	PrintNewSection();

	DoubleListElement dElement6 = InsertIntoDoubleListBeforeElement(doubleLinkedList, NewDoubleStringItem("Test 004"), dElement1);
	PrintDoubleList(doubleLinkedList);
	PrintNewSection();

	DoubleStringElement shuffledDoubleLinkedList = M_Clone((DoubleListHead)&doubleLinkedList);
	M_Shuffle((DoubleListHead)&shuffledDoubleLinkedList);
	PrintDoubleList(shuffledDoubleLinkedList);
	PrintNewSection();

	PrintDoubleList(doubleLinkedList);
	PrintNewSection();

	return 0;
}