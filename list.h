/**
 * @file list.h
 * @brief Dynamic list implementation in C using macros.
 * @author Mark Jayson Lanuzo
 * @date 2025-02-14
 */

#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct List {
    void *data;          /**< Pointer to the stored data */
    int currentCount;    /**< Number of elements currently in the list */
    int initSize;        /**< Initial allocated size (number of elements) */
    char *dataTypeOf;    /**< Data type of the elements */
    char *nameOf;        /**< Name of the list */
    size_t size;         /**< Size of each element */
    size_t dataSize;     /**< Actual size of stored data in bytes */
    size_t listSize;     /**< Total allocated memory size in bytes */
} List;


/**
 * @brief Initializes a dynamic list.
 * 
 * @param list Pointer to the list structure.
 * @param dataType Data type of the elements.
 */
#define initList(list, dataType) do {                                               \
    (list)->dataTypeOf = strdup(#dataType);                                         \
    (list)->nameOf = strdup(#list);                                                 \
    (list)->initSize = 8;                                                           \
    (list)->currentCount = 0;                                                       \
    (list)->size = sizeof(dataType);                                                \
    (list)->dataSize = 0;                                                           \
    (list)->listSize = (list)->initSize * (list)->size;                             \
    (list)->data = calloc((list)->initSize, (list)->size);                          \
    if (!(list)->data) {                                                            \
        fprintf(stderr, "Memory allocation failed\n");                              \
        exit(EXIT_FAILURE);                                                         \
    }                                                                               \
} while (0)


/**
 * @brief Adds an element to the list.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param inputData The element to add.
 */
#define add(list, dataType, inputData) do {                                         \
    dataType temp = (inputData); /* Create a temporary variable */                 \
    if ((list)->currentCount >= (list)->initSize) {                                 \
        (list)->initSize *= 2;                                                      \
        (list)->listSize = (list)->initSize * (list)->size;                         \
        void *tempPtr = realloc((list)->data, (list)->listSize);                    \
        if (!tempPtr) {                                                             \
            fprintf(stderr, "Memory allocation failed\n");                          \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
        (list)->data = tempPtr;                                                     \
    }                                                                               \
    memcpy((char*)(list)->data + ((list)->currentCount * (list)->size),             \
           &temp, (list)->size);                                                    \
    (list)->currentCount++;                                                         \
    (list)->dataSize = (list)->currentCount * (list)->size;                         \
} while (0)


/**
 * @brief Adds multiple elements to the list at once.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the elements.
 * @param count Number of elements to add.
 * @param ... Variable number of elements to add.
 * 
 * @note This macro expands into multiple calls to `add`, ensuring that all elements
 *       are inserted into the list sequentially.
 * 
 * @warning Ensure that `count` matches the number of elements provided in `...`
 *          to avoid unexpected behavior.
 * 
 * @example
 * List myList;
 * initList(&myList, int);
 * addAll(&myList, int, 3, 10, 20, 30);
 * freeList(&myList);
 */
#define addAll(list, dataType, count, ...) do {                                    \
    dataType values[] = {__VA_ARGS__};                                             \
    for (int i = 0; i < (count); i++) {                                            \
        add(list, dataType, values[i]);                                            \
    }                                                                              \
} while (0)


/**
 * @brief Inserts an element at a specified index.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param inputData The element to add.
 * @param index Position to insert the element.
 */
#define addAt(list, dataType, inputData, index) do {                                \
    if ((index) < 0 || (index) > (list)->currentCount) {                            \
        printf("Invalid index\n");                                                  \
        break;                                                                      \
    }                                                                               \
    if ((list)->currentCount >= (list)->initSize) {                                 \
        (list)->initSize *= 2;                                                      \
        (list)->listSize = (list)->initSize * (list)->size;                         \
        void *temp = realloc((list)->data, (list)->listSize);                       \
        if (!temp) {                                                                \
            fprintf(stderr, "Memory allocation failed\n");                          \
            exit(EXIT_FAILURE);                                                     \
        }                                                                           \
        (list)->data = temp;                                                        \
    }                                                                               \
    memmove((char *)(list)->data + ((index) + 1) * (list)->size,                    \
            (char *)(list)->data + (index) * (list)->size,                          \
            ((list)->currentCount - (index)) * (list)->size);                       \
    memcpy((char *)(list)->data + (index) * (list)->size,                           \
           &(inputData), (list)->size);                                             \
    (list)->currentCount++;                                                         \
    (list)->dataSize = (list)->currentCount * (list)->size;                         \
} while (0)


/**
 * @brief Removes an element from the list.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param inputData The element to remove.
 */
#define remove(list, dataType, inputData) do {                                      \
    dataType temp = (inputData); /* Store inputData in a temporary variable */      \
    int foundIndex = -1;                                                            \
    for (int i = 0; i < (list)->currentCount; i++) {                                \
        dataType *element = (dataType *)((char *)(list)->data + (i * (list)->size));\
        if (memcmp(element, &temp, sizeof(dataType)) == 0) {                        \
            foundIndex = i;                                                         \
            break;                                                                  \
        }                                                                           \
    }                                                                               \
    if (foundIndex != -1) {                                                         \
        for (int i = foundIndex; i < (list)->currentCount - 1; i++) {               \
            memcpy((char *)(list)->data + (i * (list)->size),                       \
                   (char *)(list)->data + ((i + 1) * (list)->size),                 \
                   (list)->size);                                                   \
        }                                                                           \
        (list)->currentCount--;                                                     \
        (list)->dataSize = (list)->currentCount * (list)->size;                     \
    } else {                                                                        \
        printf("Value not found in the list.\n");                                   \
    }                                                                               \
} while (0)



