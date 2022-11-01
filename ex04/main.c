#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */
#define FALSE 0
#define TRUE 1

int isLeapYear2(int const year)
{
    if((year) % 4 == 0)
    {
        if((year) % 100 == 0)
        {
            if((year) % 400 == 0)
            {
                if((year) % 4000 == 0)
                {
                    return FALSE;
                }
                return TRUE;
            }
            return FALSE;
        }
        return TRUE;    
    }
    return FALSE;
}

int isLeapYear(int const year)
{
    if ( (year % 4 == 0)&& (year % 4000 != 0) && ( year % 100 != 0 || year % 400 == 0  )){
        return TRUE;
    }
    return  FALSE;
}

int dateToIndex(int day, int month, int year, int *idx) {
    short int month31[5] = {4,6,9,11};
    short int monthCumSum[13] = {0,31, 59,90,120,151,181,212,243,273,304,334};
    *idx = 0;
    if( (day < 1 || (month <1) || (month > 12) || (year < 2000) || day > 31)
    {
        return 0;
    }
    for(int k = 0 ; k < 4; k++)
    {
        if((day > 30) && (month == month31[k]))
        {
            return 0;
        }
    }


    if(isLeapYear(year) == TRUE)
    {
        if(month == 2 && day > 29)
        {
            return 0;
        }
        for(int j = 2; j < month+1; j++)
        {
            monthCumSum[j] +=1;
        }
    }else if(month == 2 && day > 28)
    {
        return 0;
    }
    (*idx) =day + monthCumSum[month-1]; 
    return 1;
}

#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
    assert(isLeapYear( 2001 ) == FALSE );
    assert(isLeapYear( 2008) == TRUE);
    assert(isLeapYear( 2200) == FALSE);
    assert(isLeapYear( 2000) == TRUE);
    assert(isLeapYear( 4400) == TRUE);
    assert(isLeapYear( 4000) == FALSE);

    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    return 0;
}
#endif /* __PROGTEST__ */

