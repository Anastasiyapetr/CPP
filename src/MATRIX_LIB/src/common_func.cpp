#include "matrix_oop.h"

void Matrix::InitializeMatrix(size_t rows, size_t cols) {
  try {
    if (rows == 0 || cols == 0) {
      throw std::invalid_argument("Parametrs rows and columns must be > 0");
    } else {
      rows_ = rows;
      columns_ = cols;
      matrix_ = std::make_unique<arr_ptr_type[]>(rows_);
      for (size_t i = 0; i < rows_; i++)
        matrix_[i] = std::make_unique<double[]>(columns_);
    }
  } catch (std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }
}

void Matrix::DeleteMatrix() {
  for (unsigned i = 0; i < rows_; i++) {
    matrix_[i].reset();
  }
  matrix_.reset();
  rows_ = 0;
  columns_ = 0;
}

void Matrix::CopyMatrix(const Matrix &A) {
  DeleteMatrix();
  InitializeMatrix(A.rows_, A.columns_);
  CopyArray(A);
}

void Matrix::CopyArray(const Matrix &A) {
  size_t rows = FindMin(rows_, A.rows_);
  size_t columns = FindMin(columns_, A.columns_);

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      matrix_[i][j] = A.matrix_[i][j];
    }
  }
}

size_t Matrix::FindMin(size_t a, size_t b) { return a > b ? b : a; }

bool Matrix::SizeCompare(const Matrix &A) {
  bool answer = true;
  if (rows_ != A.rows_ || columns_ != A.columns_) {
    answer = false;
  }
  return answer;
}

bool Matrix::SquareMatrix() { return rows_ == columns_; }

void Matrix::CreateMinorMatrix(const Matrix &A, size_t index_r,
                                  size_t index_c, Matrix &B) {
  size_t B_rows = 0, B_columns = 0;
  for (size_t i = 0; i < A.rows_; i++) {
    if (i == index_r) {
      continue;
    }
    for (size_t j = 0; j < A.columns_; j++) {
      if (j == index_c) {
        continue;
      }
      B.matrix_[B_rows][B_columns++] = A.matrix_[i][j];
      if (B_columns >= B.columns_) {
        B_columns = 0;
        B_rows++;
      }
    }
  }
}
