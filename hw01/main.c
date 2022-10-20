#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#define FAIL INT_MIN

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

long int readInterestRate(const char *type)
{
    printf("Zadejte %s urok [%%]:\n",type);
    double interestRate;
    if ((scanf("%lf", &interestRate) != 1))
    {
        errorMessage(0);
        return FAIL;
    }
    long int interestRate100 = (interestRate * 100);
    return interestRate100;
}

double readInterestRateDouble(const char *type)
{
    printf("Zadejte %s urok [%%]:\n",type);
    double interestRate;
    if ((scanf("%lf", &interestRate) != 1))
    {
        errorMessage(0);
        return FAIL;
    }
    return interestRate;
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
    //long int creditInterest = readInterestRate("kreditni");
    double creditInterest = readInterestRateDouble("kreditni");

    if (creditInterest == FAIL)
    {
        return 0;
    }
    //long int debitInterest = readInterestRate("debetni");
    double debitInterest = readInterestRateDouble("debetni");
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
    //credit = (double)creditInterest / 10000.0;
    //debit = (double)debitInterest / 10000.0;
    credit = creditInterest/100.0 ;
    debit = debitInterest /100.0;
    char c;
    int check;
   while (((check= scanf(" %d %c %lf", &day,&c, &trasaction)) == 3) && check != EOF)
    {
         //printf("pdyw %d %d %f\n" ,day, balance,trasaction);
        //trasactionTruncate =((int)(trasaction * 100.0));
       
        //printf("pdw %d %f %c ff %d\n" , day,trasaction, c, check);
        //printf("day %d prev %d\n" , dayPrev,day);
        if ((dayPrev >= day && (day !=0)) || ((day == 0) && (dayPrev > day)) || c !=',')
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
    //printf("pdw %d %f %c ff %c\n" , day,trasaction, c, cc);
    printf("Zustatek: %.2f\n" , balance);
    return 0;
}
