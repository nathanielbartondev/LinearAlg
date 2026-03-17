// DEV NOTE: LinearAlg.h REQUIRES iostream header. Investigate ways to
//           include this header in the library itself, rather than stubbing it out in
//           Scratch.cpp
#ifndef LINEARALG_H
#define LINEARALG_H

template <typename T, int ROWS, int COLS>
class Matrix
{
  private:
    int _rows {};
    int _columns {};
    T** _elements; 

    void initElements()
    {
      // Check if _rows and _columns are valid values
      if(_rows <= 0 || _columns <= 0)
      {
        std::cout << "ERROR: Invalid Row or Column value. "
          << "Matrix elements could not be initialized."
          << std::endl;
      }
      // Allocate space for elements. Use of nested pointers allows for dynamic memory
      // allocation at object initialization.
      T* p1 = (T*)calloc(_rows*_columns, sizeof(T));
      _elements = (T**)calloc(_rows, sizeof(T*));
      // Initialize pointers for each row
      for(int i = 0; i < _rows; i++)
        _elements[i] = p1 + i*_columns;
    }

  public:
    Matrix()
    {
      setRows(ROWS);
      setColumns(COLS);
      initElements();
    }
    // getters
    int getRows()
    {
      return this->_rows;
    }
    int getColumns()
    {
      return this->_columns;
    }
    // Returns a deep-copied array. Since this is meant to be a read-only
    // function, the direct address of the _elements array should not be given.
    T** getElements()
    {
      // Construct lookup pointers for return array
      T* p1 = (T*)calloc(_rows*_columns, sizeof(T));
      T** outElements = (T**)calloc(_rows, sizeof(T*));
      // Initialize pointers for each row
      for(int i = 0; i < _rows; i++)
        outElements[i] = p1 + i*_columns;

      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          outElements[i][j] = _elements[i][j];
      }
      return outElements;
    }
    T getElement(int irow, int icol)
    {
      return _elements[irow][icol];
    }
    // setters
    void setRows(int rows)
    {
      this->_rows = rows;
    }
    void setColumns(int cols)
    {
      this->_columns = cols;
    }
    // Copies the elements of one matrix object to another.
    // Input matrix must be of equal size to the calling matrix, and elements must be of the
    // same numeric type.
    void setElements(Matrix* ref)
    {
      
      // DEV NOTE: Manual validation likely unnecessary because compiler catches 
      // type/size mismatches automatically
      /*if(ref->getRows() != _rows || ref->getColumns() != _columns)
      {
        std::cout << "ERROR: Call to setElements() failed. "
          << "Input matrix must match dimensions of calling matrix."
          << std::endl;
      }
      // Verify element type of input matrix
      if(typeid(ref->GetElement(0,0)).name() != typeid(_elements[0][0]).name())
      {
        std::cout << "ERROR: Call to setElements() failed. "
          << "Input matrix's elements must match type of calling matrix's elements."
          << std::endl;
      }*/

      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          _elements[i][j] = ref->getElement(i, j);
      }
    }
    // Sets an element in this matrix at the specified row/col index (abbreviated irow and icol)
    // to the given value
    void setElement(int irow, int icol, T value)
    {
      _elements[irow][icol] = value;
    }
    // utilities
    //void printFields(); // debug
    void printElements()
    {
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          std::cout << _elements[i][j] << " ";
        std::cout << std::endl;
      }
      std::cout << std::endl;
    }
    //void add(Matrix operand);
    //void multBy(Matrix operand);
};


#endif
