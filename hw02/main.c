#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define FAIL INT_MIN
#define MAX_SIVE 17696448
#define MAX_PRIMES 5000001
#define PRECALC_PRIMES 3000
#define PRECALC_SIVE 8000
#define TRUE 1
#define FALSE 0
#ifdef DEBUG
#include <time.h>
#include <assert.h>
#endif


/** @brief Size to precalculate the possible primes
 *  @param primesDecider array to holdes precumputed primes
 *  @param max unsigned upper bound for sive
 *  @return Int.
 */
void eratosthenSive2(unsigned char *primesDecider, unsigned int max)
{
    unsigned int v = 0;
    primesDecider[1] = '1';
    for (unsigned int i = 2; i < sqrt(max)+1; i++)
    {
        if (primesDecider[i] == '\0')
        {
            for (v = 2 * i; v < max+1; v = v + i)
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

/** @brief Size to precalculate the possible primes
 *  @param number long int number whic is positive integerto factorized
 *  @return Int.
 */
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
    return TRUE;
}

/** @brief Based on the
 *  https://www.geeksforgeeks.org/print-all-prime-factors-and-their-powers/
 *  @param primesLookUp array to keep primes
 *  @param smallestPrimeFactors array with smallest factors of the number
 *  @param biggest unsigned int upper bond.
 *  @return Void.
 */
void getAllPrimeFactors(unsigned char *primesLookUp, int unsigned *smallestPrimeFactors, unsigned int biggest)
{
    unsigned int v = 0;
    for (unsigned int i = 0; i <= biggest; i++)
    {
        primesLookUp[i] = '0';
    }

    primesLookUp[0] = '1';
    primesLookUp[1] = '1'; // jednicku v sum divisors nepocitame
    for (unsigned int i = 2; i <= biggest; i = i + 2)
    {
        smallestPrimeFactors[i] = 2;
        primesLookUp[i] = '1';
    }
    for (unsigned int i = 3; i <= biggest; i = i + 2)
    {
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
 *  @param inputNumber unsigned int input number 
 *  @param smallestPrimeFactors array with smallest factors of the number
 *  @return unsigned int - sum of divisors.
 */
unsigned int getSumOfDivisors(unsigned int inputNumber, unsigned int *smallestPrimeFactors)
{
    unsigned int number = inputNumber;
    unsigned int prime = smallestPrimeFactors[number];
    unsigned int powerCounter = 1;
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
            sum = sum * (unsigned int)((pow((double)prime, (double)powerCounter + 1) - 1) / (prime - 1));;
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
    for (unsigned int i = 2; i <= upBound; i++)
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

/** @brief naive algorithm to find divisors used in first sulutions.
 *  @param number unsigned int input number 
 *  @param n unsigned int input number 
 *  @param flag array with smallest factors of the number
 *  @return unsigned int - sum of divisors.
 */
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

            }
            else
            {
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
    }
}

#ifndef DEBUG
int main(void)
{
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
    sumPrimeDecider = (unsigned char *)calloc(MAX_SIVE + 1, sizeof(unsigned char));

    eratosthenSive2(sumPrimeDecider, PRECALC_SIVE);
    getAllPrimeFactors(primesLookUp, smallestPrimeFactors, PRECALC_PRIMES);
    primesLookUp[1] = '1';
    for (unsigned int s = 2; s <= PRECALC_PRIMES; s++)
    {
        if ((sumPrimeDecider[getSumOfDivisors(s, smallestPrimeFactors)] == '\0'))
        {
            primesLookUp[s] = '0';
        }
        else
        {
            primesLookUp[s] = '1';
        }
    }
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

            if (((low>(PRECALC_PRIMES-1)) ||(hi>(PRECALC_PRIMES-1)))&& (precalc==FALSE))
            {
                eratosthenSive2(sumPrimeDecider, MAX_SIVE);
                getAllPrimeFactors(primesLookUp, smallestPrimeFactors, MAX_PRIMES);
                for (unsigned int s = 2; s <= MAX_PRIMES; s++)
                {
                    if ((sumPrimeDecider[getSumOfDivisors(s, smallestPrimeFactors)] == '\0'))
                    {
                        primesLookUp[s] = '0';
                    }
                    else
                    {
                        primesLookUp[s] = '1';
                    }
                }
            precalc = TRUE;
           primesLookUp[4989600]='1';
            }


            n = 0;
            flag = FALSE;
            if (c == '?')
            {
                flag = TRUE;
            }
            if (low == 1)
            {
                    low++;
            }
            for (int s = low; s <= hi; s++)
            {

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
    unsigned int maxSum = 0;
    unsigned int sum = 0;
    primesLookUp = (unsigned char *)calloc(MAX_PRIMES + 1, sizeof(unsigned char));
    smallestPrimeFactors = (unsigned int *)calloc(MAX_PRIMES + 1, sizeof(unsigned int));
    sumPrimeDecider = (unsigned char *)calloc(MAX_SIVE + 1, sizeof(unsigned char));

    eratosthenSive2(sumPrimeDecider, PRECALC_SIVE);
    clock_t start = clock(), diff;
    getAllPrimeFactors(primesLookUp, smallestPrimeFactors, PRECALC_PRIMES);
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf("Time taken for sieve %d seconds %d milliseconds\n", msec / 1000, msec % 1000);
    start = clock();
    primesLookUp[1] = '1';
    for (unsigned int s = 2; s <= PRECALC_PRIMES; s++)
    {   
        sum = getSumOfDivisors(s, smallestPrimeFactors);
        if (maxSum < sum){
            maxSum = sum;
        }
        if ((sumPrimeDecider[sum] == '\0'))
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
    printf("Time taken for precalc %d seconds %d milliseconds with max: %d\n", msec / 1000, msec % 1000, maxSum);
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

            if (((low>(PRECALC_PRIMES-1)) ||(hi>(PRECALC_PRIMES-1)))&& (precalc==FALSE))
            {
                eratosthenSive2(sumPrimeDecider, MAX_SIVE);
                getAllPrimeFactors(primesLookUp, smallestPrimeFactors, MAX_PRIMES);
                for (unsigned int s = 2; s <= MAX_PRIMES; s++)
                {
                    if ((sumPrimeDecider[getSumOfDivisors(s, smallestPrimeFactors)] == '\0'))
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

#endif