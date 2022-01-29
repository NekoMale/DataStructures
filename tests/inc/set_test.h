#define CLOVE_SUITE_NAME SetSuite
#include "..\inc\clove.h"
#include "..\..\inc\set.h"

ng_set set;

static size_t Constant_Hash(const void* key, const size_t key_len)
{
	return 0;
}

static int Compare_Ints(const void* v1, const void* v2) {
	int i1 = *(int*)v1;
	int i2 = *(int*)v2;

	if (i1 < i2) return -1;
	else if (i1 > i2) return 1;
	else return 0;
}

int compare_strings(const void* o1, const void* o2) {
	return strcmp((const char*)o1, (const char*)o2);
}


CLOVE_SUITE_SETUP()
{
	set = ng_set_new_hashed(1, Constant_Hash, Compare_Ints);
}

CLOVE_TEST(SetInitialization)
{
	set = ng_set_new(Compare_Ints);
	CLOVE_NOT_NULL(set);
	CLOVE_NOT_NULL(set->nodes);
}

CLOVE_TEST(SetIncreaseHashmapSize)
{
	ng_set_increase_hashmap_size(set, 10);
	CLOVE_INT_EQ(set->hashmap_size, 11);
}

CLOVE_TEST(SetAddingOneElement)
{
	int val = 1;
	size_t length = 1;
	ng_set_add(set, &val, length);
	CLOVE_INT_EQ(*(int*)((ng_key_set)((*(set->nodes[0]->nodes))->data))->key, 1);
}

CLOVE_TEST(SetAddingOneStringElement)
{
	set = ng_set_new_hashed(1, Constant_Hash, compare_strings);
	char* el1 = "basic unit or maybe I should be another thing? I really don't know how much I can write without break it";
	char* el2 = "basic unit or maybe I should be another thing? I really don't know how mucbreak it";
	size_t length = strlen(el1);
	size_t length2 = strlen(el2);
	ng_set_add(set, el1, length);
	ng_set_add(set, el2, length2);
	CLOVE_STRING_EQ((char*)((ng_key_set)((*(set->nodes[0]->nodes))->data))->key, "basic unit or maybe I should be another thing? I really don't know how much I can write without break it");
	CLOVE_STRING_EQ((char*)((ng_key_set)((*(set->nodes[0]->nodes))->next->data))->key, "basic unit or maybe I should be another thing? I really don't know how mucbreak it");
}

CLOVE_TEST(SetAddingTwoUniqueElements)
{
	int val = 1;
	int val2 = 12;
	size_t length = 1;
	size_t length2 = 2;
	ng_set_add(set, &val, length);
	ng_set_add(set, &val2, length2);
	CLOVE_INT_EQ(*(int*)((ng_key_set)((*set->nodes[0]->nodes)->next->data))->key, 12);
}

CLOVE_TEST(SetAddingTwoDuplicateElements)
{
	int val = 1;
	int val2 = 1;
	size_t length = 1;
	ng_set_add(set, &val, length);
	CLOVE_INT_EQ(ng_set_add(set, &val2, length), -1);
}

CLOVE_TEST(SetKeyExists)
{
	int val = 1;
	int val2 = 12;
	int val3 = 12;
	size_t length = 1;
	size_t length2 = 2;
	ng_set_add(set, &val, length);
	ng_set_add(set, &val2, length2);
	CLOVE_INT_EQ(ng_set_exists(set, &val3, length2), 0);
}

CLOVE_TEST(SetKeyNotExists)
{
	int val = 1;
	int val2 = 12;
	size_t length = 1;
	size_t length2 = 2;
	ng_set_add(set, &val, length);
	CLOVE_INT_NE(ng_set_exists(set, &val2, length2), 0);
}

CLOVE_TEST(SetRemoveExistingKey)
{
	int val = 1;
	int val2 = 12;
	size_t length = 1;
	size_t length2 = 2;
	ng_set_add(set, &val, length);
	ng_set_add(set, &val2, length2);
	ng_set_remove(set, &val2, length2);
	CLOVE_NULL((*set->nodes[0]->nodes)->next);
}

CLOVE_TEST(SetRemoveNotExistingKey)
{
	int val = 1;
	int val2 = 12;
	int val3 = 15;
	size_t length = 1;
	size_t length2 = 2;
	ng_set_add(set, &val, length);
	ng_set_add(set, &val2, length2);
	CLOVE_INT_EQ(ng_set_remove(set, &val3, length2), -1);
}

CLOVE_TEST(SetAutoIncreaseHashmapSize)
{
	int val = 1;
	size_t length = 1;
	ng_set_add(set, &val, length);
	CLOVE_INT_EQ(set->hashmap_size, 5);
}
