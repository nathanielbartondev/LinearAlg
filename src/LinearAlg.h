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
    T** _elements; // TODO: replace with T

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
    // DEV NOTE: Returning the raw pointer may be bad practice; seems to nullify the 
    // private access on member _elements, allowing direct data access/manipulation
    T** getElements()
    {
      return this->_elements;
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
