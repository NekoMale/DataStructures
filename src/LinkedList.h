#pragma once
typedef struct SNodeList
{
	struct SNodeList* next;
} NodeList;

#define ListElement NodeList*
#define ListHead ListElement*

ListElement GetListTail(ListHead head);
ListElement AppendToList(ListHead head, ListElement item);
ListElement PopFromList(ListHead head);
ListElement RemoveLastFromList(ListHead head);
ListElement RemoveItemFromList(ListHead head, ListElement item);
void ReverseList(ListHead head);