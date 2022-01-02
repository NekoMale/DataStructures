#pragma once
#include "LinkedList.h"

typedef struct SStringItem {
	NodeList node;
	const char* string;
} StringItem;

#define StringElement StringItem*

StringElement NewStringItem(const char* string);