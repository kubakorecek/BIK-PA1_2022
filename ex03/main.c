#include <stdio.h>
#include <float.h>
#include <math.h>

#define TRUE 1
#define FALSE 0

void errorMessage(int input)
{
    if (input == 0)
    {
        printf("Nespravny vstup.\n");
    }
    else
    {
        printf("Nespravny vstup.%d\n", input);
    }
}

int equalTo(double a, double b)
{
    if (fabs(a - b) <= 1e4 * DBL_EPSILON * (fabs(a) + fabs(b)))
    {
        return TRUE;
    }
    return FALSE;
}

int main(void)
{
    printf("Zadejte vzorec:\n");

    int check;

     double firstNumber, secondNumber, result;
    result = 0.0;

    char op = '0'; 
    char equality = '0';

    if((check = scanf(" %lf %c %lf %c", &firstNumber, &op, &secondNumber, &equality )) != 4 
     
    || (equality != '=')
    || ((op == '/') && ( equalTo(secondNumber,0.0) == TRUE))
    )
    {
        errorMessage(0);
        return 0;
    }


    switch (op)
    {
    case '+':
        result = firstNumber + secondNumber;
        break;
    case '*':
        result = firstNumber * secondNumber;
        break;
    case '-':
        result = firstNumber - secondNumber;
        break;
    case '/':
        result = trunc(firstNumber / secondNumber);
        break;
    default:
        errorMessage(0);
        return 0;
        break;

    }
    printf("%e\n", result);
    return 0;
}