#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define FAIL INT_MIN
#define MAX_SIVE_M 17696448
#define MAX_SIVE 5000001
#define MAX_PRIMES 5000001
#define TEST 1000000
#define TRUE 1
#define FALSE 0
#ifdef DEBUG
#include <time.h>
#include <assert.h>
#endif

/// void eratosthenSive(int * primesLookUp,int * smallestPrimeFactors,  int biggest )
// {
//     int v = 0;
//     for(int i = 2; i < biggest;i = )
//     {
//         printf("sive %d i: %d true: %d\n", primesLookUp[i], i, (primesLookUp[i] == 0) );
//         if(primesLookUp[i] == 0)
//         {
//             for( v= 2*i; v < biggest;v = v +i)
//             {
//                 primesLookUp[v] = 1;
//             }
//         }
//     }
// }

void eratosthenSive2(unsigned char *primesDecider)
{
    unsigned int v = 0;
    primesDecider[1] = '1';
    for (unsigned int i = 2; i < sqrt(MAX_SIVE_M); i++)
    {
        if (primesDecider[i] == '\0')
        {
            for (v = 2 * i; v < MAX_SIVE_M; v = v + i)
            {
                primesDecider[v] = '1';
            }
        }
    }
}

/** @brief Print error message
 *  @param inputCode Number, which can help point where error happened
 *  @return Void.
 */
void errorMessage(int const inputCode)
{
    if ((inputCode == 0))
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Nespravny vstup. at %d \n", inputCode);
}

/* int sumDivisors(int divisors[MAX_FACOTRS], int *n)
{
    int sum = 1;
    for (int j = 1; j < (*n); j++)
    {
        sum += divisors[j];
    }
    return sum;
} */

int isPrimeTrial(unsigned long int number)
{
    if ((number == 2) || (number == 3) || (number == 1))
    {
        return TRUE;
    }

    int upBound = trunc(sqrt(number));
    for (int i = 2; i <= upBound; i++)
    {
        if ((number % i) == 0)
        {
            return FALSE;
        }
    }
    // printf("is PRIME %d\n",number);
    return TRUE;
}
/** @brief Based on the
 *  https://www.geeksforgeeks.org/print-all-prime-factors-and-their-powers/
 *  @return Void.
 */
void getAllPrimeFactors(unsigned char *primesLookUp, int unsigned *smallestPrimeFactors, unsigned int biggest)
{
    unsigned int v = 0;
    for (unsigned int i = 0; i < biggest; i++)
    {
        primesLookUp[i] = '0';
    }

    primesLookUp[0] = '1';
    primesLookUp[1] = '1'; // jednicku v sum divisors nepocitame
    for (unsigned int i = 2; i < biggest; i = i + 2)
    {
        smallestPrimeFactors[i] = 2;
        primesLookUp[i] = '1';
    }
    for (unsigned int i = 3; i < biggest; i = i + 2)
    {
        // printf("sive %d i: %d true: %d\n", primesLookUp[i], i, (primesLookUp[i] == 0) );
        if (primesLookUp[i] == '0')
        {

            smallestPrimeFactors[i] = i;
            for (v = i; v < (biggest / i) + 1; v = v + 2)
            {
                if (primesLookUp[i * v] == '0')
                {
                    primesLookUp[i * v] = '1';
                    smallestPrimeFactors[i * v] = i;
                }
            }
        }
    }
}
/** @brief Based on the
 *  https://www.planetmath.org/FormulaForSumOfDivisors
 *  https://www.geeksforgeeks.org/print-all-prime-factors-and-their-powers/
 *  @return Void.
 */

unsigned int getSumOfDivisors(unsigned int inputNumber, unsigned int *smallestPrimeFactors)
{
    unsigned int number = inputNumber;
    unsigned int prime = smallestPrimeFactors[number];
    unsigned int powerCounter = 1;
    unsigned int tmpS = 0;
    unsigned int power = 0;
    unsigned int sum = 1;
    if (inputNumber == prime)
    {
        return sum;
    }
    while (number > 1)
    {
        number = number / smallestPrimeFactors[number];

        if (prime == smallestPrimeFactors[number])
        {
            powerCounter++;
            continue;
        }
        else

        {
            power = pow((double)prime, (double)powerCounter + 1);
            tmpS = (unsigned int)((pow((double)prime, (double)powerCounter + 1) - 1) / (prime - 1));
            sum = sum * tmpS;
        }
        powerCounter = 1;
        prime = smallestPrimeFactors[number];
    }
    return sum - inputNumber;
}

unsigned int getSumTrivial(unsigned int number)
{
    unsigned int upBound = trunc(sqrt(number));
    unsigned int sum = 1;
    for (int i = 2; i <= upBound; i++)
    {
        if (number % i == 0)
        {
            if ((number / i) == i)
            {
                sum += i;
            }
            else
            {
                sum += i;
                sum += (number / i);
            }
        }
    }
    return sum;
}

