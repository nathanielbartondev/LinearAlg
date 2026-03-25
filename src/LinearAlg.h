#include <iostream>
#include <cmath>
#ifndef LINEARALG_H
#define LINEARALG_H

// Class Matrix: Represents a matrix of numbers (doubles) upon which various operations can be 
// performed.
class Matrix
{
  private:
    // FIELDS
    int _rows {};
    int _columns {};
    double** _elements; 

    // Initializes the 2D array representing the elements in this matrix. Internal use only.
    void initElements()
    {
      if(_rows < 2 || _columns < 2)
      {
        std::cout << "ERROR: Invalid Row or Column value. "
          << "Matrix elements could not be initialized."
          << std::endl;
        std::exit(1);
      }
      // Allocate space for elements. Use of nested pointers allows for dynamic memory
      // allocation at object initialization.
      double* pRow = (double*)calloc(_rows*_columns, sizeof(double));
      _elements = (double**)calloc(_rows, sizeof(double*));
      // Initialize pointers for each row
      for(int i = 0; i < _rows; i++)
        _elements[i] = pRow + i*_columns;
    }

  public:
    // CONSTRUCTORS
    Matrix()
    {
      _rows = 2;
      _columns = 2;
      initElements();
    }
    Matrix(int rows, int cols)
    {
      // Matrix objects must have a minimum of 2 rows and 2 columns.
      // If fewer rows/cols are required, existing primitive types can be used instead.
      if(rows < 2 || cols < 2)
      {
        std::cout << "ERROR: Invalid Row or Column value. "
          << "Matrix object could not be constructed."
          << std::endl;
        std::exit(1);
      }

      _rows = rows;
      _columns = cols;
      initElements();
    }

    // GETTERS
    int getRows()
    {
      return _rows;
    }
    int getColumns()
    {
      return _columns;
    }
    // Returns a deep-copied array. Since this is meant to be a read-only
    // function, the direct address of the _elements array is not given.
    double** getElements()
    {
      // Construct lookup pointers for return array
      double* p1 = (double*)calloc(_rows*_columns, sizeof(double));
      double** outElements = (double**)calloc(_rows, sizeof(double*));
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
    // Retrieves an element at the given row/column indices
    double getElement(int irow, int icol)
    {
      return _elements[irow][icol];
    }
    
    // SETTERS
    // Copies the elements of one matrix object to another.
    // Input matrix must be of equal dimensions to the calling matrix.
    void setElements(Matrix* ref)
    {
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          _elements[i][j] = ref->getElement(i, j);
      }
    }
    // Sets an element in this matrix at the specified row/col index (abbreviated irow and icol)
    // to the given value.
    void setElement(int irow, int icol, double value)
    {
      _elements[irow][icol] = value;
    }

    // DESTRUCTIVE OPERATIONS:
    // These functions are destructive, as they directly alter the elements of this matrix.
    // All destructive functions' names are prepended with "dst_".
    //
    // Adds the input matrix to the calling matrix.
    // Input matrix must be of equal dimensions to the calling matrix.
    void dst_add(Matrix* operand)
    {
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          _elements[i][j] += operand->getElement(i, j);
      }
    }
    //void dst_multBy(Matrix operand);
    //void dst_scale(double scalar);
   
    // NON-DESTRUCTIVE OPERATIONS:
    // These functions are identical in purpose to their destructive counterparts, but
    // instead of operating directly on the elements of this matrix, they operate on and 
    // return a copy of this matrix object, thus preserving the original object's data for 
    // later use. All non-destructive functions' names are prepended with "ndst_".


    // UTILITY & DEBUG
    // Prints matrix elements to the terminal.
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
    // FIELDS
    double* _elements;
    // vector dimensions stored as const value for better maintainability
    const int _dimensions = 2;
  public:
    // CONSTRUCTORS
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

    // GETTERS
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
    int getDimensions()
    {
      return _dimensions;
    }
    double getMagnitude()
    {
      // Perform Pythagorean calculation to obtain 2D vector's magnitude
      return std::sqrt((_elements[0]*_elements[0]) + (_elements[1]*_elements[1]));
    }
    
    // SETTERS
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

    // DESTRUCTIVE OPERATIONS:
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
