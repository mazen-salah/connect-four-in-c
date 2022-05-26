#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROWS 6
#define COLS 7
#define coop 1
#define easy 2
#define medium 3

char scores[ROWS][COLS];
char header[] = "  1   2   3   4   5   6   7  ";
char horbar[] = "|---|---|---|---|---|---|---|";
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

int main()
{
    menu();
    init_scores();
    test_scores();
    board();
    start();
    return 0;
}

void menu()
{
    printf("please choose a mode:\n");
    printf("1. 2 Player\n");
    printf("2. Easy CPU\n");
    printf("3. Medium CPU\n");
    printf("--> ");
    scanf("%d", &mode);
}

void start()
{
    while (1)
    {
        // what to print according to mode and players' turn
        (mode != coop) ? disc == 'X' ? printf("\nPlayer's turn\n") : printf("\nCPU's turn\n") : printf("Player %c, your turn!\n", disc);
        choose();
        printf("\n\n");
        board();
        if (check('X', 0, 4))
        {
            printf("\n\nPlayer X wins!\n\n");
            break;
        }
        if (check('O', 0, 4))
        {
            mode == coop ? printf("\n\nPlayer O wins!\n\n") : printf("\n\nCPU wins!\n\n");
            break;
        }
    }
}

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

void fill_bin()
{
    int level;

    for (level = ROWS - 1; level >= 0; level--)
    {
        if (scores[level][bin] == ' ')
        {
            scores[level][bin] = disc;
            break;
        }
    }
}

int check(char disc, int checkMode, int limit)
{

    int i, j, k;
    int count;

    int ways = 4;
    int response = 0;
    // row check
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
                else if (scores[i][j + k] == ' ')
                    return j + k + 1;
        }
    }

    ways = 3;
    // column check
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

char easy_cpu()
{
    time_t t1;
    srand(time(0));
    int n = (rand()) % 7;
    if (n <= 7)
        return (n);
    else
        return easy_cpu();
}

char medium_cpu()
{
    int response = 0;
    if (check('O', 0, 3))
    {
        response = check('O', 1, 3);
        if (response >= 1 && response <= 7)
            return response;
    }
    if (check('X', 0, 3))
    {
        response = check('X', 1, 3);
        if (response >= 1 && response <= 7)
            return response;
    }
    if (check('O', 0, 2))
    {
        response = check('O', 1, 2);
        if (response >= 1 && response <= 7)
            return response;
    }
    if (check('O', 0, 1))
    {
        response = check('O', 1, 1);
        if (response >= 1 && response <= 7)
            return response;
    }

    return easy_cpu();
}
