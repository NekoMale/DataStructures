#define CLOVE_SUITE_NAME SetSuite
#include "..\inc\clove.h"
#include "..\..\inc\Set.h"

NG_TableSet set;

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

CLOVE_SUITE_SETUP()
{
	set = NG_Set_New_Hashed(1, Constant_Hash, Compare_Ints);
}

CLOVE_TEST(SetInitialization)
{
	set = NG_Set_New(Compare_Ints);
	CLOVE_NOT_NULL(set);
	CLOVE_NOT_NULL(set->nodes);
}

CLOVE_TEST(SetAddingOneElement)
{
	int val = 1;
	size_t length = 1;
	NG_Set_Add(set, &val, length);
	CLOVE_INT_EQ(*(int*)(set->nodes[0]->key), 1);
}

CLOVE_TEST(SetAddingTwoUniqueElements)
{
	int val = 1;
	int val2 = 12;
	size_t length = 1;
	size_t length2 = 2;
	NG_Set_Add(set, &val, length);
	NG_Set_Add(set, &val2, length2);
	CLOVE_INT_EQ(*(int*)(set->nodes[0]->next->key), 12);
}

CLOVE_TEST(SetAddingTwoDuplicateElements)
{
	int val = 1;
	int val2 = 1;
	size_t length = 1;
	NG_Set_Add(set, &val, length);
	CLOVE_INT_EQ(NG_Set_Add(set, &val2, length), -1);
}

CLOVE_TEST(SetKeyExists)
{
	int val = 1;
	int val2 = 12;
	int val3 = 12;
	size_t length = 1;
	size_t length2 = 2;
	NG_Set_Add(set, &val, length);
	NG_Set_Add(set, &val2, length2);
	CLOVE_INT_EQ(NG_Set_Exists(set, &val3, length2), 0);
}

CLOVE_TEST(SetKeyNotExists)
{
	int val = 1;
	int val2 = 12;
	size_t length = 1;
	size_t length2 = 2;
	NG_Set_Add(set, &val, length);
	CLOVE_INT_NE(NG_Set_Exists(set, &val2, length2), 0);
}

CLOVE_TEST(SetRemoveExistingKey)
{
	int val = 1;
	int val2 = 12;
	size_t length = 1;
	size_t length2 = 2;
	NG_Set_Add(set, &val, length);
	NG_Set_Add(set, &val2, length2);
	NG_Set_Remove(set, &val2, length2);
	CLOVE_NULL(set->nodes[0]->next);
}

CLOVE_TEST(SetRemoveNotExistingKey)
{
	int val = 1;
	int val2 = 12;
	int val3 = 15;
	size_t length = 1;
	size_t length2 = 2;
	NG_Set_Add(set, &val, length);
	NG_Set_Add(set, &val2, length2);
	CLOVE_INT_EQ(NG_Set_Remove(set, &val3, length2), -1);
}

CLOVE_TEST(SetIncreaseHashmapSize)
{
	NG_Set_Increase_Hashmap_Size(set, 10);
	CLOVE_INT_EQ(set->hashmap_size, 11);
}

CLOVE_TEST(SetAutoIncreaseHashmapSize)
{
	int val = 1;
	size_t length = 1;
	NG_Set_Add(set, &val, length);
	CLOVE_INT_EQ(set->hashmap_size, 2);
}