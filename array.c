/**
 * @brief Implementation of array_h
 *
 * @author  Jesper Bystr�m
 * @since   2019-11-15
 *
 */

#include "array.h"
#include <stdlib.h>
#include <stdio.h>

Array *array_create(int n1, int n2)
{
    Array *a = malloc(sizeof(Array));
    a->n1 = n1;
    a->n2 = n2;
    a->data = calloc(n1 * n2, sizeof(int));

    return a;
}

void array_destroy(Array *arr)
{
    free(arr->data);
    free(arr);
}

int array_rows(const Array *arr)
{
    return arr->n1;
}

int array_columns(const Array *arr)
{
    return arr->n2;
}

int array_get(const Array *arr, int i1, int i2)
{
    return arr->data[i1 * arr->n2 + i2];
}

void array_set(Array *arr, int i1, int i2, int value)
{
    arr->data[i1 * arr->n2 + i2] = value;
}
