#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.h"



/**
 * @brief Returns the current length of the list.
 * @param list A pointer to the List.
 * @return The number of elements in the list.
 */
int listLength(List *list) {
    return list->currentCount;
}

/**
 * @brief Gets the name of the list.
 * 
 * @param list Pointer to the List structure.
 * @return char* Pointer to the list name, or "Unnamed List" if not initialized.
 * 
 * @note If the name starts with '&', it skips the first character.
 */
char *listGetName(List *list) {
    if (list == NULL || list->nameOf == NULL) {
        return "Unnamed List";  // Default name if uninitialized
    }

    if (list->nameOf[0] == '&') {  // If the first character is '&', skip it
        return list->nameOf + 1;
    }

    return list->nameOf;
}

/**
 * @brief Gets the data type of the elements in the list.
 * @param list A pointer to the List.
 * @return The data type of the elements in the list.
 */
char *listGetDataType(List *list) {
    return list->dataTypeOf;
}

/**
 * @brief Frees the memory allocated for the list.
 * 
 * @param list Pointer to the List structure.
 * 
 * @note This function sets pointers to NULL after freeing to avoid dangling references.
 */
void listFree(List *list) {
    if (list->data) {
        free(list->data);
    }
    if (list->nameOf) {
        list->nameOf = NULL;
    }
    if (list->dataTypeOf) {
        list->dataTypeOf = NULL;
    }

    // Reset list properties
    list->currentCount = 0;
    list->initSize = 0;
    list->size = 0;
}

/**
 * @brief Returns the memory address of an element in the list at the specified index.
 * @param list A pointer to the List.
 * @param index The index of the element.
 * @return A pointer to the memory address of the element, or NULL if the index is invalid.
 */
void *listGetMemoryAddress(List *list, int index) {
    if (index < 0 || index >= list->currentCount) {
        printf("Invalid index: %d\n", index);
        return NULL;
    }
    return (void *)((char *)(list->data) + (index * list->size));
}

/**
 * @brief Checks if the list is empty.
 * @param list A pointer to the List.
 * @return true if the list is empty, false otherwise.
 */
bool listIsEmpty(List *list) {
    return list->currentCount == 0;
}

/**
 * @brief Gets the size of each element in the list.
 * @param list A pointer to the List.
 * @return The size of each element in the list.
 */
size_t listSizeOf(List *list) {
    return list ? list->listSize : 0;
}

/**
 * @brief Gets the total size of the data stored in the list (currentCount * size).
 * @param list A pointer to the List.
 * @return The total size of the data in the list in bytes.
 */
size_t listSizeOfData(List *list) {
    return list ? list->dataSize : 0;
}
