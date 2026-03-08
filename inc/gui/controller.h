/**
 * @file controller.h
 * @brief Controller module: connects user input to game logic
 *
 * Contains descriptions of structures for interface settings
 * and key management, as well as functions for starting
 * the game loop and handling input
 */

#ifndef _TETRIS_CONTROLLER_H_
#define _TETRIS_CONTROLLER_H_

#include <unistd.h>

#include "../backend/backend_api.h"
#include "interface.h"

/**
 * @brief Key Map with action binding and description
 *
 * This structure contains a Key Map with action bindings and descriptions.
 */
typedef struct {
  int key;                     /**< Key code (ncurses) */
  UserAction_t action;         /**< Action associated with the key */
  char description[MAX_CHARS]; /**< Text description of the action */
  char icon[MAX_KEY_NAME];     /**< Symbolic designation of the key */
  bool hold; /**< Flag whether the action supports key holding */
} keymap_t;

/**
 * @brief Game window settings
 *
 * This structure contains the game window settings
 */
typedef struct {
  const char *title; /**< Window title */
  int height;        /**< Window height */
  int width;         /**< Window width */
} GameSettings_t;

/**
 * @brief Interface context
 *
 * This structure stores the screen state, the game, and the keymap
 */
typedef struct {
  Screen_t *screen;     /**< Screen (ncurses window) */
  GameInfo_t game_info; /**< Field and score information */
  keymap_t *keys;       /**< Array of available keys */
} InterfaceContext_t;

/**
 * @brief Returns default settings
 *
 * This function returns default settings (title, window size)
 */
GameSettings_t get_default_settings(void);

/**
 * @brief Starts the game
 *
 * This function starts the game
 * (initialization and transition to the game loop)
 */
void start_game(void);

/**
 * @brief Main game loop
 *
 * This function starts the Main Game Loop
 *
 * @param ctx Interface context (screen, game, keys)
 */
void game_loop(InterfaceContext_t *ctx);

/**
 * @brief Fills the help interface with a desctioption
 *
 * This function fills the help interface
 * with a description of the available keys
 *
 * @param ctx Interface context (screen, game, keys)
 */
void fill_help_with_keys(InterfaceContext_t *ctx);

/**
 * @brief Initializes the interface
 *
 * This function initializes the interface
 * (layout, windows, etc)
 *
 * @param ctx Interface context (screen, game, keys)
 */
void fill_interface(InterfaceContext_t *ctx);

/**
 * @brief Returns an array of default keys
 *
 * This function returns an array of default keys
 *
 * @return Pointer to an array with key settings
 */
keymap_t *get_default_keys(void);

/**
 * @brief Handle input
 *
 * This function processes input from the user.
 *
 * @param ch
 * @param ctx Interface context (screen, game, keys)
 */
void handle_input(int ch, InterfaceContext_t *ctx);

#endif
