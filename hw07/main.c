#include <stdio.h>

#include <limits.h>

#include <stdlib.h>

#include <string.h>

#define MAX_STONES 50
#define MAX_STONE_IN_GAME 32
#define TRUE 1
#define FALSE 0

#define PLAYER1 1
#define PLAYER2 0

/**
 * Struct holding the Score for both players and last move.
 */
typedef struct Score
{
    int m_Player1;
    int m_Player2;
    char m_Move;

} SCORE;

/**
 * Struct holding the Score for lookup table.
 */
typedef struct Result
{
    SCORE m_Score;
    int m_HasCalculated;

} RESULT;

/**
 * Find maximum of two structs holding two player scores.
 *
 * Choosing any number then 1 will result in comparing by player 2
 *
 * @param[in] one struct - SCORE - first score
 * @param[in] second struct SCORE - second score
 * @param[in] player  int - 1 for taking player 2, player 2 otherwise
 * @returns struct - SCORE - the bigger score
 */
SCORE maximumScore(SCORE const one, SCORE const second, int const player)
{
    if (player == PLAYER1)
    {
        if (one.m_Player1 > second.m_Player1)
            return one;
    }
    else
    {
        if (one.m_Player2 > second.m_Player2)
            return one;
    }
    return second;
}

/**
 * Empty ( initialize) array for Look Up table to play the Game.
 *
 * Array should not have more then 50*50*50*50 coordinates.
 * It will set variable m_HasCalculated to FALSE.
 *
 * @param[in, out] LookUP 4D array of RESULT
 * @param[in] sizeNorth int - number of stones in North direction.
 * @param[in] sizeEast int - number of stones in East direction.
 * @param[in] sizeWest int - number of stones in West direction.
 * @param[in] sizeSouth int - number of stones in South direction.
 */
void emptyResults(RESULT LookUP[MAX_STONES][MAX_STONES][MAX_STONES][MAX_STONES], int const sizeNorth,
                  int const sizeEast, int const sizeWest, int const sizeSouth)
{
    for (int w = 0; w <= sizeWest; w++)
        for (int s = 0; s <= sizeSouth; s++)
            for (int n = 0; n <= sizeNorth; n++)
                for (int e = 0; e <= sizeEast; e++)
                    LookUP[w][s][n][e].m_HasCalculated = FALSE;
}

/**
 * Results from taking stone to be assigned.
 *
 *
 * @param[in] score resulting score
 * @param[in] player int - player.
 * @param[in] Stones array - Stones.
 * @param[in] move char - Move.
 * @param[in] sizeSouth int - number of stones in South direction.
 * @returns struct - SCORE - the new score
 */
SCORE takeStoneResult( SCORE const score, int const player, int const Stones[MAX_STONES], char const move)
{
    SCORE tmp;
    if (player)
    {
        tmp.m_Player1 = Stones[0] + score.m_Player1;
        tmp.m_Player2 = 0 + score.m_Player2;
    }
    else
    {
        tmp.m_Player1 = 0 + score.m_Player1;
        tmp.m_Player2 = Stones[0] + score.m_Player2;
    }
    tmp.m_Move = move;
    return tmp;
}

/**
 * The main recursive playing function for play the game.
 *
 * It will recursively play the Game for all possibilities.
 * Due to lookup table, it will play just if the game was not played before.
 * Unless is empty - then it would be filled.
 * It wil as well switch the player whom is playing at the moment.
 *
 * @param[in] N - pointer - to the North array.
 * @param[in] sizeNorth int - position of stones in North direction.
 * @param[in] E - pointer - to the East array.
 * @param[in] sizeEast int - position of stones in East direction.
 * @param[in] W - pointer - to the West array.
 * @param[in] sizeWest int - position of stones in West direction.
 * @param[in] S - pointer - to the South array.
 * @param[in] sizeSouth int - position of stones in South direction.
 * @param[in] player  int - 1 for taking player 2, player 2 by 0
 * @param[in , out] LookUP - 4D array of RESULT - it will assign values into look up table if not exists.
 * @returns struct - SCORE - the bigger score
 */
