/**
 * @brief Implementation of the game 2048
 *
 * @author  Marut, Jesper Byström
 * @since   2019-12-03
 *
 */

#include "stdio.h"
#include <math.h>
#include "application.h"

static int get_score();
static void print_game();
static void print_header_line();
static void print_content(int box1, int box2, int box3, int box4);
static void print_empty_content_line();
static void print_menu();

void app_run(void)
{
    game_new();

    print_game();

    int selection;

    do
    {
        print_menu();

        scanf("%d", &selection);

        printf("\n");

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
        else
        {
            continue;
        }

        print_game();

    } while(selection != 0 && !game_is_game_over());

    fprintf(stderr, "GAME OVER\nYou got the score: %d\n", get_score());
}

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

static void print_game()
{
    for(int i = 0; i < BOARD_ROWS; i++)
    {
        print_header_line();
        print_empty_content_line();
        print_content(game_get_square(i, 0), game_get_square(i, 1), game_get_square(i, 2), game_get_square(i, 3));
        print_empty_content_line();
    }

    print_header_line();
    printf("\n\n\n\n");
}

static void print_header_line()
{
    for(int i = 0; i < BOARD_COLUMNS; i++)
    {
        printf("+--------");
    }

    printf("+\n");
}

static void print_empty_content_line()
{
    for(int i = 0; i < 5; i++)
    {
        printf("|        ");
    }

    printf("\n");
}

static void print_content(int box1, int box2, int box3, int box4)
{
    int boxes[] = {box1, box2, box3, box4};

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
