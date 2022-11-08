#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */

#define FALSE 0
#define TRUE 1


/** @brief Greatest common divisor recursive version based on https://dyclassroom.com/recursion-algorithm/greatest-common-divisor-gcd
 *  @param firstNumber int first number
 *  @param secondNumber int second number
 *  @return  int - gcd
 */
int GCD(int firstNumber, int secondNumber)
{
  if (secondNumber == 0)
    return firstNumber;
  return GCD(secondNumber, firstNumber % secondNumber);
}

/** @brief Algorithm is based on  A Juggling Algorithm https://www.geeksforgeeks.org/array-rotation/  
 * However, the changes are done to supprt right and left rotation, backwards represented by negative rotationBy
 *  @param array unsigned int input number
 *  @param arrayLen length of array
 *  @param rotateBy rotation negative number means backwards
 *  @return void.
 */
void rotateArray(int array[], int arrayLen, int rotateBy)
{
  int rotateByAbs = abs(rotateBy);

  int tmpNumber = 0;
  rotateByAbs = rotateByAbs % arrayLen;
  int chunkSize = GCD(rotateByAbs, arrayLen);
  for (int i = 0; i < chunkSize; i++)
  {

    // handle direction of rotation
    if (rotateBy < 0)
    {
      tmpNumber = array[i];
    }
    else
    {
      tmpNumber = array[arrayLen - 1 - i];
    }

    int j = i;
    while (TRUE)
    {
      int k = j + rotateByAbs;
      if (k >= arrayLen)
        k = k - arrayLen;

      if (k == i)
        break;
      // handle direction of rotation  
      if (rotateBy < 0)
      {

        array[j] = array[k];
      }
      else
      {
        array[arrayLen - 1 - j] = array[arrayLen - 1 - k];
      }

      j = k;
    }
    // handle direction of rotation
    if (rotateBy < 0)
    {
      array[j] = tmpNumber;
    }
    else
    {
      array[arrayLen - 1 - j] = tmpNumber;
    }
  }
}

#ifndef __PROGTEST__
int identicalArrays(const int a[], const int b[], int cnt)
{
  for (int j = 0; j < cnt; j++)
  {
    if (a[j] != b[j])
    {
      return FALSE;
    }
  }
  return TRUE;
}
int main(int argc, char *argv[])
{
  int in0[] = {1, 2, 3, 4, 5};
  int out0[] = {5, 1, 2, 3, 4};

  int in1[] = {1, 2, 3, 4, 5};
  int out1[] = {2, 3, 4, 5, 1};

  int in2[] = {1, 2, 3, 4, 5, 6};
  int out2[] = {4, 5, 6, 1, 2, 3};

  int in3[] = {1, 2, 3, 4, 5, 6, 7};
  int out3[] = {3, 4, 5, 6, 7, 1, 2};

  int in4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int out4[] = {2, 3, 4, 5, 6, 7, 8, 9, 1};

  rotateArray(in0, 5, 1);
  assert(identicalArrays(in0, out0, 5));
  rotateArray(in1, 5, -1);
  assert(identicalArrays(in1, out1, 5));
  rotateArray(in2, 6, -3);
  assert(identicalArrays(in2, out2, 6));
  rotateArray(in3, 7, 12);
  assert(identicalArrays(in3, out3, 7));
  rotateArray(in4, 9, -100);
  assert(identicalArrays(in4, out4, 9));
  return 0;
}
#endif /* __PROGTEST__ */