SCORE getScore(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth,
               int player, RESULT LookUP[MAX_STONES][MAX_STONES][MAX_STONES][MAX_STONES])
{
    /* if we already played that game we return*/
    if (LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_HasCalculated == TRUE)
    {
        return LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Score;
    };
    SCORE sc4, sc3, sc2, sc1, tmpBack;
    sc1.m_Player1 = INT_MIN;
    sc1.m_Player2 = INT_MIN;
    sc2.m_Player1 = INT_MIN;
    sc2.m_Player2 = INT_MIN;
    sc3.m_Player1 = INT_MIN;
    sc3.m_Player2 = INT_MIN;
    sc4.m_Player1 = INT_MIN;
    sc4.m_Player2 = INT_MIN;

    /* The Base case*/
    if (sizeEast == 0 && sizeWest == 0 && sizeNorth == 0 && sizeSouth == 0)
    {
        SCORE sc;
        sc.m_Player1 = 0;
        sc.m_Player2 = 0;
        return sc;
    }

    /* Player switcher */
    if (player == PLAYER1)
    {
        player = PLAYER2;
    }
    else
    {
        player = PLAYER1;
    }

    if (sizeWest > 0)
    {
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W + 1, sizeWest - 1, S, sizeSouth, player, LookUP);
        sc1 = takeStoneResult(tmpBack, player, W, 'W');
    }

    if (sizeNorth > 0)
    {
        tmpBack = getScore(N + 1, sizeNorth - 1, E, sizeEast, W, sizeWest, S, sizeSouth, player, LookUP);
        sc2 = takeStoneResult(tmpBack, player, N, 'N');
    }
    if (sizeEast > 0)
    {
        tmpBack = getScore(N, sizeNorth, E + 1, sizeEast - 1, W, sizeWest, S, sizeSouth, player, LookUP);
        sc3 = takeStoneResult(tmpBack, player, E, 'E');
    }
    if (sizeSouth > 0)
    {
        tmpBack = getScore(N, sizeNorth, E, sizeEast, W, sizeWest, S + 1, sizeSouth - 1, player, LookUP);
        sc4 = takeStoneResult(tmpBack, player, S, 'S');
    }

    /* compare scores and sing it into look up table*/
    LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Score =
        maximumScore(maximumScore(maximumScore(sc3, sc1, player), sc4, player), sc2, player);
    LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_HasCalculated = TRUE;
    return LookUP[sizeWest][sizeSouth][sizeNorth][sizeEast].m_Score;
}

/**
 * Main function for playing, it iterate over all stones.
 * print moves and then the total score.
 *
 * Due to lookup table the game is played just once.
 * Iteration only need to go and take stones on each iteration.
 *
 * @param[in] N - pointer - to the North array.
 * @param[in] sizeNorth int - position of stones in North direction.
 * @param[in] E - pointer - to the East array.
 * @param[in] sizeEast int - position of stones in East direction.
 * @param[in] W - pointer - to the West array.
 * @param[in] sizeWest int - position of stones in West direction.
 * @param[in] S - pointer - to the South array.
 * @param[in] sizeSouth int - position of stones in South direction.
 * @param[in] player  int - 1 for taking player 2, player 2 by 0
 * @param[in , out] LookUP - 4D array of RESULT - it will assign values into look up table if not exists.
 */
void play(int *N, int sizeNorth, int *E, int sizeEast, int *W, int sizeWest, int *S, int sizeSouth, int player, int numberOfStones, RESULT LookUP[MAX_STONES][MAX_STONES][MAX_STONES][MAX_STONES])
{
    /* round of the game.*/
    int round = 0;
    SCORE tmpBack;
    int Nshift = 0;
    int Sshift = 0;
    int Eshift = 0;
    int Wshift = 0;

    int playerA = 0;
    int playerB = 0;
    int playerTurn = player;

    /* empty look up table. */
    emptyResults(LookUP, sizeNorth, sizeEast, sizeWest, sizeSouth);

    while (round < numberOfStones )
    {
        char c = 'A';
        tmpBack = getScore(N + Nshift, sizeNorth - Nshift, E + Eshift, sizeEast - Eshift,
                           W + Wshift, sizeWest - Wshift, S + Sshift, sizeSouth - Sshift, player, LookUP);
        if (playerTurn == PLAYER2)
        {
            c = 'A';
        }
        else
        {
            c = 'B';
        }
        if (round == 0)
        {
            playerA = tmpBack.m_Player1;
            playerB = tmpBack.m_Player2;
        }
        if (tmpBack.m_Move == 'S')
        {
            printf("%c: S[%d] (%d)\n", c, Sshift, S[Sshift]);
            Sshift++;
        }
        else if (tmpBack.m_Move == 'W')
        {
            printf("%c: W[%d] (%d)\n", c, Wshift, W[Wshift]);
            Wshift++;
        }
        else if (tmpBack.m_Move == 'E')
        {
            printf("%c: E[%d] (%d)\n", c, Eshift, E[Eshift]);
            Eshift++;
        }
        else if (tmpBack.m_Move == 'N')
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
        round++;
    }
    printf("Celkem A/B: %d/%d\n", playerA, playerB);

    return;
}

