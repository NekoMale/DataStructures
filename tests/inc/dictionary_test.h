#define CLOVE_SUITE_NAME DictionarySuite
#include <string.h>
#include "..\inc\clove.h"
#include "..\..\inc\dictionary.h"

ng_set dictionary;

static size_t Constant_Hash(const void* key, const size_t key_len)
{
	return 0;
}

int compare_strings(const void* o1, const void* o2) {
	return strcmp((const char*)o1, (const char*)o2);
}

CLOVE_SUITE_SETUP()
{
	dictionary = ng_dictionary_new_hashed(1, Constant_Hash, compare_strings);
}

CLOVE_TEST(DictionaryInitialization)
{
	dictionary = ng_dictionary_new(compare_strings);
	CLOVE_NOT_NULL(dictionary);
	CLOVE_NOT_NULL(dictionary->nodes);
}

CLOVE_TEST(DictionaryIncreaseHashmapSize)
{
	ng_dictionary_increase_hashmap_size(dictionary, 10);
	CLOVE_INT_EQ(dictionary->hashmap_size, 11);
}

CLOVE_TEST(DictionaryAddOneElement)
{
	char* key = "peasant";
	char* value = "basic unit";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	CLOVE_STRING_EQ((char*)((ng_dictionary_pair)((*dictionary->nodes[0]->nodes)->data))->key, "peasant");
	CLOVE_STRING_EQ((char*)((ng_dictionary_pair)((*dictionary->nodes[0]->nodes)->data))->value, "basic unit");
}

CLOVE_TEST(DictionaryAddTwoElement)
{
	char* key = "peasant";
	char* value = "basic unit";
	char* key2 = "footman";
	char* value2 = "basic attacking unit";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	ng_dictionary_add(dictionary, key2, strlen(key2), value2);
	CLOVE_STRING_EQ((char*)((ng_dictionary_pair)((*dictionary->nodes[0]->nodes)->data))->key, "peasant");
	CLOVE_STRING_EQ((char*)((ng_dictionary_pair)((*dictionary->nodes[0]->nodes)->data))->value, "basic unit");
	CLOVE_STRING_EQ((char*)((ng_dictionary_pair)((*dictionary->nodes[0]->nodes)->next->data))->key, "footman");
	CLOVE_STRING_EQ((char*)((ng_dictionary_pair)((*dictionary->nodes[0]->nodes)->next->data))->value, "basic attacking unit");
}

CLOVE_TEST(DictionaryAddTwoExistingElement)
{
	char* key = "peasant";
	char* value = "basic unit";
	char* key2 = "footman";
	char* value2 = "basic attacking unit";
	char* key3 = "footman";
	char* value3 = "another footman";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	ng_dictionary_add(dictionary, key2, strlen(key2), value2);
	CLOVE_INT_EQ(ng_dictionary_add(dictionary, key3, strlen(key3), value3), -1);
}

CLOVE_TEST(DictionaryContainsKey)
{
	char* key = "peasant";
	char* value = "basic unit";
	char* key2 = "footman";
	char* value2 = "basic attacking unit";
	char* key3 = "footman";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	ng_dictionary_add(dictionary, key2, strlen(key2), value2);
	CLOVE_INT_EQ(ng_dictionary_contains_key(dictionary, key3, strlen(key3)), 0);
}

CLOVE_TEST(DictionaryNotContainsKey)
{
	char* key = "peasant";
	char* value = "basic unit";
	char* key2 = "footman";
	char* value2 = "basic attacking unit";
	char* key3 = "ranger";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	ng_dictionary_add(dictionary, key2, strlen(key2), value2);
	CLOVE_INT_EQ(ng_dictionary_contains_key(dictionary, key3, strlen(key3)), -1);
}

CLOVE_TEST(DictionaryRemoveExistingValue)
{
	char* key = "peasant";
	char* value = "basic unit";
	char* key2 = "footman";
	char* value2 = "basic attacking unit";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	ng_dictionary_add(dictionary, key2, strlen(key2), value2);
	CLOVE_INT_EQ(ng_dictionary_remove(dictionary, "footman", strlen("footman")), 0);
	CLOVE_NULL((*dictionary->nodes[0]->nodes)->next);
}

CLOVE_TEST(DictionaryRemoveNotExistingValue)
{
	char* key = "peasant";
	char* value = "basic unit";
	char* key2 = "footman";
	char* value2 = "basic attacking unit";
	ng_dictionary_add(dictionary, key, strlen(key), value);
	ng_dictionary_add(dictionary, key2, strlen(key2), value2);
	CLOVE_INT_EQ(ng_dictionary_remove(dictionary, "ranger", strlen("ranger")), -1);
}