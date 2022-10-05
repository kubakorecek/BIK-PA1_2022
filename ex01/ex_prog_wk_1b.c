#include <stdio.h>
#define FAILURE 1
#define SUCCES_RUN 0

#define MAX_MIL 999
#define MAX_SEC 59
#define MAX_MIN 59
#define MAX_H 23
#define MIN 0




void errorMessage( int inputCode ) 
{
    if((inputCode == 0))
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Nespravny vstup. at %d", inputCode);     
}

int calcTime(int * hours, int * minutes, int * seconds)
{
    return *hours * 600 + *minutes * 60 + *seconds * 60;
}

void startMessage( int timeCode ) 
{
    printf("Zadejte cas t%d:\n", timeCode);     
}


int readTime(int * hours, int * minutes, int * seconds, int * miliseconds)
{
        if((scanf(" %d : %d : %d , %d ",hours, minutes,seconds, miliseconds) != 4) )
    {
        errorMessage(0);
        return FAILURE;
    } 

        if (*hours > MAX_H || *hours < MIN)
    {
       errorMessage(0);
       return FAILURE; 
    }
    if (*minutes > MAX_MIN || *minutes < MIN)
    {
       errorMessage(0);
       return FAILURE; 
    }
    if (*seconds > MAX_SEC || *seconds < MIN)
    {
       errorMessage(0);
       return FAILURE; 
    }
    if (*miliseconds > MAX_MIL || *miliseconds < MIN)
    {
       errorMessage(0);
       return FAILURE; 
    }
    return SUCCES_RUN;
}

int main ( int arg, char ** args )
{
    int hours, minutes, seconds, miliseconds;

    int hours2, minutes2, seconds2, miliseconds2;

    int hoursDiff, minutesDiff, secondsDiff, milisecondsDiff;



    startMessage( 1 ); 
    readTime(&hours, &minutes, &seconds, &miliseconds);

    startMessage( 2 ); 
    readTime(&hours2, &minutes2, &seconds2, &miliseconds2);




    hoursDiff = hours2-hours;
    minutesDiff = minutes2-minutes;
    secondsDiff = seconds2-seconds;
    milisecondsDiff = miliseconds2-miliseconds;

    printf("%d:",hoursDiff);
    if(minutesDiff < 10)
    {
        printf("0%d:",minutesDiff);
    }else 
    {
       printf("%d:",minutesDiff); 
    }
    if(secondsDiff < 10)
    {
        printf("0%d:",secondsDiff);
    }else 
    {
       printf("%d:",secondsDiff); 
    }

    if(milisecondsDiff < 10)
    {
        printf("00%d:",milisecondsDiff);
    }else if (milisecondsDiff <100)
    {
       printf("0%d:",milisecondsDiff); 
    }else 
    {
       printf("%d:",milisecondsDiff); 
    }
    printf("\n");
}
