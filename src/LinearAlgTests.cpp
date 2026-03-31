#include "LinearAlg.h"

/* LINEAR ALG LIBRARY TESTS
 * 
 * This file runs a battery of tests designed to cover each major function of the
 * LinearAlg library. It can be used to verify correct setup of your development
 * environment (i.e. failure to run this file indicates issues), or simply to view
 * a concrete example of library usage.
 * 
 * */

using namespace std;
#define EQ_RESULT_BAR "-------------------------------------------\n"

int main()
{
  cout << "-- MATRIX CLASS TESTS --" << endl;

  cout << "-- Matrix Default Constructor" << endl;
  Matrix matrix1;
  matrix1.printObjectInfo();
  cout << endl;

  cout << "-- Matrix Param Constructor" << endl;
  matrix1 = Matrix(4, 4);
  matrix1.printObjectInfo();
  cout << endl;

  cout << "-- Matrix Element Setting (Individual)" << endl;
  matrix1.setElement(0, 0, 1);
  matrix1.setElement(1, 1, 2);
  matrix1.setElement(2, 2, 3);
  matrix1.setElement(3, 3, 4);
  matrix1.printObjectInfo();
  cout << endl;

  cout << "-- Matrix Element Setting (Reference Matrix)" << endl;
  Matrix matrix2(4, 4);
  cout << "-- Before:" << endl;
  matrix2.printObjectInfo();
  matrix2.setElements(&matrix1);
  cout << "-- After:" << endl;
  matrix2.printObjectInfo();
  cout << endl; 

  cout << "-- Matrix Destructive Addition" << endl;
  matrix1.setElement(0, 0, 1);
  matrix1.setElement(1, 1, 3);
  matrix1.setElement(2, 2, 5);
  matrix1.setElement(3, 3, 7);
  matrix2.setElement(0, 0, 9);
  matrix2.setElement(1, 1, 7);
  matrix2.setElement(2, 2, 5);
  matrix2.setElement(3, 3, 3);
  matrix1.printElements();
  cout << "\n+\n";
  matrix2.printElements();
  matrix1.dst_add(&matrix2);
  cout << EQ_RESULT_BAR;
  matrix1.printElements();
  cout << endl;

  cout << "-- Matrix Destructive Multiplication" << endl;
  matrix2 = Matrix(4, 2);
  matrix2.setElement(0, 0, 2);
  matrix2.setElement(1, 1, 4);
  matrix2.setElement(2, 0, 6);
  matrix2.setElement(3, 1, 8);
  matrix1.printElements();
  cout << "\n*\n";
  matrix2.printElements();
  matrix1.dst_multBy(&matrix2);
  cout << EQ_RESULT_BAR;
  matrix1.printElements();
  cout << endl;

  cout << "-- Matrix Destructive Scale" << endl;
  matrix1 = Matrix(4, 4);
  matrix1.setElement(0, 0, 1);
  matrix1.setElement(1, 1, 2);
  matrix1.setElement(2, 2, 3);
  matrix1.setElement(3, 3, 4);
  double scalar = 5;
  matrix1.printElements();
  cout << "\n*\n\n";
  cout << scalar << endl;
  matrix1.dst_scale(scalar);
  cout << EQ_RESULT_BAR;
  matrix1.printElements();
  cout << endl;

  cout << "-- Matrix Destructive Zero-ing (Reset All Elems to Zero)" << endl;
  cout << "-- Before:";
  matrix1.printElements();
  matrix1.dst_zero();
  cout << "-- After:";
  matrix1.printElements();
  cout << endl;

  // DEV NOTE: Place non-destructive matrix tests here, once implemented

  cout << "-- VEC2D CLASS TESTS --" << endl;

  cout << "-- Vec2D Default Constructor" << endl;
  Vec2D vector1;
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- Vec2D Param Constructor" << endl;
  vector1 = Vec2D(5, 10);
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- Vector Element Setting (Individual)" << endl;
  vector1 = Vec2D();
  cout << "-- Before:" << endl;
  vector1.printObjectInfo();
  vector1.setElement(0, 15);
  vector1.setElement(1, 30);
  cout << "-- After:" << endl;
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- Vector Element Setting (Reference Vector)" << endl;
  Vec2D vector2;
  cout << "-- Before:" << endl;
  vector2.printObjectInfo();
  vector2.setElements(&vector1);
  cout << "-- After:" << endl;
  vector2.printObjectInfo();
  cout << endl;

  cout << "-- Vector Destructive Scalar Add" << endl;
  scalar = 10;
  vector1.printElements();
  cout << "\n+\n\n";
  cout << scalar << endl;
  vector1.dst_addScalar(scalar);
  cout << EQ_RESULT_BAR;
  vector1.printElements();
  cout << endl;

  cout << "-- Vector Destructive Scale" << endl;
  scalar = 0.1;
  vector1.printElements();
  cout << "\n*\n\n";
  cout << scalar << endl;
  vector1.dst_scale(scalar);
  cout << EQ_RESULT_BAR;
  vector1.printElements();
  cout << endl;
  
  cout << "-- Vector Destructive Add" << endl;
  vector1.printElements();
  cout << "\n+\n";
  vector2.setElement(0, 7.5);
  vector2.setElement(1, 6);
  vector2.printElements();
  vector1.dst_add(&vector2);
  cout << EQ_RESULT_BAR;
  vector1.printElements();
  cout << endl;
  
  cout << "-- Vector Destructive Normalize" << endl;
  cout << "-- Before:" << endl;
  vector1.printObjectInfo();
  vector1.dst_normalize();
  cout << "-- After:" << endl;
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- Vector Dot Product (normalized)" << endl;
  vector1.setElement(0, 3);
  vector1.setElement(1, 4);
  vector1.printElements();
  cout << "\n* (DOT)" << endl;
  vector2.setElement(0, 5);
  vector2.setElement(1, 5);
  vector2.printElements();
  double result = vector1.dotProd(&vector2);
  cout << EQ_RESULT_BAR;
  cout << "\n" << result << "\n\n";


  // Vec2D: Non-destructive tests
  Vec2D ndst_vector_result;

  cout << "-- Vector Non-Destructive Scalar Add" << endl;
  vector1.printElements();
  cout << "\n+\n\n";
  scalar = 2;
  cout << scalar << endl;
  vector1.ndst_addScalar(&ndst_vector_result, scalar);
  cout << EQ_RESULT_BAR;
  ndst_vector_result.printElements();
  cout << "-- Operand 1 Vector Object (preserved):" << endl;
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- Vector Non-Destructive Scale" << endl;
  vector1.printElements();
  cout << "\n*\n\n";
  scalar = 5;
  cout << scalar << endl;
  vector1.ndst_scale(&ndst_vector_result, scalar);
  cout << EQ_RESULT_BAR;
  ndst_vector_result.printElements();
  cout << "-- Operand 1 Vector Object (preserved):" << endl;
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- Vector Non-Destructive Add" << endl;
  vector1.printElements();
  cout << "\n+\n";
  vector2.printElements();
  vector1.ndst_add(&ndst_vector_result, &vector2);
  cout << EQ_RESULT_BAR;
  ndst_vector_result.printElements();
  cout << "-- Operand 1 Vector Object (preserved):" << endl;
  vector1.printObjectInfo();
  cout << endl;
  
  cout << "-- Vector Non-Destructive Normalize" << endl;
  cout << "-- Before:" << endl;
  vector1.printObjectInfo();
  vector1.ndst_normalize(&ndst_vector_result);
  cout << "-- After:" << endl;
  ndst_vector_result.printObjectInfo();
  cout << "-- Operand 1 Vector Object (preserved):" << endl;
  vector1.printObjectInfo();
  cout << endl;

  cout << "-- ALL TESTS COMPLETE --" << endl;
  return 0;
}
