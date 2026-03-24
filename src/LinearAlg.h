#include <iostream>
#include <cmath>
//#include <typeinfo>
#ifndef LINEARALG_H
#define LINEARALG_H

// Class Matrix: Represents a matrix of numbers upon which various operations can be performed.
//
// Matrices can be of any numeric type (conventionally 'double' for mosot graphics applications).
// 
// For arithmetic operations, both the calling matrix and the second operand matrix must be of
// identical types. Also be sure to observe operation-specific rules (e.g. addition requires that
// matrix dimensions of both operands match).
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
    //void printFields(); // debug
    // Adds the input matrix to the calling matrix.
    // Matrices must have equivalent dimensions and element type.
    void add(Matrix* operand)
    {
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          _elements[i][j] += operand->getElement(i, j);
      }
    }
    //void multBy(Matrix operand);
    //void scale(double scalar);

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
    //void printObjectInfo();
};

// Class Vec2D: Represents 2D vectors and their common mathemetical operations.
class Vec2D
{
  private:
    double* _elements;
    const int _dimensions = 2;
  public:
    Vec2D()
    {
      _elements = (double*)calloc(_dimensions, sizeof(double));
      _elements[0] = 0;
      _elements[1] = 0;
    }
    Vec2D(double x, double y)
    {
      _elements = (double*)calloc(_dimensions, sizeof(double));
      _elements[0] = x;
      _elements[1] = y;
    }
    // GETTERS:
    // These functions retrieve or otherwise calculate certain information about this
    // vector object.

    // Get all elements of this vector object.
    // Returns a deep-copied array to prevent direct access to vector elements
    double* getElements()
    {
      double* outElements = (double*)calloc(_dimensions, sizeof(double));
      for(int i = 0; i < _dimensions; i++)
      {
        outElements[i] = _elements[i];
      }
      return outElements;
    }
    // Returns element at given index (starting at 0)
    double getElement(int index)
    {
      // DEV NOTE: Using this scheme for error handling is sufficient for now.
      // This scheme allows printing of custom error messages AND immediate program exit.
      // This scheme will only be used for fatal errors.
      if(index >= _dimensions || index < 0)
      {
        std::cout << "ERROR: getElement() could not retrieve element from vector. "
          << "Index out of bounds." 
          << std::endl;
        std::exit(1);
      }
      return _elements[index];
    }
    // Getting vector dimensions in this way enforces reference to same
    // value in memory across all scopes, and (redundantly) ensures _dimensions is not altered.
    int getDimensions()
    {
      return _dimensions;
    }
    
    double getMagnitude()
    {
      // Perform Pythagorean calculation to obtain 2D vector's magnitude. All values
      // are typecast to double to avoid rounding/truncation issues.
      return std::sqrt((_elements[0]*_elements[0]) + 
          (_elements[1]*_elements[1]));
    }

    void setElements(Vec2D* ref)
    {
      for(int i = 0 ; i < _dimensions; i++)
        _elements[i] = ref->getElement(i);
    }

    void setElement(int index, double elem)
    {
      if(index >= _dimensions || index < 0)
      {
        std::cout << "ERROR: setElement() failed. Provided index was out of bounds."
          << std::endl;
        std::exit(1);
      }
      _elements[index] = elem;
    }

    // DESTRUCTIVE OPERATIONS
    // These functions are destructive to the vector object, as they each operate directly
    // on member _elements. All destructive functions' names are prepended with "dst_".

    // Adds a scalar value to this vector. Scalars will always be added to all elements
    // of the vector.
    void dst_addScalar(double scalar)
    {
      for(int i = 0; i < _dimensions; i++)
        _elements[i] += scalar;
    }
    // Scales this vector by a scalar value. All elements of the vector will be multiplied
    // by this scalar.
    void dst_scale(double scalar)
    {
      for(int i = 0; i < _dimensions; i++)
        _elements[i] *= scalar;
    }

    void dst_add(Vec2D* operand)
    {
      for(int i = 0; i < _dimensions; i++)
        _elements[i] += operand->getElement(i);
    }
    // Normalizes this vector, setting its magnitude to 1.
    void dst_normalize()
    {
      double magnitude = getMagnitude();

      for(int i = 0; i < _dimensions; i++)
        _elements[i] = _elements[i] / magnitude;
    }

    double dotProd(Vec2D* operand)
    {
      // Magnitude of this object and operand object, respectively
      //double thisMag = getMagnitude();
      //double opMag = operand->getMagnitude();
      Vec2D thisCopy;
      Vec2D operandCopy;
      ndst_normalize(&thisCopy);
      operand->ndst_normalize(&operandCopy);
      double result = 0;
      
      for(int i = 0; i < _dimensions; i++)
        result += (thisCopy.getElement(i)*operandCopy.getElement(i));

      return result;
    }

    // NON-DESTRUCTIVE OPERATIONS:
    // These functions are identical in purpose to their destructive counterparts, but
    // instead of operating directly on the _elements member of the vector object, they
    // operate on and return a copy of the vector object, thus preserving the original
    // object's data for later use. All non-destructive functions' names are prepended
    // with "ndst_".
    
    // Normalizes a copy of this vector object, provided as input arg "result"
    void ndst_normalize(Vec2D* result)
    {
      result->setElements(this);

      double magnitude = getMagnitude();

      for(int i = 0; i < _dimensions; i++)
        result->setElement(i, result->getElement(i) / magnitude);
    }

    void ndst_addScalar(Vec2D* result, double scalar)
    {
      result->setElements(this);
      for(int i = 0; i < _dimensions; i++)
        result->setElement(i, result->getElement(i) + scalar);
    }
    // Scales this vector by a scalar value. All elements of the vector will be multiplied
    // by this scalar.
    void ndst_scale(Vec2D* result, double scalar)
    {
      result->setElements(this);
      for(int i = 0; i < _dimensions; i++)
        result->setElement(i, result->getElement(i) * scalar);
    }

    void ndst_add(Vec2D* result, Vec2D* operand)
    {
      result->setElements(this);
      for(int i = 0; i < _dimensions; i++)
        result->setElement(i, result->getElement(i) + operand->getElement(i));
    }
    
    // MISC UTILITY

    // Displays elements of this vector to the screen
    void printElements()
    {
      std::cout << "{ ";
      for(int i = 0; i < _dimensions; i++)
      {
        std::cout << _elements[i] << " ";
      }
      std::cout << "}" << std::endl;
    }
    // DEBUG FUNCTION -- Prints all member values for this vector object.
    void printObjectInfo()
    {
      std::cout << "Vec2D Object Info\n"
        << "Dimensions: " << _dimensions << "\n"
        << "Elements:   ";
      printElements();
      std::cout << "Magnitude: " << getMagnitude() << std::endl;
    }
};
#endif
