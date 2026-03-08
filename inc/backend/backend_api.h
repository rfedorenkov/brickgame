/**
 * @file backend_api.h
 * @brief Public API of the game library
 *
 * Contains functions for interacting with the game model,
 * checking states, handling input, and getting the current shape
 */

#ifndef _TETRIS_BACKEND_API_H_
#define _TETRIS_BACKEND_API_H_

#include <stdbool.h>

#include "../define.h"
#include "types.h"

/**
 * @copydoc updateCurrentState
 */
GameInfo_t updateCurrentState(void);

/**
 * @copydoc is_action_allowed
 */
bool is_action_allowed(UserAction_t action);

/**
 * @copydoc userInput
 */
void userInput(UserAction_t action, bool hold);

/**
 * @copydoc init_game
 */
void init_game(void);

/**
 * @copydoc game_over
 */
void game_over(void);

/**
 * @copydoc is_started
 */
bool is_started();

/**
 * @copydoc is_paused
 */
bool is_paused(void);

/**
 * @copydoc is_game_over
 */
bool is_game_over(void);

/**
 * @copydoc is_exit
 */
bool is_exit(void);

/**
 * @copydoc is_time
 */
bool is_time(void);

/**
 * @copydoc move_down
 */
void move_down(void);

/**
 * @copydoc get_current_figure
 */
int **get_current_figure(void);

/**
 * @copydoc get_figure_x
 */
int get_figure_x(void);

/**
 * @copydoc get_figure_y
 */
int get_figure_y(void);

#endif