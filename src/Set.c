#include <stddef.h> // required for NULL
#include <stdlib.h>
#include "..\inc\Set.h"

size_t djb33x_hash(const char* key, const size_t keylen)
{
	size_t hash = 5381;
	for (size_t i = 0; i < keylen; i++)
	{
		hash = ((hash << 5) + hash) ^ key[i];
	}
	return hash;
}

size_t M_GetIndex(const size_t hashmapSize, const char* key)
{
	size_t hash = djb33x_hash(key, strlen(key));
	size_t index = hash % hashmapSize;
	return index;
}

TableElement M_NewTableSet(const size_t hashmapSize)
{
	TableElement table = malloc(sizeof(TableSet));
	if (!table)
	{
		return NULL;
	}
	table->hashmapSize = hashmapSize;
	table->nodes = calloc(table->hashmapSize, sizeof(NodeSet));
	if (!table->nodes)
	{
		free(table);
		return NULL;
	}
	return table;
}

SetElement M_SearchHavingIndex(TableElement table, const char* key, size_t index)
{
	SetElement currentNode = table->nodes[index];
	while (currentNode)
	{
		if (strcmp(key, currentNode->key) == 0)
			return currentNode;
		currentNode = currentNode->next;
	}
	return NULL;
}

SetElement M_Search(TableElement table, const char* key)
{
	size_t index = M_GetIndex(table->hashmapSize, key);
	return M_SearchHavingIndex(table, key, index);
}

SetElement M_InsertToSet(TableElement table, const char* key, const size_t keyLen)
{
	size_t index = M_GetIndex(table->hashmapSize, key);
	
	SetElement head = table->nodes[index];
	if (!head)
	{
		table->nodes[index] = malloc(sizeof(NodeSet));
		if (!table->nodes[index])
		{
			return NULL;
		}
		table->nodes[index]->key = key;
		table->nodes[index]->key_len = keyLen;
		table->nodes[index]->next = NULL;
		return table->nodes[index];
	}
	
	SetElement existingItem = M_SearchHavingIndex(table, key, index);
	if (existingItem)
		return existingItem;

	SetElement new_item = malloc(sizeof(NodeSet));
	if (!new_item)
	{
		return NULL;
	}
	new_item->key = key;
	new_item->key_len = keyLen;
	new_item->next = NULL;
	
	SetElement tail = head;
	int nElements = 1; // cause cycle doesn't count element it's going to insert
	while (head)
	{
		nElements++;
		tail = head;
		head = head->next;
	}
	tail->next = new_item;
	if (nElements > table->hashmapSize)
		M_IncreaseHashmapSize(table);
	return new_item;
}

SetElement M_Remove(TableElement table, const char* key)
{
	size_t index = M_GetIndex(table->hashmapSize, key);
	SetElement lastNode = NULL;
	SetElement currentNode = table->nodes[index];
	while (currentNode)
	{
		if (strcmp(key, currentNode->key) == 0)
		{
			if (lastNode) 
			{
				lastNode->next = currentNode->next;
			}
			else
			{
				table->nodes[index] = currentNode->next;
			}
			currentNode->next = NULL;
			return currentNode;
		}
		lastNode = currentNode;
		currentNode = currentNode->next;
	}
	return NULL;
}

void M_IncreaseHashmapSize(TableElement table) 
{
	TableElement largerTable = M_NewTableSet(table->hashmapSize * 2);
	SetHead set = table->nodes;
	for (int i = 0; i < table->hashmapSize; i++)
	{
		SetElement currentNode = set[i];
		while (currentNode)
		{
			M_InsertToSet(largerTable, currentNode->key, currentNode->key_len);
			currentNode = currentNode->next;
		}
	}
	*table = *largerTable;
}