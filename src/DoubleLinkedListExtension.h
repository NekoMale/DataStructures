#pragma once
#include "DoubleLinkedList.h"

typedef struct SDoubleStringItem {
	DoubleNodeList node;
	const char* string;
} DoubleStringItem;

#define DoubleStringElement DoubleStringItem*

#define Clone(originalHead) M_Clone((DoubleListHead)&originalHead)

DoubleStringElement NewDoubleStringItem(const char* string);
DoubleStringElement M_Clone(DoubleListHead originalHead);