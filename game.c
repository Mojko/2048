#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "array.h"
#include "game.h"

static int randomize_tile_value();
static void randomize_tile();

static Array *field;
static bool game_over = false;


static bool is_board_full()
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

static void copy_board(Array *cpy)
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            array_set(cpy, i, j, game_get_square(i, j));
        }
    }
}

static bool compare_boards(Array *board)
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(array_get(field, i, j) != array_get(board, i, j))
            {
                return false;
            }
        }
    }

    return true;
}

static int randomize_tile_value()
{
    return rand() % 100 < 10 ? 4 : 2;
}

void game_print()
{
    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(array_get(field, i, j) == 0)
            {
                printf(". | ");
            }
            else
            {
                printf("%d | ", array_get(field, i, j));
            }

        }
        printf("\n");
    }
    printf("\n");
}


static void randomize_tile()
{
    int index = 0;
    int array[16][2];

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
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

// Start a new game.
void game_new(void)
{
    field = array_create(4, 4);

    for(int i = 0; i < 2; i++)
    {
        array_set(field, rand() % array_rows(field), rand() % array_columns(field), randomize_tile_value());
    }
}

// Return the value of the specified piece (0 if empty).
int game_get_square(int row, int column)
{
    return array_get(field, row, column);
}

void game_slide(int c[4][4][2])
{
    Array *cpy = array_create(4, 4);
    copy_board(cpy);

    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            int current_value = game_get_square(c[i][j][0], c[i][j][1]);

            if(current_value != 0)
            {
                for(int k = i + 1; k < 4; k++)
                {
                    int target_value = game_get_square(c[k][j][0], c[k][j][1]);

                    if(target_value == current_value)
                    {
                        array_set(field, c[i][j][0], c[i][j][1], current_value * 2);
                        array_set(field, c[k][j][0], c[k][j][1], 0);
                        break;
                    }
                    else if(target_value != current_value && target_value != 0)
                    {
                        break;
                    }
                }

                for(int k = i; k > 0; k--)
                {
                    if(game_get_square(c[k-1][j][0], c[k-1][j][1]) == 0)
                    {
                        array_set(field, c[k-1][j][0], c[k-1][j][1], game_get_square(c[k][j][0], c[k][j][1]));
                        array_set(field, c[k][j][0], c[k][j][1], 0);
                    }
                }
            }
        }
    }

    game_over = is_board_full() && compare_boards(cpy);

    randomize_tile();
}

// Slide all pieces up, right, down, or left.
void game_slide_up(void)
{
    int c[4][4][2] =
    {
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
    };

    game_slide(c);
}

void game_slide_right(void)
{
    int c[4][4][2] =
    {
        {{3, 3}, {2, 3}, {1, 3}, {0, 3}},
        {{3, 2}, {2, 2}, {1, 2}, {0, 2}},
        {{3, 1}, {2, 1}, {1, 1}, {0, 1}},
        {{3, 0}, {2, 0}, {1, 0}, {0, 0}},
    };

    game_slide(c);
}

void game_slide_down(void)
{
    int c[4][4][2] =
    {
        {{3, 3}, {3, 2}, {3, 1}, {3, 0}},
        {{2, 3}, {2, 2}, {2, 1}, {2, 0}},
        {{1, 3}, {1, 2}, {1, 1}, {1, 0}},
        {{0, 3}, {0, 2}, {0, 1}, {0, 0}},
    };

    game_slide(c);
}

void game_slide_left(void)
{
    int c[4][4][2] =
    {
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{0, 3}, {1, 3}, {2, 3}, {3, 3}},
    };

    game_slide(c);
}

// Return true if the game is over (2048 reached or no empty squares).
bool game_is_game_over(void)
{
    bool found_2048 = false;

    for(int i = 0; i < array_rows(field); i++)
    {
        for(int j = 0; j < array_columns(field); j++)
        {
            if(game_get_square(i, j) == 2048)
            {
                found_2048 = true;
            }
        }
    }

    return game_over || found_2048;
}

