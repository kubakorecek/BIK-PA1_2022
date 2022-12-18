#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STONES 50
#define TRUE 1
#define FALSE 0

long long int g_Calls = 0;
long long int g_0Calls = 0;
typedef struct Score
{
    int m_Player1;
    int m_Player2;
    char m_Move;

} SCORE;

typedef struct Result
{
    SCORE m_Score;
    int m_Has;

} RESULT;

int maximum(int size, int *array, int max)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

SCORE maximumScore(SCORE a, SCORE b, int player)
{
    if (player == 1)
    {
        if (a.m_Player1 > b.m_Player1)
            return a;
        else
            return b;
    }
    else

    {
        if (a.m_Player2 > b.m_Player2)
            return a;
        else
            return b;
    }
}
void emptyResults(RESULT LookUP[MAX_STONES][MAX_STONES][MAX_STONES][MAX_STONES], int sizeNorth, int sizeEast, int sizeWest, int sizeSouth)
{
    for (int w = 0; w <= sizeWest; w++)
        for (int s = 0; s <= sizeSouth; s++)
            for (int n = 0; n <= sizeNorth; n++)
                for (int e = 0; e <= sizeEast; e++)
                    LookUP[w][s][n][e].m_Has = FALSE;
}
int maximumScalar(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

void copyARR(char arr1[35], char arr2[35])
{
    for (int i = 0; i < 35; i++)
    {
        arr1[i] = arr2[i];
        // printf("%c\n", arr1[i]);
    }
}

SCORE getScore(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth, int player, int depth, RESULT LookUP[MAX_STONES][MAX_STONES][MAX_STONES][MAX_STONES])
{
    if(LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Has == TRUE)
    {
        return LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Score;
    };
    g_Calls++;
    SCORE sc4;
    SCORE sc3;
    SCORE sc2;
    SCORE sc1;
    SCORE tmpBack;
    sc1.m_Player1 = INT_MIN;
    sc1.m_Player2 = INT_MIN;
    sc2.m_Player1 = INT_MIN;
    sc2.m_Player2 = INT_MIN;
    sc3.m_Player1 = INT_MIN;
    sc3.m_Player2 = INT_MIN;
    sc4.m_Player1 = INT_MIN;
    sc4.m_Player2 = INT_MIN;
    if (sizeEast == 0 && sizeWest == 0 && sizeNorth == 0 && sizeSouth == 0)
    {
        g_0Calls++;
        SCORE sc;
        sc.m_Player1 = 0;
        sc.m_Player2 = 0;
        return sc;
    }

    if (player == 1)
    {
        player = 0;
    }
    else
    {
        player = 1;
    }
    if (sizeWest > 0)
    {
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W + 1, sizeWest - 1, S, sizeSouth, player, depth + 1, LookUP);

        if (player)
        {
            sc1.m_Player1 = W[0] + tmpBack.m_Player1;
            sc1.m_Player2 = 0 + tmpBack.m_Player2;
        }
        else
        {
            sc1.m_Player1 = 0 + tmpBack.m_Player1;
            sc1.m_Player2 = W[0] + tmpBack.m_Player2;
        }
        sc1.m_Move = 'W';
    }

    if (sizeNorth > 0)
    {
        tmpBack = getScore(N + 1, sizeNorth - 1, E, sizeEast, W, sizeWest, S, sizeSouth, player, depth + 1, LookUP);

        if (player)
        {

            sc2.m_Player1 = N[0] + tmpBack.m_Player1;
            sc2.m_Player2 = tmpBack.m_Player2;
        }
        else
        {
            sc2.m_Player2 = N[0] + tmpBack.m_Player2;
            sc2.m_Player1 = 0 + tmpBack.m_Player1;
        }
        sc2.m_Move = 'N';
    }
    if (sizeEast > 0)
    {
        tmpBack = getScore(N, sizeNorth, E + 1, sizeEast - 1, W, sizeWest, S, sizeSouth, player, depth + 1, LookUP);

        if (player)
        {
            sc3.m_Player1 = E[0] + tmpBack.m_Player1;
            sc3.m_Player2 = 0 + tmpBack.m_Player2;
        }
        else
        {
            sc3.m_Player1 = 0 + tmpBack.m_Player1;
            sc3.m_Player2 = E[0] + tmpBack.m_Player2;
        }
        sc3.m_Move = 'E';
    }
    if (sizeSouth > 0)
    {
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W, sizeWest, S + 1, sizeSouth - 1, player, depth + 1, LookUP);

        if (player)
        {
            sc4.m_Player1 = S[0] + tmpBack.m_Player1;
            sc4.m_Player2 = 0 + tmpBack.m_Player2;
        }
        else
        {
            sc4.m_Player1 = 0 + tmpBack.m_Player1;
            sc4.m_Player2 = S[0] + tmpBack.m_Player2;
        }
        sc4.m_Move = 'S';
    }

    LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Score= maximumScore(maximumScore(maximumScore(sc3, sc1, player), sc4, player), sc2, player);
    LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Has = TRUE;
    return LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Score;
}

