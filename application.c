/**
 * @brief Implementation of the game 2048
 *
 * @author  Marut Khrutanang, Jesper Byström
 * @since   2019-11-29
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "application.h"

static int get_score();
static void print_game();
static void print_header_line();
static void print_content(int boxes[]);
static void print_empty_content_line();
static void print_menu();

void app_run(void)
{
    srand(time(0));

    game_new();

    int selection;

    do
    {
        print_game();

        do
        {
            print_menu();

            scanf("%d", &selection);

            printf("\n");

        } while(selection > 4 || selection < 1);

        if(selection == 1)
        {
            printf("> Sliding up ...\n");
            game_slide_up();
        }

        else if(selection == 2)
        {
            printf("> Sliding right ...\n");
            game_slide_right();
        }

        else if(selection == 3)
        {
            printf("> Sliding down ...\n");
            game_slide_down();
        }

        else if(selection == 4)
        {
            printf("> Sliding left ...\n");
            game_slide_left();
        }

    } while(selection != 0 && !game_is_game_over());

    fprintf(stderr, "GAME OVER\nYou got the score: %d\n", get_score());
}

/**
 * @brief Gets the score
 *
 * @param -
 * @return -
 */
static int get_score()
{
    int score = 0;
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        for(int j = 0; j < BOARD_COLUMNS; j++)
        {
            score += game_get_square(i, j);
        }
    }

    return score;
}

/**
 * @brief Prints the game
 *
 * @param -
 * @return -
 */
static void print_menu()
{
    printf("SELECT ACTION\n");
    printf("0: quit\n");
    printf("1: slide up\n");
    printf("2: slide right\n");
    printf("3: slide down\n");
    printf("4: slide left\n");
    printf("? ");
}

/**
 * @brief Prints the game
 *
 * @param -
 * @return -
 */
static void print_game()
{
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        print_header_line();
        print_empty_content_line();

        int boxes[BOARD_COLUMNS];

        for(int j = 0; j < BOARD_COLUMNS; j++)
        {
            boxes[j] = game_get_square(i, j);
        }

        print_content(boxes);
        print_empty_content_line();
    }

    print_header_line();
    printf("\n\n\n\n");
}

/**
 * @brief Prints the header line
 *
 * @param -
 * @return -
 */
static void print_header_line()
{
    for(int i = 0; i < BOARD_COLUMNS; i++)
    {
        printf("+--------");
    }

    printf("+");
    printf("\n");
}

/**
 * @brief Prints the empty boxes without any values in them
 *
 * @param -
 * @return -
 */

static void print_empty_content_line()
{
    for(int i = 0; i < BOARD_COLUMNS; i++)
    {
        printf("|        ");
    }

    printf("|"); //at the end
    printf("\n");
}

/**
 * @brief Prints the numbers inside each box
 *
 * @param box1 the first box
 * @param box2 the second box
 * @param box3 the third box
 * @param box4
 * @return -
 */

static void print_content(int boxes[])
{
    for(int i = 0; i < BOARD_COLUMNS; i++)
    {
        if(boxes[i] == 0)
        {
            printf("|        ");
        }
        else
        {
            printf("|%4d    ", boxes[i]);
        }
    }

    printf("|\n");
}
