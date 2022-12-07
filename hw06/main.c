#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE -1
#define NOREGAL -1
#define INTENALMAX 5

unsigned long long stringHash(char const *inputStr, unsigned long long const n)
{
    unsigned long long p = 31;
    unsigned long long m = 1e9 + 9;
    unsigned long long hashHalue = 0;
    unsigned long long PPow = 1;
    for (unsigned long long i = 0; i < n; i++)
    {
        hashHalue = (hashHalue + (tolower(inputStr[i]) - 'a' + 1) * PPow) % m;
        PPow = (PPow * p) % m;
    }
    return hashHalue;
}

typedef struct Good
{
    char *m_Name;
    unsigned long long m_NameLength;
    // unsigned long long *m_HashValues;
    // unsigned long long m_HashValuesLen;
    unsigned long long m_HashValue;
    long long m_RegalId;
    long long m_RegalIdMatch;

} GOOD;

typedef struct ListItems
{
    GOOD *m_Goods;
    unsigned long long m_NumberOfGoods;
} LISTITEMS;

typedef struct OptRegal
{
    GOOD *m_Goods;
    unsigned long long m_NumberOfGoods;
    unsigned long long m_InternalMax;
} OPTREGAL;

// typedef struct OptShopping
// {
//     OPTREGAL *m_Regal;
//     unsigned long long m_NumberOfregals;
// } OPTSHOPPING;

void errorFunction()
{
    printf("Nespravny vstup.\n");
}
void destroyListOpt(OPTREGAL *list, long long nr)
{
    for (long long i = 0; i <= nr; i++)
    {

        for (unsigned long long j = 0; j < list[i].m_NumberOfGoods; j++)
        {
            free(list[i].m_Goods[j].m_Name);
            // free(list[i].m_Goods[j].);
        }
        free(list[i].m_Goods);
    }
    free(list);
}
long long checkMatch(char *name, unsigned long long hashvalue, LISTITEMS *regals, long long numberOfRegals, long long *regalGoodId)
{
    int flag = FALSE;
    char *ret = NULL;
    long long checkSubstrReg = NOREGAL;
    long long checkSubstrRegGood = NOREGAL;
    long long checkSubhashReg = NOREGAL;
    long long checkSubhashRegGood = NOREGAL;
    for (long long reg = 0; reg < numberOfRegals + 1; reg++)
    {
        for (long long goodsReg = 0; goodsReg < (long long)regals[reg].m_NumberOfGoods; goodsReg++)
        {
            if (hashvalue == regals[reg].m_Goods[goodsReg].m_HashValue)
            {
                *regalGoodId = goodsReg;
                return reg;
            }
            else if (ret == NULL)
            {
                ret = strcasestr(regals[reg].m_Goods[goodsReg].m_Name, name);
                if (ret)
                {
                    checkSubstrReg = reg;
                    checkSubstrRegGood = goodsReg;
                }
                else
                {
                }
            }
        }
    }
    if (flag == TRUE)
    {
        *regalGoodId = checkSubhashRegGood;
        return checkSubhashReg;
    }

    *regalGoodId = checkSubstrRegGood;
    return checkSubstrReg;
}