SCORE play(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth, int player, int numberOfStones, RESULT LookUP[MAX_STONES][MAX_STONES][MAX_STONES][MAX_STONES])
{
    g_0Calls = 0;
    g_Calls = 0;
    int depth = 0;
    SCORE tmpBack;
    int Nshift = 0;
    int Sshift = 0;
    int Eshift = 0;
    int Wshift = 0;

    int playerA = 0;
    int playerB = 0;
    int playerTurn = player;

    emptyResults(LookUP,  sizeNorth,  sizeEast,  sizeWest,  sizeSouth);

    while (depth <= numberOfStones - 1)
    {
        char c = 'A';
        tmpBack = getScore(N + Nshift, sizeNorth - Nshift, E + Eshift, sizeEast - Eshift,
                           W + Wshift, sizeWest - Wshift, S + Sshift, sizeSouth - Sshift, player, depth, LookUP);
        // printf("return %d %d %lld move %c\n", tmpBack.m_Player1, tmpBack.m_Player2, g_Calls, tmpBack.m_Move);
        if (playerTurn == 0)
        {
            c = 'A';
        }
        else
        {
            c = 'B';
        }
        if (depth == 0)
        {
            playerA = tmpBack.m_Player1;
            playerB = tmpBack.m_Player2;
        }
        if (tmpBack.m_Move == 'S')
        {
            printf("%c: S[%d] (%d)\n", c, Sshift, S[Sshift]);
            Sshift++;
        }
        if (tmpBack.m_Move == 'W')
        {
            printf("%c: W[%d] (%d)\n", c, Wshift, W[Wshift]);
            Wshift++;
        }

        if (tmpBack.m_Move == 'E')
        {
            printf("%c: E[%d] (%d)\n", c, Eshift, E[Eshift]);
            Eshift++;
        }

        if (tmpBack.m_Move == 'N')
        {
            printf("%c: N[%d] (%d)\n", c, Nshift, N[Nshift]);
            Nshift++;
        }
        if (playerTurn == 1)
        {
            playerTurn = 0;
        }
        else
        {
            playerTurn = 1;
        }
        depth++;
    }
    printf("Celkem A/B: %d/%d\n", playerA, playerB);

    return tmpBack;
}

int readStoned(int *Array, int *size)
{
    char c;
    int i;
    int check;

    while (1)
    {
        check = scanf(" %c ", &c);
        if (check != 1)
        {
            // printf("wrong2\n");
            return FALSE;
        }
        if (c == '}')
        {
            break;
        }
        else if (c == ',')
        {
        }
        else
        {
            // printf("wrong3\n");
            return FALSE;
        }
        check = scanf(" %d ", &i);
        if (check != 1)
        {
            // printf("wrong4\n");
            return FALSE;
        }
        else
        {
            Array[(*size)] = i;
            if (*size > 32)
            {
                return FALSE;
            }
            (*size)++;
        }
    }

    return TRUE;
}

int readStones(int *N, int *sizeNorth, int *E, int *sizeEast, int *W, int *sizeWest, int *S, int *sizeSouth)
{
    char c;
    int i = 0;
    int cnt = 0;
    while (cnt < 4)
    {

        int check = scanf("%c : { %d", &c, &i);
        if (check != 2)
        {
            // printf("wrong1 %d\n", check);
            return FALSE;
        }
        if (!(c == 'S' || c == 'W' || c == 'E' || c == 'N'))
        {
            // printf("wrong %c\n", c);
            return FALSE;
        }
        else
        {
            // printf("c is %c", c);
        }
        if (c == 'S')
        {
            // printf("%d  south%c\n", *sizeSouth);
            if (*sizeSouth > 0)
            {
                // printf("wrong  south%c\n", c);
                return FALSE;
            }

            S[*sizeSouth] = i;
            (*sizeSouth)++;
            if (readStoned(S, sizeSouth) == FALSE)
            {
                return FALSE;
            };
        }

        if (c == 'W')
        {
            if (*sizeWest > 0)
            {
                return FALSE;
            }
            W[*sizeWest] = i;
            (*sizeWest)++;
            if (readStoned(W, sizeWest) == FALSE)
            {
                return FALSE;
            };
        }
        if (c == 'E')
        {
            if (*sizeEast > 0)
            {
                return FALSE;
            }
            E[*sizeEast] = i;
            (*sizeEast)++;
            if (readStoned(E, sizeEast) == FALSE)
            {
                return FALSE;
            };
        }
        if (c == 'N')
        {
            if (*sizeNorth > 0)
            {
                return FALSE;
            }
            N[*sizeNorth] = i;
            (*sizeNorth)++;
            if (readStoned(N, sizeNorth) == FALSE)
            {
                return FALSE;
            };
        }
        cnt++;
    }
    if ((*sizeNorth) == 0 || (*sizeSouth) == 0 || (*sizeEast) == 0 || (*sizeWest) == 0)
    {
        return FALSE;
    }

    return TRUE;
}



