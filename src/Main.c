#include <stddef.h> // required for NULL
#include <stdio.h>
#include "LinkedListExtension.h"
#include "DoubleLinkedListExtension.h"
#include "Set.h"

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

void PrintSet(TableElement table)
{
	SetHead set = table->nodes;
	for (int i = 0; i < table->hashmapSize; i++)
	{
		SetElement currentNode = set[i];
		printf("Node[%d]: ", i);
		while (currentNode)
		{
			printf("%s, ", currentNode->key);
			currentNode = currentNode->next;
		}
		printf("\n");
	}
}

void PrintSetElement(SetElement element, const char* key)
{
	if(element)
		printf("Found this key: %s\n", element->key);
	else
		printf("There is no element with this key: %s\n", key);
}

int main()
{
	// LinkedListExercise();
	// DoubleLinkedListExercise();

	TableElement table = NewTableSet(1);
	SetElement element1 = InsertToSet(table, "Casa");
	PrintSet(table);
	PrintNewSection();
	SetElement element2 = InsertToSet(table, "Tavolo");
	SetElement element3 = InsertToSet(table, "Posate");
	SetElement element4 = InsertToSet(table, "Ciao");
	SetElement element5 = InsertToSet(table, "Rasa");
	PrintSet(table);
	PrintNewSection();

	SetElement element6 = InsertToSet(table, "Miao");
	SetElement element7 = InsertToSet(table, "Portale");
	SetElement element8 = InsertToSet(table, "Albero");
	SetElement element9 = InsertToSet(table, "Cellulare");
	SetElement element10 = InsertToSet(table, "Unity");
	PrintSet(table);
	PrintNewSection();

	SetElement element11 = InsertToSet(table, "Videogiochi");
	SetElement element12 = InsertToSet(table, "Telegram");
	SetElement element13 = InsertToSet(table, "Disegno");
	SetElement element14 = InsertToSet(table, "Manga");
	SetElement element15 = InsertToSet(table, "Porpora");
	PrintSet(table);
	PrintNewSection();

	SetElement element16 = InsertToSet(table, "Miao");
	SetElement element17 = InsertToSet(table, "Portale");
	SetElement element18 = InsertToSet(table, "Albero");
	SetElement element19 = InsertToSet(table, "Cellulare");
	SetElement element20 = InsertToSet(table, "Unity");
	PrintSet(table);
	PrintNewSection();

	SetElement element21 = InsertToSet(table, "1");
	SetElement element22 = InsertToSet(table, "2");
	SetElement element23 = InsertToSet(table, "3");
	SetElement element24 = InsertToSet(table, "4");
	SetElement element25 = InsertToSet(table, "5");

	PrintSet(table);
	PrintNewSection();

	PrintSetElement(Search(table, "Manga"), "Manga");
	PrintSetElement(Search(table, "Pane"), "Pane");
	PrintNewSection();

	Remove(table, "Ciao");
	PrintSet(table);
	PrintNewSection();


	Remove(table, "Pane");
	PrintSet(table);
	PrintNewSection();

	return 0;
}

void LinkedListExercise() {
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
}

void DoubleLinkedListExercise() {
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
}