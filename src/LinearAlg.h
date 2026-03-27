#include <iostream>
#include <iomanip>
#include <cmath>
#ifndef LINEARALG_H
#define LINEARALG_H

using namespace std;

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
      // Matrix objects must have a minimum of 2 rows and 2 columns.
      // Any fewer, and they would just be glorified 1D arrays.
      if(_rows < 2 || _columns < 2)
      {
        cout << "ERROR: Invalid Row or Column value. "
          << "Matrix elements could not be initialized."
          << endl;
        exit(1);
      }
      // Allocate space for elements. Use of nested pointers allows for dynamic memory
      // allocation at object initialization.
      double* pRow = (double*)calloc(_rows*_columns, sizeof(double));
      _elements = (double**)calloc(_rows, sizeof(double*));
      // Initialize pointers for each row
      for(int i = 0; i < _rows; i++)
        _elements[i] = pRow + i*_columns;
    }
// SETTERS
// DEV NOTE: May not need these, holding onto them for now
/*    void setRows(int rows)
    {
      if(rows < 2) 
      {
        cout << "ERROR: Call to Matrix.setRows() failed. "
          << "Input 'rows' must be greater than or equal to 2."
          << endl;
        exit(1);
      }
      _rows = rows;
    }
    void setColumns(int cols)
    {
      if(cols < 2) 
      {
        cout << "ERROR: Call to Matrix.setColumns() failed. "
          << "Input 'cols' must be greater than or equal to 2."
          << endl;
        exit(1);
      }
      _cols = cols;
    }*/

  public:
// CONSTRUCTORS
    Matrix(int rows = 2, int cols = 2)
    {
      if(rows < 2 || cols < 2)
      {
        cout << "ERROR: Invalid Row or Column value. "
          << "Matrix object could not be constructed."
          << endl;
        exit(1);
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
      if(ref->getRows() != _rows || ref->getColumns() != _columns)
      {
        cout << "ERROR: Matrix.setElements() failed. Dimensions of source matrix "
          << "must equal dimensions of destination matrix." << endl;
        exit(1);
      }

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
    // Multiplies this matrix (1st operand) by the input matrix (2nd operand).
    void dst_multBy(Matrix* operand)
    {
      if(_columns != operand->getRows())
      {
        cout << "ERROR: dst_multBy(): Matrix multiplication failed. "
          << "Number of columns in calling matrix must be equal to "
          << "number of rows in operand matrix." << endl;
        exit(1);
      }
      // Some of these values are altered before the actual multiplication, but are
      // still required for said multiplication, so they are saved into local variables first
      int thisCols = _columns;
      int opCols = operand->getColumns();

      // Elements of this matrix must be copied to a temporary buffer, as
      // field _elements must be re-initialized to accommodate the new dimensions
      // of the product, which may differ from this matrix's original dimensions
      double** thisElements = getElements();
      _columns = opCols;
      initElements();
      dst_zero();
      
      // Output will have i rows and j columns:
      // > i is the number of rows in operand 1
      // > j is the number of columns in operand 2 (assigned to this object above)
      // DEV NOTE: Try to find a way to do this without a triple for loop, ffs
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
        {
          // Number of terms to sum per element in output
          // thisCols or opRows could be checked as upper bound; they are equal
          for(int k = 0; k < thisCols; k++)
          {
            _elements[i][j] += thisElements[i][k] * operand->getElement(k, j);
          }
        }
      }

    }
    // Scales every element in this matrix by the input scalar.
    void dst_scale(double scalar)
    {
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
          _elements[i][j] *= scalar;
      }
    }
    // Sets all elements of this matrix to 0
    void dst_zero()
    {
      for(int i = 0; i < _rows; i++)
      {
        for(int j = 0; j < _columns; j++)
        {
          _elements[i][j] = 0;
        }
      }
    }
   
// NON-DESTRUCTIVE OPERATIONS:
    // These functions are identical in purpose to their destructive counterparts, but
    // instead of operating directly on the elements of this matrix, they operate on and 
    // return a separate matrix object, thus preserving the original object's data for 
    // later use. All non-destructive functions' names are prepended with "ndst_".


// UTILITY & DEBUG
    // Prints matrix elements to the terminal, padding each element with trailing spaces.
    void printElements(int padding = 6)
    {
      cout << endl;
      for(int i = 0; i < _rows; i++)
      {
        if(i == 0) cout << "/ ";
        else if(i == _rows-1) cout << "\\ ";
        else cout << "| ";
        
        for(int j = 0; j < _columns; j++)
        {
          cout << setw(padding) << left;
          cout << _elements[i][j];
        }

        if(i == 0) cout << " \\";
        else if(i == _rows-1) cout << " /";
        else cout << " |";

        cout << endl;
      }
    }

    void printObjectInfo(int elemPadding = 6)
    {
      cout << "[Matrix Object Info]" << endl;
      cout << "Rows:     " << _rows << endl;
      cout << "Columns:  " << _columns << endl;
      cout << "Elements:";
      printElements(elemPadding);
    }
};

// Class Vec2D: Represents 2D vectors and their common mathemetical operations.
class Vec2D
{
  private:
// FIELDS
    double* _elements;
    // Vector dimensions stored as constant value for better maintainability.
    // However the "const" keyword is not used due to all C++ class members being implicitly
    // assignable in certain contexts (i.e. re-initializing object with new constructor call),
    // which leads to compiler errors.
    int _dimensions = 2;

  public:
// CONSTRUCTORS
    Vec2D(double x = 0, double y = 0)
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
        cout << "ERROR: Vector.getElement() failed. Input index out of bounds." << endl;
        exit(1);
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
      return sqrt((_elements[0]*_elements[0]) + (_elements[1]*_elements[1]));
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
        cout << "ERROR: setElement() failed. Provided index was out of bounds."
          << endl;
        exit(1);
      }
      _elements[index] = elem;
    }

// DESTRUCTIVE OPERATIONS:
    // These functions are destructive to this vector object, as they each operate directly
    // on its elements. All destructive functions' names are prepended with "dst_".

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
    // instead of operating directly on the elements of this vector object, they
    // operate on and return a separate vector object, thus preserving the original
    // object's data for later use. All non-destructive functions' names are prepended
    // with "ndst_".
    

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
    // Normalizes a copy of this vector object, provided as input arg "result"
    void ndst_normalize(Vec2D* result)
    {
      result->setElements(this);

      double magnitude = getMagnitude();

      for(int i = 0; i < _dimensions; i++)
        result->setElement(i, result->getElement(i) / magnitude);
    }
    
// UTILITY & DEBUG

    // Displays elements of this vector to the screen, left-padded by the number of input
    // whitespace chars (6 by default)
    void printElements(int padding = 6)
    {
      cout << endl; 
      for(int i = 0; i < _dimensions; i++)
      {
        // Fancy left brace
        if(i == 0) cout << "/ ";
        else if(i == _dimensions-1) cout << "\\ ";
        else cout << "| ";

        cout << setw(padding) << left;
        cout << _elements[i];

        // Fancy right brace
        if(i == 0) cout << " \\";
        else if(i == _dimensions-1) cout << " /";
        else cout << " |";

        cout << endl;
      }
    }
    // Prints all field values for this vector object.
    void printObjectInfo(int elemPadding = 6)
    {
      cout << "[Vec2D Object Info]" << endl;
      cout << "Dimensions: " << _dimensions << endl;
      cout << "Elements:   ";
      printElements(elemPadding);
      cout << "Magnitude: " << getMagnitude() << endl;
    }
};
#endif
