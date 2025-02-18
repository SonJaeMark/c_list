# ListV2 Library

## Overview
`List` is a dynamic list implementation in C using macros and functions to provide an easy-to-use, efficient, and flexible data structure for managing collections of elements. It supports adding, removing, accessing, and managing elements dynamically while maintaining memory efficiency.

## Features
- Dynamic memory allocation and resizing
- Easy element insertion and deletion
- Macro-based operations for efficiency
- Supports any data type
- List of Macros:
  - `list_INIT`
  - `list_ADD`
  - `list_ADD_ALL`
  - `list_ADD_AT`
  - `list_REMOVE`
  - `list_REMOVE_AT`
  - `list_GET`
  - `list_SET`
  - `list_GET_INDEX_OF`
  - `list_CONTAINS`
  - `list_TO_ARRAY`
  - `list_ARRAY_TO_LIST`
  - `list_COLLECT_TO_SUBLIST`
- List of Functions:
  - `listLenght`
  - `listGetName`
  - `listGetDataType`
  - `listFree`
  - `listGetMemoryAddress`
  - `listIsEmpty`
  - `listSizeOf`
  - `listSizeOfData`
- Dynamic memory allocation and resizing
- Easy element insertion and deletion
- Macro-based operations for efficiency
- Supports any data type

## Installation
To use `List` in your project, include the following files:

- `list.h`
- `list.c`

Include them in your project and compile with:
```sh
gcc your_program.c list.c -o your_program
```

## Using `List` with the `Person` Struct
### Struct Definition
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

## Example Usage of Each Function and Macro with `Person`

### Initializing a List
```c
List people;
list_INIT(&people, Person);
```

### Adding a Person to the List
```c
Person p1 = {"Alice", 30, 'F', {1, 15, 1993}, {"123 Main St", "Apt 4B"}};
list_ADD(&people, Person, p1);
// or
// list_ADD(&people, Person, {"Alice", 30, 'F', {1, 15, 1993}, {"123 Main St", "Apt 4B"}});
```

### Adding Multiple People
```c
Person p2 = {"Bob", 25, 'M', {6, 20, 1998}, {"456 Elm St", ""}};
Person p3 = {"Charlie", 40, 'M', {12, 5, 1983}, {"789 Oak St", "Suite 2"}};
list_ADD_ALL(&people, Person, 2, p2, p3);
```

### Adding a Person at a Specific Index
```c
Person p4 = {"David", 28, 'M', {4, 10, 1995}, {"321 Pine St", ""}};
list_ADD_AT(&people, Person, p4, 1);
```

### Checking if the List is Empty
```c
if (listIsEmpty(&people)) {
    printf("The list is empty.\n");
} else {
    printf("The list is not empty.\n");
}
```

### Getting the List Name
```c
printf("List Name: %s\n", listGetName(&people));
```

### Getting the Data Type of List Elements
```c
printf("List Data Type: %s\n", listGetDataType(&people));
```

### Getting Index of a Person
```c
int index = list_GET_INDEX_OF(&people, Person, p3);
printf("Charlie is at index %d\n", index);
```

### Checking if a Person Exists in the List
```c
if (list_CONTAINS(&people, Person, p1)) {
    printf("Alice is in the list.\n");
}
```

### Retrieving a Person from the List
```c
Person *retrieved = list_GET(&people, Person, 1);
if (retrieved) {
    printf("Retrieved Person: %s, Age: %d\n", retrieved->name, retrieved->age);
}
```

### Setting a Person at a Specific Index
```c
Person p5 = {"Eve", 35, 'F', {7, 22, 1988}, {"555 Birch Rd", "Apt 10"}};
list_SET(&people, Person, 2, p5);
```

### Getting Memory Address of an Element
```c
void *address = listGetMemoryAddress(&people, 1);
printf("Memory Address of Index 1: %p\n", address);
```

### Removing a Person from the List
```c
list_REMOVE(&people, Person, p2);
```

### Removing a Person by Index
```c
list_REMOVE_AT(&people, Person, 0);
```

### Getting List Length
```c
printf("List Length: %d\n", listLength(&people));
```

### Getting Size of an Element
```c
printf("Element Size: %zu\n", listSizeOf(&people));
```

### Getting Total Data Size
```c
printf("Total Data Size: %zu\n", listSizeOfData(&people));
```

### Converting the List to an Array
```c
Person *array = list_TO_ARRAY(&people, Person);
printf("First person in array: %s\n", array[0].name);
free(array);
```

### Collecting a Sublist of People Older Than 30
To use this macro always refer on element in comaparing. Use "*element" to dereference and get the
value of in its internal logic for data types such as int, double, char etc.. As well as "element->"
for accessing the member of a struct.

example with int:

```c
List gradeList;
List passedGradesList;

list_INIT(&gradeList, int);

list_ADD_ALL(&gradeList, int, 6, 79, 75, 89, 73, 98, 70);

list_COLLECT_TO_SUBLIST(&gradeList, int, *element >= 75, &passedGradesList);

for(int i = 0; i < listLenght(&passedGradesList); i++)
{
    printf("Grade: %d\n", list_GET(&passedGradesList, int, i));
}

listFree(&gradeList);
listFree(&passedGradesList);
```
example in *char[]/char[][]:

```c
// Initialize main list
List stringList;
list_INIT(&stringList, char*);
       
// Define an array of strings
char *words[] = {"Apple", "Banana", "Avocado", "Cherry", "Apricot", "Blueberry"};
       
// Add words to list
for (int i = 0; i < sizeof(words) / sizeof(words[0]); i++) {
    list_ADD(&stringList, char*, words[i]);
}
       
// Initialize sublist
List subList;
       
// Collect strings starting with 'A'
list_COLLECT_TO_SUBLIST(&stringList, char*, (*element[0] == 'A'), &subList);
       
// Print sublist contents
printf("Filtered List (Words starting with 'A'):\n");
for (int i = 0; i < subList.currentCount; i++) {
    printf("%s\n", *(char**)list_GET(&subList, char*, i));
}
       
// Free memory
listFree(&stringList);
listFree(&subList);
```
example with struct: 

```c
List olderPeople;
list_COLLECT_TO_SUBLIST(&people, Person, element->age > 30, &olderPeople);
printf("Older People List Length: %d\n", listLenght(&olderPeople));
listFree(&olderPeople);
```

### Converting an Array to a List
```c
Person peopleArray[] = {p1, p2, p3};
list_ARRAY_TO_LIST(&people, Person, peopleArray);
printf("New List Length: %d\n", listLenght(&people));
```

### Freeing List Memory
```c
listFree(&people);
```

## Conclusion
The `List` library provides a powerful and easy-to-use dynamic list system in C. By using macros, it simplifies list management, making it highly efficient and adaptable for various data types, including user-defined structures like `Person`.

