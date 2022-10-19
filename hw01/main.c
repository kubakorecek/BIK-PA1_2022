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

double changeBalance(double balance, double interestRate)
{
    //int trasactionTruncate =((int)((balance * interestRate) * 100.0))/100;
    
    /*if (balance < 0)
    {
        printf("BAL:%f ret %f\n", balance, -(balance * interestRate));
        return  (balance * interestRate);
    }*/
    return  (balance * interestRate);
}

double truncate(double input)
{
    int tmp = (int)(input * 100.0);
    return ((double)tmp) / 100.0;
}

int main(void)
{
    int creditInterest = readInterestRate("kreditni");

    if (creditInterest == FAIL)
    {
        return 0;
    }
    int debitInterest = readInterestRate("debetni");
    if (debitInterest == FAIL)
    {
        return 0;
    }
    //int accountBalance = 0;
    printf("Zadejte transakce:\n");
    //int days[DAYS] = {0};
    int day;//, trasactionTruncate;
    double trasaction , credit, debit, balance, interestRate;


    int dayPrev = 0;
    balance = 0;
    credit = (double)creditInterest / 10000.0;
    debit = (double)debitInterest / 10000.0;

   while ((scanf(" %d , %lf ", &day, &trasaction) == 2))
    {
         //printf("pdyw %d %d %f\n" ,day, balance,trasaction);
        //trasactionTruncate =((int)(trasaction * 100.0));
       
        //printf("pdw %d %f\n" , balance,trasaction);
        if (dayPrev >= day && (day !=0))
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
            //printf("pd %d %f %f %f\n" , j, balance, trasaction, interestRate);
        
        }
        balance +=truncate(trasaction);
        dayPrev = day;
        if (trasaction == 0)
        {
            break;
        }
    }
    printf("Zustatek: %.2f\n" , balance);
    return 0;
}
