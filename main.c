
#include <stdio.h>

#include "list.h"

typedef struct {
    int MM;             /**< Month of birth */
    int DD;             /**< Day of birth */
    int YYYY;           /**< Year of birth */
} Date;

typedef struct {
    char *address1;     /**< First line of the address */
    char *address2;     /**< Second line of the address (optional) */
} Address;

typedef struct {
    char *name;         /**< Name of the person */
    int age;            /**< Age of the person */
    char gender;        /**< Gender of the person */
    Date dateOfBirth;   /**< Date of birth of the person */
    Address homeAddress; /**< Home address of the person */
} Person;

void printPerson(Person *p) {
    printf("Name: %s, Age: %d, Gender: %c, Date of Birth: %02d/%02d/%04d, Address 1: %s, Address 2: %s\n",
           p->name, p->age, p->gender, p->dateOfBirth.MM, p->dateOfBirth.DD, p->dateOfBirth.YYYY,
           p->homeAddress.address1, p->homeAddress.address2[0] != '\0' ? p->homeAddress.address2 : "N/A");
}

int main(int argc, char const *argv[])
{
    List personList;
    List olderPeople;


    Person person1 = {"John Doe", 30, 'M', {5, 15, 1993}, {"123 Main St", "Apt 4B"}};
    Person person2 = {"Jane Smith", 28, 'F', {8, 22, 1995}, {"456 Oak Ave", "Suite 2A"}};
    Person person3 = {"Alice Johnson", 35, 'F', {3, 10, 1988}, {"789 Pine Rd", ""}};
    Person person4 = {"Bob Brown", 40, 'M', {11, 30, 1983}, {"101 Maple Dr", "Floor 3"}};
    Person person5 = {"Charlie White", 25, 'M', {2, 5, 1998}, {"202 Birch Blvd", ""}};
    Person person6 = {"Diana Green", 22, 'F', {6, 18, 2001}, {"303 Cedar Ln", "Unit 1"}};


    list_INIT(&personList, Person);

    list_ADD(&personList, Person, person1);

    list_ADD_ALL(&personList, Person, 4, person2, person3, person4, person5);

    list_ADD_AT(&personList, Person, person6, 0);

    for (size_t i = 0; i < 6; i++)
    {
        printPerson(list_GET(&personList, Person, i));
    }

    printf("----------------------------------------------------------------------------------\n");
    
    list_REMOVE(&personList, Person, person1);

    for (size_t i = 0; i < 5; i++)
    {
        printPerson(list_GET(&personList, Person, i));
    }

    list_REMOVE_AT(&personList, Person, 1);
    
    printf("----------------------------------------------------------------------------------\n");

    for (size_t i = 0; i < 4; i++)
    {
        printPerson(list_GET(&personList, Person, i));
    }

    printf("----------------------------------------------------------------------------------\n");

    printPerson(list_GET(&personList, Person, list_GET_INDEX_OF(&personList, Person, person3)));
    
    
    printf("----------------------------------------------------------------------------------\n");

    list_COLLECT_TO_SUBLIST(&personList, Person, element->age > 30, &olderPeople);

    for (size_t i = 0; i < listLength(&olderPeople); i++)
    {
        printPerson(list_GET(&olderPeople, Person, i));
    }

    
    printf("----------------------------------------------------------------------------------\n");

    List gradeList;
    List passedGradesList;

    list_INIT(&gradeList, int);

    list_ADD_ALL(&gradeList, int, 6, 79, 75, 89, 73, 98, 70);

    list_COLLECT_TO_SUBLIST(&gradeList, int, *element >= 75, &passedGradesList);

    for(int i = 0; i < listLength(&passedGradesList); i++)
    {
        printf("Grade: %d\n", *list_GET(&passedGradesList, int, i));
    }

    printf("----------------------------------------------------------------------------------\n");


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

    listFree(&gradeList);
    listFree(&passedGradesList);

    listFree(&personList);
    listFree(&olderPeople);
    return 0;
}
