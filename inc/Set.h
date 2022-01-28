#pragma once
#include <string.h>
#include "LinkedList.h"

typedef struct NG_S_KeySet
{
	size_t key_length;
	const void* key;
} NG_T_KeySet;

typedef NG_T_KeySet* NG_KeySet;

typedef struct NG_S_TableSet
{
	NG_List* nodes;
	size_t hashmap_size;
	size_t(*hash_function)(const void*, size_t);
	int(*compare_node_function)(const void*, const void*);
} NG_T_TableSet;

typedef NG_T_TableSet* NG_TableSet;

#define NG_Set_New(compare_function) __NG_Set_New(compare_function)
#define NG_Set_New_Hashed(hashmap_size, custom_hash_function, compare_function) __NG_Set_New_Hashed(hashmap_size, custom_hash_function, compare_function)
#define NG_Set_Add(set, value, key_length) __NG_Set_Add((NG_TableSet) set, value, key_length)
#define NG_Set_Exists(set, value, key_length) __NG_Set_Exists((NG_TableSet) set, value, key_length)
#define NG_Set_Remove(set, value, key_length) __NG_Set_Remove((NG_TableSet) set, value, key_length)
#define NG_Set_Increase_Hashmap_Size(set, size_increase_amount) __NG_Set_Increase_Hashmap_Size((NG_TableSet) set, size_increase_amount)

NG_TableSet __NG_Set_New(int(*compare_function)(const void* v1, const void* v2));
NG_TableSet __NG_Set_New_Hashed(const size_t hashmap_size, size_t(*hash_function)(const void* key, size_t key_length), int(*compare_function)(const void* v1, const void* v2));
int __NG_Set_Add(NG_TableSet set, const void* value, const size_t key_length);
int __NG_Set_Exists(NG_TableSet set, void* value, const size_t key_length);
int __NG_Set_Remove(NG_TableSet set, void* value, const size_t key_length);
int __NG_Set_Increase_Hashmap_Size(NG_TableSet set, const size_t size_increase_amount);