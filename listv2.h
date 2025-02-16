/**
 * @file listv2.h
 * @brief Dynamic list implementation in C using macros.
 * @author Mark Jayson Lanuzo
 * @date 2025-02-14
 */

#ifndef LISTV2_H
#define LISTV2_H

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



#endif /* LISTV2_H */