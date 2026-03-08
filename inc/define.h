#ifndef _TETRIS_DEFINE_H_
#define _TETRIS_DEFINE_H_

/**
 * @file define.h
 * @brief Constants and macros for the Tetris game
 */

/** @brief Name of the game */
#define GAME_NAME "TETRIS"

/** @brief Minimum and maximum level */
#define MIN_LEVEL 1
#define MAX_LEVEL 10

/** @brief Points to advance to the next level */
#define SCORE_PER_LEVEL 600

/** @brief Initial game speed and acceleration step (ms) */
#define START_SPEED 800
#define SPEED_STEP 83

/** @brief Dimensions of the playing field */
#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20

/** @brief Maximum length of strings and key names */
#define MAX_CHARS 100
#define MAX_KEY_NAME 8

/** @brief Dimensions and number of figures */
#define FIGURE_SIZE 4
#define FIGURE_COUNT 7

/** @brief Initial coordinates of the new figure */
#define FIGURE_START_X (FIELD_WIDTH - FIGURE_SIZE) / 2
#define FIGURE_START_Y -1

/** @brief File for storing the highscore */
#define HIGH_SCORE_FILE ".data.db"

#endif