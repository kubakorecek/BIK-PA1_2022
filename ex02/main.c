
#include <stdio.h>

#define SUCCESS_RUN 0
#define FAIL 1

#define CORNERS '+'
#define SIDES '|'
#define FIRST_LAST_LINE '-'


void PrintTopBottom(const int boadSize, const int numberOfFieldsCol)
{
    printf("%c", CORNERS);
    for (int col = 0; col < boadSize * numberOfFieldsCol; col++ )
    {
        printf("%c", FIRST_LAST_LINE);
    }
    printf("%c\n", CORNERS);
}


void PrintBoard(const int boadSize, const int numberOfFieldsRow,const int numberOfFieldsCol )
{
    PrintTopBottom(boadSize,numberOfFieldsCol);
    int mainRow = 0;
    
    // going over all rows
    for(mainRow = 0;mainRow<boadSize; mainRow++)
    {
       
            for(int row = 0; row < numberOfFieldsCol;row++)
            {
                printf("%c", SIDES); 
               for(int mainCol = 0; mainCol < boadSize; mainCol++)
               {
                   
                   for (int col = 0; col < numberOfFieldsCol ; col++)
                    {
                       // if(mainCol ==3 && mainRow ==0)
                       // {
                           // printf("%c", 'W');
                       // }



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

    PrintTopBottom(boadSize,numberOfFieldsCol);
}






int main(void)
{

    PrintBoard(5,5,5);
    PrintBoard(5, 4,4);
    PrintBoard(4, 4,4);

    PrintBoard(3, 3,3);
    PrintBoard(2, 3,3);
    PrintBoard(3, 2,2);


//short int x = -0x197b; /* !!! short */
short int x = -0xab; /* !!! short */

printf ( "%x", x );
    return SUCCESS_RUN;
}