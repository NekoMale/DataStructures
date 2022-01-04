#pragma once
#include <string.h>

typedef struct S_NodeSet
{
	const char* key;
	size_t key_len;
	struct S_NodeSet* next;
} NodeSet;

#define SetElement NodeSet*
#define SetHead NodeSet**

typedef struct S_TableSet
{
	SetHead nodes;
	size_t hashmapSize;
} TableSet;

#define TableElement TableSet*

#define NewTableSet(hashmapSize) M_NewTableSet(hashmapSize)
#define InsertToSet(table, key) M_InsertToSet((TableElement)table, key, strlen(key))
#define Search(table, key) M_Search((TableElement)table, key)
#define Remove(table, key) M_Remove((TableElement)table, key)

TableElement M_NewTableSet(const size_t hashmapSize);
SetElement M_InsertToSet(TableElement table, const char* key, const size_t keyLen);
SetElement M_Search(TableElement table, const char* key);
SetElement M_Remove(TableElement table, const char* key);
void M_IncreaseHashmapSize(TableElement table);