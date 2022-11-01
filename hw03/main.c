#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define FALSE 0
#define TRUE 1

#define DAY_SUM_RU_ING_B1 240
#define DAY_SUM_RU_ING_B2 78

int isLeapYear(int const year)
{
        if ((year % 4 == 0) && (year % 4000 != 0) && (year % 100 != 0 || year % 400 == 0))
        {
                return TRUE;
        }
        return FALSE;
}
short int monthToday(const int *month, const int *day, const short isLeap)
{
        short int monthCumSum[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
        short int days = 0;
        if (isLeap == TRUE)
        {
                for (int j = 2; j < *month + 1; j++)
                {
                        monthCumSum[j] += 1;
                }
        }
        days = monthCumSum[*month - 1] + (*day);
        return days;
}

unsigned long long int dateTonumericDay(const int year, const int month, const int day)
{

        unsigned long long int numricDate = 0;

        numricDate += ((year) * 365 + monthToday(&month, &day, isLeapYear(year)));
        return numricDate;
}

unsigned long long int dateTonumericMin(const int year, const int month, const int day, const int hour, const int minut)
{

        unsigned long long int numericDate = 0;
        numericDate += (dateTonumericDay(year, month, day) * 1440) + 60 * hour + minut;
        return numericDate;
}

int leapYearsArray(int y1, int y2)
{
        //unsigned int *leapYears = (unsigned int *)calloc(y2 + 1, sizeof(unsigned int));
        int n = 0;
        for (int j = y1; j <= y2; j++)
        {
                if (isLeapYear(j))
                {
                        // leapYears[*n] = j;
                        n++;
                }
        }
        // for (int j = 0; j < (*n); j++)
        // {
        //         printf("leep year inner: %d\n",leapYears[j]);
        // }
        return n;
}

int leapYearsArrayAdj(int y1, int y2)
{
        //unsigned int *leapYears = (unsigned int *)calloc(y2 + 1, sizeof(unsigned int));
         int n = 0;
        for (int j = y1+1; j < y2; j++)
        {
                if (isLeapYear(j))
                {
                        // leapYears[*n] = j;
                        n++;
                }
        }
        // for (int j = 0; j < (*n); j++)
        // {
        //         printf("leep year inner: %d\n",leapYears[j]);
        // }
        return n;
}

int bells(int y1, int m1, int d1, int h1, int i1,
          int y2, int m2, int d2, int h2, int i2,
          long long int *b1, long long int *b2)
{
        unsigned long long int numericDateStartMin = dateTonumericMin(y1, m1, d1, h1, i1);
        unsigned long long int numericDateEndMin = dateTonumericMin(y2, m2, d2, h2, i2);


       


        int n  =leapYearsArray(y1, y2);
        int n2 = leapYearsArrayAdj(y1, y2);
        
        //nsigned int *leapYears = leapYearsArray(y1, y2, &n);


        if (numericDateStart > numericDateEnd)
        {
                return 0;
        }
        else if (numericDateStart == numericDateEnd)
        {
                *b1 = 0;
                *b2 = 0;
                return 1;
        }


        // for (int j = 0; j < n; j++)
        // {
        //         printf("leep year outer: %d\n",leapYears[j]);
        // }
        // printf("number of years %d\n",n);



         unsigned long long int numberOfDays = dateTonumericDay(y2-y1, m2, d2);

        // free(leapYears);
        return 1;

        /* todo */
}

#ifndef __PROGTEST__
int main(int argc, char *argv[])
{
        long long int b1, b2;

        int year = 1900;
        int day = 31;
        int month = 1;

        assert(isLeapYear(2019) == FALSE);
        assert(isLeapYear(2024) == TRUE);

        assert(monthToday(&month, &day, TRUE) == 31);
        month = 4;
        day = 30;
        assert(monthToday(&month, &day, TRUE) == 121);
        assert(monthToday(&month, &day, FALSE) == 120);

        assert(leapYearsArray(1, 400) == 97);
        assert(leapYearsArray(400,2000) == 389);
        assert(leapYearsArray(1600,2022 ) == 103);
        assert(leapYearsArray(1600,1600 ) == 1);
        assert(leapYearsArray(1601,1601 ) == 0);

        assert(leapYearsArrayAdj(1, 400) == 96);
        assert(leapYearsArrayAdj(400,2000) == 387);
        assert(leapYearsArrayAdj(1600,2022 ) == 102);
        assert(leapYearsArrayAdj(1600,1600 ) == 0);
        assert(leapYearsArrayAdj(1601,1601 ) == 0);



        bells(1600, 10, 1, 13, 15,
              2022, 10, 1, 18, 45, &b1, &b2);

        

        bells(400, 10, 1, 13, 15,
              2000, 10, 1, 18, 45, &b1, &b2);
        
        bells(1, 10, 1, 13, 15,
              400, 10, 1, 18, 45, &b1, &b2);

        /*assert(bells(2022, 10, 1, 13, 15,
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
               b1 == 0 && b2 == 0);*/
        return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
