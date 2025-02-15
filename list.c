#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "list.h"



/**
 * @brief Gets the current number of elements in the list.
 * 
 * @param list Pointer to the List structure.
 * @return int Number of elements in the list.
 */
int listSize(List *list) {
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
char *getNameOf(List *list) {
    if (list == NULL || list->nameOf == NULL) {
        return "Unnamed List";  // Default name if uninitialized
    }

    if (list->nameOf[0] == '&') {  // If the first character is '&', skip it
        return list->nameOf + 1;
    }

    return list->nameOf;
}

/**
 * @brief Gets the data type of the elements stored in the list.
 * 
 * @param list Pointer to the List structure.
 * @return char* Pointer to the data type string.
 */
char *getDataTypeOf(List *list) {
    return list->dataTypeOf;
}

/**
 * @brief Frees the memory allocated for the list.
 * 
 * @param list Pointer to the List structure.
 * 
 * @note This function sets pointers to NULL after freeing to avoid dangling references.
 */
void freeList(List *list) {
    if (!list) return;  // Prevent null pointer dereference

    free(list->data);
    list->data = NULL;
    list->nameOf = NULL;
    list->dataTypeOf = NULL;

    // Reset list properties
    list->currentCount = 0;
    list->initSize = 0;
    list->size = 0;
}

/**
 * @brief Gets the memory address of an element at the specified index.
 * 
 * @param list Pointer to the List structure.
 * @param index Position of the element.
 * @return void* Pointer to the memory location, or NULL if index is invalid.
 * 
 * @warning Returns NULL if the index is out of bounds.
 */
void *getMemoryAddress(List *list, int index) {
    if (index < 0 || index >= list->currentCount) {
        printf("Invalid index: %d\n", index);
        return NULL;
    }
    return (void *)((char *)(list->data) + (index * list->size));
}

/**
 * @brief Checks if the list is empty.
 * 
 * @param list Pointer to the List structure.
 * @return bool True if the list is empty, false otherwise.
 */
bool isEmpty(List *list) {
    return list->currentCount == 0;
}

/**
 * @brief Returns the total allocated memory size of the list in bytes.
 * @param list Pointer to the List structure.
 * @return The total allocated memory size in bytes.
 */
size_t sizeOfList(List *list) {
    return list ? list->listSize : 0;
}

/**
 * @brief Returns the actual used memory size for stored data in bytes.
 * @param list Pointer to the List structure.
 * @return The actual used memory size in bytes.
 */
size_t sizeOfData(List *list) {
    return list ? list->dataSize : 0;
}