/**
 * It's a connect 4 game with 3 modes: 2 player, easy CPU and medium CPU
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// defining the number of rows, columns, and the modes.
#define ROWS 6
#define COLS 7
#define coop 1
#define easy 2
#define medium 3

// creating a 2D array of characters which represents the board.
char scores[ROWS][COLS];
// defining the header and the horizontal bar.
char header[] = "  1   2   3   4   5   6   7  ";
char horbar[] = "|---|---|---|---|---|---|---|";
// declaring the variables bin and disc.
int bin = 0;
char disc = 'X';

void init_scores();
void test_scores();
void board();
void choose();
void fill_bin();
void start();
void menu();
char medium_cpu();
char easy_cpu();
int check(char disc, int mode, int limit);
int mode = 0;

/**
 * The function "menu" is called, which displays the menu. The function "init_scores" is called, which
 * initializes the scores to 0. The function "test_scores" is called, which tests the scores to see if
 * they are 0. The function "board" is called, which displays the board. The function "start" is
 * called, which starts the game
 *
 * @return the value of the variable "choice"
 */

int main()
{
    menu();
    init_scores();
    test_scores();
    board();
    start();
    return 0;
}

/**
 * It prints a menu and asks the user to choose a mode.
 */

void menu()
{
    printf("please choose a mode:\n");
    printf("1. 2 Player\n");
    printf("2. Easy CPU\n");
    printf("3. Medium CPU\n");
    printf("--> ");
    scanf("%d", &mode);
}

/**
 * It's a function that prints the board, asks the user to choose a position, and checks if the game is
 * over
 */

void start()
{
    while (1)
    {

        /*checking if the mode is not coop, and if it's not, it checks if the disc is X, and if it
        is, it prints "Player's turn", and if it's not, it prints "CPU's turn". If the mode is coop,
        it prints "Player %c, your turn!", where %c is the disc. */

        (mode != coop) ? disc == 'X' ? printf("\nPlayer's turn\n") : printf("\nCPU's turn\n") : printf("Player %c, your turn!\n", disc);
        choose();
        printf("\n\n");
        board();
        // checking if there are 4 consecutive discs of the same color in a row, column or diagonal.
        if (check('X', 0, 4))
        {
            // printing "Player X wins!" and then it's breaking out of the loop.
            printf("\n\nPlayer X wins!\n\n");
            break;
        }
        if (check('O', 0, 4))
        {
            /*checking if the mode is coop, and if it is, it's printing "Player O wins!", and if
            it's not, it prints "CPU wins!". */
            mode == coop ? printf("\n\nPlayer O wins!\n\n") : printf("\n\nCPU wins!\n\n");
            break;
        }
    }
}

/**
 * It initializes the scores array to all spaces
 */
void init_scores()
{
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            scores[i][j] = ' ';
        }
    }
}

/**
 * This function prints the contents of the scores array to validate the function "init_scores"
 */

void test_scores()
{
    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%c ", scores[i][j]);
        }
        printf("\n");
    }
}

/**
 * It prints the header, then the horizontal bar, then it prints the scores array, then the horizontal
 * bar
 */

void board()
{
    printf("%s\n", header);
    printf("%s\n", horbar);

    int i, j;

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("| %c ", scores[i][j]);
        }
        printf("|\n");
        printf("%s\n", horbar);
    }
}

/**
 * It asks the user to choose a bin, and then fills it with the appropriate disc
 */

void choose()
{

    char c;

    while (1)
    {

        if (mode == coop || disc == 'X')
        {
            printf("\nChoose bin: ");
            scanf(" %c", &c);
        }
        else if (mode == easy)
        {
            c = easy_cpu();
        }
        else if (mode == medium)
        {
            c = medium_cpu();
        }

        switch (c)
        {
        case '1':
        case 1:
            bin = 0;
            break;
        case '2':
        case 2:
            bin = 1;
            break;
        case '3':
        case 3:
            bin = 2;
            break;
        case '4':
        case 4:
            bin = 3;
            break;
        case '5':
        case 5:
            bin = 4;
            break;
        case '6':
        case 6:
            bin = 5;
            break;
        case '7':
        case 7:
            bin = 6;
            break;
        default:
            bin = 666;
            printf("\nWrong number! Try again.\n\n");
            board();
        }
        if ((bin >= 0 && bin <= 6) && (scores[0][bin] == ' '))
        {
            fill_bin();
            disc = (disc == 'X') ? 'O' : 'X';
            break;
        }
    }
}

/**
 * The function fill_bin() takes the value of the variable bin and uses it to fill the array scores[][]
 * with the value of the variable disc
 */
