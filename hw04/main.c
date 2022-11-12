#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int m_Number;
    int m_CumSum;

} SEQUENCE;

typedef struct
{
    int m_StartIndex;
    int m_EndIndex;
    int m_Sum;

} EQUATIONS;

void errorMessage(int inputCode)
{
    if ((inputCode == 0))
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Nespravny vstup. at %d", inputCode);
}

unsigned long long Factorial(unsigned long long const n)
{
    unsigned long long facts = 1;
    unsigned long long i;
    for (i = 1; i <= n; i++)
        facts = facts * i;
    return (facts);
}

static long GetBinCoeff(long N, long K)
{
   // This function gets the total number of unique combinations based upon N and K.
   // N is the total number of items.
   // K is the size of the group.
   // Total number of unique combinations = N! / ( K! (N - K)! ).
   // This function is less efficient, but is more likely to not overflow when N and K are large.
   // Taken from:  http://blog.plover.com/math/choose.html
   //
   if (K > N) return 0;
   long r = 1;
   long d;
   for (d = 1; d <= K; d++)
   {
      r *= N--;
      r /= d;
   }
   return r;
}

int Combination(unsigned long long int n, unsigned long long k)
{
    return (int)(Factorial(n) / (Factorial(k) * Factorial(n - k)));
}

int cmp(void const *a, void const *b)
{
    EQUATIONS *aIn = (EQUATIONS *)a;
    EQUATIONS *bIn = (EQUATIONS *)b;
    return (bIn->m_Sum - aIn->m_Sum);
}

SEQUENCE *readToCumSum(int *nr)
{
    SEQUENCE number;
    SEQUENCE *sq = NULL;

    *nr = 0;
    int max = 0;
    int res;
    int tmp;
    while ((res = scanf(" %d ", &tmp)) == 1 && res != EOF)
    {

        if (*nr >= max)
        {
            max += (max < 100) ? 10 : max / 2;

            sq = (SEQUENCE *)realloc(sq, max * sizeof(*sq));

            if (sq == NULL)
            {
                free(sq);
                return sq;
            }
        }
        number.m_Number = tmp;
        if ((*nr) > 0)
        {
            number.m_CumSum = sq[(*nr) - 1].m_CumSum + number.m_Number;
        }
        else
        {
            number.m_CumSum = number.m_Number;
        }
        sq[(*nr)] = number;
        (*nr)++;
   if((*nr) > 1999)
   {
    break;
   }
   }

    if (res != EOF || ((*nr) == 0) || (*nr) > 1999)
    {
        //errorMessage(0);
        free(sq);
        return NULL;
    }

    return sq;
}

int maxEquations(int const *n)
{
    return ((*n) * ((*n) + 1) / 2) - (*n);
}

int sum(int const index1, int const index2, SEQUENCE *input)
{
    if (index1 == 0)
    {
        return input[index2].m_CumSum;
    }
    return input[index2].m_CumSum - input[index1 - 1].m_CumSum;
}

EQUATIONS *getEquations(SEQUENCE *input, int const *inr, int *nr)
{
    int max =10000000;// maxEquations(inr) + 10;
    EQUATIONS equation;
    EQUATIONS *eq = NULL;

    eq = (EQUATIONS *)realloc(eq, max * sizeof(*eq));

    if (eq == NULL)
    {
        free(eq);
        return eq;
    }
    (*nr) = 0;
    for (int index1 = 0; index1 < (*inr) - 1; index1++)
    {
        for (int index2 = index1 + 1; index2 < (*inr); index2++)
        {
            equation.m_Sum = sum(index1, index2, input);
            equation.m_StartIndex = index1;
            equation.m_EndIndex = index2;
            eq[(*nr)] = equation;
            (*nr)++;
        }
    }
    return eq;
}

int getFrequencies(EQUATIONS *eq, int const *n)
{
    int freq = 0;
    int tmpFreq = 1;

    for (int j = 1; j < (*n); j++)
    {
        //printf("j:%d\n", j);
        if (eq[j - 1].m_Sum == eq[j].m_Sum)
        {
            tmpFreq++;
        }
        else if (tmpFreq > 1)
        {
            freq += GetBinCoeff(tmpFreq, 2);
            tmpFreq = 1;
        }
        else
        {
        }
        if (j == ((*n) - 1))
        {
            if (eq[j - 1].m_Sum == eq[j].m_Sum)
            {
                freq += GetBinCoeff(tmpFreq, 2);
            }
        }
    }

    return freq;
}

int main(void)
{
    SEQUENCE *sq = NULL;
    int n = 0;
    printf("Posloupnost:\n");
    sq = readToCumSum(&n);
    if (!sq)
    {
        errorMessage(0);
        return 1;
    }

    EQUATIONS *eq = NULL;
    int en = 0;
    eq = getEquations(sq, &n, &en);

    if (!eq)
    {
        free(sq);
        errorMessage(0);
        return 1;
    }
    // printf( "%ld %ld", sizeof(eq), sizeof(*eq));
    qsort(eq, en, sizeof(*eq), cmp);
    int res = getFrequencies(eq, &en);
    printf("Pocet dvojic: %d\n", res);
    free(sq);
    free(eq);
}