#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

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

void printPerson(const Person *p) {
    if (!p) {
        printf("Null Person reference.\n");
        return;
    }

    printf("Person(Name: %s, Age: %d, Gender: %c, DOB: %02d-%02d-%d, Address: %s%s%s)\n",
           p->name, p->age, p->gender,
           p->dateOfBirth.MM, p->dateOfBirth.DD, p->dateOfBirth.YYYY,
           p->homeAddress.address1,
           p->homeAddress.address2 ? ", " : "",
           p->homeAddress.address2 ? p->homeAddress.address2 : "");
}

void testIntList() {
    List intList;
    initList(&intList, int);
    add(&intList, int, 10);
    add(&intList, int, 20);
    add(&intList, int, 30);
    printf("Int List contains 20: %d\n", contains(&intList, int, 20));
    remove(&intList, int, 20);
    printf("Int List after removing 20, contains 20: %d\n", contains(&intList, int, 20));
    freeList(&intList);
}

void testDoubleList() {
    List doubleList;
    initList(&doubleList, double);
    add(&doubleList, double, 5.5);
    add(&doubleList, double, 10.1);
    printf("Double List contains 10.1: %d\n", contains(&doubleList, double, 10.1));
    remove(&doubleList, double, 10.1);
    printf("Double List after removing 10.1, contains 10.1: %d\n", contains(&doubleList, double, 10.1));
    freeList(&doubleList);
}

void testCharList() {
    List charList;
    initList(&charList, char);
    add(&charList, char, 'A');
    add(&charList, char, 'B');
    printf("Char List contains 'B': %d\n", contains(&charList, char, 'B'));
    remove(&charList, char, 'B');
    printf("Char List after removing 'B', contains 'B': %d\n", contains(&charList, char, 'B'));
    freeList(&charList);
}

void testPersonList() {
    List personList;
    initList(&personList, Person);

    Person person1 = {"John Doe", 25, 'M', {12, 25, 1998}, {"123 Street", "Apt 456"}};
    Person person2 = {"Jane Smith", 30, 'F', {6, 15, 1993}, {"789 Avenue", "Suite 101"}};

    add(&personList, Person, person1);
    add(&personList, Person, person2);
    printf("Person List contains Jane Smith: %d\n", contains(&personList, Person, person2));
    remove(&personList, Person, person2);
    printf("Person List after removing Jane Smith, contains Jane Smith: %d\n", contains(&personList, Person, person2));
    freeList(&personList);
}

int main() {
    testIntList();
    testDoubleList();
    testCharList();
    testPersonList();

    printf("\n");
    Person p;

    typeof(p) p2 = { "Jose", 44, 'M', {2, 22, 2222}, {"add1", "add2"}};
    printPerson(&p2);

    return 0;
}