/**
 * @brief Removes an element at a specified index.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param index Index of the element to remove.
 */
#define removeAt(list, dataType, index) do {                                        \
    if ((index) < 0 || (index) >= (list)->currentCount) {                           \
        printf("Invalid index: %d\n", (index));                                     \
        break;                                                                      \
    }                                                                               \
    for (int i = (index); i < (list)->currentCount - 1; i++) {                      \
        memcpy((char *)(list)->data + (i * (list)->size),                           \
               (char *)(list)->data + ((i + 1) * (list)->size),                     \
               (list)->size);                                                       \
    }                                                                               \
    (list)->currentCount--;                                                         \
    (list)->dataSize = (list)->currentCount * (list)->size;                         \
} while (0)


/**
 * @brief Gets the index of an element in the list.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param inputData The element to search for.
 * @return The index of the element, or -1 if not found.
 */
#define getIndexOf(list, dataType, inputData) ({                                    \
    int foundIndex = -1;                                                            \
    for (int i = 0; i < (list)->currentCount; i++) {                                \
        if (memcmp((char *)(list)->data + (i * (list)->size),                       \
                   &(inputData), (list)->size) == 0) {                              \
            foundIndex = i;                                                         \
            break;                                                                  \
        }                                                                           \
    }                                                                               \
    foundIndex;                                                                     \
})


/**
 * @brief Checks if an element exists in the list.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param inputData The element to check.
 * @return 1 if found, 0 otherwise.
 */
#define contains(list, dataType, inputData) ({                     \
    int found = 0;                                                 \
    dataType temp = (inputData);                                   \
    for (int i = 0; i < (list)->currentCount; i++) {               \
        if (memcmp((char *)(list)->data + (i * (list)->size),      \
                   &temp, (list)->size) == 0) {                    \
            found = 1;                                             \
            break;                                                 \
        }                                                          \
    }                                                              \
    found;                                                         \
})


/**
 * @brief Converts the list to an array.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the elements.
 * @return A dynamically allocated array of elements.
 */
#define toArray(list, dataType) ({                              \
    dataType *array = malloc((list)->currentCount * (list)->size); \
    if (!array) {                                              \
        fprintf(stderr, "Memory allocation failed\n");         \
        exit(EXIT_FAILURE);                                    \
    }                                                          \
    memcpy(array, (list)->data, (list)->dataSize);             \
    array;                                                     \
})


/**
 * @brief Collects elements matching an expression into a sublist.
 * 
 * @param list Source list.
 * @param dataType Type of elements.
 * @param expression Condition to match.
 * @param subList Destination list.
 */
#define collectToSubList(list, dataType, expression, subList) do {    \
    initList(subList, dataType);                                     \
    for (int i = 0; i < (list)->currentCount; i++) {                  \
        dataType *element = (dataType *)((char *)(list)->data + (i * (list)->size)); \
        if (expression) {                                             \
            add(subList, dataType, *element);                        \
        }                                                             \
    }                                                                 \
} while (0)


/**
 * @brief Retrieves an element at a given index.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param index Index of the element.
 * @return Pointer to the element, or NULL if out of bounds.
 */
#define get(list, dataType, index)                                                  \
    ((index) < (list)->currentCount ?                                               \
        (dataType *)((char *)(list)->data + (index) * (list)->size) :               \
(printf("No value\n"), (dataType*)NULL))


/**
 * @brief Sets an element at a given index.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of the element.
 * @param index Index of the element.
 * @param inputData New value to set.
 */
#define set(list, dataType, index, inputData) do {                                  \
    dataType temp = (inputData);                                                    \
    if ((index) < 0 || (index) >= (list)->currentCount) {                           \
        printf("Invalid index: %d\n", (index));                                     \
        break;                                                                      \
    }                                                                               \
    memcpy((char *)(list)->data + ((index) * (list)->size), &temp, (list)->size);   \
    (list)->dataSize = (list)->currentCount * (list)->size;                         \
    (list)->listSize = (list)->initSize * (list)->size;                             \
} while (0)


/**
 * @brief Converts an array to a dynamic list.
 * 
 * @param list Pointer to the list.
 * @param dataType Type of elements.
 * @param array Source array.
 */
#define arrayToList(list, dataType, array) do {                      \
    size_t arraySize = sizeof(array) / sizeof((array)[0]);           \
    for (size_t i = 0; i < arraySize; i++) {                         \
        add(list, dataType, array[i]);                               \
    }                                                                \
} while (0)


/**
 * @brief Converts an array into a dynamic list.
 * 
 * @param list Pointer to the List structure to initialize.
 * @param dataType The data type of elements in the array.
 * @param array The source array.
 * @param arraySize The number of elements in the array.
 * 
 * @note This macro initializes the list and adds all elements from the array.
 */
#define arrayToList(list, dataType, array, arraySize) do {  \
    initList(list, dataType);                              \
    for (size_t i = 0; i < (arraySize); i++) {             \
        add(list, dataType, (array)[i]);                   \
    }                                                      \
} while (0)

int listSize(List *list);

char *getNameOf(List *list);

char *getDataTypeOf(List *list);

void freeList(List *list);

void *getMemoryAddress(List *list, int index);

bool isEmpty(List *list);    

size_t sizeOfList(List *list);

size_t sizeOfData(List *list);

#endif /* LIST_H */