int main()
{
    printf("Zetony:\n");

    int North[MAX_STONES];
    int South[MAX_STONES];
    int East[MAX_STONES];
    int West[MAX_STONES];

    //     int (*data)[dataFilter][dataWidth][dataHeight];
    // data = malloc(dataNumber*sizeof(*data));

    int westNumber = 0;
    int southNumber = 0;
    int northNumber = 0;
    int eastNumber = 0;

    // printf("Zetony1:\n");
    if (readStones(North, &northNumber, East, &eastNumber, West, &westNumber, South, &southNumber) == FALSE)
    {
        printf("Nespravny vstup.\n");
        return 0;
    }
    RESULT(*LookUP)[MAX_STONES][MAX_STONES][MAX_STONES] = NULL;
    LookUP = (RESULT (*)[50][50][50])malloc(MAX_STONES * sizeof(*LookUP));
    int numberOfStones = westNumber + southNumber + northNumber + eastNumber;
    play(North, northNumber, East, eastNumber, West, westNumber, South, southNumber, 0, numberOfStones, LookUP);
    free(LookUP);
    // int N[] = {1, 2};
    // int W[] = {5};
    // int E[] = {1, 1, 1};
    // int S[] = {1, 7};
    // int numberOfStones = 8;
    // //

    // // max.m_Player1 = INT_MIN;
    // // max.m_Player2 = INT_MIN;
    // // int N[] = {1, 5000, 500};
    // // int W[] = {5, 4, 10};
    // // int E[] = {2};
    // // int S[] = {3};
    // // SCORE sc = getScore(N, 1, E, 1, W, 1, S, 1, 0, &max);
    // // SCORE sc1 =  getScore(N, 1, E, 1, W, 1, S, 1, 1);
    // // SCORE sc =  getScore(N, 2, E, 3, W, 1, S, 2, 0, &max);
    // // printf("max 1: %d  2: %d calls: %lld\n", max.m_Player1, max.m_Player2, g_Calls);
    // // sc = getScore(N, 2, E, 0, W, 2, S, 0, 0, &max);
    // // printf("max 1: %d  2: %d calls: %lld\n", max.m_Player1, max.m_Player2, g_Calls);

    // // printf("return %d %d %lld move %c\n", sc.m_Player1, sc.m_Player2, g_Calls, sc.m_Move);
    // //  sc = play(N, 2, E, 3, W, 1, S + 1, 2 - 1, 0);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // //  sc = play(N, 2, E, 3, W, 1, S + 2, 2 - 2, 1);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // //  sc = play(N, 2, E, 3, W+1, 1-1, S + 2, 2 - 2, 1);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    // int NN[] = {-66, -52, 109};
    // int WW[] = {78};
    // int EE[] = {118, 146, 46, 77};
    // int SS[] = {67, 159, -13};
    // numberOfStones = 11;
    // sc = play(NN, 3, EE, 4, WW, 1, SS, 3, 0,numberOfStones);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // //      sc =  getScore(NN, 3, EE+1, 3, WW, 1, SS, 3, 1, &max);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // //      sc =  getScore(NN, 3, EE, 4, WW+1, 0, SS, 3, 1, &max);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // //      sc =  getScore(NN, 3, EE, 4, WW, 1, SS+1, 2, 1, &max);
    // //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    // int NNN[] = {1, 2};
    // int WWW[] = {3, 5};
    // int EEE[] = {9, 1, 1, 1};
    // int SSS[] = {1, 7};
    // // sc = play(NNN, 2, EEE, 4, WWW, 2, SSS, 2, 1);
    // // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    // int NNNN[] = {1, 2, -4};
    // int EEEE[] = {9, 1, 1};
    // int WWWW[] = {3, 5, -2};
    // int SSSS[] = {1, 7};
    // sc = play(NNNN, 3, EEEE, 3, WWWW, 3, SSSS, 2, 1);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    //   printf("%d %d\n", sc1.m_Player1, sc1.m_Player2);
}