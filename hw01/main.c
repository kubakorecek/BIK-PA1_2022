#include <stdio.h>
#include <limits.h>

#define FAIL INT_MIN
#define DAYS 10000000


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

double readInterestRate(const char * type)
{
    printf("Zadejte %s urok [%]:\n",type);
    double interestRate;
    if((scanf("%lf", &interestRate) != 1))
    {
        errorMessage(0);
        return INT_MIN;
    }
}

int main(void)
{
double creditInterest = readInterestRate("kreditni");
double debitInterest = readInterestRate("debetni");
if (creditInterest == FAIL)
{
    return 0;
}
if (debitInterest == FAIL)
{
    return 0;
}
printf("Zadejte transakce:\n");
int days[DAYS] = {0};
return 0;
}