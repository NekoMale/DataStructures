# NG Data Collections
 
 *Flexible structures representing data collections on C*
 
 Project includes:
- LinkedList - *simple data structure collecting informations in a list*
- DoubleLinkedList - *data structure collecting informations in a list and iterable forward and backward*
- Set (unique keys) - *data structure with fast searching. Can store unique values only*
- Dictionary - *complex data structure where a key corresponds a value*

All of them are generics

**In-code documentation is coming soon**

## Installation

Actually you should import in your project all files *.c and *.h in src\ and inc\ folders.
A single header file would be available soon.

## How does it work?

Just import the single data structure header you need where you need.

## APIs

### Linked List

| Function | Description |
| --- | --- |
| ng_list_new(item_type, compare_function) | Create a **Linked List** which will contains items of *item_type*. This list will use *compare_function* you'll provide to compare values if needed |
| ng_list_increase_capacity(list, size_increase_amount) | Increase *list* capacity of *size_increase_amount* |
| ng_list_add(list, value) | Add a list element to *list* with *value* as value. The new element will be add at the list end |
| ng_list_get_at(list, index) | Return the *list* element value at given *index* |
| ng_list_reverse(list) | Return a new **Linked List** with same *list* element on reverse order |
| ng_list_get_last(list) | Return the last element value of *list* |
| ng_list_remove_first(list) | Remove the first element from *list* |
| ng_list_remove_at(list, index) | Remove the element at given *index* from *list* |
| ng_list_remove(list, value_to_remove) | Remove the first element found with *value_to_remove* value from *list* |
| ng_list_remove_last(list) | Remove the last element from *list* |

### Double Linked List

| Function | Description |
| --- | --- |
| ng_double_list_new(item_type, compare_function) 									| Create a **Double Linked List** which will contains items of *item_type*. This list will use *compare_function* you'll provide to compare values if needed |
| ng_double_list_increase_capacity(double_list, size_increase_amount)				| Increase *double_list* capacity of *size_increase_amount* |
| ng_double_list_add(double_list, value) 											| Add a new double list element to *double_list* with *value* as value. The new element will be add at the list end |
| ng_double_list_get_at(double_list, index)											| Return the *double_list* element value at given *index* |
| ng_double_list_remove_at(double_list, index) 										| Remove the element at given *index* from *double_list* |
| ng_double_list_add_after(double_list, value_to_add, value_after) 					| Add a new double list element to *double_list* after the first element found with *value_after* value. The new element will has *value_to_add* as value |
| ng_double_list_add_before(double_list, value_to_add, value_before) 				| Add a new double list element to *double_list* before the first element found with *value_before* value.The new element will has *value_to_add* as value |
| ng_double_list_shuffle(double_list)												| Return a new **Double Linked List** with same *double_list* elements on random order. This will shuffle element "half double_list length" times with default random function |
| ng_double_list_shuffle_pick_function(double_list, time_to_shuffle, pick_function)	| Same of **ng_double_list_shuffle(double_list)**. A *time_to_shuffle* and a *pick_function* for random can be provided |

### Set

| Function | Description |
| --- | --- |
| ng_set_new(compare_function)												| Create a **Set**. This set will use *compare_function* you'll provide to compare values if needed, a default hashing algorithm and hashmap_size. |
| ng_set_new_hashed(hashmap_size, custom_hash_function, compare_function) 	| Same of **ng_set_new(compare_function)**. A *hashmap_size* and *custom_hash_function* can be provided |
| ng_set_increase_hashmap_size(set, size_increase_amount) 					| Increase *set* hashmap size of *size_increase_amount* |
| ng_set_add(set, value, key_length) 										| Add a new set element to *set* with *value* as value. Its *key_length* will be used to hashing |
| ng_set_exists(set, value, key_length) 									| Return 0 if a set element exists inside *set* with same *value* |
| ng_set_remove(set, value, key_length) 									| Remove the element with given *value* from *set* |

### Dictionary
**NB:** Dictionary uses ng_set as container. 
You should do

```
ng_set dictionary = ng_dictionary_new(my_compare_function);
```

| Function | Description |
| --- | --- |
| ng_dictionary_new(compare_function)										| Create a **Dictionary**. This dictionary will use *compare_function* to compare keys when needed, a default hashing algorithm and hashmap size |
| ng_dictionary_new_hashed(hashmap_size, custom_hash_function, compare_function) 	| Same of **ng_dictionary_new(compare_function)**. A *hashmap_size* and *custom_hash_function* can be provided |
| ng_dictionary_increase_hashmap_size(dictionary, size_increase_amount) 	| Increase *dictionary* hashmap size of *size_increase_amount* |
| ng_dictionary_add(dictionary, key, key_length, value) 					| Add a new dictionary element to *dictionary* with *key* as key and *value* as value. Its *key_length* will be used to hashing |
| ng_dictionary_contains_key(dictionary, key, key_length) 					| Return 0 if given *key* already exists inside *dictionary*. Its *key_length* will be used to hashing |
| ng_dictionary_remove(dictionary, key, key_length) 						| Remove the dictionary element with *key* as key. Its *key_length* will be used to hashing |
