/**
 * @file fsm.h
 * @brief Finite state machine of the game
 *
 * Describes game states and transitions between them
 * State management functions: start, pause, game over, etc
 */

#ifndef _TETRIS_BACKEND_FSM_H_
#define _TETRIS_BACKEND_FSM_H_

#include "backend.h"
#include "move.h"

/**
 * @brief Update Current State
 *
 * This function updates the current game state
 * (one "tick" update of the FSM)
 *
 * @return Structure with up-to-date information
 * about the game (field, score, figure, etc.)
 */
GameInfo_t updateCurrentState(void);

/**
 * @brief Checking permitted actions
 *
 * This function checks whether the action is allowed
 * to be performed in the current game state.
 *
 * @param action User action
 * @return true if the action is allowed, otherwise false
 */
bool is_action_allowed(UserAction_t action);

/**
 * @brief Processes a user action
 *
 * This function processes user actions,
 * changes the game state, and calls control functions
 *
 * @param action
 * @param hold
 */
void userInput(UserAction_t action, bool hold);

/**
 * @brief Checking if the game is running
 *
 * This function checks if the game is running
 *
 * @return true if the game is in the starting or running state
 */
bool is_started(void);

/**
 * @brief Checks if the game is paused
 *
 * This function checks if the game is paused
 *
 * @return true if the game is paused
 */
bool is_paused(void);

/**
 * @brief Checks if the game is finished
 *
 * This function checks if the game is finished
 *
 * @return true if the game is over (Game Over)
 */
bool is_game_over(void);

/**
 * @brief Checks if the game exit flag is set
 *
 * This function checks if the game exit flag is set
 *
 * @return true if the game was terminated by the exit command
 */
bool is_exit(void);

/**
 * @brief Start of the game
 *
 * This function initializes the start of the game
 *
 * @param model Pointer to the game model
 */
void start(GameModel_t *model);

/**
 * @brief Pause the game
 *
 * This function pauses or unpauses the game depending on the game state
 *
 * @param info Pointer to information about the game
 * @param state Current state of the machine
 */
void pause_game(GameInfo_t *info, GameState_t state);

/**
 * @brief Puts the game into the "Game Over" state.
 *
 * Frees resources: the game board, the next piece, and the current piece.
 * Clears the GameInfo structure and sets the machine to the GS_Over state.
 *
 * @note After calling this function, the game model loses its current data.
 */
void game_over(void);

#endif