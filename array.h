/**
 * @defgroup array_h Array
 *
 * @brief The module is used to create a two dimensional array
 *
 *
 * The module act as a two dimensional array by saving all values in a one dimensional array and jump a certain amount of steps each time the row index increases.
 * Which means that in memory the array is stored one dimensional but it can be visualized as a two dimensional array
 *
 * @author  Jesper Byström
 * @since   2019-11-15
 *
 * @{
 */

#ifndef ARRAY_H
#define ARRAY_H

/**
 * @brief The type for a 2D array.
 *
 * @param n1 is the amount of rows the array contains
 * @param n2 is the amount of rows the columns contains
 * @param data is the data the array contains
 */
typedef struct array
{
    /** Amount of rows the array contains */
    int n1;
    /** Amount of columns the array contains */
    int n2;
    /** The data the array contains */
    int *data;
} Array;

/**
 * @brief Create and return a zero array of size n1 rows by n2 columns.
 *
 * Responsability is on the user to deallocate the array by calling array_destroy when finished
 *
 * @param n1 Amount of rows
 * @param n2 Amount of columns
 * @return Newly created struct Array with allocated memory for the data
 */
Array *array_create(int n1, int n2);

/**
 * @brief Destroy an array and deallocate all items.
 *
 * @param arr The array to destroy
 * @return           -
 */
void array_destroy(Array *arr);

/**
 * @brief Get the number of rows.
 *
 * @param arr The array to fetch the rows from
 * @return The amount of rows the array contains
 */
int array_rows(const Array *arr);

/**
 * @brief Get the number of columns.
 *
 * @param arr The array to fetch the columns from
 * @return The amount of columns the array contains
 */
int array_columns(const Array *arr);

/**
 * @brief Return the value at row i1 and column i2 (zero-based indexing).
 *
 * @param arr The array to get the values from
 * @param i1 The row index
 * @param i2 The column index
 * @return The value at (i1, i2)
 */
int array_get(const Array *arr, int i1, int i2);

/**
 * @brief Set the value at row i1 and column i2 (zero-based indexing).
 *
 * @param arr The array to set values in
 * @param i1 The row index
 * @param i2 The column index
 * @param value The value to set
 * @return           -
 */
void array_set(Array *arr, int i1, int i2, int value);

#endif /* ARRAY_H */

/**
 * @}
 */
