#include <stddef.h> // required for NULL
#include <stdlib.h>
#include "..\inc\Set.h"

size_t djb33x_hash(const void* key, const size_t key_length)
{
	size_t hash = 5381;
	const char* c_key = key;
	for (size_t i = 0; i < key_length; i++)
	{
		hash = ((hash << 5) + hash) ^ c_key[i];
	}
	return hash;
}

NG_TableSet __NG_Set_New(int(*compare_function)(const void* v1, const void* v2)) {
	return __NG_Set_New_Hashed(10, djb33x_hash, compare_function);
}

NG_TableSet __NG_Set_New_Hashed(const size_t hashmap_size, size_t(*hash_function)(const void* key, size_t key_length), int(*compare_function)(const void* v1, const void* v2)) 
{
	NG_TableSet set = (NG_TableSet)malloc(sizeof(NG_T_TableSet));
	if (!set)
	{
		return NULL;
	}
	set->hashmap_size = hashmap_size;
	set->hash_function = hash_function;
	set->compare_node_function = compare_function;
	set->nodes = (NG_HeadSet)calloc(hashmap_size, sizeof(NG_T_NodeSet));
	if (!set->nodes)
	{
		free(set);
		return NULL;
	}
	return set;
}

int __NG_Set_Add(NG_TableSet set, const void* value, const size_t key_length)
{
	size_t hash = set->hash_function(value, key_length);
	size_t index = hash % set->hashmap_size;

	NG_NodeSet new_element = (NG_NodeSet)malloc(sizeof(NG_T_NodeSet));
	if (!new_element)
	{
		return -1;
	}
	new_element->key = value;
	new_element->key_length = key_length;
	new_element->next = NULL;

	size_t node_length = 1;
	NG_NodeSet head = set->nodes[index];
	if (!head)
	{
		set->nodes[index] = new_element;
	}
	else
	{
		NG_NodeSet tail;
		do
		{
			if (set->compare_node_function(head->key, value) == 0)
			{
				free(new_element);
				return -1;
			}
			tail = head;
			head = head->next;
			++node_length;
		} while (head);
		tail->next = new_element;
	}
	if (node_length > (size_t)(set->hashmap_size * 0.5f))
	{
		__NG_Set_Increase_Hashmap_Size(set, set->hashmap_size);
	}
	return 0;
}

int __NG_Set_Exists(NG_TableSet set, void* value, const size_t key_length)
{
	size_t hash = set->hash_function(value, key_length);
	size_t index = hash % set->hashmap_size;

	NG_NodeSet head = set->nodes[index];
	while (head)
	{
		if (set->compare_node_function(head->key, value) == 0)
		{
			return 0;
		}
		head = head->next;
	}
	return -1;
}

int __NG_Set_Remove(NG_TableSet set, void* value, const size_t key_length)
{
	size_t hash = set->hash_function(value, key_length);
	size_t index = hash % set->hashmap_size;

	NG_NodeSet lastNode;
	NG_NodeSet node = set->nodes[index];
	while (node)
	{
		if (set->compare_node_function(node->key, value) == 0)
		{
			if (lastNode)
			{
				lastNode->next = node->next;
			}
			else {
				set->nodes[index] = node->next;
			}
			return 0;
		}
		lastNode = node;
		node = node->next;
	}
	return -1;
}

int __NG_Set_Increase_Hashmap_Size(NG_TableSet set, const size_t size_increase_amount)
{
	NG_TableSet larger_set = __NG_Set_New_Hashed(set->hashmap_size + size_increase_amount, set->hash_function, set->compare_node_function);
	if (!larger_set)
	{
		return -1;
	}

	const size_t current_set_size = set->hashmap_size;
	for (size_t i = 0; i < current_set_size; ++i)
	{
		NG_NodeSet current_node = set->nodes[i];
		while (current_node)
		{
			__NG_Set_Add(larger_set, current_node->key, current_node->key_length);
			current_node = current_node->next;
		}
	}
	*set = *larger_set;
	return 0;
}