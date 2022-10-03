#include <stdio.h>
#define FAILURE 1
#define SUCCES_RUN 0

static char letterMap[7] = {'a','b','c','d','e','f', '\0'};
static char hexRepresentation[7];

#define MAX_COLOR 255
#define MIN_COLOR 0

void toHexRepresentation( )
{

}

void reset()
{
    for ( int i = 0; i < 7; i++)
    {
        hexRepresentation[i] = '\0';
    }
     
}

void errorMessage( int inputCode ) 
{
    if((inputCode == 0))
    {
        printf("Nespravny vstup.");
        return;
    }
    printf("Nespravny vstup. at %d", inputCode);     
}

int main ( int arg, char ** args )
{
    int r,g,b;
    printf("Zadejte barvu v RGB formatu:\n");
    if(scanf("rgb \(%d,%d,%d\)",&r, &g,&b) != 3)
    {
        errorMessage(1);
        return FAILURE;
    } 

    if (r > MAX_COLOR || r < MIN_COLOR)
    {
       errorMessage(2);
       return FAILURE; 
    }
    reset( );

}