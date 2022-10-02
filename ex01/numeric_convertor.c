#include <stdio.h>
#define SUCCES 0
#define FAIL 1

int main ( int arg, char ** args)
{
	if( arg < 4 ) 
	{
		printf("There is not enough arguments\n");
		printf("PLease run program, given four numbers.");
		printf("n1 b1 n2 b2 - n as number and b is given base.\n");
		return FAIL;
	}
	return SUCCES;
}
