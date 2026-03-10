#include "LinearAlg.h"
#include <cstdlib>
#include <iostream>

//using namespace Matrix;

Matrix::Matrix(int rows, int cols)
{
  setRows(rows);
  setColumns(cols);
  initElements();
}

int Matrix::getRows()
{
  return this->_rows;
}

int Matrix::getColumns()
{
  return this->_columns;
}

int** Matrix::getElements()
{
  return this->_elements;
}

void Matrix::setRows(int rows)
{
  this->_rows = rows;
}

void Matrix::setColumns(int cols)
{
  this->_columns = cols;
}

void Matrix::initElements()
{
  // Check if _rows and _columns are valid values
  if(_rows <= 0 || _columns <= 0)
  {
    std::cout << "ERROR: Invalid Row or Column value. Matrix elements could not be intialized."
      << std::endl;
  }
  // Allocate space for elements. Use of nested pointers allows for dynamic memory
  // allocation at object initialization.
  int* p1 = (int*)calloc(_rows*_columns, sizeof(int));
  _elements = (int**)calloc(_rows, sizeof(int*));
  // Initialize pointers for each row
  for(int i = 0; i < _rows; i++)
    _elements[i] = p1 + i*_columns;
}
