/**
 * @file storage.h
 * @brief Working with files
 *
 * Features for loading and saving game records
 */

#ifndef _TETRIS_BACKEND_STORAGE_H_
#define _TETRIS_BACKEND_STORAGE_H_

#include <stdio.h>

#include "../define.h"

/**
 * @brief Loads the maximum score from a file
 *
 * The function loads the previously recorded high score value
 * from the file into the variable pointer.
 * If an error occurs, the file is not loaded.
 *
 * @param high_score A pointer to a variable where the result will be written
 * @return 0 on successful reading,
 * -1 if an error occurred (NULL passed, file not found, or invalid data)
 */
int load_high_score_file(int *high_score);

/**
 * @brief Saves the maximum score to a file
 *
 * This function saves the current value passed to the function to a file.
 * If an error occurs, the file is not written.
 *
 * @param high_score The high score to be recorded.
 * @return 0 if writing was successful,
 * -1 if an error occurred (failed to open file or write data).
 */
int save_high_score_file(int high_score);

#endif