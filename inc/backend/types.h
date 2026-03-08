/**
 * @file types.h
 * @brief Basic game data types and structures
 *
 * Contains structures: GameInfo_t, GameModel_t
 * and enums: GameState_t, UserAction_t
 */

#ifndef _TETRIS_BACKEND_TYPES_H_
#define _TETRIS_BACKEND_TYPES_H_

/**
 * @brief Basic information about the game
 *
 * This structure containing information about
 * the playing field and player statistics
 */
typedef struct {
  int **field;    /**< Current playing field (matrix) */
  int **next;     /**< Matrix of the next figure */
  int score;      /**< Current score of the game */
  int high_score; /**< Game high score */
  int level;      /**< Game level */
  int speed;      /**< Game speed (in ms)*/
  int pause;      /**< Pause flag (0 - not present, 1 - paused) */
} GameInfo_t;

/**
 * @enum UserAction_t
 * @brief User actions (control)
 *
 * This enum describes the possible game control commands
 */
typedef enum {
  Start,     /**< Start of the game */
  Pause,     /**< Pause */
  Terminate, /**< Forced game closure */
  Left,      /**< Movement of the figure to the left */
  Right,     /**< Movement of the figure to the right */
  Up,        /**< Not used in this game */
  Down,      /**< Accelerated downward movement of the figure */
  Action     /**< Special action: Rotate the figure. */
} UserAction_t;

/**
 * @enum GameState_t
 * @brief Game state. Finite state machine. (FSM)
 *
 * This enum is used as a state machine for the status of each step of the game.
 */
typedef enum {
  GS_Start,     /**< Start of the game */
  GS_Spawn,     /**< The spawn of a figure */
  GS_Moving,    /**< Movement of the figure */
  GS_Shifting,  /**< The shifting of a figure */
  GS_Attaching, /**< Attaching a figure */
  GS_Over,      /**< Game over */
  GS_Exit,      /**< Exiting the game */
} GameState_t;

/**
 * @brief Main game model (MVC: Model).
 *
 * This structure represents a model for storing
 * and managing the game. It contains the following fields:
 * game board, game information, game state,
 * current piece and coordinates, and a time interval.
 */
typedef struct {
  GameInfo_t *info;    /**< Field and score information */
  int **figure;        /**< Current figure */
  int figure_x;        /**< X-coordinate of the figure */
  int figure_y;        /**< Y-coordinate of the figure */
  int figure_id;       /**< ID of the current figure */
  int next_figure_id;  /**< ID of the next figure */
  long long last_time; /**< Last recorded time */
  int interval;        /**< Interval of falling figures */
  GameState_t state;   /**< Current state of the machine */
} GameModel_t;

#endif