/**
 * Read stones values into array.
 * Helping function ot read the stones.
 *
 * It as well check the game setting.
 * Like MAX_STONE_IN_GAME.
 *
 * @param[out] Array int array - holding stones values.
 * @param[out] size int - how many stones are in array.
 * @returns TRUE/FALSE - based on success or fail of checks
 */
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
            return FALSE;
        }
        if (c == '}')
        {
            break;
        }
        else if (c == ',')
        {
            check = scanf(" %d ", &i);
            if (check != 1)
            {
                return FALSE;
            }
            else
            {
                Array[(*size)] = i;
                if (*size > MAX_STONE_IN_GAME)
                {
                    return FALSE;
                }
                (*size)++;
            }
        }
        else
        {
            return FALSE;
        }
    }

    return TRUE;
}

/**
 * Results from taking stone to be assigned.
 * It will as well check, if the direction was not already taken.
 *
 *
 * @param[in] stones int array - holding stones values.
 * @param[in] size int - how many stones are in array.
 * @param[in] firstStone int - first stone to be assigned.
 * @returns TRUE/FALSE - based on success or fail of checks.
 */
int checkDirection(int *stones, int *size, int const *firstStone)
{
    /* that is the Array was already assigned.*/
    if (*size > 0)
        return FALSE;
    stones[*size] = *firstStone;
    (*size)++;
    if (readStoned(stones, size) == FALSE)
        return FALSE;
    return TRUE;
}

/**
 * Main function to read each Array of stones in every direction.
 * North - N, West - W, East - E, South - S
 *
 * @param[out] N - pointer - to the North array.
 * @param[out] sizeNorth int pointer - position of stones in North direction.
 * @param[out] E - pointer - to the East array.
 * @param[out] sizeEast int pointer - position of stones in East direction.
 * @param[out] W - pointer - to the West array.
 * @param[out] sizeWest int pointer- position of stones in West direction.
 * @param[out] S - pointer - to the South array.
 * @param[out] sizeSouth int pointer- position of stones in South direction.
 * @returns struct - SCORE - the new score
 */
int readStones(int *N, int *sizeNorth, int *E, int *sizeEast, int *W, int *sizeWest, int *S, int *sizeSouth)
{
    char c;
    int i = 0;
    int cnt = 0;
    while (cnt < 4)
    {

        int check = scanf("%c : { %d", &c, &i);
        if (check != 2)
            return FALSE;
        if (!(c == 'S' || c == 'W' || c == 'E' || c == 'N'))
            return FALSE;
        if (c == 'S')
        {
            if (checkDirection(S, sizeSouth, &i) == FALSE)
                return FALSE;
        }

        if (c == 'W')
        {
            if (checkDirection(W, sizeWest, &i) == FALSE)
                return FALSE;
        }
        if (c == 'E')
        {
            if (checkDirection(E, sizeEast, &i) == FALSE)
                return FALSE;
        }
        if (c == 'N')
        {
            if (checkDirection(N, sizeNorth, &i) == FALSE)
                return FALSE;
        }
        cnt++;
    }
    if ((*sizeNorth) == 0 || (*sizeSouth) == 0 || (*sizeEast) == 0 || (*sizeWest) == 0)
    {
        return FALSE;
    }

    return TRUE;
}

/**
 * PLay game Stones.
 * Entry point of the program.
 */
int main()
{
    printf("Zetony:\n");

    int North[MAX_STONES];
    int South[MAX_STONES];
    int East[MAX_STONES];
    int West[MAX_STONES];
    int westNumber = 0;
    int southNumber = 0;
    int northNumber = 0;
    int eastNumber = 0;
    if (readStones(North, &northNumber, East, &eastNumber, West, &westNumber, South, &southNumber) == FALSE)
    {
        printf("Nespravny vstup.\n");
        return EXIT_SUCCESS;
    }
    RESULT(*LookUP)
    [MAX_STONES][MAX_STONES][MAX_STONES] = NULL;
    LookUP = (RESULT(*)[50][50][50])malloc(MAX_STONES * sizeof(*LookUP));
    int numberOfStones = westNumber + southNumber + northNumber + eastNumber;
    play(North, northNumber, East, eastNumber, West, westNumber, South, southNumber, PLAYER2, numberOfStones, LookUP);
    free(LookUP);
    return EXIT_SUCCESS;
}