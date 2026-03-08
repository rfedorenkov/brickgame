/**
 * @file logic.h
 * @brief Game logic
 *
 * Contains functions for handling piece movement,
 * rotation, falling, collision checking,
 * line destruction, and score updating
 */

#ifndef _TETRIS_BACKEND_LOGIC_H_
#define _TETRIS_BACKEND_LOGIC_H_

#include <stdbool.h>

#include "backend.h"
#include "types.h"

/**
 * @brief Lock the current figure
 *
 * This function locks the current figure on the playing field
 *
 * @param model Pointer to the game model
 */
void lock_figure(GameModel_t *model);

/**
 * @brief Removing lines on the field
 *
 * This function removes filled lines from the field
 *
 * @param info Pointer to a structure containing game data
 * @return Number of lines removed
 */
int remove_lines_on_field(GameInfo_t *info);

/**
 * @brief Update score and level
 *
 * This function updates the player's score and level after deleting rows
 *
 * @param info Pointer to a structure containing game data
 * @param count Number of lines removed
 */
void update_score_and_level(GameInfo_t *info, int count);

/**
 * @brief Collision Check
 *
 * This function checks for collisions between
 * a shape and its borders or other blocks
 *
 * @param model Pointer to the game model
 * @param start_x The position of the figure along the X axis
 * @param start_y The position of the figure along the Y axis
 * @return true if there is a collision, otherwise false
 */
bool check_collision(GameModel_t *model, int start_x, int start_y);

/**
 * @brief Gets a figure by ID
 *
 * This function gets a shape by its ID
 *
 * @param id Figure ID
 * @return Pointer to a figure array of size FIGURE_SIZE × FIGURE_SIZE
 */
const int (*get_available_figure(int id))[FIGURE_SIZE];

/**
 * @brief Generating a random figure
 *
 * This function generates a random shape and stores it in the game structure
 *
 * @param info Pointer to a structure containing game data
 */
void generate_random_figure(GameInfo_t *info);

/**
 * @brief Generating a new figure
 *
 * This function generates and prepares the current figure
 */
void generate_figure(void);

/**
 * @brief Getting a pointer to the current figure
 *
 * This function (getter) receives a pointer to the current figure
 *
 * @return Pointer to the shape matrix
 */
int **get_current_figure(void);

/**
 * @brief Getting the X coordinate
 *
 * This function (getter) gets the current X coordinate of the shape
 *
 * @return X coordinate
 */
int get_figure_x(void);

/**
 * @brief Getting the Y coordinate
 *
 * This function (getter) gets the current Y coordinate of the shape
 *
 * @return Y coordinate
 */
int get_figure_y(void);

#endif