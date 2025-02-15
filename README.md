# Dynamic List Library

## Overview
This library provides a dynamic list implementation in C using macros and functions. It supports adding, removing, retrieving, and managing elements in a dynamically allocated array-like structure.

## Installation
Simply include `list.h` and `list.c` in your project:
```c
#include "list.h"
```
Compile with:
```sh
gcc -o program main.c list.c
```

## Data Structure
```c
typedef struct List {
    void *data;          // Pointer to the stored data
    int currentCount;    // Number of elements currently in the list
    int initSize;        // Initial allocated size
    char *dataTypeOf;    // Data type of the elements
    char *nameOf;        // Name of the list
    size_t size;         // Size of each element
    size_t dataSize;     // Actual size of stored data
    size_t listSize;     // Total allocated memory size
} List;
```

## Functions and Examples

### `initList(List *list, dataType)`
Initializes a list with a given data type.
```c
List myList;
initList(&myList, int);
```

### `add(List *list, dataType, inputData)`
Adds an element to the list.
```c
int value = 10;
add(&myList, int, value);
```

### `addAt(List *list, dataType, inputData, index)`
Inserts an element at a specified index.
```c
int value = 20;
addAt(&myList, int, value, 0);
```

### `remove(List *list, dataType, inputData)`
Removes an element from the list.
```c
remove(&myList, int, value);
```

### `removeAt(List *list, dataType, index)`
Removes an element at a specified index.
```c
removeAt(&myList, int, 0);
```

### `getIndexOf(List *list, dataType, inputData)`
Gets the index of an element.
```c
int index = getIndexOf(&myList, int, value);
```

### `contains(List *list, dataType, inputData)`
Checks if the list contains a given element.
```c
if (contains(&myList, int, value)) {
    printf("Element found!\n");
}
```

### `toArray(List *list, dataType)`
Converts the list to an array.
```c
int *array = toArray(&myList, int);
free(array);
```

### `collectToSubList(List *list, dataType, expression, subList)`
Filters elements based on a condition and stores them in a sublist.
```c
List evenNumbers;
collectToSubList(&myList, int, (*element % 2 == 0), &evenNumbers);
```

### `get(List *list, dataType, index)`
Retrieves an element at a given index.
```c
int *val = get(&myList, int, 0);
if (val) printf("%d\n", *val);
```

### `set(List *list, dataType, index, inputData)`
Sets an element at a given index.
```c
set(&myList, int, 0, 50);
```

### `arrayToList(List *list, dataType, array)`
Converts an array to a list.
```c
int numbers[] = {1, 2, 3};
arrayToList(&myList, int, numbers);
```

### `listSize(List *list)`
Returns the number of elements in the list.
```c
int count = listSize(&myList);
```

### `getNameOf(List *list)`
Gets the name of the list.
```c
printf("%s\n", getNameOf(&myList));
```

### `getDataTypeOf(List *list)`
Gets the data type of the elements stored in the list.
```c
printf("%s\n", getDataTypeOf(&myList));
```

### `freeList(List *list)`
Frees the memory allocated for the list.
```c
freeList(&myList);
```

### `isEmpty(List *list)`
Checks if the list is empty.
```c
if (isEmpty(&myList)) {
    printf("List is empty\n");
}
```

### `sizeOfList(List *list)`
Returns the total allocated memory size of the list in bytes.
```c
size_t totalSize = sizeOfList(&myList);
```

### `sizeOfData(List *list)`
Returns the actual used memory size for stored data in bytes.
```c
size_t usedSize = sizeOfData(&myList);
```

## License
MIT License

## Author
Mark Jayson Lanuzo
