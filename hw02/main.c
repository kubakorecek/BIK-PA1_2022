#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#define FAIL INT_MIN
#define MAX_FACOTRS 1000000
#define TRUE 1
#define FALSE 0
#ifdef DEBUG
#include <assert.h>
#endif


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

int sumDivisors( int divisors[MAX_FACOTRS], int * n )
{
    int sum = 1;
    for(int j = 1 ; j < (*n); j++ )
    {
        sum += divisors[j];
    }
    return sum;
}

int isPrimeTrial( int number)
{
    if( (number ==2) || (number == 3) ||(number == 1)){return TRUE;}

    int upBound = trunc(sqrt( number ));
    int sum = 1;
    for (int i = 2; i <= upBound; i++)
    {
        if((number % i ) == 0)
        {return FALSE;}
    }
    printf("is PRIME %d\n",number);
    return TRUE;
}


void getDivisors(const int number, int * n)
{
    int upBound = trunc(sqrt( number ));
    int sum = 1;
    int divisors = 0;
    for (int i = 2; i <= upBound; i++)
    {
        if(number%i == 0)
        {   
            divisors++;
            if((number / i) == i)
            {
                sum +=i;
                //printf("i %d\n", i);
            }else 
            {
                //printf("i %d i %d\n", i, (number / i));
                sum +=i;
                sum +=(number / i);
            }
        }
        
    }
    if(sum == 1)
    {
        return;
    }
    if(isPrimeTrial(sum) ==TRUE)
    {
        (*n)++;
         printf("is PRIME n %d %d %d\n", (*n), sum, number);
    }
    //printf("divisors:%d sum: %d\n", divisors, sum);

}

#ifndef DEBUG
int main( void )
{
    return 0;
}
#else 
int main( void )
{
    printf("debug mode\n");
    int n = 0;
    getDivisors(27,&n);
    printf("n: %d\n", n);
    n = 0;
    for(int s = 100; s <= 120; s++)
    {
        getDivisors(s,&n);
    }
      printf("n: %d\n", n);
      assert(2 == n);
    n = 0;
    for(int s = 265; s <= 327; s++)
    {
        getDivisors(s,&n);
    }
      printf("n: %d\n", n);
      assert(12 == n);
    return 0;
}

#endif