# C-DataStructures
 
## LinkedList
Actually there is only LinkedList data structure prototype. It can be declared with any var type inside "LinkedListExtension.h" in this way:

```
typedef struct S{VarType}Item {
	NodeList node;
	const {VarType}* {VarName};
} {VarType}Item;
```

I'm going to improving it without the need to declare for any kind of LinkedList.

#### LinkedList methods:
- GetListTail
- AppendToList
- PopFromList
- RemoveLastFromList
- RemoveItemFromList
- ReverseList
