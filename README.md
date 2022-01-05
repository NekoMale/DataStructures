# C-DataStructures
 
Actually there are only:
- LinkedList
- DoubleLinkedList
- Set (unique keys)

**LinkedList** and **DoubleLinkedList** either have already implemented a version with string value.<br>
I'm going to improve them in order to not have to declare a structure for every var type.

## LinkedList
It can be declared with any var type inside "LinkedListExtension.h" in this way:

```
typedef struct S{VarType}Item {
	NodeList node;
	const {VarType}* {VarName};
} {VarType}Item;
```

#### LinkedList methods:
- GetListTail
- AppendToList
- PopFromList
- RemoveLastFromList
- RemoveItemFromList
- ReverseList

## DoubleLinkedList
It can be declared with any var type inside "LinkedListExtension.h" in this way:

```
typedef struct SDouble{VarType}Item {
	DoubleNodeList node;
	const {VarType}* {VarName};
} Double{VarType}Item;
```

#### DoubleLinkedList methods:
- GetDoubleListTail
- AppendToDoubleList
- RemoveFromDoubleList
- InsertIntoDoubleListAfterElement
- InsertIntoDoubleListBeforeElement
- GetDoubleElementAt
- Length
- Shuffle

#### StringDoubleLinkedList methods:
- Clone
 
## Set
Actually it's only for strings. Set can only store unique key.<br>
It enlarge its size everytime it would add an element in an index with size hashmapSize - 1.

#### Set methods:
- NewTableSet
- InsertToSet
- Search
- Remove
- M_IncreaseHashmapSize (You should not use it - It will be hide next updates)
