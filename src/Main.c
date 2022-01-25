#include <stddef.h> // required for NULL
#include <stdio.h>
#include "..\inc\LinkedList.h"
#include "..\inc\Set.h"

void PrintNewSection()
{
	printf("------------------------\n");
}

void PrintStringList(List list)
{
	printf("Printing string list:\n");
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		printf("%s\n", (char*)currentNode->data);
		currentNode = currentNode->next;
	}
}

void PrintIntList(List list)
{
	printf("Printing int list:\n");
	NodeList currentNode = *(list->nodes);
	while (currentNode)
	{
		printf("%d\n", *(int*)currentNode->data);
		currentNode = currentNode->next;
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

void LinkedListExercise() {
	List list = List_New(char);
	char* stringa = "Test 001";
	List_Append(list, stringa);
	List_Append(list, "Test 002");
	List_Append(list, "Test 003");
	List_Append(list, "Test 004");
	List_Append(list, "Test 005");
	List_Append(list, "Test 006");

	PrintStringList(list);
	PrintNewSection();

	List_Reverse(list);
	PrintStringList(list);
	PrintNewSection();

	List_RemoveValue(list, "Test 004");
	List_RemoveValue(list, "Test 001");
	List_RemoveValue(list, "Test 006");
	List_RemoveLast(list);
	List_RemoveValue(list, 2);
	PrintStringList(list);
	PrintNewSection();


	List list2 = List_New(int);

	int a = 101;
	int b = 2;
	int c = 33;
	List_Append(list2, &a);
	List_Append(list2, &b);
	List_Append(list2, &c);
	List_RemoveValue(list2, 2);
	PrintIntList(list2);
	PrintNewSection();

	List list3 = List_New(char);
	List_Append(list3, "Test 003");
	printf("%s\n", (char*)(*(list3->nodes))->data);
}

int main()
{
	 LinkedListExercise();
	 SetExercise();
	 return 0;
}