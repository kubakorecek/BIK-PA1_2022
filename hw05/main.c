#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <string.h>

typedef struct Fligth
{
    long double m_X;
    long double m_Y;
    char m_Name[200];
} FLIGTH;

typedef struct Pairs
{
    char m_Name[200];
    char m_Name2[200];
} PAIRS;

/*
DATA:

Pozice letadel:
0,0: KLM
5,0: Lufthansa
10,0: SmartWings
7,0: AirFrance
2,0: Qantas
Vzdalenost nejblizsich letadel: 2.000000
Nalezenych dvojic: 2
KLM - Qantas
Lufthansa - AirFrance

*/

/** @brief Print error message
 *
 * Function is just printing to the standard output error message with
 * posibility to add number in case to help locate error.
 * .
 *  @param[in] inputCode Number, which can be seen in error massage.
 *  @returns Void.
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

/** @brief Metric function for euclidean distance.
 *
 * Function is calculating euclidean distance. It is returning the distance.
 *
 *  @param[in] fistFlight struct holding  one flight data.
 *  @param[in] secondFlight struct holding  one flight data..
 *  @returns long double distance.
 */
long double euclideanDistnce(FLIGTH fistFlight, FLIGTH secondFlight)
{
    return sqrt(pow((fistFlight.m_X - secondFlight.m_X), 2.0) + pow((fistFlight.m_Y - secondFlight.m_Y), 2.0));
}

FLIGTH *readFligths(unsigned long long int *nr)
{
    int res = 0;
    unsigned long long int max = 0;

    FLIGTH fl;

    FLIGTH *data = NULL;

    while ((res = scanf(" %Lf , %Lf : %199s", &fl.m_X, &fl.m_Y, fl.m_Name)) == 3 && res != EOF)
    {
        if (max <= (*nr))
        {
            max += (max < 100) ? 10 : (max / 2);

            data = (FLIGTH *)realloc(data, max * sizeof(*data));
            if (!data)
            {
                free(data);
                return NULL;
            }
        }

        data[(*nr)] = fl;
        (*nr)++;
    }
    if (res != EOF || (*nr) < 2)
    {
        free(data);
        // errorMessage((*nr));
        return NULL;
    }
    return data;
}

int eq(long double a, long double b)
{

    if (fabs(a - b) <= 1e4 * DBL_EPSILON * (fabs(a) + fabs(a)))
    {
        return 1;
    }
    return 0;
}

int gt(long double a, long double b)
{

    if (fabs(a - b) <= 1e4 * DBL_EPSILON * (fabs(a) + fabs(a)))
    {
        return 1;
    }
    return 0;
}

PAIRS *naiveMin(FLIGTH *fl, long long unsigned const *nr, long long unsigned *numberPairs, long double *distance)
{
    PAIRS *pairs = NULL;
    PAIRS pr;
    long long unsigned max = 0;

    long double min = LDBL_MAX;
    long double tmpMin = 0;
    for (long long unsigned j = 0; j < (*nr); j++)
    {
        for (long long unsigned i = j + 1; i < (*nr); i++)
        {

            tmpMin = euclideanDistnce(fl[j], fl[i]);
            if (eq(tmpMin, min)) /* meed to redo*/
            {
                if (max <= (*numberPairs))
                {
                    max += (max < 100) ? 10 : (max / 2);

                    pairs = (PAIRS *)realloc(pairs, max * sizeof(*pairs));
                    if (!pairs)
                    {
                        free(pairs);
                        return NULL;
                    }
                }

                *distance = tmpMin;
                strcpy(pr.m_Name, fl[j].m_Name);
                strcpy(pr.m_Name2, fl[i].m_Name);
                pairs[*numberPairs] = pr;
                (*numberPairs)++;
            }
            else if (tmpMin < min) /* need redo */
            {
                if (max <= (*numberPairs))
                {
                    max += (max < 100) ? 10 : (max / 2);

                    pairs = (PAIRS *)realloc(pairs, max * sizeof(*pairs));
                    if (!pairs)
                    {
                        free(pairs);
                        return NULL;
                    }
                }

                *distance = tmpMin;
                strcpy(pr.m_Name, fl[j].m_Name);
                strcpy(pr.m_Name2, fl[i].m_Name);
                pairs[0] = pr;
                (*numberPairs) = 1;
                min = tmpMin;
            }
        }
    }

    return pairs;
}

int main(void)
{

    FLIGTH *data = NULL;
    printf("Pozice letadel:\n");

    unsigned long long int n = 0;
    data = readFligths(&n);
    if (!data)
    {
        free(data);
        errorMessage(0);
        return EXIT_SUCCESS;
    }
    unsigned long long int cntPairs = 0;
    long double distance = 0;
    PAIRS *pairs = NULL;

    pairs = naiveMin(data, &n, &cntPairs, &distance);

    if (!pairs)
    {
        free(data);
        free(pairs);
        errorMessage(0);
        return EXIT_SUCCESS;
    }
    printf("Vzdalenost nejblizsich letadel: %Lf\n", distance);
    printf("Nalezenych dvojic: %llu\n", cntPairs);

    for (unsigned long long int j = 0; j < cntPairs; j++)
    {
        printf("%s - %s\n", pairs[j].m_Name, pairs[j].m_Name2);
    }

    free(data);
    free(pairs);
    return EXIT_SUCCESS;
}