#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
long long int g_Calls = 0;

#define MAX_COINS 500




int minFITCoinsChangeDP(int coins[], int numberOfCoins, int value)
{
	int * posibilites = (int *)calloc(value+5, sizeof(*posibilites));

	posibilites[0] = 0;
	for (int i = 1; i <= value; i++)
		posibilites[i] = INT_MAX;


	for (int i = 1; i <= value; i++) {
		for (int j = 0; j < numberOfCoins; j++)
			if (coins[j] <= i) {
				int sub_res = posibilites[i - coins[j]];
				if (sub_res != INT_MAX && sub_res + 1 < posibilites[i])
					posibilites[i] = sub_res + 1;
			}
	}
    int ret = posibilites[value];
    free(posibilites);
	if (ret == INT_MAX)
		return ret;
	return ret;
}



int minFITCoinsChangeRec(int coins[], int numberOfCoins, int value)
{

    int cnt = INT_MAX;
    int tmpCnt = INT_MAX;

    if (value == 0)
        return value;
    for (int i = 0; i < numberOfCoins; i++)
    {
        // printf("coin:%d\n", coins[i]);
        if (coins[i] <= value)
        {
            tmpCnt = minFITCoinsChangeDP(coins, numberOfCoins, value - coins[i]);
            if (tmpCnt != INT_MAX && tmpCnt + 1 < cnt)
                cnt = tmpCnt + 1;
        }
    }

    return cnt;
}
void err()
{
    printf("Nespravny vstup.\n");
}


int *readCoins(int *numberCoins)
{
    int *coins = (int *)calloc(MAX_COINS, sizeof(*coins));
    int rs = -2;
    int coin = 0;
    while ((rs = scanf(" %d", &coin)) == 1 && (rs != EOF) && coin > 0)
    {

        // printf("coin %d\n", coin);
        coins[*numberCoins] = coin;
        (*numberCoins)++;
    }
    if (coin < 0 || rs != 1 || *numberCoins == 0)
    {
        err();
        free(coins);
        coins = NULL;
    }
    return coins;
}

void readPays(int *coins, int n)
{
    // int*pays = (int *)calloc(MAX_COINS, sizeof(*pays));
    int rs = -2;
    int pay = 0;
    int result = INT_MAX;
    // int numberPays = 0;
    while ((rs = scanf(" %d", &pay)) == 1 && (rs != EOF) && (pay > -1))
    {

        //printf("pay %d\n", pay);
        //  pays[numberPays] = pay;minFITCoinsChangeRec(coins, n - 1, pay));
        result = minFITCoinsChangeRec(coins, n, pay);
        if (result == INT_MAX)
        {
            printf("= nema reseni\n");
        }
        else
        {
            printf("= %d\n", result);
        }
    }
    //printf("pay %d\n", pay);
    if( !feof(stdin) || pay < 0)
    {
        err();
    }
    // free(pays);
    return;
}

int main()
{
    //     int coins[] = {1, 2, 5, 10, 20, 50, 5000, 2000, 1000, 500, 200, 100, 0};
    //     int check[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // int m = sizeof(coins)/sizeof(coins[0]);
    // int V = 11;
    // printf("Minimum coins required is \n");
    // for (int i = 0 ; i < 10;i++)
    // {
    //     printf("%d = %d\n",check[i], minCoins(coins, 10, check[i]) );
    // }

    printf("Mince:\n");

    int *coins = NULL;
    int numberCoins = 0;
    coins = readCoins(&numberCoins);
    if (coins)
    {
        printf("Castky:\n");
        readPays(coins, numberCoins);

        free(coins);
    }

    return 0;
}