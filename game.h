/**
 * @defgroup game_h Game
 *
 * @brief The module is used to create the game 2048
 *
 * @author  Marut, Jesper Byström
 * @since   2019-12-03
 *
 * @{
 */

#include <stdbool.h>

#define BOARD_COLUMNS 4
#define BOARD_ROWS 4

#define GAME_H

#ifdef GAME_H


/**
 * @brief Start a new game.
 *
 * This function will start by creating a dynamiccaly allocated array.
 * Than this function will randomize two numbers that will be put out on the board
 * at the start of a new game. It will be beetween 4 and 2 90% chance that
 * one of the start values is 2 and 10% chance that it becomes a 4.
 *
 * @param void
 * @return void
 */
void game_new(void);

/**
 * @brief Return the value of the specified piece (0 if empty).
 *
 * This function takes row and column, and will return the value associated
 * to that specific row and column. If there is no value it will return 0.
 *
 * @param row, which row you want the value from.
 * @param column, which column you want the value from.
 * @return int, the value associated to row and column.
 */
int game_get_square(int row, int column);

// Slide all pieces up, right, down, or left.

/**
 * @brief Slide all pieces up.
 *
 * This function takes no parameter, but it will use the board of the game
 * and take all of it values and slide it up, it any two values collide and
 * are of the same number they will be combined to one value which will be the
 * sum of the two values together.
 *
 * @param void
 * @return void
 */
void game_slide_up(void);

/**
 * @brief Slide all pieces right.
 *
 * This function takes no parameter, but it will use the board of the game
 * and take all of it values and slide it right, it any two values collide and
 * are of the same number they will be combined to one value which will be the
 * sum of the two values together.
 *
 * @param void
 * @return void
 */
void game_slide_right(void);

/**
 * @brief Slide all pieces down.
 *
 * This function takes no parameter, but it will use the board of the game
 * and take all of it values and slide it down, it any two values collide and
 * are of the same number they will be combined to one value which will be the
 * sum of the two values together.
 *
 * @param void
 * @return void
 */
void game_slide_down(void);

/**
 * @brief Slide all pieces left.
 *
 * This function takes no parameter, but it will use the board of the game
 * and take all of it values and slide it left, it any two values collide and
 * are of the same number they will be combined to one value which will be the
 * sum of the two values together.
 *
 * @param void
 * @return void
 */
void game_slide_left(void);

/**
 * @brief Return true if the game is over (2048 reached or no moves left).
 *
 * This function will look on the board see if it is full and give the user
 * one last move, if there is a move that makes a difference the game will
 * will continue otherwise it will be game over. But it can also end by
 * reaching 2048 which is the max value, if the number is reached the user win
 * and the game is over.
 *
 * @param void
 * @return bool, true if the game is over false if otherwise.
 */
bool game_is_game_over(void);

#endif

/**
 * @}
 */
