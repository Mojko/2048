/**
 * @brief Implementation of the game.h
 *
 * @author  Marut Khrutanang, Jesper Byström
 * @since   2019-11-29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array.h"
#include "game.h"

static int randomize_tile_value(void);
static void spawn_random_tile(void);
static bool is_board_full(void);
static void slide_by_map(int c[BOARD_ROWS][BOARD_COLUMNS][2]);

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
    int array[16][2];

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
 * The function takes in a map of coordinates which will be used to set the tile at a position specified by the map
 *
 * @param map the map of coordinates to walk in
 * @return -
 */
static void slide_by_map(int map[BOARD_ROWS][BOARD_COLUMNS][2])
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            int current_value = game_get_square(map[i][j][0], map[i][j][1]);

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
    int map[BOARD_ROWS][BOARD_COLUMNS][2] =
    {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
    };

    slide_by_map(map);
}

void game_slide_right(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2] =
    {
        {{3, 3}, {2, 3}, {1, 3}, {0, 3}},
        {{3, 2}, {2, 2}, {1, 2}, {0, 2}},
        {{3, 1}, {2, 1}, {1, 1}, {0, 1}},
        {{3, 0}, {2, 0}, {1, 0}, {0, 0}},
    };

    slide_by_map(map);
}

void game_slide_down(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2] =
    {
        {{3, 3}, {3, 2}, {3, 1}, {3, 0}},
        {{2, 3}, {2, 2}, {2, 1}, {2, 0}},
        {{1, 3}, {1, 2}, {1, 1}, {1, 0}},
        {{0, 3}, {0, 2}, {0, 1}, {0, 0}},
    };

    slide_by_map(map);
}

void game_slide_left(void)
{
    int map[BOARD_ROWS][BOARD_COLUMNS][2] =
    {
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{0, 3}, {1, 3}, {2, 3}, {3, 3}},
    };

    slide_by_map(map);
}

bool game_is_game_over(void)
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(game_get_square(i, j) == 2048)
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

    for(int i = 1; i < array_rows(field) - 1; i++)
    {
        for(int j = 1; j < array_columns(field) - 1; j++)
        {
            //If the tile (i,j) return 2048, the game is over, or if there are no neighbours left with the same value as (i,j)
            int value = game_get_square(i, j);
            if(game_get_square(i-1, j) == value ||
                game_get_square(i+1, j) == value ||
                game_get_square(i, j+1) == value ||
                game_get_square(i, j-1) == value)
            {
                game_over = false;
            }
        }
    }

    return game_over;
}

