#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

typedef struct 
{
    char *name;
    int age;
    char gender;
} Person;

void testListFunctions();
void collectToTest();
void arrayToListTest();
void printList(List *list);

int main(int argc, char const *argv[])
{
    testListFunctions();
    printf("\n");
    collectToTest();
    printf("\n");
    arrayToListTest();
    
    return 0;
}

void testListFunctions() {
    printf("===== TESTING LIST FUNCTIONS =====\n");

    // Initialize list
    List personList;
    initList(&personList, Person);
    printf("List initialized successfully.\n\n");

    // Create test data
    Person p1 = {"Alice", 25, 'F'};
    Person p2 = {"Bob", 30, 'M'};
    Person p3 = {"Charlie", 22, 'M'};
    Person p4 = {"Diana", 28, 'F'};

    // Add elements
    add(&personList, Person, p1);
    add(&personList, Person, p2);
    add(&personList, Person, p3);
    printf("Added 3 elements.\n\n");

    // Check list size
    printf("List size after additions: %d\n\n", listSize(&personList));

    // Get and print elements
    printf("Retrieving elements:\n");
    for (int i = 0; i < listSize(&personList); i++) {
        Person *p = get(&personList, Person, i);
        if (p) printf("Index %d -> Name: %s, Age: %d, Gender: %c\n", i, p->name, p->age, p->gender);
    }

    // Insert element at index 1
    addAt(&personList, Person, p4, 1);
    printf("\nAdded Diana at index 1.\n");

    // Print elements again
    printf("After addAt operation:\n");
    for (int i = 0; i < listSize(&personList); i++) {
        Person *p = get(&personList, Person, i);
        if (p) printf("Index %d -> Name: %s, Age: %d, Gender: %c\n", i, p->name, p->age, p->gender);
    }

    // Test contains macro
    printf("Checking if Bob exists: %s\n", contains(&personList, Person, p2) ? "Yes" : "No");
    printf("Checking if Diana exists: %s\n\n", contains(&personList, Person, p4) ? "Yes" : "No");

    // Test getIndexOf macro
    printf("Index of Charlie: %d\n\n", getIndexOf(&personList, Person, p3));

    // Test set macro
    Person p5 = {"Eve", 26, 'F'};
    set(&personList, Person, 2, p5);
    printf("Replaced element at index 2 with Eve.\n\n");

    // Print elements after set operation
    printf("After set operation:\n");
    for (int i = 0; i < listSize(&personList); i++) {
        Person *p = get(&personList, Person, i);
        if (p) printf("Index %d -> Name: %s, Age: %d, Gender: %c\n", i, p->name, p->age, p->gender);
    }

    // Test remove macro
    remove(&personList, Person, p2);
    printf("\nRemoved Bob from the list.\n");

    // Print elements after remove operation
    printf("\nAfter remove operation:\n");
    for (int i = 0; i < listSize(&personList); i++) {
        Person *p = get(&personList, Person, i);
        if (p) printf("Index %d -> Name: %s, Age: %d, Gender: %c\n", i, p->name, p->age, p->gender);
    }

    // Test removeAt macro
    removeAt(&personList, Person, 1);
    printf("\nRemoved element at index 1.\n");

    // Print elements after removeAt operation
    printf("After removeAt operation:\n");
    for (int i = 0; i < listSize(&personList); i++) {
        Person *p = get(&personList, Person, i);
        if (p) printf("Index %d -> Name: %s, Age: %d, Gender: %c\n", i, p->name, p->age, p->gender);
    }

    // Test toArray macro
    Person *personArray = toArray(&personList, Person);
    printf("Converted list to array.\n");

    // Print converted array
    printf("Array contents:\n");
    for (int i = 0; i < personList.currentCount; i++) {
        printf("Index %d -> Name: %s, Age: %d, Gender: %c\n", i, personArray[i].name, personArray[i].age, personArray[i].gender);
    }
    free(personArray);

    // Test list metadata
    printf("\nList name: %s\n", getNameOf(&personList));
    printf("Data type: %s\n", getDataTypeOf(&personList));

    // Test memory address retrieval
    printf("\nMemory address of index 0: %p\n", getMemoryAddress(&personList, 0));

    // Test isEmpty function
    printf("\nIs list empty? %s\n", isEmpty(&personList) ? "Yes" : "No");

    // Free list memory
    freeList(&personList);
    printf("Freed list memory.\n");

    printf("===== TESTING COMPLETE =====\n");
}

void collectToTest()
{
    List people;
    initList(&people, Person);

    // Adding people
    Person p1 = {"Alice", 25, 'F'};
    Person p2 = {"Bob", 30, 'M'};
    Person p3 = {"Charlie", 22, 'M'};
    Person p4 = {"Diana", 28, 'F'};

    add(&people, Person, p1);
    add(&people, Person, p2);
    add(&people, Person, p3);
    add(&people, Person, p4);

    // Collect only people older than 25
    List olderThan25;
    collectToSubList(&people, Person, element->gender == 'F', &olderThan25);

    

    // Print the collected sublist
    printf("People older than 25:\n");
    for (int i = 0; i < olderThan25.currentCount; i++) {
        Person *p = (Person *)((char *)olderThan25.data + (i * olderThan25.size));
        printf("%s, Age: %d, Gender: %c\n", p->name, p->age, p->gender);
    }

    freeList(&people);
    freeList(&olderThan25);
}


void arrayToListTest()
{
    // Step 1: Initialize a List for Person
    List people;
    initList(&people, Person);

    // Step 2: Add individual Person elements
    Person p1 = {"Alice", 25, 'F'};
    Person p2 = {"Bob", 30, 'M'};
    add(&people, Person, p1);
    add(&people, Person, p2);

    // Step 3: Convert an array of Person structs into the List
    Person personArray[] = {
        {"Charlie", 22, 'M'},
        {"Diana", 28, 'F'},
        {"Eve", 35, 'F'}
    };
    arrayToList(&people, Person, personArray);

    // Step 4: Print the list
    printList(&people);

    // Step 5: Verify memory addresses (checking deep copy behavior)
    printf("\nMemory Addresses of Persons in List:\n");
    for (int i = 0; i < people.currentCount; i++) {
        printf("Person %d memory address: %p\n", i, (char *)people.data + (i * people.size));
    }

    // Step 6: Free memory
    freeList(&people);
}

void printList(List *list) {
    printf("List contains %d elements:\n", list->currentCount);
    for (int i = 0; i < list->currentCount; i++) {
        Person *p = (Person *)((char *)list->data + (i * list->size));
        printf("Person %d -> Name: %s, Age: %d, Gender: %c\n", i, p->name, p->age, p->gender);
    }
}