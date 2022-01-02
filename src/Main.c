#include <stddef.h> // required for NULL
#include <stdio.h>
#include "LinkedListExtension.h"

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

int main()
{
	StringElement linkedList = NULL;
	AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Hello World"));
	ListElement element = AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Test001"));
	AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Test002"));
	AppendToList((ListHead)&linkedList, (ListElement)NewStringItem("Last Item of the Linked List"));
	PrintList(linkedList);
	PrintNewSection();

	ReverseList((ListHead)&linkedList);
	PrintList(linkedList);
	PrintNewSection();
	
	RemoveItemFromList((ListHead)&linkedList, element);
	PrintList(linkedList);
	PrintNewSection();

	RemoveLastFromList((ListHead)&linkedList);
	PrintList(linkedList);
	PrintNewSection();

	return 0;
}