#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define FALSE 0
#define TRUE 1
#define LEAPYEARS 500000
#define SHIFT 1600
#define MIN_DAYS 1440

#define DAY_SUM_RU_ING_B1 240
#define HOUR_SUM_RU_ING_B1 10
#define DAY_SUM_RU_ING_B2 156

static short int monthCumSum[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
static short int month31[5] = {4, 6, 9, 11};
//static int leapsYear[LEAPYEARS / 4 + 1] = {0};
//static int  PRECALC = FALSE;

int isLeapYear(int const year)
{
    if ((year % 4 == 0) && (year % 4000 != 0) && (year % 100 != 0 || year % 400 == 0))
    {
        return TRUE;
    }
    return FALSE;
}

// void fillLeapYears(unsigned int end)
// {
//     int pos = 0;
//     for (unsigned int j = 1600; j < end; j += 4)
//     {
//         if (isLeapYear(j) == TRUE)
//         {
//             leapsYear[pos] = j;
//             pos++;
//         }
//     }
// }


// int leapYearsArray(int y1, int y2)
// {
//     int n = 0;
//     for (int j = 0; j < (LEAPYEARS / 4); j++)
//     {
//         if (leapsYear[j] <= y1)
//         {
//             continue;
//         }
//         if (leapsYear[j] >= y2)
//         {
//             break;
//         }
//         n++;
//     }
//     return n;
// }

unsigned long long  int getLeaps2(int startYear, const int endYear)
{
    //long long  int leaps = 0;
    
    if(isLeapYear(startYear)==TRUE){startYear--;}
    long long  int  startNumber = (startYear / 4) - (startYear/100) +(startYear/400) - (startYear/4000); 
    long long  int  endNumber = (endYear / 4) - (endYear/100) +(endYear/400) - (endYear/4000); 
    if(isLeapYear(endYear)==TRUE){endNumber--;}
    return endNumber - startNumber;
}



unsigned long long int monthToday(const int *month, const int *day, const short isLeap)
{

    unsigned long long int days = 0;
    if (isLeap == TRUE && *month > 2)
    {
        days += 1;
    }
    days += (unsigned long long int)monthCumSum[*month - 1] + (unsigned long long int)(*day) - 1;
    return days;
}
unsigned long long int dateTonumericMin(const unsigned long long int leaps, const int year, const int month,
                                        const int day, const int hour, const int minut)
{
    unsigned long long int numericDate = 0;
    unsigned long long int days = 0;
    // unsigned long long int t = 0;
    // unsigned long long int t1 = 0;
    // unsigned long long int t2 = 0;
    if (year == 1600)
    {
        days += monthToday(&month, &day, isLeapYear(year)) + leaps;
        numericDate += days * 1440 + 60 * (unsigned long long int)hour + (unsigned long long int)minut;
    }
    else
    {

        // t = ((unsigned long long int)year - SHIFT) * 365;
        // t1 = t + leaps;
        // t2 = monthToday(&month, &day, isLeapYear(year));
        days += (((unsigned long long int)year - SHIFT) * 365 + monthToday(&month, &day, isLeapYear(year))) + leaps;
        numericDate += days * 1440 + 60 * (unsigned long long int)hour + (unsigned long long int)minut;
    }
    return numericDate;
}
long long int  getLeaps(const int startYear, const int endYear)
{
    long long int  leaps = 0;
    for (long long int  j = startYear; j < endYear; j += 4)
    {
        if (isLeapYear(j) == TRUE)
        {
            leaps++;
        }
    }
    return leaps;
}

unsigned long long int getMinDiff(long long unsigned int *m1, long long unsigned int *m2)
{
    unsigned long long int res = (unsigned long long int)((*m2) - (*m1));
    return res;
}
unsigned long long int  getSundaysCount(unsigned long long int days,  int  origin)
{
    // 0 is saturday
    origin = (origin + 5) % 7;
    unsigned long long int  sundays = 0;

    sundays += (days + (unsigned long long int )origin) / 7;
    return sundays;
}
long long int calcB(unsigned long long int minDiff, int h1, int m1, int h2, int m2, int origin, long long int *b2)
{
    unsigned long long int  sundays = getSundaysCount((minDiff / MIN_DAYS) + 1, origin);
    minDiff = minDiff - sundays * MIN_DAYS;

     long long int daysTMP = (long long int)(minDiff / MIN_DAYS);
    (*b2) = DAY_SUM_RU_ING_B2 * (daysTMP);
    long long int endH = h1 + ((minDiff % MIN_DAYS) + m1)/60 ;
    long long int b1 = HOUR_SUM_RU_ING_B1 * (long long int)(minDiff / 60);

    if (m1 == 0)
    {
        if (h1 % 12 == 0)
        {
            (*b2) += 12;
        }
        (*b2) += (h1 % 12);
    }
    for (int i = h1 + 1; i <= endH; i++)
    {
        (*b2) += (i % 12);
        if (i % 12 == 0)
        {
            (*b2) += 12;
        }
    }
    
    int jMod = 0;
    int cor = 0;
    int mStart =m1;
    if (m1 > 0 && m1 < 15)
        {
            mStart= 15;
            cor = mStart-m1;
        }
        else if (m1 > 15 && m1 < 30)
        {
            mStart= 30;
            cor = mStart-m1;
        }
        else if (m1 > 30 && m1< 45)
        {
            mStart= 45;
            cor = mStart-m1;
        }
        else if (m1 > 45 && m1 < 60)
        {
            mStart= 0;
            cor = 60 - m1;
        }else 
        {
            mStart =m1;
        }

    long long int endM = mStart + (minDiff % 60)-cor;
    for (int j = mStart; j <= endM; j += 15)
    {
        jMod = j %60;
        if (jMod >= 0 && jMod < 15)
        {
            b1 += 4;
        }
        else if (jMod >= 15 && jMod < 30)
        {
            b1 += 1;
        }
        else if (jMod >= 30 && jMod< 45)
        {
            b1 += 2;
        }
        else if (jMod >= 45 && jMod < 60)
        {
            b1 += 3;
        }
    }

    return b1;
}
int checkMonthDays(int year, int m, int d)
{

    if (isLeapYear(year) == TRUE)
    {
        if (m == 2 && d > 29)
        {
            return FALSE;
        }
    }
    else if (m == 2 && d > 28)
    {
        return FALSE;
    }

    for (int k = 0; k < 4; k++)
    {
        if ((d > 30) && (m == month31[k]))
        {
            return FALSE;
        }
    }
    return TRUE;
}

int bells(int y1, int m1, int d1, int h1, int i1,
          int y2, int m2, int d2, int h2, int i2,
          long long int *b1, long long int *b2)
{
    long long int  leaps1 = getLeaps2(SHIFT, y1);
    long long int  leaps2 = getLeaps2(SHIFT, y2);
    
    // if(y2 > 4000 && PRECALC == FALSE)
    // {
    //     fillLeapYears(4036532);
    //     PRECALC = TRUE;
    // }
    // if(PRECALC == FALSE)
    // {
    //     fillLeapYears(4001);
    // }
    
    //assert(getLeaps2(SHIFT, y1)== getLeaps(SHIFT, y1));
    //assert(getLeaps2(SHIFT, y2)== getLeaps(SHIFT, y2));

    unsigned long long int a = dateTonumericMin(leaps1, y1, m1, d1, h1, i1);
    unsigned long long int b = dateTonumericMin(leaps2, y2, m2, d2, h2, i2);
    if (a > b)
    {
        return FALSE;
    }
    if (y1 < 1600 || y2 < 1600 || m1 > 12 || m2 > 12 || m1 < 1 || m2 < 1 || d1 < 1 || d2 < 1 || h1 < 0 || h2 < 0 || h1 > 23 || h2 > 23 || i1 < 0 || i2 < 0 || i1 > 59 || i2 > 59 || d1 > 31 || d2 > 31)
    {
        return FALSE;
    }

    if (checkMonthDays(y1, m1, d1) == FALSE)
    {
        return FALSE;
    }

    if (checkMonthDays(y2, m2, d2) == FALSE)
    {
        return FALSE;
    }
    if ((((a / MIN_DAYS)) % 7 == 1) && (((b / MIN_DAYS)) % 7 == 1) && ((b / MIN_DAYS) == (a / MIN_DAYS)))
    {
        (*b1) = 0;
        (*b2) = 0;
        return TRUE;
    }
    if (((a / 60) / 24) % 7 == 1)
    {
        a = a + MIN_DAYS - (i1 + h1 * 60);
        h1 = 0;
        i1 = 0;
    }

    if (((b / 60) / 24) % 7 == 1)
    {
        b = b - (i2 + h2 * 60) - 1;
        h2 = 23;
        i2 = 59;
    }
    (*b1) = 0;
    (*b2) = 0;
    int origin = ((a / 60) / 24) % 7;
    *b1 = calcB(getMinDiff(&a, &b), h1, i1, h2, i2, origin, b2);
    return TRUE;
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{

    // assert(leapYearsArray(1600, 1792) == 46);
    // assert(leapYearsArray(1600, 1792) == 46);

    // assert(isLeapYear(2019) == FALSE);
    // assert(isLeapYear(2024) == TRUE);
    // assert(isLeapYear(4000) == FALSE);
    // assert(isLeapYear(2024) == TRUE);
    // // // unsigned long long int days1 = 0;
    // // unsigned long long int days2 = 0;
    // // unsigned long long int dayst = 0;
    // // int y1 = 1600;
    // // int y2 = 1600;
    // // int leaps1 = getLeaps(SHIFT, y1);
    // // int leaps2 = getLeaps(SHIFT, y2);

    // // int h1 = 13;
    // // int h2 = 18;
    // // int m1 = 15;
    // // int m2 = 45;
    // // long long int bt1 = 0;
    // // long long int bt2 = 0;
    // // unsigned long long int res = 0;
    // int leaps1 = getLeaps(SHIFT, 1604);
    //  unsigned long long int aa = dateTonumericMin(0, 1600, 12, 31, 23, 59)/MIN_DAYS;
    //  unsigned long long int a = dateTonumericMin(0, 1600, 12, 31, 23, 60)/MIN_DAYS;
    //  unsigned long long int b = dateTonumericMin(leaps1, 1601, 1, 1, 23, 60) /MIN_DAYS;
    //  unsigned long long int c = dateTonumericMin(leaps1, 1601, 12, 31, 23, 60) /MIN_DAYS;
    //  unsigned long long int d = dateTonumericMin(leaps1, 1601, 12, 31, 23, 59) /MIN_DAYS;
    //  leaps1 = getLeaps(SHIFT, 1605);
    //  unsigned long long int d1 = dateTonumericMin(leaps1, 1605, 12, 31, 23, 59) /MIN_DAYS;
    //  unsigned long long int d2 = dateTonumericMin(leaps1, 1605, 12, 31, 23, 60) /MIN_DAYS;
    //  unsigned long long int d3 = dateTonumericMin(103, 2022, 12, 31, 23, 60) ;
    //       unsigned long long int d4 = dateTonumericMin(103, 2022, 12, 31, 23, 59) ;

    //  assert(1== getLeaps(SHIFT, 1604));
    //  assert( 2== getLeaps(SHIFT, 1605));
    //  assert(0== getLeaps(SHIFT, 1600));
    //  assert(1== getLeaps(SHIFT, 1601));
    //  int t = getLeaps(SHIFT, 4000);

    //  assert(b == 367);
    //  assert(a == 366 );
    //  assert(aa == 365 );
    //  assert(c == 731);
    //  assert(d == 730);
    //  assert(d1 == 2191);
    //  assert(d2 == 2192);

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

    assert(bells(2022, 10, 1, 13, 15,
                 2022, 10, 1, 18, 45, &b1, &b2) == 1 &&
           b1 == 56 && b2 == 20);
    assert(bells(2022, 10, 3, 13, 15,
                 2022, 10, 4, 11, 20, &b1, &b2) == 1 &&
           b1 == 221 && b2 == 143);
    assert(bells(2022, 10, 1, 13, 15,
                 2022, 10, 2, 11, 20, &b1, &b2) == 1 &&
           b1 == 106 && b2 == 65);
    assert(bells(2022, 10, 2, 13, 15,
                 2022, 10, 3, 11, 20, &b1, &b2) == 1 &&
           b1 == 115 && b2 == 78);
    assert(bells(2022, 10, 1, 13, 15,
                 2022, 10, 3, 11, 20, &b1, &b2) == 1 &&
           b1 == 221 && b2 == 143);
    assert(bells(2022, 1, 1, 13, 15,
                 2022, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 56861 && b2 == 36959);
    assert(bells(2019, 1, 1, 13, 15,
                 2019, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 57101 && b2 == 37115);
    assert(bells(2024, 1, 1, 13, 15,
                 2024, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 57341 && b2 == 37271);
    assert(bells(1900, 1, 1, 13, 15,
                 1900, 10, 5, 11, 20, &b1, &b2) == 1 &&
           b1 == 57101 && b2 == 37115);
    assert(bells(2022, 10, 1, 0, 0,
                 2022, 10, 1, 12, 0, &b1, &b2) == 1 &&
           b1 == 124 && b2 == 90);
    assert(bells(2022, 10, 1, 0, 15,
                 2022, 10, 1, 0, 25, &b1, &b2) == 1 &&
           b1 == 1 && b2 == 0);
    assert(bells(2022, 10, 1, 12, 0,
                 2022, 10, 1, 12, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(2022, 11, 1, 12, 0,
                 2022, 10, 1, 12, 0, &b1, &b2) == 0 &&
           b1 == 4 && b2 == 12);
    assert(bells(2022, 10, 32, 12, 0,
                 2022, 11, 10, 12, 0, &b1, &b2) == 0 &&
           b1 == 4 && b2 == 12);
    assert(bells(2100, 2, 29, 12, 0,
                 2100, 2, 29, 12, 0, &b1, &b2) == 0 &&
           b1 == 4 && b2 == 12);
    assert(bells(2000, 2, 29, 12, 0,
                 2000, 2, 29, 12, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(2004, 2, 29, 12, 0,
                 2004, 2, 29, 12, 0, &b1, &b2) == 1 &&
           b1 == 0 && b2 == 0);
    assert(bells(2004, 2, 29, 0, 0,
                 2004, 2, 29, 23, 59, &b1, &b2) == 1 &&
           b1 == 0 && b2 == 0);
    assert(bells(2004, 2, 29, 23, 59,
                 2004, 3, 1, 0, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(1600, 1, 1, 12, 0,
                 1600, 1, 1, 12, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(1600, 2, 29, 12, 0,
                 1600, 2, 29, 12, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);
    assert(bells(2000, 12, 26, 0, 0,
                 2000, 12, 31, 0, 0, &b1, &b2) == 1 &&
           b1 == 1200 && b2 == 780);

    assert(bells(2000, 12, 27, 0, 0,
                 2000, 12, 27, 0, 0, &b1, &b2) == 1 &&
           b1 == 4 && b2 == 12);

    assert(bells(1932, 4, 8, 21, 50,
                 1980, 2, 26, 1, 22, &b1, &b2) == 1 &&
           b1 == 3597635 && b2 == 2338474);

    assert(bells(1954, 9, 13, 19, 30,
                 2012, 11, 11, 21, 6, &b1, &b2) == 1 &&
           b1 == 4370205 && b2 == 2840642);

    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2163, 4, 22, 20, 31, 2036532, 5, 24, 17, 11, &b1, &b2 ) == 1 &&  b1==152853437247 && b2==99354734211);
    assert(bells ( 2107, 3, 28, 8, 15, 2022010586, 11, 12, 15, 37, &b1, &b2 )  == 1 &&  b1==151924716333193 && b2==98751065616576);
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */