#ifndef MATRIX_OOP_H_
#define MATRIX_OOP_H_
#include <cmath>
#include <exception>
#include <iostream>
#include <memory>

class Matrix {
 public:
  using arr_ptr_type = std::unique_ptr<double[]>;
  Matrix() noexcept;
  Matrix(size_t, size_t);
  ~Matrix() noexcept;
  Matrix(const Matrix &other) noexcept;
  Matrix(Matrix &&other) noexcept;

  // /*accessors*/
  size_t getRows();
  size_t getColumns();
  double getMatrix(size_t, size_t);
  // /*Mutators*/
  void setRows(size_t);
  void setColumns(size_t);
  void setMatrixValue(size_t, size_t, double);

  // /*Operations*/
  bool EqMatrix(const Matrix &other);
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  // /*Common functions*/
  void DeleteMatrix();
  void InitializeMatrix(size_t rows, size_t cols);
  void CopyMatrix(const Matrix &);
  void CopyArray(const Matrix &);
  size_t FindMin(size_t, size_t);
  bool SizeCompare(const Matrix &);
  bool SquareMatrix();
  void CreateMinorMatrix(const Matrix &, size_t index_r, size_t index_c,
                         Matrix &);

  // /*Overload operators*/
  Matrix operator+(const Matrix &);
  Matrix operator-(const Matrix &);
  Matrix operator*(const Matrix &);
  Matrix operator*(const double &);
  bool operator==(const Matrix &);
  Matrix &operator=(const Matrix &);
  Matrix &operator+=(const Matrix &);
  Matrix &operator-=(const Matrix &);
  Matrix &operator*=(const Matrix &);
  Matrix &operator*=(const double &);
  double operator()(const size_t &, const size_t &);

 private:
  size_t rows_, columns_;
  std::unique_ptr<arr_ptr_type[]> matrix_;
};
#endif  // MATRIX_OOP_H_
