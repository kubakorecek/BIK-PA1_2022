
#include <stdio.h>

#define SUCCESS_RUN 0
#define FAIL 1

#define CORNERS '+'
#define SIDES '|'
#define FIRST_LAST_LINE '-'


void errorMessage( int inputCode ) 
{
    if((inputCode == 0))
    {
        printf("Nespravny vstup.\n");
        return;
    }
    printf("Nespravny vstup. at %d", inputCode);     
}

void PrintTopBottom(const int boardSize, const int numberOfFieldsCol)
{
    printf("%c", CORNERS);
    for (int col = 0; col < boardSize * numberOfFieldsCol; col++ )
    {
        printf("%c", FIRST_LAST_LINE);
    }
    printf("%c\n", CORNERS);
}

void PrintBoard(const int boardSize, const int numberOfFieldsRow, const int numberOfFieldsCol)
{
    PrintTopBottom(boardSize,numberOfFieldsCol);
    int mainRow = 0;
    for(mainRow = 0;mainRow<boardSize; mainRow++)
    {
       
            for(int row = 0; row < numberOfFieldsRow;row++)
            {
                printf("%c", SIDES); 
               for(int mainCol = 0; mainCol < boardSize; mainCol++)
               {
                   
                   for (int col = 0; col < numberOfFieldsCol ; col++)
                    {
                          if(mainRow % 2 == mainCol % 2){
                        printf("%c", ' ');
                    }else{
                        printf("%c", 'X');
                    }
                    }
                    
               } 
             printf("%c\n", SIDES);
            }
    
   
    }

    PrintTopBottom(boardSize,numberOfFieldsCol);
}






int main(void)
{

    int numberOfFields;
    int sizeOfField;

    printf("Zadejte pocet poli:\n");
    if((scanf("%d",&numberOfFields ) != 1) || (numberOfFields < 1))
    {
        errorMessage(0);
        return SUCCESS_RUN;
    }
    printf("Zadejte velikost pole:\n");
    if((scanf("%d",&sizeOfField ) != 1) || (sizeOfField < 1))
    {
        errorMessage(0);
        return SUCCESS_RUN;
    }

    PrintBoard(numberOfFields, sizeOfField, sizeOfField);

    return SUCCESS_RUN;
}