OPTREGAL *allocGood(char *inputName, ssize_t inputSize, LISTITEMS *regals, long long numberOfRegals, OPTREGAL *shoppingByRegal)
{
    GOOD newGood;
    // newGood.m_Name = (char *)malloc(inputSize * sizeof(inputName));
    if (inputName[strlen(inputName) - 1] == '\n')
    {
        inputSize = inputSize - 1;
    }
    // strncpy(newGood.m_Name, inputName, inputSize);
    inputName[inputSize] = '\0';
    // newGood.m_Name[inputSize] = '\0';
    newGood.m_NameLength = inputSize;
    newGood.m_HashValue = stringHash(inputName, newGood.m_NameLength);
    long long regalGoodId = 0;
    long long regalId = 0;

    regalGoodId = NOREGAL;
    regalId = checkMatch(inputName, newGood.m_HashValue, regals, numberOfRegals, &regalGoodId);
    if (regalId == NOREGAL)
    {
        newGood.m_RegalId = NOREGAL;
        newGood.m_RegalIdMatch = NOREGAL;

        if (shoppingByRegal[numberOfRegals + 1].m_InternalMax <= shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods)
        {
            shoppingByRegal[numberOfRegals + 1].m_InternalMax += (shoppingByRegal[numberOfRegals + 1].m_InternalMax < 100) ? 25 : shoppingByRegal[numberOfRegals + 1].m_InternalMax / 2;
            shoppingByRegal[numberOfRegals + 1].m_Goods = (GOOD *)realloc(shoppingByRegal[numberOfRegals + 1].m_Goods, shoppingByRegal[numberOfRegals + 1].m_InternalMax * sizeof(*shoppingByRegal[numberOfRegals + 1].m_Goods));
        }
        shoppingByRegal[numberOfRegals + 1].m_Goods[shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods] = newGood;
        shoppingByRegal[numberOfRegals + 1].m_Goods[shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods].m_Name = (char *)malloc(inputSize * sizeof(inputName));
        strncpy(shoppingByRegal[numberOfRegals + 1].m_Goods[shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods].m_Name, inputName, inputSize);
        shoppingByRegal[numberOfRegals + 1].m_Goods[shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods].m_Name[inputSize] = '\0';
        shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods++;
    }
    else
    {
        newGood.m_RegalId = regalId;
        newGood.m_RegalIdMatch = regalGoodId;
        if (shoppingByRegal[regalId].m_InternalMax <= shoppingByRegal[regalId].m_NumberOfGoods)
        {
            shoppingByRegal[regalId].m_InternalMax += (shoppingByRegal[regalId].m_InternalMax < 100) ? 25 : shoppingByRegal[regalId].m_InternalMax / 2;
            shoppingByRegal[regalId].m_Goods = (GOOD *)realloc(shoppingByRegal[regalId].m_Goods, shoppingByRegal[regalId].m_InternalMax * sizeof(*shoppingByRegal[numberOfRegals + 1].m_Goods));
        }
        shoppingByRegal[regalId].m_Goods[shoppingByRegal[regalId].m_NumberOfGoods] = newGood;
        shoppingByRegal[regalId].m_Goods[shoppingByRegal[regalId].m_NumberOfGoods].m_Name = (char *)malloc(inputSize * sizeof(inputName));
        strncpy(shoppingByRegal[regalId].m_Goods[shoppingByRegal[regalId].m_NumberOfGoods].m_Name, inputName, inputSize);
        shoppingByRegal[regalId].m_Goods[shoppingByRegal[regalId].m_NumberOfGoods].m_Name[inputSize] = '\0';
        shoppingByRegal[regalId].m_NumberOfGoods++;
    }
    // free(newGood.m_Name);
    return shoppingByRegal;
}

GOOD readNewGood(char *inputName, ssize_t inputSize)
{
    GOOD newGood;
    newGood.m_Name = (char *)malloc(inputSize * sizeof(inputName));
    if (inputName[strlen(inputName) - 1] == '\n')
    {
        inputSize = inputSize - 1;
    }
    strncpy(newGood.m_Name, inputName, inputSize);
    newGood.m_Name[inputSize] = '\0';
    newGood.m_NameLength = inputSize;
    newGood.m_HashValue = stringHash(newGood.m_Name, newGood.m_NameLength);
    return newGood;
}

