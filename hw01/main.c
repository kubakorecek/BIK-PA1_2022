#include <stdio.h>
#include <limits.h>

#define FAIL INT_MIN
#define DAYS 1000000

/*float original = 4.48;

int tmp = original * 10; // 44.8 truncated to 44

float truncated = tmp / 10.0; // 4.4
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

int readInterestRate(const char *type)
{
    printf("Zadejte %s urok [%%]:\n",type);
    double interestRate;
    if ((scanf("%lf", &interestRate) != 1))
    {
        errorMessage(0);
        return FAIL;
    }
    int interestRate100 = (interestRate * 100.0);
    return interestRate100;
}

int changeBalance(int balance, int interestRate)
{
    if (balance < 0)
    {
        return balance -= (balance * interestRate);
    }
    return balance += (balance * interestRate);
}

int main(void)
{
    int creditInterest = readInterestRate("kreditni");
    int debitInterest = readInterestRate("debetni");
    if (creditInterest == FAIL)
    {
        return 0;
    }
    if (debitInterest == FAIL)
    {
        return 0;
    }
    int accountBalance = 0;
    printf("Zadejte transakce:\n");
    int days[DAYS] = {0};
    int day, trasaction10000, balance, interestRate;
    double trasaction;
    int dayPrev = 0;
    balance = 0;
   while ((scanf(" %d , %lf ", &day, &trasaction) == 2))
    {
         printf("pdyw %d %f\n" , balance,trasaction);
        balance +=((int)(trasaction * 100.0))/100;
        printf("pdw %d %f\n" , balance,trasaction);
        if (dayPrev >= day && (day !=0))
        {
            errorMessage(0);
            return FAIL;
        }
        for (int j = dayPrev; j < day; j++)
        {
            interestRate = creditInterest;
            if (balance < 0)
            {
                interestRate = debitInterest;
            }
            balance += changeBalance(balance, interestRate);
        }
        if (trasaction == 0)
        {
            break;
        }
    }
    printf("pd %d\n" , balance);
    return 0;
}
