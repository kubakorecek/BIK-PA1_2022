#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE -1

typedef struct Good
{
    char *m_Name;
    unsigned long long m_NameLength;
    unsigned long long * m_Id;
} GOOD;

typedef struct ListItems
{
    GOOD *m_Goods;
    unsigned long long m_NumberOfGoods;
} LISTITEMS;


int errorFunction()
{
    printf("Nespravny vstup\n.");
}

GOOD readNewGood(char const *inputName, ssize_t inputSize)
{
    GOOD newGood;
    newGood.m_Name = (char *)malloc(inputSize * sizeof(inputName));
    newGood.m_Id = (unsigned long long *)malloc(inputSize * sizeof(unsigned long long));
    strncpy(newGood.m_Name, inputName, inputSize - 1);
    newGood.m_Name[inputSize - 1] = '\0';
    newGood.m_NameLength = inputSize;
    return newGood;
}

LISTITEMS *readToShoppingList(long long *nr)
{
    long long maxShoppingLists = 0;
    unsigned long long maxGoods = 0;
    unsigned long long cntGoods = 0;

    char *buff;

    LISTITEMS *shoppingList = NULL;
    shoppingList = (LISTITEMS *)realloc(shoppingList,
                                                    1 * sizeof(*shoppingList));
    shoppingList[0].m_Goods = (GOOD *)realloc(shoppingList[(*nr)].m_Goods, 
            1 * sizeof(*shoppingList[(*nr)].m_Goods));
    shoppingList[0].m_NumberOfGoods = 0;        
    size_t size = 0;
    ssize_t nread = -2;
    unsigned long long goodsCnt = 0;

    while ((nread = getline(&buff,
                            &size, stdin)) != EOF)
    {
        if (buff[0] == '\n')
        {
            (*nr)++;
            if (maxShoppingLists <= (*nr))
            {
                maxShoppingLists += (maxShoppingLists < 100) ? 25 : maxShoppingLists / 2;
                shoppingList = (LISTITEMS *)realloc(shoppingList,
                                                    maxShoppingLists * sizeof(*shoppingList));
            }
            shoppingList[(*nr)].m_NumberOfGoods = 0;
            shoppingList[(*nr)].m_Goods = NULL;
            maxGoods = 0;
        }
        else
        {
            if (maxGoods <= shoppingList[(*nr)].m_NumberOfGoods)
            {
                maxGoods += (maxGoods < 100) ? 25 : maxGoods / 2;
                shoppingList[(*nr)].m_Goods = (GOOD *)realloc(shoppingList[(*nr)].m_Goods, maxGoods * sizeof(*shoppingList[(*nr)].m_Goods));
            }

            shoppingList[(*nr)].m_Goods[shoppingList[(*nr)].m_NumberOfGoods] = readNewGood(buff, nread);
            shoppingList[(*nr)].m_NumberOfGoods++;
        }
    };

    return shoppingList;
}


LISTITEMS *readToRegals(long long *nr)
{
    long long maxRegals = 0;
    unsigned long long maxGoods = 0;
    unsigned long long cntGoods = 0;
    long long maxShoppingLists = 0;

    char *buff;

    LISTITEMS *regals = NULL;
    LISTITEMS *shoppingList = NULL;
    size_t size = 0;
    ssize_t nread = -2;
    unsigned long long goodsCnt = 0;

    while ((nread = getline(&buff,
                            &size, stdin)) != EOF)
    {
        if (buff[0] == '#')
        {
            (*nr)++;
            if (maxRegals <= (*nr))
            {
                maxRegals += (maxRegals < 100) ? 25 : maxRegals / 2;
                regals = (LISTITEMS *)realloc(regals, maxRegals * sizeof(*regals));
            }
            regals[(*nr)].m_NumberOfGoods = 0;
            regals[(*nr)].m_Goods = NULL;
            maxGoods = 0;
        }
        else if (buff[0] == '\n')
        {
            break;
        }
        else
        {
            if (maxGoods <= regals[(*nr)].m_NumberOfGoods)
            {
                maxGoods += (maxGoods < 100) ? 25 : maxGoods / 2;
                regals[(*nr)].m_Goods = (GOOD *)realloc(regals[(*nr)].m_Goods, maxGoods * sizeof(*regals[(*nr)].m_Goods));
            }

            regals[(*nr)].m_Goods[regals[(*nr)].m_NumberOfGoods] = readNewGood(buff, nread);
            regals[(*nr)].m_NumberOfGoods++;
        }
    };

    return regals;
}



int main(void)
{
    LISTITEMS *regals = NULL;
    long long nr = -1;
    regals = readToRegals(&nr);
    if (regals == NULL)
    {
        return EXIT_SUCCESS;
    }

    LISTITEMS *shoppingList = NULL;
    long long nrSl = 0;
    shoppingList = readToShoppingList(&nrSl);

    if (shoppingList == NULL)
    {
        return EXIT_SUCCESS;
    }

    // SHOPPING_LIST *optiShoppingList = NULL;
    // long long nrOSl = 0;
    // optiShoppingList = optimazeShopping(shoppingList, &nrOSl);

    // if (optiShoppingList == NULL || optiShoppingList == FALSE)
    // {
    //     return EXIT_SUCCESS;
    // }

    return EXIT_SUCCESS;
}