void readToShoppingLists(long long *nr, int *flag, LISTITEMS *regals, long long numberOfRegals)
{
    // long long maxShoppingLists = 0;
    // unsigned long long maxGoods = 0;
    // unsigned long long cntGoods = 0;

    char *buff;

    // LISTITEMS *shoppingLists = NULL;
    // shoppingLists = (LISTITEMS *)realloc(shoppingLists,
    //                                      1 * sizeof(*shoppingLists));
    // shoppingLists[0].m_Goods = NULL;
    // shoppingLists[0].m_Goods = (GOOD *)realloc(shoppingLists[(*nr)].m_Goods,
    //                                            1 * sizeof(*shoppingLists[(*nr)].m_Goods));
    // shoppingLists[0].m_NumberOfGoods = 0;
    size_t size = 0;
    ssize_t nread = -2;

    OPTREGAL *shoppingByRegal = NULL;
    shoppingByRegal = (OPTREGAL *)realloc(shoppingByRegal,
                                          (numberOfRegals + 2) * sizeof(*shoppingByRegal));

    for (long long i = 0; i < numberOfRegals + 2; i++)
    {
        shoppingByRegal[i].m_Goods = (GOOD *)realloc(NULL, INTENALMAX * sizeof(*shoppingByRegal[i].m_Goods));
        shoppingByRegal[i].m_NumberOfGoods = 0;
        shoppingByRegal[i].m_InternalMax = INTENALMAX;
    }

    while ((nread = getline(&buff,
                            &size, stdin)) != EOF)
    {
        if (buff[0] == '\n')
        {
            int cnt = 0;
            printf("Optimalizovany seznam:\n");
            for (long long regId = 0; regId < numberOfRegals + 1; regId++)
            {
                for (unsigned long long goodId = 0; goodId < shoppingByRegal[regId].m_NumberOfGoods; goodId++)
                {
                    printf(" %d. %s -> #%lld %s\n", cnt, shoppingByRegal[regId].m_Goods[goodId].m_Name,
                           regId, regals[regId].m_Goods[shoppingByRegal[regId].m_Goods[goodId].m_RegalIdMatch].m_Name);
                    cnt++;
                }
            }
            for (unsigned long long goodId = 0; goodId < shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods; goodId++)
            {
                printf(" %d. %s -> N/A\n", cnt, shoppingByRegal[numberOfRegals + 1].m_Goods[goodId].m_Name);
                cnt++;
            }
            // destroyListOpt(shoppingByRegal, numberOfRegals + 1);
            for (long long i = 0; i < numberOfRegals + 2; i++)
            {
                for (unsigned long long j = 0; j < shoppingByRegal[i].m_NumberOfGoods; j++)
                {
                    free(shoppingByRegal[i].m_Goods[j].m_Name);
                    // free(list[i].m_Goods[j].);
                }
                shoppingByRegal[i].m_NumberOfGoods = 0;
            }
            (*nr)++;
            // if (maxShoppingLists <= (*nr))
            // {
            //     maxShoppingLists += (maxShoppingLists < 100) ? 25 : maxShoppingLists / 2;
            //     shoppingLists = (LISTITEMS *)realloc(shoppingLists,
            //                                          maxShoppingLists * sizeof(*shoppingLists));
            // }
            // shoppingLists[(*nr)].m_NumberOfGoods = 0;
            // shoppingLists[(*nr)].m_Goods = NULL;
            // maxGoods = 0;
        }
        else
        {
            // if (maxGoods <= shoppingLists[(*nr)].m_NumberOfGoods)
            // {
            //     maxGoods += (maxGoods < 100) ? 25 : maxGoods / 2;
            //     shoppingLists[(*nr)].m_Goods = (GOOD *)realloc(shoppingLists[(*nr)].m_Goods, maxGoods * sizeof(*shoppingLists[(*nr)].m_Goods));
            // }

            // shoppingLists[(*nr)].m_Goods[shoppingLists[(*nr)].m_NumberOfGoods] =
            // shoppingLists[(*nr)].m_NumberOfGoods++;
            shoppingByRegal = allocGood(buff, nread, regals, numberOfRegals, shoppingByRegal);
        }
    };
    if (nread == EOF)
    {
        int cnt = 0;
        printf("Optimalizovany seznam:\n");
        for (long long regId = 0; regId < numberOfRegals + 1; regId++)
        {
            for (unsigned long long goodId = 0; goodId < shoppingByRegal[regId].m_NumberOfGoods; goodId++)
            {
                printf(" %d. %s -> #%lld %s\n", cnt, shoppingByRegal[regId].m_Goods[goodId].m_Name,
                       regId, regals[regId].m_Goods[shoppingByRegal[regId].m_Goods[goodId].m_RegalIdMatch].m_Name);
                cnt++;
            }
        }
        for (unsigned long long goodId = 0; goodId < shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods; goodId++)
        {
            printf(" %d. %s -> N/A\n", cnt, shoppingByRegal[numberOfRegals + 1].m_Goods[goodId].m_Name);
            cnt++;
        }
    }

    free(buff);
    destroyListOpt(shoppingByRegal, numberOfRegals + 1);
    return;
}

long long checkRegal(char *buff)
{
    long long tmp = 0;
    if (sscanf(buff, "#%lld ", &tmp) != 1)
    {
        return FALSE;
    };
    return tmp;
}

