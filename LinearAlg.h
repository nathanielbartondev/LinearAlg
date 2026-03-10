#ifndef LINEARALG_H
#define LINEARALG_H

// TODO: implement template usage to cover all numeric types for
// matrix elements (hardcoded int for now)
//template <typename T>
class Matrix
{
  public:
    Matrix(int rows, int cols);
    // getters
    int getRows();
    int getColumns();
    int** getElements(); // TODO: replace with T
    // setters
    void setRows(int rows);
    void setColumns(int cols);
    // utilities
    //void printFields(); // debug
    //void printElements();
    //void add();
    //void mult();
  private:
    int _rows {};
    int _columns {};
    int** _elements; // TODO: replace with T

    void initElements();
};


#endif
