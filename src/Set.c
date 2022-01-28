#include <stddef.h> // required for NULL
#include <stdlib.h>
#include "..\inc\Set.h"
#include "..\inc\LinkedList.h"

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
	set->nodes = (NG_List*)malloc(sizeof(NG_T_List));
	if (!set->nodes)
	{
		free(set);
		return NULL;
	}
	*(set->nodes) = NG_List_New(NG_T_KeySet, compare_function);
	if (!(*set->nodes))
	{
		free(set->nodes);
		set->nodes = NULL;
		free(set);
		return NULL;
	}
	return set;
}

int __NG_Set_Add(NG_TableSet set, const void* value, const size_t key_length)
{
	size_t hash = set->hash_function(value, key_length);
	size_t index = hash % set->hashmap_size;

	NG_NodeList new_element = (NG_NodeList)malloc(sizeof(NG_T_NodeList));
	if (!new_element)
	{
		return -1;
	}

	NG_KeySet set_element = (NG_KeySet)malloc(sizeof(NG_T_KeySet));
	if (!set_element)
	{
		return -1;
	}

	set_element->key_length = key_length;
	set_element->key = value;

	new_element->data = set_element;
	new_element->next = NULL;

	size_t node_length = 1;
	NG_NodeList head = *set->nodes[index]->nodes;
	if (!head)
	{
		*(set->nodes[index]->nodes) = new_element;
	}
	else
	{
		NG_NodeList tail;
		do
		{
			if (set->compare_node_function(((NG_KeySet)(head->data))->key, value) == 0)
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
		size_t increase_size = set->hashmap_size;
		if (increase_size < 4) increase_size = 4;
		__NG_Set_Increase_Hashmap_Size(set, increase_size);
	}
	return 0;
}

int __NG_Set_Exists(NG_TableSet set, void* value, const size_t key_length)
{
	size_t hash = set->hash_function(value, key_length);
	size_t index = hash % set->hashmap_size;

	NG_NodeList head = *set->nodes[index]->nodes;
	while (head)
	{
		if (set->compare_node_function(((NG_KeySet)(head->data))->key, value) == 0)
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

	NG_NodeList lastNode;
	NG_NodeList node = *set->nodes[index]->nodes;
	while (node)
	{
		if (set->compare_node_function(((NG_KeySet)(node->data))->key, value) == 0)
		{
			if (lastNode)
			{
				lastNode->next = node->next;
			}
			else {
				*set->nodes[index]->nodes = node->next;
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
		NG_NodeList current_node = *(set->nodes[i]->nodes);
		while (current_node)
		{
			NG_KeySet node_value = (NG_KeySet)(current_node->data);
			__NG_Set_Add(larger_set, node_value->key, node_value->key_length);
			current_node = current_node->next;
		}
	}
	*set = *larger_set;
	return 0;
}