LISTITEMS *readToRegals(long long *nr, int *flag)
{
    long long maxRegals = 0;
    unsigned long long maxGoods = 0;
    // unsigned long long cntGoods = 0;
    // long long maxShoppingLists = 0;

    char *buff;
    int flagFirstLine = TRUE;

    LISTITEMS *regals = NULL;
    // LISTITEMS *shoppingLists = NULL;
    size_t size = 0;
    ssize_t nread = -2;
    // unsigned long long goodsCnt = 0;
    long long regCheck = 0;
    while ((nread = getline(&buff,
                            &size, stdin)) != EOF)
    {
        if (flagFirstLine == TRUE)
        {
            if (strlen(buff) != 3 || strncmp("#0\n", buff, 3))
            {
                (*flag) = FALSE;
                free(buff);
                return NULL;
            }
            flagFirstLine = FALSE;
            (*nr)++;
            maxRegals += (maxRegals < 100) ? 25 : maxRegals / 2;
            regals = (LISTITEMS *)realloc(regals, maxRegals * sizeof(*regals));
            regals[(*nr)].m_NumberOfGoods = 0;
            regals[(*nr)].m_Goods = NULL;
            maxGoods = 0;
        }

        else if (buff[0] == '#')
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
            regCheck = checkRegal(buff);
            if (regCheck == FALSE || regCheck != (*nr) || (nread == EOF))
            {
                (*flag) = FALSE;
                free(buff);
                return regals;
            }
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
    free(buff);
    if (nread == EOF)
    {
        *flag = FALSE;
    }
    return regals;
}

void printList(LISTITEMS *list, long long nr)
{
    printf("Lists :# %lld\n", nr);
    for (long long i = 0; i <= nr; i++)
    {
        printf("current List :# %lld\n", i);
        printf("GOODS :# %lld\n", list[i].m_NumberOfGoods);
        for (unsigned long long j = 0; j < list[i].m_NumberOfGoods; j++)
        {

            printf("good : %s\n", list[i].m_Goods[j].m_Name);
            printf("good name len :# %lld\n", list[i].m_Goods[j].m_NameLength);
            printf("good hash :# %lld\n", list[i].m_Goods[j].m_HashValue);
            printf("good regal :# %lld\n", list[i].m_Goods[j].m_RegalId);
            printf("good regalid :# %lld\n", list[i].m_Goods[j].m_RegalIdMatch);
        }
    }
}

void destroyList(LISTITEMS *list, long long nr)
{
    for (long long i = 0; i <= nr; i++)
    {

        for (unsigned long long j = 0; j < list[i].m_NumberOfGoods; j++)
        {
            free(list[i].m_Goods[j].m_Name);
            // free(list[i].m_Goods[j].m_HashValues);
        }
        free(list[i].m_Goods);
    }
    free(list);
}

// void destroyListOpt(OPTREGAL *list, long long nr)
// {
//     for (long long i = 0; i <= nr; i++)
//     {

//         // for (unsigned long long j = 0; j < list[i].m_NumberOfGoods; j++)
//         // {
//         //     free(list[i].m_Goods[j].m_Name);
//         //     free(list[i].m_Goods[j].m_HashValues);
//         // }
//         free(list[i].m_Goods);
//     }
//     free(list);
// }

// char * cmp(const char * s1, const char * s2)
// {
//     return strstr(s1,s2);
// }

// void optimazeList(LISTITEMS *regals, LISTITEMS *shoppingLists, long long numberOfRegals, long long numberOfLists)
// {
//     // OPTSHOPPINGLIST *opttShopLists = NULL;
//     // opttShopLists = (OPTSHOPPINGLIST *)realloc(opttShopLists,
//     //                                            (numberOfLists + 1) * sizeof(*opttShopLists));

//     long long regalGoodId = 0;
//     long long regalId = 0;

//     OPTREGAL *shoppingByRegal = NULL;
//     shoppingByRegal = (OPTREGAL *)realloc(shoppingByRegal,
//                                           (numberOfRegals + 2) * sizeof(*shoppingByRegal));

//     for (long long i = 0; i < numberOfRegals + 2; i++)
//     {
//         shoppingByRegal[i].m_Goods = (GOOD *)realloc(NULL, INTENALMAX * sizeof(*shoppingByRegal[i].m_Goods));
//         shoppingByRegal[i].m_NumberOfGoods = 0;
//         shoppingByRegal[i].m_InternalMax = INTENALMAX;
//     }

//     for (long long j = 0; j < numberOfLists + 1; j++)
//     {
//         for (long long i = 0; i < numberOfRegals + 2; i++)
//         {

//             shoppingByRegal[i].m_NumberOfGoods = 0;
//         }

//         for (unsigned long long goodCurrent = 0; goodCurrent < shoppingLists[j].m_NumberOfGoods; goodCurrent++)
//         {

//             regalGoodId = NOREGAL;
//             regalId = checkMatch(shoppingLists[j].m_Goods[goodCurrent], regals, numberOfRegals, &regalGoodId);
//             if (regalId == NOREGAL)
//             {
//                 shoppingLists[j].m_Goods[goodCurrent].m_RegalId = NOREGAL;
//                 shoppingLists[j].m_Goods[goodCurrent].m_RegalIdMatch = NOREGAL;

//                 if (shoppingByRegal[numberOfRegals + 1].m_InternalMax <= shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods)
//                 {
//                     shoppingByRegal[numberOfRegals + 1].m_InternalMax += (shoppingByRegal[numberOfRegals + 1].m_InternalMax < 100) ? 25 : shoppingByRegal[numberOfRegals + 1].m_InternalMax / 2;
//                     shoppingByRegal[numberOfRegals + 1].m_Goods = (GOOD *)realloc(shoppingByRegal[numberOfRegals + 1].m_Goods, shoppingByRegal[numberOfRegals + 1].m_InternalMax * sizeof(*shoppingByRegal[numberOfRegals + 1].m_Goods));
//                 }
//                 shoppingByRegal[numberOfRegals + 1].m_Goods[shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods] = shoppingLists[j].m_Goods[goodCurrent];
//                 shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods++;
//             }
//             else
//             {
//                 shoppingLists[j].m_Goods[goodCurrent].m_RegalId = regalId;
//                 shoppingLists[j].m_Goods[goodCurrent].m_RegalIdMatch = regalGoodId;
//                 if (shoppingByRegal[regalId].m_InternalMax <= shoppingByRegal[regalId].m_NumberOfGoods)
//                 {
//                     shoppingByRegal[regalId].m_InternalMax += (shoppingByRegal[regalId].m_InternalMax < 100) ? 25 : shoppingByRegal[regalId].m_InternalMax / 2;
//                     shoppingByRegal[regalId].m_Goods = (GOOD *)realloc(shoppingByRegal[regalId].m_Goods, shoppingByRegal[regalId].m_InternalMax * sizeof(*shoppingByRegal[numberOfRegals + 1].m_Goods));
//                 }
//                 shoppingByRegal[regalId].m_Goods[shoppingByRegal[regalId].m_NumberOfGoods] = shoppingLists[j].m_Goods[goodCurrent];
//                 shoppingByRegal[regalId].m_NumberOfGoods++;
//             }
//         }
//         int cnt = 0;
//         printf("Optimalizovany seznam:\n");
//         for (long long regId = 0; regId < numberOfRegals + 1; regId++)
//         {
//             for (unsigned long long goodId = 0; goodId < shoppingByRegal[regId].m_NumberOfGoods; goodId++)
//             {
//                 printf(" %d. %s -> #%lld %s\n", cnt, shoppingByRegal[regId].m_Goods[goodId].m_Name,
//                        regId, regals[regId].m_Goods[shoppingByRegal[regId].m_Goods[goodId].m_RegalIdMatch].m_Name);
//                 cnt++;
//             }
//         }
//         for (unsigned long long goodId = 0; goodId < shoppingByRegal[numberOfRegals + 1].m_NumberOfGoods; goodId++)
//         {
//             printf(" %d. %s -> N/A\n", cnt, shoppingByRegal[numberOfRegals + 1].m_Goods[goodId].m_Name);
//             cnt++;
//         }
//     }
//     destroyListOpt(shoppingByRegal, numberOfRegals + 1);
// }

int main(void)
{
    // unsigned long long hashValue = stringHash(" ", 1);
    LISTITEMS *regals = NULL;
    int flag = TRUE;
    long long nr = -1;
    regals = readToRegals(&nr, &flag);
    if (regals == NULL || flag == FALSE)
    {
        flag = FALSE;
        destroyList(regals, nr);
        errorFunction();
        return EXIT_SUCCESS;
    }
    // printList(regals, nr);

    // printf("regals FINISHED\n");

    // printf("regals FINISHED \n");
    // LISTITEMS *shoppingLists = NULL;
    long long nrSl = 0;
    readToShoppingLists(&nrSl, &flag, regals, nr);
    // if (flag == TRUE)
    // {
    //     shoppingLists = readToShoppingLists(&nrSl, &flag);
    // }

    // if (shoppingLists == NULL || flag == FALSE)
    // {
    //     flag = FALSE;
    //     destroyList(regals, nr);
    //     destroyList(shoppingLists, nrSl);
    //     errorFunction();
    //     return EXIT_SUCCESS;
    // }

    // printList(shoppingLists, nrSl);
    // printf("shopping FINISHED \n");
    // SHOPPING_LIST *optiShoppingList = NULL;
    // long long nrOSl = 0;
    // optiShoppingList = optimazeShopping(shoppingLists, &nrOSl);

    // if (optiShoppingList == NULL || optiShoppingList == FALSE)
    // {
    //     return EXIT_SUCCESS;
    // }
    // if (flag == TRUE)
    // {
    //     optimazeList(regals, shoppingLists, nr, nrSl);
    // }

    // printList(shoppingLists, nrSl);
    // printf("optimaze FINISHED \n");
    destroyList(regals, nr);
    // free(regals);
    //
    // destroyList(shoppingLists, nrSl);
    return EXIT_SUCCESS;
}