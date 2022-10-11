#include <stdio.h>
#include <assert.h>
#include <string.h>

#define FAILURE 1
#define NEG_FAILURE -1
#define SUCCES_RUN 0
#define BUFFER 4

#define MAX_MIL 999
#define MAX_SEC 59
#define MAX_MIN 59
#define MAX_H 23
#define MIN 0

void errorMessage(int const inputCode)
{
    if ((inputCode == 0))
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Nespravny vstup. at %d \n", inputCode);
}

int calcTime(int const *hours, int const *minutes, int const *seconds, int const *miliseconds)
{
    return *hours * 3600000 + *minutes * 60000 + *seconds * 1000 + *miliseconds;
}

void deCalcTime(int const *timeInMiliseconds, int *hours, int *minutes, int *seconds, int *miliseconds)
{
    *miliseconds = (*timeInMiliseconds % 1000);
    *seconds = (*timeInMiliseconds / 1000);
    *minutes = (*seconds / 60);
    *hours = (*minutes / 60);

    *seconds %= 60;
    *minutes %= 60;
    *hours %= 24;
}

int checkBoundary(int const *number, int const max, int const min)
{
    if (*number > max || *number < min)
    {
        return FAILURE;
    }
    return SUCCES_RUN;
}

void startMessage(int const timeCode)
{
    printf("Zadejte cas t%d:\n", timeCode);
}

int convertCharToDigit(const char c)
{
    int result = ((int)c - (int)'0');
    if ((result < 0) || (result > 9))
    {
        return NEG_FAILURE;
    }

    return result;
}

int readTime(int *hours, int *minutes, int *seconds, int *miliseconds)
{
    char tmpMilisecondsArray[BUFFER] = {'\0'};
    int ret = scanf(" %d : %d :%d , %4s", hours, minutes, seconds, tmpMilisecondsArray);
    if ((ret != 4) || tmpMilisecondsArray[3] != '\0')
    {

        errorMessage(0);
        return FAILURE;
    }
    int len = strlen(tmpMilisecondsArray);
    for (int j = 0; j < len; j++)
    {

        if (convertCharToDigit(tmpMilisecondsArray[j]) == NEG_FAILURE)
        {
            errorMessage(0);
            return FAILURE;
        }
        switch (j)
        {
        case 0:
            *miliseconds += convertCharToDigit(tmpMilisecondsArray[j]) * 100;
            break;
        case 1:
            *miliseconds += convertCharToDigit(tmpMilisecondsArray[j]) * 10;
            break;
        case 2:
            *miliseconds += convertCharToDigit(tmpMilisecondsArray[j]);
            break;

        default:
            break;
        }
    }

    if (checkBoundary(hours, MAX_H, MIN) || checkBoundary(minutes, MAX_MIN, MIN) ||
        checkBoundary(seconds, MAX_SEC, MIN) || checkBoundary(miliseconds, MAX_MIL, MIN))

    {
        errorMessage(0);
        return FAILURE;
    }

    return SUCCES_RUN;
}

int main(int arg, char **args)
{
    int hours, minutes, seconds, miliseconds;

    int hours2, minutes2, seconds2, miliseconds2;

    hours = 7;
    minutes = 15;
    seconds = 0;
    miliseconds = 0;
    int result = calcTime(&hours, &minutes, &seconds, &miliseconds);

    assert(result == 26100000);

    deCalcTime(&result, &hours2, &minutes2, &seconds2, &miliseconds2);

    assert(hours2 == 7);

    assert(minutes2 == 15);

    assert(seconds2 == 0);

    assert(miliseconds2 == 0);

    int timeDiff;
    startMessage(1);
    if (readTime(&hours, &minutes, &seconds, &miliseconds) == FAILURE)
    {
        return SUCCES_RUN;
    };

    startMessage(2);
    if (readTime(&hours2, &minutes2, &seconds2, &miliseconds2) == FAILURE)
    {
        return SUCCES_RUN;
    };

    int time1 = calcTime(&hours, &minutes, &seconds, &miliseconds);
    int time2 = calcTime(&hours2, &minutes2, &seconds2, &miliseconds2);

    timeDiff = time2 - time1;

    if (timeDiff < 0)
    {
        errorMessage(0);
        return SUCCES_RUN;
    }

    deCalcTime(&timeDiff, &hours2, &minutes2, &seconds2, &miliseconds2);
    printf("Doba:%3d:%02d:%02d,%03d", hours2, minutes2, seconds2, miliseconds2);
    printf("\n");
}
