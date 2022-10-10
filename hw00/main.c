#include <stdio.h>

#define SUCCESS_RUN 0
#define FAILURE_RUN 1
#define BUFFER 1000000

int main(void)
{
    int sentence=0;
    int ret = 0;

    char buffer[BUFFER] = {'\0'};

    printf("ml' nob:\n");

    if ((scanf("%s", buffer) != 1 ))   
    {   
        sentence = -1;
    }  
    for (int j = 0; j < BUFFER; j++)
    {
        if((buffer[j] == '0' && buffer[0] == '0') || buffer[j] =='\0')
        {

        }else 
        {
                ret++;
                sentence = buffer[j] - '0';
        }
    }

    if((ret == 1) && (sentence < 10 && sentence > 0))
    {
        printf("Qapla'\n");
    }else 
    {
        sentence = -1;
    }

    switch (sentence)
    {
    case 1:
        printf("noH QapmeH wo' Qaw\'lu\'chugh yay chavbe\'lu\' \'ej wo\' choqmeH may\' DoHlu\'chugh lujbe\'lu\'.\n");
        break;

    case 2:
        printf("bortaS bIr jablu\'DI\' reH QaQqu\' nay\'.\n");
        break;

    case 3:
        printf("Qu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
        break;

    case 4:
        printf("bISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
        break;

    case 5:
        printf("qaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
        break;

    case 6:
        printf("Suvlu'taHvIS yapbe' HoS neH.\n");
        break;

    case 7:
        printf("Ha'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
        break;

    case 8:
        printf("Heghlu'meH QaQ jajvam.\n");
        break;

    case 9:
        printf("leghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
        break;

    default:
        printf("luj\n");
        return SUCCESS_RUN;
    }

    return SUCCESS_RUN;
}