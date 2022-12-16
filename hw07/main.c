#include <stdio.h>
#include <limits.h>
#include <string.h>
long long int g_Calls = 0;
long long int g_0Calls = 0;
typedef struct Score
{
    int m_Player1;
    int m_Player2;
    char m_Moves[35];

} SCORE;

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
        //printf("%c\n", arr1[i]);
    }
}



void assignDecssici

SCORE getScore(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth, int player, int depth)
{
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
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W + 1, sizeWest - 1, S, sizeSouth, player, depth + 1);

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
        copyARR(sc1.m_Moves, tmpBack.m_Moves);
        sc1.m_Moves[depth] = 'W';
    }

    if (sizeNorth > 0)
    {
        tmpBack = getScore(N + 1, sizeNorth - 1, E, sizeEast, W, sizeWest, S, sizeSouth, player, depth + 1);

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
        copyARR(sc2.m_Moves, tmpBack.m_Moves);
        sc2.m_Moves[depth] = 'W';
    }
    if (sizeEast > 0)
    {
        sc1.m_Moves[depth] = 'E';
        tmpBack = getScore(N, sizeNorth, E + 1, sizeEast - 1, W, sizeWest, S, sizeSouth, player, depth + 1);

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
        copyARR(sc3.m_Moves, tmpBack.m_Moves);
        sc3.m_Moves[depth] = 'W';
    }
    if (sizeSouth > 0)
    {
        sc1.m_Moves[depth] = 'S';
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W, sizeWest, S + 1, sizeSouth - 1, player, depth + 1);

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
        copyARR(sc4.m_Moves, tmpBack.m_Moves);
        sc4.m_Moves[depth] = 'W';
    }

    // if( max.m_Player2 > 0 || max.m_Player1 > 0)
    // printf("max player %d %d %d\n", (*max).m_Player1, (*max).m_Player2, player);
    // printf("return P1 %d P2 %d\n", sc.m_Player1, sc.m_Player2);
    return maximumScore(maximumScore(maximumScore(sc1, sc2, player), sc3, player), sc4, player);
}

SCORE play(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth, int player)
{
    g_0Calls = 0;
    g_Calls = 0;
    int depth = 0;

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

    if (sizeWest > 0)
    {
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W + 1, sizeWest - 1, S, sizeSouth, player, depth);

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
    }

    if (sizeNorth > 0)
    {
        tmpBack = getScore(N + 1, sizeNorth - 1, E, sizeEast, W, sizeWest, S, sizeSouth, player, depth);

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
    }
    if (sizeEast > 0)
    {
        tmpBack = getScore(N, sizeNorth, E + 1, sizeEast - 1, W, sizeWest, S, sizeSouth, player, depth);

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
    }
    if (sizeSouth > 0)
    {
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W, sizeWest, S + 1, sizeSouth - 1, player, depth);

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
    }
    char a[10]; 
    a[5] = 'P';
    printf("WEST %d %d %s m\n", sc1.m_Player1, sc1.m_Player2);
        for (int i = 0; i < 35; i++)
    {
        //arr1[i] = arr2[i];
        printf("%c\n", sc1.m_Moves[i]);
    }

    printf("NORT %d %d\n", sc2.m_Player1, sc2.m_Player2);

    printf("EAST %d %d\n", sc3.m_Player1, sc3.m_Player2);

    printf("SOUTH %d %d\n", sc4.m_Player1, sc4.m_Player2);

    return maximumScore(maximumScore(maximumScore(sc1, sc2, player), sc3, player), sc4, player);
}
int main()
{

    int N[] = {1, 2};
    int W[] = {5};
    int E[] = {1, 1, 1};
    int S[] = {1, 7};
    SCORE sc = play(N, 2, E, 3, W, 1, S, 2, 1);

    // max.m_Player1 = INT_MIN;
    // max.m_Player2 = INT_MIN;
    // int N[] = {1, 5000, 500};
    // int W[] = {5, 4, 10};
    // int E[] = {2};
    // int S[] = {3};
    // SCORE sc = getScore(N, 1, E, 1, W, 1, S, 1, 0, &max);
    // SCORE sc1 =  getScore(N, 1, E, 1, W, 1, S, 1, 1);
    // SCORE sc =  getScore(N, 2, E, 3, W, 1, S, 2, 0, &max);
    // printf("max 1: %d  2: %d calls: %lld\n", max.m_Player1, max.m_Player2, g_Calls);
    // sc = getScore(N, 2, E, 0, W, 2, S, 0, 0, &max);
    // printf("max 1: %d  2: %d calls: %lld\n", max.m_Player1, max.m_Player2, g_Calls);

    printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // sc = play(N, 2, E, 3, W, 1, S + 1, 2 - 1, 0);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // sc = play(N, 2, E, 3, W, 1, S + 2, 2 - 2, 1);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    // sc = play(N, 2, E, 3, W+1, 1-1, S + 2, 2 - 2, 1);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    int NN[] = {-66, -52, 109};
    int WW[] = {78};
    int EE[] = {118, 146, 46, 77};
    int SS[] = {67, 159, -13};
    // sc = play(NN, 3, EE, 4, WW, 1, SS, 3, 1);
    //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    //      sc =  getScore(NN, 3, EE+1, 3, WW, 1, SS, 3, 1, &max);
    //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    //      sc =  getScore(NN, 3, EE, 4, WW+1, 0, SS, 3, 1, &max);
    //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    //      sc =  getScore(NN, 3, EE, 4, WW, 1, SS+1, 2, 1, &max);
    //  printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    int NNN[] = {1, 2};
    int WWW[] = {3, 5};
    int EEE[] = {9, 1, 1, 1};
    int SSS[] = {1, 7};
    // sc = play(NNN, 2, EEE, 4, WWW, 2, SSS, 2, 1);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    int NNNN[] = {1, 2, -4};
    int EEEE[] = {9, 1, 1};
    int WWWW[] = {3, 5, -2};
    int SSSS[] = {1, 7};
    // sc = play(NNNN, 3, EEEE, 3, WWWW, 3, SSSS, 2, 1);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    //   printf("%d %d\n", sc1.m_Player1, sc1.m_Player2);
}