void fill_bin()
{
    int level;

    // checking if the bin is empty, and if it is, it fills it with the appropriate disc.
    for (level = ROWS - 1; level >= 0; level--)
    {
        if (scores[level][bin] == ' ')
        {
            scores[level][bin] = disc;
            break;
        }
    }
}

/**
 * It checks if there are 4 consecutive discs of the same color in a row, column or diagonal.
 *
 * @param disc the disc to check for
 * @param checkMode 0 for checking if there's a win, 1 for checking if there's a block
 * @param limit the number of consecutive discs needed to win
 *
 * @return the column number of the next move.
 */

int check(char disc, int checkMode, int limit)
{

    int i, j, k;
    int count;

    int ways = 4;
    int response = 0;

    // checking if there are 4 consecutive discs of the same color in a row.
    for (i = 0; i < ROWS; ++i)
    {
        for (j = 0; j < ways; ++j)
        {
            count = 0;
            for (k = 0; k < limit; ++k)
            {
                if (scores[i][j + k] == disc)
                    count++;
            }
            if (count == limit)
                if (checkMode == 0)
                    return 1;
                // checking if the next move is Empty.
                else if (scores[i][j + k] == ' ')
                    // returning the column number of the next move.
                    return j + k + 1;
        }
    }

    ways = 3;

    // checking if there are 4 consecutive discs of the same color in a column.
    for (j = 0; j < COLS; ++j)

    {
        for (i = 0; i < ways; ++i)
        {
            count = 0;
            for (k = 0; k < limit; ++k)
            {
                if (scores[i + k][j] == disc)
                    count++;
            }
            if (count == limit)
                if (checkMode == 0)
                    return 1;
                else if (scores[i + k + 1][j] == ' ')
                    return j - 1;
        }
    }

    int ii, jj;
    // checking if there are 4 consecutive discs of the same color in a diagonal.
    for (i = 1; i < ROWS - 1; i++)
    {

        for (j = 1; j < COLS - 1; j++)
        {

            count = 0;
            for (ii = i, jj = j; (ii >= 0) || (jj >= 0); ii--, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == limit)
                        if (checkMode == 0)
                            return 1;
                        else if (scores[ii][jj] == ' ')
                            return jj;
                }
                else
                    break;
            }

            for (ii = i + 1, jj = j + 1; (ii <= ROWS - 1) || (jj <= COLS - 1); ii++, jj++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == limit)
                        if (checkMode == 0)
                            return 1;
                        else if (scores[ii][jj] == ' ')
                            return jj;
                }
                else
                    break;
            }

            count = 0;
            for (ii = i, jj = j; (ii <= ROWS - 1) || (jj >= 0); ii++, jj--)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == limit)
                        if (checkMode == 0)
                            return 1;
                        else if (scores[ii][jj] == ' ')
                            return jj;
                }
                else
                    break;
            }
            for (ii = i - 1, jj = j + 1; (ii >= 0) || (jj <= COLS - 1); ii--, j++)
            {
                if (scores[ii][jj] == disc)
                {
                    count++;
                    if (count == limit)
                        if (checkMode == 0)
                            return 1;
                        else if (scores[ii][jj] == ' ')
                            return jj;
                }
                else
                    break;
            }
        }
    }

    return 0;
}

/**
 * It generates a random number between 0 and 6, and returns that number.
 *
 * @return A random number between 0 and 7.
 */

char easy_cpu()
{
    time_t t1;
    srand(time(0));
    int n = (rand()) % 7;
    if (n >= 1 && n <= 7)
        return (n);
    else
        return easy_cpu();
}

/**
 * If the computer can win, it will. If the player can win, it will block the player. If neither can
 * win, it will make a random move
 *
 * @return the value of the easy_cpu() function.
 */

char medium_cpu()
{
    int response = 0;
    // checking if the computer can win, and if it can, it will.
    if (check('O', 0, 3))
    {
        response = check('O', 1, 3);
        if (response >= 1 && response <= 7)
            return response;
    }
    // checking if the player can win, and if it can, it will block the player.
    if (check('X', 0, 3))
    {
        response = check('X', 1, 3);
        if (response >= 1 && response <= 7)
            return response;
    }
    // checking if there are 2 consecutive discs of the same color in a row, column or diagonal.
    if (check('O', 0, 2))
    {
        response = check('O', 1, 2);
        if (response >= 1 && response <= 7)
            return response;
    }
    // checking if there's a disc of the same color in a row, column or diagonal.
    if (check('O', 0, 1))
    {
        response = check('O', 1, 1);
        if (response >= 1 && response <= 7)
            return response;
    }
    return easy_cpu();
}
