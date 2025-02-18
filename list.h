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
 * @brief Initializes a list with a specific data type.
 * @param list A pointer to the list to initialize.
 * @param dataType The data type of the list's elements.
 *
 * Initializes the list with the specified data type, setting the initial size to 8.
 * It also allocates memory for the list's data and sets up the necessary metadata.
 */
#define list_INIT(list, dataType) do {                                              \
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
 * @param list A pointer to the list to add an element to.
 * @param dataType The data type of the element to add.
 * @param inputData The element to add to the list.
 *
 * If the list's current capacity is exceeded, the list will be reallocated to double
 * its size. The element is copied into the list at the next available position.
 */
#define list_ADD(list, dataType, inputData) do {                                    \
    dataType temp = (inputData); /* Create a temporary variable */                  \
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
 * @brief Adds multiple elements to the list.
 * @param list A pointer to the list to add elements to.
 * @param dataType The data type of the elements to add.
 * @param count The number of elements to add.
 * @param ... The elements to add to the list.
 *
 * This macro takes a variable number of arguments and adds each one to the list.
 */
#define list_ADD_ALL(list, dataType, count, ...) do {                              \
    dataType values[] = {__VA_ARGS__};                                             \
    for (int i = 0; i < (count); i++) {                                            \
        list_ADD(list, dataType, values[i]);                                            \
    }                                                                              \
} while (0)


/**
 * @brief Adds an element at a specific index in the list.
 * @param list A pointer to the list to add the element to.
 * @param dataType The data type of the element to add.
 * @param inputData The element to add to the list.
 * @param index The index at which to insert the element.
 *
 * This macro adds an element to the list at the specified index. The existing elements
 * are shifted accordingly to accommodate the new element.
 */
#define list_ADD_AT(list, dataType, inputData, index) do {                          \
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
 * @param list A pointer to the list from which to remove an element.
 * @param dataType The data type of the element to remove.
 * @param inputData The element to remove from the list.
 *
 * This macro removes the first occurrence of the specified element from the list.
 * The remaining elements are shifted accordingly.
 */
#define list_REMOVE(list, dataType, inputData) do {                                 \
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
 * @brief Removes an element at a specific index in the list.
 * @param list A pointer to the list from which to remove an element.
 * @param dataType The data type of the element to remove.
 * @param index The index of the element to remove.
 *
 * This macro removes the element at the specified index, shifting the remaining
 * elements accordingly.
 */
#define list_REMOVE_AT(list, dataType, index) do {                                  \
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
 * @param list A pointer to the list.
 * @param dataType The data type of the element.
 * @param inputData The element to search for.
 * @return The index of the element, or -1 if the element is not found.
 *
 * This macro returns the index of the first occurrence of the specified element.
 */
#define list_GET_INDEX_OF(list, dataType, inputData) ({                             \
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
 * @brief Checks if the list contains a specific element.
 * @param list A pointer to the list.
 * @param dataType The data type of the element.
 * @param inputData The element to check for.
 * @return true if the element is found in the list, false otherwise.
 */
#define list_CONTAINS(list, dataType, inputData) ({                \
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
 * @param list A pointer to the list.
 * @param dataType The data type of the elements in the list.
 * @return A pointer to an array of the list's elements.
 *
 * This macro allocates memory for an array, copies the elements of the list into
 * the array, and returns the array.
 */
#define list_TO_ARRAY(list, dataType) ({                              \
    dataType *array = malloc((list)->currentCount * (list)->size); \
    if (!array) {                                              \
        fprintf(stderr, "Memory allocation failed\n");         \
        exit(EXIT_FAILURE);                                    \
    }                                                          \
    memcpy(array, (list)->data, (list)->dataSize);             \
    array;                                                     \
})


/**
 * @brief Collects elements from the list into a sublist based on an expression.
 * @param list A pointer to the list.
 * @param dataType The data type of the elements in the list.
 * @param expression The expression to evaluate for each element.
 * @param subList A pointer to the sublist to collect the elements into.
 *
 * This macro creates a sublist by iterating over the elements of the list and adding
 * them to the sublist if they satisfy the given expression. 
 * 
 * @warning Use "element" to compare and treat it as a pointer. Read more in README.
 * 
 */
#define list_COLLECT_TO_SUBLIST(list, dataType, expression, subList) do {           \
    list_INIT(subList, dataType);                                                    \
    for (int i = 0; i < (list)->currentCount; i++) {                                \
        dataType *element = (dataType *)((char *)(list)->data + (i * (list)->size));\
        if (expression) {                                                           \
            list_ADD(subList, dataType, *element);                                       \
        }                                                                           \
    }                                                                               \
} while (0)


/**
 * @brief Retrieves an element from the list at a specific index.
 * @param list A pointer to the list.
 * @param dataType The data type of the element.
 * @param index The index of the element to retrieve.
 * @return A pointer to the element at the specified index, or NULL if the index is invalid.
 */
#define list_GET(list, dataType, index)                                             \
    ((index) < (list)->currentCount ?                                               \
        (dataType *)((char *)(list)->data + (index) * (list)->size) :               \
(printf("No value\n"), (dataType*)NULL))


/**
 * @brief Sets an element at a specific index in the list.
 * @param list A pointer to the list.
 * @param dataType The data type of the element.
 * @param index The index at which to set the element.
 * @param inputData The new element to set at the specified index.
 *
 * This macro replaces the element at the specified index with the new element.
 */
#define list_SET(list, dataType, index, inputData) do {                             \
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
 * @brief Converts an array to a list.
 * @param list A pointer to the list to which to add the array elements.
 * @param dataType The data type of the elements in the array.
 * @param array The array to convert to a list.
 *
 * This macro iterates over the elements of the array and adds each one to the list.
 */
#define list_ARRAY_TO_LIST(list, dataType, array) do {                      \
    size_t arraySize = sizeof(array) / sizeof((array)[0]);           \
    for (size_t i = 0; i < arraySize; i++) {                         \
        list_ADD(list, dataType, array[i]);                               \
    }                                                                \
} while (0)

int listLength(List *list);

char *listGetName(List *list);

char *listGetDataType(List *list);

void listFree(List *list);

void *listGetMemoryAddress(List *list, int index);

bool listIsEmpty(List *list);    

size_t listSizeOf(List *list);

size_t listSizeOfData(List *list);

#endif /* LIST_H */