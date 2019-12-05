/**
 * @brief Implementation of the game.h
 *
 * @author  Marut Khrutanang (dv19mkg)
 * @author  Jesper Byström (dv19jbm)
 * @since   2019-11-29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array.h"
#include "game.h"

static bool is_board_full(void);
static int randomize_tile_value(void);
static void spawn_random_tile(void);
static void slide_by_map(int c[BOARD_ROWS][BOARD_COLUMNS][2]);
static bool check_neighbours(int row, int column);

static Array *field;

void game_new(void)
{
    if(field != NULL)
    {
        array_destroy(field);
    }

    field = array_create(BOARD_ROWS, BOARD_COLUMNS);

    for(int i = 0; i < 2; i++)
    {
        array_set(field, rand() % array_rows(field), rand() % array_columns(field), randomize_tile_value());
    }
}

/**
 * @brief Checks if the board is full
 *
 * @param -
 * @return true if the board is full, else false
 */
static bool is_board_full(void)
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(game_get_square(i, j) == 0)
            {
                return false;
            }
        }
    }

    return true;
}

/**
 * @brief Randomizes a value for a tile
 *
 * @param -
 * @return a randomized value for a tile
 */
static int randomize_tile_value(void)
{
    return rand() % 100 < 10 ? 4 : 2;
}

/**
 * @brief Spawns a randomized value on a randomized tile
 *
 * @param -
 * @return -
 */
static void spawn_random_tile(void)
{
    int index = 0;
    int array[BOARD_COLUMNS * BOARD_ROWS][2];

    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(array_get(field, i, j) == 0)
            {
                array[index][0] = i;
                array[index][1] = j;
                index++;
            }
        }
    }

    if(index > 0)
    {
        int randvalue = rand() % index;

        array_set(field, array[randvalue][0], array[randvalue][1], randomize_tile_value());
    }
}

int game_get_square(int row, int column)
{
    return array_get(field, row, column);
}

/**
 * @brief Slides the tiles in a direction based off of the map's coordinates
 *
 * This function takes in a map of coordinates which will be decided
 * depending on what move the user wants to do. It looks for a value through
 * the map. When a value is found it will look in the opposite direction
 * and look for another value. If a target is found it will
 * combine the values otherwise it will push the value to the furthest
 * available spot in the direction desired.
 *
 * @param map the map of coordinates to walk in
 * @return -
 */
static void slide_by_map(int map[BOARD_ROWS][BOARD_COLUMNS][2])
{
    int current_value = 0;
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            current_value = game_get_square(map[i][j][0], map[i][j][1]);

            if(current_value != 0)
            {
                for(int k = i + 1; k < 4; k++)
                {
                    int target_value = game_get_square(map[k][j][0], map[k][j][1]);

                    if(target_value == current_value)
                    {
                        array_set(field, map[i][j][0], map[i][j][1], current_value * 2);
                        array_set(field, map[k][j][0], map[k][j][1], 0);
                        break;
                    }
                    else if(target_value != current_value && target_value != 0)
                    {
                        break;
                    }
                }

                for(int k = i; k > 0; k--)
                {
                    if(game_get_square(map[k-1][j][0], map[k-1][j][1]) == 0)
                    {
                        array_set(field, map[k-1][j][0], map[k-1][j][1], game_get_square(map[k][j][0], map[k][j][1]));
                        array_set(field, map[k][j][0], map[k][j][1], 0);
                    }
                }
            }
        }
    }

    spawn_random_tile();
}

void game_slide_up(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2];

    for(int i =  0; i < BOARD_ROWS; i++)
    {
        for(int j =  0; j < BOARD_COLUMNS; j++)
        {
            map[i][j][0] = i;
            map[i][j][1] = j;
        }
    }

    /*
        4x4 up map example
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
    */

    slide_by_map(map);
}

void game_slide_right(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2];

    for(int i =  0; i < BOARD_ROWS; i++)
    {
        for(int j =  0; j < BOARD_COLUMNS; j++)
        {
            map[i][j][0] = BOARD_COLUMNS - 1 - j;
            map[i][j][1] = BOARD_ROWS - 1 - i;
        }
    }

    /*
        4x4 right map example
        {{3, 3}, {2, 3}, {1, 3}, {0, 3}},
        {{3, 2}, {2, 2}, {1, 2}, {0, 2}},
        {{3, 1}, {2, 1}, {1, 1}, {0, 1}},
        {{3, 0}, {2, 0}, {1, 0}, {0, 0}},
    */

    slide_by_map(map);
}

void game_slide_down(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2];

    for(int i =  0; i < BOARD_ROWS; i++)
    {
        for(int j =  0; j < BOARD_COLUMNS; j++)
        {
            map[i][j][0] = BOARD_COLUMNS - 1 - i;
            map[i][j][1] = BOARD_ROWS - 1 - j;
        }
    }

    /*
        4x4 down map example
        {{3, 3}, {3, 2}, {3, 1}, {3, 0}},
        {{2, 3}, {2, 2}, {2, 1}, {2, 0}},
        {{1, 3}, {1, 2}, {1, 1}, {1, 0}},
        {{0, 3}, {0, 2}, {0, 1}, {0, 0}},
    */

    slide_by_map(map);
}

void game_slide_left(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2];

    for(int i =  0; i < BOARD_ROWS; i++)
    {
        for(int j =  0; j < BOARD_COLUMNS; j++)
        {
            map[i][j][0] = j;
            map[i][j][1] = i;
        }
    }

    /*
        4x4 left map example
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{0, 3}, {1, 3}, {2, 3}, {3, 3}},
    */

    slide_by_map(map);
}

bool game_is_game_over(void)
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(game_get_square(i, j) == GOAL)
            {
                return true;
            }
        }
    }

    if(!is_board_full())
    {
        return false;
    }

    bool game_over = true;

    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(check_neighbours(i, j))
            {
                game_over = false;
            }
        }
    }

    return game_over;
}

static bool check_neighbours(int row, int column)
{
    int directions[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

    int neighbourR, neighbourC;

    for(int i = 0; i < 4; i++)
    {
        neighbourR = row + directions[i][0];
        neighbourC = column + directions[i][1];

        if(neighbourR >= array_rows(field) || neighbourR < 0 || neighbourC >= array_columns(field) || neighbourC < 0)
        {
            continue;
        }

        if(game_get_square(neighbourR, neighbourC) == game_get_square(row, column))
        {
            return true;
        }
    }

    return false;
}
