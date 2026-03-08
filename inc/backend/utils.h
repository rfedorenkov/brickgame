/**
 * @file utils.h
 * @brief Auxiliary functions for the game
 *
 * Creating and deleting matrices, generating shapes,
 * timers, and shape utilities
 */

#ifndef _TETRIS_BACKEND_UTILS_H_
#define _TETRIS_BACKEND_UTILS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#include "backend.h"

/**
 * @brief Creates a two-dimensional matrix of int
 *
 * The function allocates memory for each row of the matrix
 * depending on the number of columns
 * If a negative or zero number of rows or columns is passed,
 * the matrix is ​​not created and a null pointer is returned
 *
 * @param rows Number of rows (must be > 0)
 * @param columns Number of columns (must be > 0)
 * @return A pointer to the created matrix,
 * or NULL if memory could not be allocated.
 */
int **create_matrix(int rows, int columns);

/**
 * @brief Frees the memory allocated for the matrix
 *
 * The function frees memory for each row of the matrix and the matrix itself
 * If a negative size is passed, the matrix is ​​not touched and is returned
 * as is
 *
 * @param matrix Pointer to a matrix (two-dimensional array)
 * @param size Number of rows in the matrix
 * @return NULL if the deallocation was successful
 * the original matrix pointer if size < 0.
 */
int **remove_matrix(int **matrix, int size);

/**
 * @brief Returns the current time in milliseconds
 *
 * The function uses gettimeofday and converts the result
 * to the number of milliseconds since the Unix epoch (1970-01-01)
 *
 * @return Current time in milliseconds
 */
long long get_current_time(void);

/**
 * @brief Checks if it is time for the next step of the game
 * Compares the current time with the previously saved time (model->last_time)
 * and speed interval (info->speed)
 * If enough time has passed, returns true and updates last_time.
 *
 * @return true - if it is time to perform the next step
 * @return false - if it's too early
 */
bool is_time(void);

#endif