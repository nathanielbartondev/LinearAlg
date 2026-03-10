#include <iostream>
#include "LinearAlg.h"

void printArray2Di(int rows, int cols, int** array);

int main()
{
  int ROWS = 3;
  int COLUMNS = 4;
  // p1 allocates space for entire array
  // p1 is also used to initialize individual rows' pointers (below)
  int* p1 = (int*)calloc(ROWS*COLUMNS, sizeof(int));
  // p2 points to an array of int pointers, each representing a different row's first element.
  // p2 is used to index into the array, once fully initilized.
  // For all intents and purposes, p2 IS the array.
  int** p2 = (int**)calloc(ROWS, sizeof(int*));
  // Must initialize addresses for each row's pointer manually
  for (int i = 0; i < ROWS; i++)
    p2[i] = p1 + i*COLUMNS;

  //printArray2Di(ROWS, COLUMNS, p2);
  
  // Matrix class tests
  Matrix matrix(5, 6);
  printArray2Di(matrix.getRows(), matrix.getColumns(), matrix.getElements());

  return 0;
}

void printArray2Di(int rows, int cols, int** array)
{
  // DEV NOTE: validation step may be good here to test
  // against bad pointers
  //

  for(int i = 0; i < rows; i++)
  {
    for(int j = 0; j < cols; j++)
      std::cout << array[i][j] << " ";
    std::cout << std::endl;
  }
}