void getDivisors(const int number, int *n, int flag)
{
    int upBound = trunc(sqrt(number));
    int sum = 1;
    int divisors = 0;
    for (int i = 2; i <= upBound; i++)
    {
        if (number % i == 0)
        {
            divisors++;
            if ((number / i) == i)
            {
                sum += i;
                // printf("i %d\n", i);
            }
            else
            {
                // printf("i %d i %d\n", i, (number / i));
                sum += i;
                sum += (number / i);
            }
        }
    }
    if (sum == 1)
    {
        return;
    }
    if (isPrimeTrial(sum) == TRUE)
    {
        (*n)++;
        if (flag == TRUE)
        {
            printf("%d\n", number);
        }
        // printf("is PRIME n %d %d %d\n", (*n), sum, number);
    }
    // printf("divisors:%d sum: %d\n", divisors, sum);
}

#ifndef DEBUG
int main(void)
{
    int useSive = FALSE;
    int hi = 0;
    int low = 0;
    int flag = FALSE;
    char c = ' ';
    int check = EOF;
    int n = 0;
    printf("Intervaly:\n");
    unsigned char *primesLookUp;
    unsigned int *smallestPrimeFactors;
    unsigned char *sumPrimeDecider;

    primesLookUp = (unsigned char *)calloc(MAX_PRIMES + 1, sizeof(unsigned char));
    smallestPrimeFactors = (unsigned int *)calloc(MAX_PRIMES + 1, sizeof(unsigned int));
    sumPrimeDecider = (unsigned char *)calloc(MAX_SIVE_M + 1, sizeof(unsigned char));

    eratosthenSive2(sumPrimeDecider);
    clock_t start = clock(), diff;
    getAllPrimeFactors(primesLookUp, smallestPrimeFactors, MAX_PRIMES);
    //  for (int s = 2; s <= 100; s++)
    //  {
    //      printf("s:%d factor: %d\n",s,smallestPrimeFactors[s]);
    //      if(primesLookUp[s] == '0')
    //      {
    //         printf("Prime %d\n",s);
    //      }

    //  }
    unsigned int wtf = smallestPrimeFactors[2];

    // for (int s = 2; s <= 100; s++)
    // {
    //     if(sumPrimeDecider[s] == '\0')
    //     {
    //         printf("Prime %d\n",s);
    // }
    //     }

    wtf = smallestPrimeFactors[2];
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken for sieve %d seconds %d milliseconds\n", msec / 1000, msec % 1000);
    start = clock();
    primesLookUp[1] = '1';
    unsigned int sum;
    for (unsigned int s = 2; s <= TEST; s++)
    {

        // wtf = smallestPrimeFactors[s];
        // unsigned int sum = getSumOfDivisors(s, smallestPrimeFactors);
        if ((sumPrimeDecider[getSumOfDivisors(s, smallestPrimeFactors)] == '\0'))
        {
            primesLookUp[s] = '0';
            // printf("Prime sum %ld at s:%d\n",sum,s);
        }
        else
        {
            primesLookUp[s] = '1';
        }

        //    if(sum>max){max = sum;}
        //     useSive = FALSE;
        //     if (sum < MAX_SIVE)
        //     {
        //         useSive = TRUE;
        //     }
        //     if ((useSive == TRUE))
        //     {
        //         if ((sumPrimeDecider[sum] == '\0'))
        //         {
        //             sumPrimeDecider[s] = '1';
        //         }
        //     }
        //     else if ((useSive == FALSE) && isPrimeTrial(sum))
        //     {
        //         sumPrimeDecider[s] = '1';

        //     }
    }

    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken for precalc %d seconds %d milliseconds\n", msec / 1000, msec % 1000);

    start = clock();
    primesLookUp[1] = '1';
    for (unsigned int s = 2; s <= TEST; s++)
    {
        if ((sumPrimeDecider[getSumTrivial(s)] == '\0'))
        {
            primesLookUp[s] = '0';
        }
        else
        {
            primesLookUp[s] = '1';
        }
    }

    diff = clock() - start;
    msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken for precalc2 %d seconds %d milliseconds", msec / 1000, msec % 1000);

    int precalc = FALSE;

    while ((check = scanf(" %c %d %d ", &c, &low, &hi)) == 3 && check != EOF)
    {

        if (!(c == '#' || c == '?'))
        {
            free(primesLookUp);
            free(sumPrimeDecider);
            free(smallestPrimeFactors);
            errorMessage(0);
            return 0;
        }
        else if ((low > hi) || check != 3 || low < 1 || hi < 1)
        {
            free(primesLookUp);
            free(sumPrimeDecider);
            free(smallestPrimeFactors);
            errorMessage(0);
            return 0;
        }
        else
        {

            if (((low>(TEST-1)) ||(hi>(TEST-1)))&& (precalc==FALSE))
            {
                for (unsigned int s = TEST; s <= MAX_PRIMES; s++)
                {
                    if ((sumPrimeDecider[getSumTrivial(s)] == '\0'))
                    {
                        primesLookUp[s] = '0';
                    }
                    else
                    {
                        primesLookUp[s] = '1';
                    }
                }
            precalc = TRUE;
            }


            n = 0;
            flag = FALSE;
            if (c == '?')
            {
                flag = TRUE;
            }
            for (int s = low; s <= hi; s++)
            {
                if (s == 1)
                {
                    continue;
                }
                if ((primesLookUp[s] == '0'))
                {
                    n++;
                    if (flag == TRUE)
                    {
                        printf("%d\n", s);
                    }
                }
            }
            printf("Celkem: %d\n", n);
        }
    }
    free(primesLookUp);
    free(sumPrimeDecider);
    free(smallestPrimeFactors);
    if (check != EOF)
    {

        errorMessage(0);
    }
    return 0;
}
#else
int main(void)
{
    printf("debug mode\n");
    int n = 0;
    getDivisors(27, &n, TRUE);
    printf("n: %d\n", n);
    n = 0;
    for (int s = 100; s <= 120; s++)
    {
        getDivisors(s, &n, TRUE);
    }
    printf("n: %d\n", n);
    assert(2 == n);
    n = 0;
    for (int s = 265; s <= 327; s++)
    {
        getDivisors(s, &n, TRUE);
    }
    printf("n: %d\n", n);
    assert(12 == n);
    int *primesLookUp;
    int *smallestPrimeFactors;

    clock_t start = clock(), diff;

    primesLookUp = (int *)calloc(MAX_SIVE + 1, sizeof(int));
    smallestPrimeFactors = (int *)calloc(MAX_SIVE + 1, sizeof(int));
    eratosthenSive(primesLookUp, smallestPrimeFactors, MAX_SIVE);

    for (int i = 0; i < 10; i++)
    {
        printf("i %d prime %d sfactor %d\n", i, primesLookUp[i], smallestPrimeFactors[i]);
    }

    printf("sum of divisors: %d\n", getSumOfDivisors(8, smallestPrimeFactors));
    assert(13 == getSumOfDivisors(27, smallestPrimeFactors));

    if (primesLookUp[getSumOfDivisors(27, smallestPrimeFactors)] == 0)
    {
        printf("sum of divisors (13) is prime %d\n", getSumOfDivisors(300567, smallestPrimeFactors));
    }

    n = 0;
    for (unsigned int s = 300567; s <= 300567; s++)
    {
        if (s == 1)
        {
            continue;
        }
        if (primesLookUp[getSumOfDivisors(s, smallestPrimeFactors)] == 0)
        {
            printf("sum of divisors %d is prime for %d \n", getSumOfDivisors(s, smallestPrimeFactors), s);
            n++;
        }
    }
    printf("n: %d\n", n);
    // assert(12 == n);

    free(smallestPrimeFactors);
    free(primesLookUp);

    diff = clock() - start;

    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken %d seconds %d milliseconds", msec / 1000, msec % 1000);

    int useSive = FALSE;
    int hi = MAX_PRIMES;
    int low = 1;
    int flag = FALSE;
    char c = '#';
    char *list;
    int check = EOF;
    n = 0;
    printf("Intervaly:\n");
    // unsigned int *primesLookUp;
    // unsigned int *smallestPrimeFactors;
    primesLookUp = (unsigned int *)calloc(MAX_PRIMES + 1, sizeof(unsigned int));
    smallestPrimeFactors = (unsigned int *)calloc(MAX_PRIMES + 1, sizeof(unsigned int));
    list = (unsigned char *)calloc(MAX_PRIMES + 1, sizeof(char));
    eratosthenSive(primesLookUp, smallestPrimeFactors, MAX_PRIMES);

    n = 0;
    flag = FALSE;
    if (c == '?')
    {
        flag = TRUE;
    }
    for (int s = low; s <= hi; s++)
    {

        if (s == 1)
        {
            continue;
        }
        unsigned long int sum = getSumOfDivisors(s, smallestPrimeFactors);
        useSive = FALSE;
        if (sum < MAX_SIVE)
        {
            useSive = TRUE;
        }
        if ((useSive == TRUE))
        {
            if ((primesLookUp[sum] == 0))
            {
                list[s] = '1';
                if (flag == TRUE)
                {
                    printf("%d\n", s);
                }
            }
            // printf("sum of divisors %d is prime for %d \n", getSumOfDivisors(s, smallestPrimeFactors), s);
        }
        else if ((useSive == FALSE) && isPrimeTrial(sum))
        {
            list[s] = '1';
            if (flag == TRUE)
            {
                printf("%d\n", s);
            }
        }
    }
    n = 0;
    for (int s = 6278; s <= 94186; s++)
    {
        if (list[s] == '1')
        {
            n++;
        }
    }

    printf("Celkem: %d\n", n);

    return 0;
}

#endif