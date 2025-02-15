# Dynamic List Library in C

## Overview

This library provides a simple dynamic list implementation in C using macros and functions. It allows users to create, manage, and manipulate lists that can store elements of any data type.

## Features

- Dynamic resizing
- Macros for easy list manipulation
- Support for various data types
- Functions for querying and memory management

## Installation

Simply include `list.h` and `list.c` in your project and compile them along with your main C file.

```sh
gcc -o main main.c list.c
```

## Structure Definitions

```c
typedef struct {
    int MM;
    int DD;
    int YYYY;
} Date;

typedef struct {
    char *address1;
    char *address2;
} Address;

typedef struct {
    char *name;
    int age;
    char gender;
    Date dateOfBirth;
    Address homeAddress;
} Person;
```

## Usage

### 1. Initializing a List

```c
List people;
initList(&people, Person);
```

**Use Case:** Creating a list to store `Person` structures dynamically.

### 2. Adding Elements

```c
Person p1 = {"John Doe", 30, 'M', {12, 25, 1993}, {"123 Main St", "Apt 4B"}};
add(&people, Person, p1);
```

**Use Case:** Appending a `Person` structure to the list.

### 3. Adding Multiple Elements

```c
Person p2 = {"Jane Smith", 28, 'F', {6, 15, 1995}, {"456 Oak St", "Suite 300"}};
Person p3 = {"Bob Johnson", 40, 'M', {3, 8, 1983}, {"789 Pine St", NULL}};
addAll(&people, Person, 2, p2, p3);
```

**Use Case:** Quickly adding multiple `Person` structures at once.

### 4. Inserting at a Specific Index

```c
Person p4 = {"Alice Brown", 35, 'F', {9, 10, 1988}, {"159 Elm St", "Floor 2"}};
addAt(&people, Person, p4, 1);
```

**Use Case:** Inserting a `Person` at index 1, shifting elements accordingly.

### 5. Removing an Element

```c
remove(&people, Person, p2);
```

**Use Case:** Removing a `Person` from the list if they exist.

### 6. Removing by Index

```c
removeAt(&people, Person, 0);
```

**Use Case:** Deleting a `Person` at index 0.

### 7. Checking if a List Contains an Element

```c
if (contains(&people, Person, p3)) {
    printf("Person exists in the list!\n");
}
```

**Use Case:** Searching for a `Person` before performing an operation.

### 8. Getting an Element

```c
Person *retrievedPerson = get(&people, Person, 2);
if (retrievedPerson) printf("Retrieved: %s, Age: %d\n", retrievedPerson->name, retrievedPerson->age);
```

**Use Case:** Retrieving a `Person` by index safely.

### 9. Setting a Value at an Index

```c
Person newPerson = {"Michael Scott", 45, 'M', {7, 15, 1979}, {"Dunder Mifflin", NULL}};
set(&people, Person, 1, newPerson);
```

**Use Case:** Updating a `Person` at a specific index.

### 10. Getting the Index of an Element

```c
int index = getIndexOf(&people, Person, p3);
```

**Use Case:** Finding where a `Person` is stored.

### 11. Converting List to an Array

```c
Person *array = toArray(&people, Person);
free(array);
```

**Use Case:** Exporting the list's contents to a normal array.

### 12. Collecting Elements into a Sublist

```c
List adults;
collectToSubList(&people, Person, (*element).age >= 18, &adults);
```

**Use Case:** Filtering only adults (age 18 or older) into a separate list.

```c
List ageList;
collectToSubList(&people, int, element->age, &ageList);
```

**Use Case:** Creating a separate list containing only ages of people.

### 13. Converting an Array to a List

```c
Person peopleArray[] = {
    {"John Doe", 30, 'M', {12, 25, 1993}, {"123 Main St", "Apt 4B"}},
    {"Jane Smith", 28, 'F', {6, 15, 1995}, {"456 Oak St", "Suite 300"}},
    {"Bob Johnson", 40, 'M', {3, 8, 1983}, {"789 Pine St", NULL}}
};

List peopleList;
arrayToList(&peopleList, Person, peopleArray, 3);
```

**Use Case:** Converting an array of `Person` structures into a dynamic list.

### 14. Checking if the List is Empty

```c
if (isEmpty(&people)) {
    printf("List is empty\n");
}
```

**Use Case:** Avoiding operations on an empty list.

### 15. Getting List Size

```c
int count = listSize(&people);
```

**Use Case:** Checking the number of elements in the list.

### 16. Getting Total Memory Allocated

```c
size_t totalMemory = sizeOfList(&people);
```

**Use Case:** Understanding memory usage.

### 17. Getting Used Data Memory Size

```c
size_t usedMemory = sizeOfData(&people);
```

**Use Case:** Measuring actual data storage.

### 18. Freeing the List

```c
freeList(&people);
```

**Use Case:** Preventing memory leaks.

## Conclusion

This dynamic list implementation provides a convenient way to handle dynamically allocated lists in C, with macros and functions simplifying usage. The examples above showcase various use cases to manage lists effectively using the `Person` structure.

