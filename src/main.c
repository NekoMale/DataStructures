#include <stddef.h> // required for NULL
#include <stdio.h>
#include <string.h>
#include "..\inc\linked_list.h"
#include "..\inc\set.h"

int compare_int(const void* v1, const void* v2)
{
	int i1 = *(int*)v1;
	int i2 = *(int*)v2;

	if (i1 < i2) return -1;
	else if (i1 > i2) return 1;
	else return 0;
}

int compare_strings(const void* o1, const void* o2) {
	return strcmp((const char*)o1, (const char*)o2);
}

int main()
{
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;


	printf("****** Linked List ******\n");
	ng_list list = ng_list_new(int, compare_int);
	ng_list_add(list, &a);
	ng_list_add(list, &b);
	ng_list_add(list, &c);
	ng_list_add(list, &d);
	ng_list_add(list, &e);
	ng_list_add(list, &f);

	for (int i = 0; i < list->length; ++i)
	{
		printf("%d) %d\n", i, *(int*)ng_list_get_at(list, i));
	}

	printf("****** Set ******\n");
	ng_set set = ng_set_new(compare_int);
	ng_set_add(set, "ciao", 4);
	ng_set_add(set, "come", 4);
	ng_set_add(set, "stai", 4);
	ng_set_add(set, "io", 2);
	ng_set_add(set, "mi", 2);
	ng_set_add(set, "sento", 5);
	ng_set_add(set, "bene", 4);
	ng_set_add(set, "continuo", 8);
	ng_set_add(set, "ad", 2);
	ng_set_add(set, "an", 2);
	ng_set_add(set, "da", 2);
	ng_set_add(set, "sa", 2);
	ng_set_add(set, "fa", 2);
	ng_set_add(set, "bah", 3);
	ng_set_add(set, "beh", 3);
	ng_set_add(set, "mah", 3);
	ng_set_add(set, "meh", 3);
	ng_set_add(set, "aggiungere", 10);
	ng_set_add(set, "elementi", 8);
	ng_set_add(set, "a", 1);
	ng_set_add(set, "chissa", 5);
	ng_set_add(set, "quanti", 5);
	ng_set_add(set, "ne", 2);
	ng_set_add(set, "he", 2);
	ng_set_add(set, "te", 2);
	ng_set_add(set, "ze", 2);
	ng_set_add(set, "devo", 4);
	ng_set_add(set, "inserire", 8);
	ng_set_add(set, "inserier", 8);
	ng_set_add(set, "insarier", 8);
	ng_set_add(set, "inaarier", 8);
	ng_set_add(set, "inearier", 8);
	ng_set_add(set, "insyrier", 8);

	for (int i = 0; i < set->hashmap_size; ++i)
	{
		ng_node_list node = *set->nodes[i]->nodes;
		printf("%d) ", i);
		while (node) {
			printf(" %s ", (char*)((ng_key_set)(node->data))->key);
			node = node->next;
			if (node)
			{
				printf("->");
			}
		}
		printf("\n");
	}

	return 0;
}
