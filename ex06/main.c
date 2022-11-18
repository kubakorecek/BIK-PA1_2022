#include <stdio.h>
#include <stdlib.h>

// char *rowField(int *nr)
// {
//     char *row = NULL;
//     size_t size;
//     int len;
//     int max = 0;
//     int res = ;
//     char c;
//     while ((c = fgetc(stdin)))
//     {
//         printf("%c");
//         // if (max =< *nr)
//         // {
//         //     max += (max < 100) ? 10 : max / 2;
//         //     row = (char *)realloc(row, sizeof(*row) * max);
//         // }
//         // if(  c != '*' || c != '.' )
//         // {

//         // }
//     }
// }

int main(void)
{
    char c;
    char **matrix = NULL;
    int **matrixInt = NULL;
    // char *row = NULL;
    int maxc = 100;
    int nrc = 0;
    int max = 100;
    int nr = 0;
    int len_old = 0;
    int tmp = -1000;
    matrix = (char **)malloc(sizeof(char *) * max*maxc);
    printf("Zadejte hraci plochu:\n");
    while ((c = fgetc(stdin)))
    {
        if (c == EOF)
        {
            break;
        }
        if (c == '.' || c == '*')
        {
            if (nrc == 0)
            {
                matrix[nr] = (char *)malloc(sizeof(char) * (maxc ));
            }
            else if (maxc <= nrc)
            {
                maxc += (maxc < 100) ? 10 : maxc / 2;
                matrix[nr] = (char *)realloc(matrix[nr], sizeof(char) * (maxc));
            }
            matrix[nr][nrc] = c;
            nrc++;
        }
        else if (c == '\n')
        {
            //matrix[nr][nrc] = c;
            //nrc++;

            if (max <= nr)
            {
                max += (max < 100) ? 10 : max / 2;
                matrix = (char **)realloc(matrix, sizeof(char *) * max*maxc);

                // for(int j = 0; j < nr;j++ )
                // {
                //    // matrix[nr] = (char *)realloc(matrix,sizeof(char) * maxc + 1);
                // }
            }
            // matrix[nr] = matrix[nr];
            nr++;

            if (len_old == 0)
            {
                len_old = nrc;
            }
            if (len_old != nrc)
            {
                // printf("Nespravny vstup2.\n");
                break;
            }
            nrc = 0;
        }
        else
        {
            nr++;
            break;
        }
        // printf("%c", c);
    }
    if (!feof(stdin) || len_old<1)
    {
        printf("Nespravny vstup.\n");
        if(len_old<1)
        {
            free(matrix);
            return EXIT_SUCCESS;
        }
        for (int i = 0; i < nr; i++)
        {
            free(matrix[i]);
            
        }
        free(matrix);
        return EXIT_SUCCESS;
    }

    // for (int i = 0; i < nr; i++)
    //     for (int j = 0; j < len_old; j++)
    //         printf("%c", matrix[i][j]);

    matrixInt = (int **)malloc(sizeof(int *) * (nr * (len_old + 2) + 2));
    for (int j = 0; j < nr + 3; j++)
    {
        matrixInt[j] = (int *)calloc((len_old + 2), sizeof(int));
    }

    for (int i = 0; i < nr; i++)
        for (int j = 0; j < len_old; j++)
        {
            if (matrix[i][j] == '*')
            {
                matrixInt[i + 1][j + 1] = -100;
                for (int k = -1; k < 2; k++)
                {
                    for (int l = -1; l < 2; l++)
                    {
                        matrixInt[i + 1 + k][j + 1 + l]++;
                    }
                }
            };
        }
    printf("Vyplnena hraci plocha:\n");
    for (int i = 1; i < nr + 1; i++)
    {
        
        for (int j = 1; j < len_old+1; j++)
        {
            tmp = matrixInt[i][j];
            if (tmp < -20)
            {
                printf("*");
            }
            else if (tmp == 0)
            {
                printf(".");
            }
            else
            {
                printf("%d", tmp);
            }
        }
    printf("\n");
    }
    for (int i = 0; i < nr; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    for (int i = 0; i < nr + 3; i++)
    {
        free(matrixInt[i]);
    }
    free(matrixInt);
    return EXIT_SUCCESS;
}