#include <stdio.h>
#define FAILURE 1
#define SUCCES_RUN 0

static char letterMap[7] = {'A','B','C','D','E','F', '\0'};
static char hexRepresentation[7];

#define MAX_COLOR 255
#define MIN_COLOR 0

void toHexRepresentation( int inputNumber, int position)
{
    int rest, mod;

    rest = inputNumber / 16;
    mod = inputNumber % 16;
    if ( mod > 9 )
    {
      hexRepresentation[position - 1] = letterMap[mod-10];  
    } else 
    {
      hexRepresentation[position - 1] = (char)(mod + 48);  
    }
    if (rest != 0)
    {
        position++;
        toHexRepresentation(rest,position);
    }
    
}

void reset()
{
    for ( int i = 0; i < 6; i++)
    {
        hexRepresentation[i] = '0';
    }
     hexRepresentation[6] = '\0';
}

void errorMessage( int inputCode ) 
{
    if((inputCode == 0))
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Nespravny vstup. at %d", inputCode);     
}

int main ( int arg, char ** args )
{
    int r,g,b;
    char rb;
    printf("Zadejte barvu v RGB formatu:\n");
    if((scanf(" rgb ( %d , %d , %d %c",&r, &g,&b, &rb) != 4) || rb != ')')
    {
        errorMessage(0);
        return FAILURE;
    } 

    if (r > MAX_COLOR || r < MIN_COLOR)
    {
       errorMessage(0);
       return FAILURE; 
    }
    if (g > MAX_COLOR || g < MIN_COLOR)
    {
       errorMessage(0);
       return FAILURE; 
    }
    if (b > MAX_COLOR || b < MIN_COLOR)
    {
       errorMessage(0);
       return FAILURE; 
    }
    
    reset( );

    toHexRepresentation(r,5);
    toHexRepresentation(g,3);
    toHexRepresentation(b,1);   

    printf("#");
    for(int i = 5; i > -1;i--)
    {
        printf("%c", hexRepresentation[i]);
    }
    printf("\n");
}