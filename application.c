#include "stdio.h"
#include <math.h>
#include "application.h"

static void print_horizontal(void);
static void print_vertical(int k);
static void print_game();

void app_run(void)
{
    game_new();

    print_game();

    char str[2];
    do
    {
        scanf("%s", str);
        if(str[0] == 'w')
        {
            game_slide_up();
        }
        if(str[0] == 's')
        {
            game_slide_down();
        }
        if(str[0] == 'a')
        {
            game_slide_left();
        }
        if(str[0] == 'd')
        {
            game_slide_right();
        }

        print_game();

    } while(str[0] != 'x' && !game_is_game_over());

    if(game_is_game_over())
    {
        fprintf(stderr, "GAME OVER\n");
    }
}

static void print_game()
{
    for(int i = 0; i < 4; i++)
    {
        print_horizontal();
        print_vertical(i);
    }

    print_horizontal();
    printf("\n\n\n\n\n\n\n\n\n\n");
}

static void print_horizontal(void)
{
    for(int i = 0; i < 4; i++)
    {
        printf("+");
        for(int j = 0; j < 8; j++)
        {
            printf("-");
        }
    }
    printf("+");
}


static void print_vertical(int k)
{
    int wew = 4;
    printf("\n");
    int count = 0;
    int n;

    int l = 0;

    for(int i = 0; i < 4; i++)
    {
        if(i == 3)
        {
            //continue;
        }
        else
        {
            for(int j = 0, l = 0; j < 4; j++, l++)
            {
                printf("|");

                n = game_get_square(k, l);

                if(i == 1)
                {
                    count = 0;
                    while(n != 0)
                    {
                        n /= 10;
                        ++count;
                    }
                    if(game_get_square(k, l) != 0 && count > 0)
                    {
                        switch(count)
                        {
                                case 1:
                                    printf("    %d   ", game_get_square(k, l));
                                    break;

                                case 2:
                                    printf("   %d   ", game_get_square(k, l));
                                    break;

                                case 3:
                                    printf("  %d   ", game_get_square(k, l));
                                    break;

                                case 4:
                                    printf(" %d   ", game_get_square(k, l));
                                    break;
                                default:
                                    printf("        ");
                            }
                        }
                    else
                    {
                        printf("        ");
                    }
                }
                else
                {
                    printf("        ");
                }

                if(j == 3)
                {

                    printf("|");
                }

                //printf("[%d, %d]", k, l);
            }
            printf("\n");
        }
    }
    //printf("\n|\t |");
    /*
    int k = 0;
    int l = 0;
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        printf("\n");

        for(int j = 0; j < 4; j++)
        {

            if(j == 3)
            {
               // printf("|        ");
               // printf("|        ");

            }
            if(i == 1)
            {
                if(i == 1)
            {
                n = game_get_square(k, l);
                while(n != 0)
                {

                    n /= 10;
                    ++count;
                }
                switch(count)
                {
                    case 1:
                        printf("    %d   ", game_get_square(k, l));
                        break;

                    case 2:
                        printf("   %d   ", game_get_square(k, l));
                        break;

                    case 3:
                        printf("  %d   ", game_get_square(k, l));
                        break;

                    case 4:
                        printf(" %d   ", game_get_square(k, l));
                        break;
                    default:
                        printf("       ");
                }
            }
            else
            {
                printf("        ");
            }
            }
            else
            {
                printf("|        ");
            }
            l++;
        }
        k++;
    }*/


    /*
    int n2 = n;
    int count = 0;
    for(int i = 0; i < 4; i++)
    {
        printf("\n");
        for(int j = 0; j < 4; j++)
        {
            printf("|");
            if(i == 1 && j != 4)
            {
                n = game_get_square(i, j);
                while(n != 0)
                {

                    n /= 10;
                    ++count;
                }
                switch(count)
                {
                    case 1:
                        printf("    %d   ", game_get_square(i, j));
                        break;

                    case 2:
                        printf("   %d   ", game_get_square(i, j));
                        break;

                    case 3:
                        printf("  %d   ", game_get_square(i, j));
                        break;

                    case 4:
                        printf(" %d   ", game_get_square(i, j));
                        break;
                    default:
                        printf("       ");
                }
            }
            else
            {
                printf("        ");
            }
        }
    }*/
    //printf("\n|\t |");
}
