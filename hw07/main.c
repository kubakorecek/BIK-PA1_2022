#include <stdio.h>
#include <limits.h>
#include <string.h>
long long int g_Calls = 0;
typedef struct Score
{
    int m_Player1;
    int m_Player2;

} SCORE;

typedef struct MaxScore
{
    int m_Player1;
    int m_Player2;
} MAXSCORE;

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

SCORE getScore(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth, int player, MAXSCORE *max)
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
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W + 1, sizeWest - 1, S, sizeSouth, player, max);

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
        tmpBack = getScore(N + 1, sizeNorth - 1, E, sizeEast, W, sizeWest, S, sizeSouth, player, max);

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
        tmpBack = getScore(N, sizeNorth, E + 1, sizeEast - 1, W, sizeWest, S, sizeSouth, player, max);

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
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W, sizeWest, S + 1, sizeSouth - 1, player, max);

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

    // if( max.m_Player2 > 0 || max.m_Player1 > 0)
    // printf("max player %d %d %d\n", (*max).m_Player1, (*max).m_Player2, player);
    // printf("return P1 %d P2 %d\n", sc.m_Player1, sc.m_Player2);
    return maximumScore(maximumScore(maximumScore(sc1, sc2, player), sc3, player), sc4, player);
}

int main()
{

    MAXSCORE max;
    int N[] = {1, 2};
    int W[] = {5};
    int E[] = {1, 1, 1};
    int S[] = {1, 7};
    SCORE sc = getScore(N, 2, E, 3, W, 1, S, 2, 1, &max);

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
    max.m_Player1 = INT_MIN;
    max.m_Player2 = INT_MIN;
    // sc = getScore(N, 2, E, 0, W, 2, S, 0, 0, &max);
    // printf("max 1: %d  2: %d calls: %lld\n", max.m_Player1, max.m_Player2, g_Calls);
    printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    int NN[] = {-66, -52, 109};
    int WW[] = {78};
    int EE[] = {118, 146, 46, 77};
    int SS[] = {67, 159, -13};
    sc = getScore(NN, 3, EE, 4, WW, 1, SS, 3, 1, &max);
    printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    //     sc =  getScore(NN, 3, EE+1, 3, WW, 1, SS, 3, 1, &max);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    //     sc =  getScore(NN, 3, EE, 4, WW+1, 0, SS, 3, 1, &max);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);
    //     sc =  getScore(NN, 3, EE, 4, WW, 1, SS+1, 2, 1, &max);
    // printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    int NNN[] = {1, 2};
    int WWW[] = {3, 5};
    int EEE[] = {9, 1, 1, 1};
    int SSS[] = {1, 7};
    sc = getScore(NNN, 2, EEE, 4, WWW, 2, SSS, 2, 1, &max);
    printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    int NNNN[] = {1, 2, -4};
    int EEEE[] = {9, 1, 1};
    int WWWW[] = {3, 5, -2};
    int SSSS[] = {1, 7};
    sc = getScore(NNNN, 3, EEEE, 3, WWWW, 3, SSSS, 2, 1, &max);
    printf("return %d %d %lld\n", sc.m_Player1, sc.m_Player2, g_Calls);

    //   printf("%d %d\n", sc1.m_Player1, sc1.m_Player2);
}