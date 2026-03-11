#ifndef LINEARALG_H
#define LINEARALG_H

// TODO: implement template usage to cover all numeric types for
// matrix elements (hardcoded int for now)
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
        std::cout << "ERROR: Invalid Row or Column value. Matrix elements could not be initialized."
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
    // setters
    void setRows(int rows)
    {
      this->_rows = rows;
    }
    void setColumns(int cols)
    {
      this->_columns = cols;
    }
    // utilities
    //void printFields(); // debug
    //void printElements();
    //void add(Matrix operand);
    //void multBy(Matrix operand);
};


#endif
