# C-DataStructures
 
Actually there are only:
- LinkedList
- DoubleLinkedList
- Set (unique keys)

**LinkedList** and **DoubleLinkedList** are now generic.

**Set** works only with string.
I'm going to improve them in order to not have to declare a structure for every var type.

#### Any examples provided in Main.c as well.

## LinkedList

#### List informations availables:
- elementSize (var type bytes)
- capacity (how many items can have list)
- length (how many items list actually has)

LinkedList auto increment its capacity everytime length is equals to capacity - 1.

#### LinkedList methods:
- List_New
- List_Append
- List_GetAt
- List_GetLast
- List_RemoveFirst
- List_RemoveAt
- List_RemoveLast
- List_RemoveValue
- List_Reverse

#### LinkedList examples:
```
List list = List_New(char); // Makes new string list
List_Append(list, "Test 001"); // Appends new string value as last element
List_Append(list, "Test 002");
List_Append(list, "Test 003");
List_Append(list, "Test 004");

// Actually list is: "Test 001" -> "Test 002" -> "Test 003" -> "Test 004"

List_Reverse(list); // Reverses list
// Actually list is: "Test 004" -> "Test 003" -> "Test 002" -> "Test 001"

List_RemoveFirst(list);
// Actually list is: "Test 003" -> "Test 002" -> "Test 001"

List_RemoveLast(list);
// Actually list is: "Test 003" -> "Test 002"

List_RemoveValue(list, "Test 002");
// Actually list is: "Test 002"

List_RemoveAt(list, 0);
// Actually list is: Empty

/*********************************/

List list2 = List_New(int);

int a = 101;
int b = 2;
int c = 33;
List_Append(list2, &a);
List_Append(list2, &b);
List_Append(list2, &c);

// Actually list is: 101 -> 2 -> 33
```

## DoubleLinkedList

#### DoubleLinkedList informations availables:
- elementSize (var type bytes)
- capacity (how many items can double linked list can have)
- length (how many items double linked list actually has)

#### DoubleLinkedList methods:
- DoubleList_New
- DoubleList_Append
- DoubleList_RemoveAt
- DoubleList_GetAt
- DoubleList_Shuffle
- DoubleList_SwitchElements
- DoubleList_Clone
- DoubleList_InsertAfter
- DoubleList_InsertBefore
- DoubleList_IncreaseCapacity
 
## Set
Actually it's only for strings. Set can only store unique key.<br>
It enlarge its size everytime it would add an element in an index with size hashmapSize - 1.

#### Set methods:
- NewTableSet
- InsertToSet
- Search
- Remove
- M_IncreaseHashmapSize (You should not use it - It will be hide next updates)
