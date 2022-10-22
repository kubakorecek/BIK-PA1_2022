#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#define FAIL INT_MIN


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

/** @brief Read interest rate into long int.
 *  @param type Adres of the string to be printed.
 *  @return long int.
 */
long int readInterestRate(const char *type)
{
    printf("Zadejte %s urok [%%]:\n", type);
    double interestRate;
    if ((scanf("%lf", &interestRate) != 1))
    {
        errorMessage(0);
        return FAIL;
    }
    long int interestRate100 = (interestRate * 100);
    return interestRate100;
}

/** @brief Read interest rate into double.
 *  @param type Adres of the string to be printed.
 *  @return double.
 */
double readInterestRateDouble(const char *type)
{
    printf("Zadejte %s urok [%%]:\n", type);
    double interestRate;
    if ((scanf("%lf", &interestRate) != 1))
    {
        errorMessage(0);
        return FAIL;
    }
    return interestRate;
}

/** @brief RChange balance
 *  @param balance double of currecnt balance
 *  @param interestRate double of interest Rate
 *  @return double.
 */
double changeBalance(double balance, double interestRate)
{
    return (balance * interestRate);
}

double truncate(double input)
{
    int tmp = (int)(input * 100.0);
    return ((double)tmp) / 100.0;
}

int main(void)
{
    double creditInterest = readInterestRateDouble("kreditni");

    if (creditInterest == FAIL)
    {
        return 0;
    }
    double debitInterest = readInterestRateDouble("debetni");
    if (debitInterest == FAIL)
    {
        return 0;
    }
    printf("Zadejte transakce:\n");
    int day;
    double trasaction, credit, debit, balance, interestRate;

    int dayPrev = 0;
    balance = 0;
    credit = creditInterest / 100.0;
    debit = debitInterest / 100.0;
    char c;
    int check;
    while (((check = scanf(" %d %c %lf", &day, &c, &trasaction)) == 3) && check != EOF)
    {
        if ((dayPrev >= day && (day != 0)) || ((day == 0) && (dayPrev > day)) || c != ',')
        {
            errorMessage(0);
            return FAIL;
        }
        for (int j = dayPrev; j < day; j++)
        {
            interestRate = credit;
            if (balance < 0)
            {
                interestRate = debit;
            }
            balance += truncate(changeBalance(balance, interestRate));
        }
        balance += truncate(trasaction);
        dayPrev = day;
        if (fabs(trasaction - 0.0) <= 1e4 * DBL_EPSILON * (fabs(0) + fabs(trasaction)))
        {
            check = EOF;
            break;
        }
    }
    if (check != EOF)
    {
        errorMessage(0);
        return FAIL;
    }
    printf("Zustatek: %.2f\n", balance);
    return 0;
}
