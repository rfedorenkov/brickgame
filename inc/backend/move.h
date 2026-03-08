/**
 * @file move.h
 * @brief Functions for moving and rotating figures.
 *
 * Contains functions such as:
 * move_left, move_right, move_down, drop_down, and rotate
 */

#ifndef _TETRIS_BACKEND_MOVE_H_
#define _TETRIS_BACKEND_MOVE_H_

#include "logic.h"

/**
 * @brief Moves the piece to the left one square
 *
 * This function shifts the current figure in the model by 1 cell to the left
 *
 * @param model Pointer to the game model
 */
void move_left(GameModel_t *model);

/**
 * @brief Moves the piece to the right one square
 *
 * This function shifts the current figure in the model by 1 cell to the right
 *
 * @param model Pointer to the game model
 */
void move_right(GameModel_t *model);

/**
 * @brief Moves a piece down one square
 *
 * This function moves the current shape down one cell
 * This function is used for step-by-step falling
 */
void move_down(void);

/**
 * @brief Drops the figure straight down to the stop
 *
 * This function lowers the piece down to the edge of the playing field
 * or to the nearest piece on the playing field.
 *
 * @param model Pointer to the game model
 */
void drop_down(GameModel_t *model);

/**
 * @brief Performs a rotation of the figure.
 *
 * This function rotates the current shape by 90 degrees.
 *
 * @param model Pointer to the game model
 */
void rotate(GameModel_t *model);

#endif