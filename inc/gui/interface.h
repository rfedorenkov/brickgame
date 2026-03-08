/**
 * @file interface.h
 * @brief Interface module: working with ncurses and screen rendering
 *
 * Contains a description of the screen structure (ncurses window)
 * and functions for initializing the interface, managing colors,
 * and drawing game elements
 */

#ifndef _TETRIS_INTERFACE_H_
#define _TETRIS_INTERFACE_H_

#include <locale.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief A structure describing the game interface windows
 *
 * This structure stores information about all windows
 */
typedef struct {
  const char *title;   /**<  Window title */
  int field_width;     /**<  Width of the playing field */
  int field_height;    /**<  Height of the playing field */
  WINDOW *game_field;  /**< Window for the playing field */
  WINDOW *game_stats;  /**< Statistics window */
  WINDOW *next_figure; /**< Window for the next shape */
  WINDOW *game_help;   /**< Window for tips (help) */
  WINDOW *logo;        /**< Window for the logo */
} Screen_t;

/**
 * @brief Interface initialization
 *
 * This function initializes the interface and creates windows
 *
 * @param title Window title
 * @param field_height Playing field height
 * @param field_width Playing field width
 * @return Screen_t* Pointer to the created interface structure
 */
Screen_t *init_interface(const char *title, int field_height, int field_width);

/**
 * @brief Initialization of color pairs
 *
 * This function initializes color pairs for ncurses
 */
void init_colors(void);

/**
 * @brief Destroying the interface
 *
 * This function frees resources and destroys the interface
 *
 * @param screen Pointer to a Screen_t structure
 */
void destroy_interface(Screen_t *screen);

/**
 * @brief Refresh all windows
 *
 * This function refreshes all interface windows
 *
 * @param screen Pointer to a Screen_t structure
 */
void refresh_windows(Screen_t *screen);

/**
 * @brief Print in the center of the window
 *
 * This function prints an array of strings centered in the specified window
 *
 * @param window Pointer to an ncurses window
 * @param y Starting vertical coordinate
 * @param text Array of strings to output
 * @param count Number of lines
 */
void print_centered(WINDOW *window, int y, const char **text, int count);

/**
 * @brief Drawing all windows
 *
 * This function draws all interface windows
 *
 * @param screen Pointer to a Screen_t structure
 */
void draw_windows(Screen_t *screen);

/**
 * @brief Drawing the main window
 *
 * This function draws the main window
 *
 * @param screen Pointer to a Screen_t structure
 */
void draw_menu(Screen_t *screen);

/**
 * @brief Drawing the pause menu
 *
 * This function draws the pause menu
 *
 * @param screen Pointer to a Screen_t structure
 */
void draw_pause(Screen_t *screen);

/**
 * @brief Drawing the game over screen
 *
 * This function draws the game over screen
 *
 * @param screen Pointer to a Screen_t structure
 */
void draw_game_over(Screen_t *screen);

/**
 * @brief Rendering game statistics
 *
 * This function renders game statistics
 *
 * @param screen Pointer to a Screen_t structure
 * @param high_score Current high score
 * @param score Current score
 * @param level Current level
 */
void draw_stats(Screen_t *screen, int high_score, int score, int level);

/**
 * @brief Renders help
 *
 * This function displays help
 *
 * @param screen Pointer to a Screen_t structure
 * @param lines Array of strings
 * @param count Number of lines
 */
void draw_help(Screen_t *screen, const char **lines, int count);

/**
 * @brief Renders logo
 *
 * This function displays logo
 *
 * @param screen Pointer to a Screen_t structure
 */
void draw_logo(Screen_t *screen);

/**
 * @brief Drawing the playing field
 *
 * This function draws the game board
 *
 * @param screen Pointer to a Screen_t structure
 * @param field Two-dimensional array of the playing field
 */
void draw_field(Screen_t *screen, int **field);

/**
 * @brief Drawing the current figure
 *
 * This function draws the current shape
 *
 * @param screen Pointer to a Screen_t structure
 * @param figure Two-dimensional array of shape
 * @param x_start Initial coordinate X
 * @param y_start Initial coordinate Y
 * @param size Size of the figure
 */
void draw_figure(Screen_t *screen, int **figure, int x_start, int y_start,
                 int size);

/**
 * @brief Drawing the next figure
 *
 * This function draws the next shape.
 *
 * @param screen Pointer to a Screen_t structure
 * @param figure Two-dimensional array of shape
 * @param size Size of the figure
 */
void draw_next_figure(Screen_t *screen, int **figure, int size);

#endif