#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define FALSE 0
#define TRUE 1
#define LEAPYEARS 40000
#define SHIFT 1600
#define MIN_DAYS 1440

#define DAY_SUM_RU_ING_B1 240
#define HOUR_SUM_RU_ING_B1 10
#define DAY_SUM_RU_ING_B2 156

typedef struct Date
{
    int year;
    int month;
    int day;
    short dayInWeek; // 1 monday

} Date;

static short int monthCumSum[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static short int month31[5] = {4, 6, 9, 11};
static unsigned int leapsYear[LEAPYEARS / 4 + 1] = {0};

int isLeapYear(int const year)
{
    if ((year % 4 == 0) && (year % 4000 != 0) && (year % 100 != 0 || year % 400 == 0))
    {
        return TRUE;
    }
    return FALSE;
}

void fillLeapYears(unsigned int end)
{
    int pos = 0;
    for (unsigned int j = 1600; j < end; j += 4)
    {
        if (isLeapYear(j) == TRUE)
        {
            leapsYear[pos] = j;
            pos++;
        }
    }
}
int leapYearsArray(int y1, int y2)
{
    int n = 0;
    for (int j = 0; j < (LEAPYEARS / 4); j++)
    {
        if (leapsYear[j] <= y1)
        {
            continue;
        }
        if (leapsYear[j] >= y2)
        {
            break;
        }
        n++;
    }
    return n;
}
short int monthToday(const int *month, const int *day, const short isLeap)
{

    short int days = 0;
    if (isLeap == TRUE && *month > 2)
    {
        days += 1;
    }
    days += monthCumSum[*month - 1] + (*day) - 1;
    return days;
}
unsigned long long int dateTonumericMin(const int leaps, const int year, const int month,
                                        const int day, const int hour, const int minut)
{
    unsigned long long int numericDate = 0;
    unsigned long long int days = 0;
    unsigned int pos = 0;
    days += ((year)*365 + monthToday(&month, &day, isLeapYear(year))) + leaps;
    numericDate += days * 1440 + 60 * hour + minut;
    return numericDate;
}
int getLeaps(const int starYear, const int endYear)
{
    int leaps = 0;
    int pos = 0;
    while (leapsYear[pos] < endYear)
    {
        pos++;
        if (leapsYear[pos] > starYear)
        {
            leaps++;
        }
    }
    return leaps;
}

long long int getMinDiff(long long unsigned int  *m1, long long  unsigned int *m2)
{   
    long long int res =(long long int)((*m2) - (*m1));
    return res;
}
int getSundaysCount(long long int days, int origin)
{
    // 0 is aturday 
    origin = (origin +5) % 7;
    //int days = (minDiff/MIN_DAYS);
    int sundays = 0;
    // if(((origin + days) % 7) >=6)
    // {
    //     sundays++;
    // }
    sundays += (days+origin) / 7; 
    return sundays;
}
long long int calcB(long long int minDiff, int h1, int m1, int h2, int m2,int origin, long long int *b2)
{   
    int sundays = getSundaysCount((minDiff/MIN_DAYS)+1,origin);
    minDiff = minDiff - sundays *MIN_DAYS;

    int daysTMP = (int)(minDiff / MIN_DAYS);
    (*b2) = DAY_SUM_RU_ING_B2 * (daysTMP);
    if(daysTMP > 0)
    {
        // inner day //
        //(*b2)-=DAY_SUM_RU_ING_B2;
    } 
    // rest ot hours and get upper bondary
    int endH = h1 + ((minDiff % MIN_DAYS) / 60);

    // number of hours
    int hourTMP =(int)(minDiff / 60);
    long long int b1 = HOUR_SUM_RU_ING_B1 * (int)(minDiff / 60) ;
    if(hourTMP > 24)
    {
       // b1 -= DAY_SUM_RU_ING_B1;
    }
    
    
    if(m1 == 0)
    {
        if (h1 == 0)
        {
            (*b2) += 12;
        }
        (*b2) += (h1 % 12);
    }
    for (int i = h1 + 1; i <= endH; i++)
    {
        (*b2) += (i % 12);
        if(i % 12 == 0)
        {
           (*b2) += 12; 
        }
    }
    int endM = m1 + (minDiff % 60);
    for (int j = m1; j <= endM; j += 15)
    {
        if (j >= 0 && j < 15)
        {
            b1 += 4;
        }
        else if (j >= 15 && j < 30)
        {
            b1 += 1;
        }
        else if (j >= 30 && j < 45)
        {
            b1 += 2;
        }
        else if (j >= 45 && j < 60)
        {
            b1 += 3;
        }
    }

    return b1;
}




int bells(int y1, int m1, int d1, int h1, int i1,
          int y2, int m2, int d2, int h2, int i2,
          long long int *b1, long long int *b2)
{
    int leaps1 = getLeaps(SHIFT, y1);
    int leaps2 = getLeaps(SHIFT, y2);

    (*b1) = 0;
    (*b2) = 0;
    unsigned long long int a = dateTonumericMin(leaps1, y1 - SHIFT, m1, d1, h1, i1);
    if(((a/60)/24) % 7 == 1)
    {   
        d1 = d1+1;
        h1 = 0;
        i1 = 0;
        a = dateTonumericMin(leaps1, y1 - SHIFT, m1, d1, h1, i1);
    } 
    unsigned long long int b = dateTonumericMin(leaps2, y2 - SHIFT, m2, d2, h2, i2);
    if(((b/60)/24) % 7 == 1)
    {
        d2 = d2-1;
        h2 = 23;
        i2 = 45;
        b = dateTonumericMin(leaps2, y2 - SHIFT, m2, d2, h2, i2);
    } 
    int origin = ((a/60)/24) % 7;
    *b1 = calcB(getMinDiff(&a, &b), h1, i1, h2, i2,origin, b2);
    return TRUE;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
    fillLeapYears(LEAPYEARS);
    assert(leapYearsArray(1600, 1792) == 46);
    assert(leapYearsArray(1600, 1792) == 46);

    assert(isLeapYear(2019) == FALSE);
    assert(isLeapYear(2024) == TRUE);
    // unsigned long long int days1 = 0;
    // unsigned long long int days2 = 0;
    // unsigned long long int dayst = 0;
    // int y1 = 1600;
    // int y2 = 1600;
    // int leaps1 = getLeaps(SHIFT, y1);
    // int leaps2 = getLeaps(SHIFT, y2);

    // int h1 = 13;
    // int h2 = 18;
    // int m1 = 15;
    // int m2 = 45;
    // long long int bt1 = 0;
    // long long int bt2 = 0;
    // unsigned long long int res = 0;
    // unsigned long long int a = dateTonumericMin(leaps1, y1 - SHIFT, 1, 1, 0, 0);
    // unsigned long long int b = dateTonumericMin(leaps2, y2 - SHIFT, 1, 1, 0, 0);
    // unsigned long long int c = ((dateTonumericMin(getLeaps(SHIFT, 1605), 1605 - SHIFT, 1, 1, 0, 0)/60)/24) % 7 ;
    // assert(0 == getMinDiff(&a, &b));
    // assert(0 == getMinDiff(&a, &b) / MIN_DAYS);
    // assert(c == 0); // 0 saturday
    // c = ((dateTonumericMin(getLeaps(SHIFT, 1699), 1699 - SHIFT, 1, 1, 0, 0)/60)/24) % 7 ;
    // assert(c == 5); //  5 thursday
    // c = ((dateTonumericMin(getLeaps(SHIFT, 2022), 2022 - SHIFT, 1, 1, 0, 0)/60)/24) % 7 ;
    // assert(c == 0); //  0 saturday
    // c = ((dateTonumericMin(getLeaps(SHIFT, 2300), 2300 - SHIFT, 1, 1, 0, 0)/60)/24) % 7 ;
    // assert(c == 2); //  2 monday
    // c = ((dateTonumericMin(getLeaps(SHIFT, 3000), 3000 - SHIFT, 1, 1, 0, 0)/60)/24) % 7 ;
    // assert(c == 4); //  4 Wednesday
    // c = ((dateTonumericMin(getLeaps(SHIFT, 3000), 3000 - SHIFT, 2, 2, 0, 0)/60)/24) % 7 ;
    // assert(c == 1); //  1 sunday

    // assert(getSundaysCount(MIN_DAYS*22,0) ==4);
    // assert(getSundaysCount(MIN_DAYS*20,5) ==2);
    // assert(getSundaysCount(MIN_DAYS*21,5) ==3);

    // y1 = 2022;
    // y2 = 2022;
    // leaps1 = getLeaps(SHIFT, y1);
    // leaps2 = getLeaps(SHIFT, y2);
    // a = dateTonumericMin(leaps1, y1 - SHIFT, 10, 1, 23, 0);
    // b = dateTonumericMin(leaps2, y2 - SHIFT, 10, 1, 23, 15);
    // assert(15 == getMinDiff(&a, &b));
    // assert(0 == getMinDiff(&a, &b) / MIN_DAYS);

    // y1 = 2022;
    // y2 = 2022;
    // h1 = 13;
    // h2 = 18;
    // m1 = 15;
    // m2 = 45;
    // bt1 = 0;
    // bt2 = 0;
    // leaps1 = getLeaps(SHIFT, y1);
    // leaps2 = getLeaps(SHIFT, y2);
    // a = dateTonumericMin(leaps1, y1 - SHIFT, 10, 1, h1, m1);
    // b = dateTonumericMin(leaps2, y2 - SHIFT, 10, 1, h2, m2);
    // assert(330 == getMinDiff(&a, &b));
    // assert(0 == getMinDiff(&a, &b) / MIN_DAYS);
    // bt1 = calcB(b - a, h1, m1, h2, m2,0, &bt2);
    // assert(20 == bt2);
    // assert(56 == bt1);

    // y1 = 2022;
    // y2 = 2022;
    // leaps1 = getLeaps(SHIFT, y1);
    // leaps2 = getLeaps(SHIFT, y2);
    // a = dateTonumericMin(leaps1, y1 - SHIFT, 10, 1, 23, 45);
    // b = dateTonumericMin(leaps2, y2 - SHIFT, 10, 2, 0, 15);
    // assert(30 == getMinDiff(&a, &b));
    // assert(0 == getMinDiff(&a, &b) / MIN_DAYS);

    // y1 = 2022;
    // y2 = 2022;
    // leaps1 = getLeaps(SHIFT, y1);
    // leaps2 = getLeaps(SHIFT, y2);
    // a = dateTonumericMin(leaps1, y1 - SHIFT, 10, 1, 23, 45);
    // b = dateTonumericMin(leaps2, y2 - SHIFT, 10, 3, 0, 15);
    // assert(30+MIN_DAYS == getMinDiff(&a, &b));
    // assert(1 == getMinDiff(&a, &b) / MIN_DAYS);

    long long int b1, b2;

      assert ( bells ( 2022, 10,  1, 13, 15,
                       2022, 10,  1, 18, 45, &b1, &b2 ) == 1
               && b1 == 56
               && b2 == 20 );
      assert ( bells ( 2022, 10,  3, 13, 15,
                       2022, 10,  4, 11, 20, &b1, &b2 ) == 1
               && b1 == 221
               && b2 == 143 );
      assert ( bells ( 2022, 10,  1, 13, 15,
                       2022, 10,  2, 11, 20, &b1, &b2 ) == 1
               && b1 == 106
               && b2 == 65 );
      assert ( bells ( 2022, 10,  2, 13, 15,
                       2022, 10,  3, 11, 20, &b1, &b2 ) == 1
               && b1 == 115
               && b2 == 78 );
      assert ( bells ( 2022, 10,  1, 13, 15,
                       2022, 10,  3, 11, 20, &b1, &b2 ) == 1
               && b1 == 221
               && b2 == 143 );
      assert ( bells ( 2022,  1,  1, 13, 15,
                       2022, 10,  5, 11, 20, &b1, &b2 ) == 1
               && b1 == 56861
               && b2 == 36959 );
      assert ( bells ( 2019,  1,  1, 13, 15,
                       2019, 10,  5, 11, 20, &b1, &b2 ) == 1
               && b1 == 57101
               && b2 == 37115 );
      assert ( bells ( 2024,  1,  1, 13, 15,
                       2024, 10,  5, 11, 20, &b1, &b2 ) == 1
               && b1 == 57341
               && b2 == 37271 );
      assert ( bells ( 1900,  1,  1, 13, 15,
                       1900, 10,  5, 11, 20, &b1, &b2 ) == 1
               && b1 == 57101
               && b2 == 37115 );
      assert ( bells ( 2022, 10,  1,  0,  0,
                       2022, 10,  1, 12,  0, &b1, &b2 ) == 1
               && b1 == 124
               && b2 == 90 );
      assert ( bells ( 2022, 10,  1,  0, 15,
                       2022, 10,  1,  0, 25, &b1, &b2 ) == 1
               && b1 == 1
               && b2 == 0 );
      assert ( bells ( 2022, 10,  1, 12,  0,
                       2022, 10,  1, 12,  0, &b1, &b2 ) == 1
               && b1 == 4
               && b2 == 12 );
      assert ( bells ( 2022, 11,  1, 12,  0,
                       2022, 10,  1, 12,  0, &b1, &b2 ) == 0
               && b1 == 4
               && b2 == 12 );
      assert ( bells ( 2022, 10, 32, 12,  0,
                       2022, 11, 10, 12,  0, &b1, &b2 ) == 0
               && b1 == 4
               && b2 == 12 );
      assert ( bells ( 2100,  2, 29, 12,  0,
                       2100,  2, 29, 12,  0, &b1, &b2 ) == 0
               && b1 == 4
               && b2 == 12 );
      assert ( bells ( 2000,  2, 29, 12,  0,
                       2000,  2, 29, 12,  0, &b1, &b2 ) == 1
               && b1 == 4
               && b2 == 12 );
      assert ( bells ( 2004,  2, 29, 12,  0,
                       2004,  2, 29, 12,  0, &b1, &b2 ) == 1
               && b1 == 0
               && b2 == 0 );
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */