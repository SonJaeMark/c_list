# Dynamic List Library in C

## Overview
This library provides a dynamic list implementation in C using macros and functions. It supports various data types, including primitive types and structures, and offers flexible memory management.

## Features
- Generic list implementation
- Dynamic memory allocation
- Functions for adding, removing, searching, and managing list elements
- Works with any data type
- Easy-to-use macros

---

## Installation
Include `list.h` and `list.c` in your C project.

```c
#include "list.h"
```

Compile your program with:
```sh
gcc -o program your_file.c list.c
```

---

## Usage

### 1. Initializing a List
**Macro:** `initList(list, dataType)`

#### Example:
```c
List myList;
initList(&myList, int);
```

Creates a dynamic list that stores integers.

---

### 2. Adding Elements
**Macro:** `add(list, dataType, inputData)`

#### Example:
```c
add(&myList, int, 42);
```
Adds `42` to the list.

---

### 3. Adding an Element at a Specific Index
**Macro:** `addAt(list, dataType, inputData, index)`

#### Example:
```c
addAt(&myList, int, 50, 1);
```
Inserts `50` at index `1`.

---

### 4. Removing an Element
**Macro:** `remove(list, dataType, inputData)`

#### Example:
```c
remove(&myList, int, 42);
```
Removes the element `42` from the list.

---

### 5. Removing an Element at an Index
**Macro:** `removeAt(list, dataType, index)`

#### Example:
```c
removeAt(&myList, int, 0);
```
Removes the element at index `0`.

---

### 6. Checking if an Element Exists
**Macro:** `contains(list, dataType, inputData)`

#### Example:
```c
if (contains(&myList, int, 42)) {
    printf("42 is in the list!\n");
}
```
Returns `1` if `42` is found, otherwise `0`.

---

### 7. Getting an Element by Index
**Macro:** `get(list, dataType, index)`

#### Example:
```c
int *value = get(&myList, int, 1);
if (value) printf("Value: %d\n", *value);
```
Retrieves the value at index `1`.

---

### 8. Setting an Element at an Index
**Macro:** `set(list, dataType, index, inputData)`

#### Example:
```c
set(&myList, int, 1, 99);
```
Updates the element at index `1` to `99`.

---

### 9. Getting the Index of an Element
**Macro:** `getIndexOf(list, dataType, inputData)`

#### Example:
```c
int index = getIndexOf(&myList, int, 99);
```
Returns the index of `99` or `-1` if not found.

---

### 10. Converting a List to an Array
**Macro:** `toArray(list, dataType)`

#### Example:
```c
int *array = toArray(&myList, int);
free(array);
```
Converts the list into an array.

---

### 11. Freeing a List
**Function:** `void freeList(List *list);`

#### Example:
```c
freeList(&myList);
```
Frees allocated memory.

---

## Use Cases
- Managing dynamic collections of elements in C
- Working with unknown sizes of data
- Implementing generic data storage
- Avoiding fixed-size arrays in C programs

---

## Example Code
```c
#include <stdio.h>
#include "list.h"

int main() {
    List myList;
    initList(&myList, int);
    add(&myList, int, 10);
    add(&myList, int, 20);
    printf("Contains 20: %d\n", contains(&myList, int, 20));
    remove(&myList, int, 20);
    freeList(&myList);
    return 0;
}
```

---

## License
MIT License.

