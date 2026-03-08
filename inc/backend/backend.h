/**
 * @file backend.h
 * @brief The main interface for working with the game model
 *
 * Contains functions and structures for initializing the game,
 * retrieving the current model, working with game states,
 * and basic interaction with logic.
 *
 * This file is internal to the library;
 * most functions should be called through backend_api.h
 */

#ifndef _TETRIS_BACKEND_H_
#define _TETRIS_BACKEND_H_

#include <stdlib.h>
#include <time.h>

#include "../define.h"
#include "logic.h"
#include "storage.h"
#include "types.h"
#include "utils.h"

/**
 * @brief Returns a pointer to the current game model (singleton)
 *
 * This function (getter) returns the current model
 *
 * @return Pointer to a GameModel_t structure
 */
GameModel_t *get_current_model(void);

/**
 * @brief Full Game Initialization
 *
 * This function fully initializes the game (model, game board, and figures)
 */
void init_game(void);

/**
 * @brief Initializing Game Information
 *
 * This function initializes a structure with information about the game
 *
 * @param info Pointer to the GameInfo_t structure to fill with initial values
 */
void init_game_info(GameInfo_t *info);

/**
 * @brief Initialize the game board and figure
 *
 * Creates and clears the game board and "next figure" matrices
 *
 * @param info Pointer to the GameInfo_t structure to fill with initial values
 */
void init_fields(GameInfo_t *info);

#endif