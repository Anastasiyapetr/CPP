#include "matrix_oop.h"

Matrix::Matrix() noexcept { InitializeMatrix(1, 1); }

Matrix::Matrix(size_t rows, size_t cols) { InitializeMatrix(rows, cols); }

Matrix::~Matrix() noexcept { rows_ = 0, columns_ = 0; }

Matrix::Matrix(const Matrix &other) noexcept {
  this->InitializeMatrix(1, 1);
  CopyMatrix(other);
}

Matrix::Matrix(Matrix &&other) noexcept {
  this->InitializeMatrix(1, 1);
  CopyMatrix(other);
  other.DeleteMatrix();
}

size_t Matrix::getRows() { return rows_; }
size_t Matrix::getColumns() { return columns_; }
double Matrix::getMatrix(size_t r, size_t c) { return matrix_[r][c]; }

void Matrix::setRows(size_t new_rows) {
  try {
    if (new_rows == 0) {
      throw std::invalid_argument("Number of rows must be > 0");
    }
    Matrix A(new_rows, columns_);
    A.CopyArray(*this);
    CopyMatrix(A);
    A.DeleteMatrix();
  } catch (std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }
}

void Matrix::setColumns(size_t new_columns) {
  try {
    if (new_columns <= 0) {
      throw std::invalid_argument("Number of columns must be > 0");
    }
    Matrix A(rows_, new_columns);
    A.CopyArray(*this);
    CopyMatrix(A);
    A.DeleteMatrix();
  } catch (std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }
}

void Matrix::setMatrixValue(size_t row, size_t column, double value) {
  try {
    if (row >= rows_) {
      throw std::invalid_argument(
          "Row number must be <= the total number of rows - 1");
    }
    if (column >= columns_) {
      throw std::invalid_argument(
          "Column number must be <= the total number of columns - 1");
    }
    matrix_[row][column] = value;
  } catch (std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
  }
}

bool Matrix::EqMatrix(const Matrix &other) {
  bool answer = true;
  if (!SizeCompare(other)) {
    answer = false;
  } else {
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < columns_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) >= 1e-7) {
          answer = false;
        }
      }
    }
  }
  return answer;
}

void Matrix::SumMatrix(const Matrix &other) {
  try {
    if (!SizeCompare(other)) {
      throw std::out_of_range(
          "Incorrect input, matrices should have the same size");
    }
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < columns_; j++) {
        matrix_[i][j] += other.matrix_[i][j];
      }
    }
  } catch (std::out_of_range &e) {
    std::cout << e.what() << "\n";
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  try {
    if (!SizeCompare(other)) {
      throw std::out_of_range(
          "Incorrect input, matrices should have the same size");
    }
    for (size_t i = 0; i < rows_; i++) {
      for (size_t j = 0; j < columns_; j++) {
        matrix_[i][j] -= other.matrix_[i][j];
      }
    }
  } catch (std::out_of_range &e) {
    std::cout << e.what() << "\n";
  }
}

void Matrix::MulNumber(const double num) {
  for (size_t i = 0; i < rows_; i++) {
    for (size_t j = 0; j < columns_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  try {
    if (columns_ != other.rows_) {
      throw std::out_of_range("Columns of matrix1 should be = Rows of matrix2");
    }
    if (rows_ > 0 && columns_ > 0 && other.columns_ > 0 && other.rows_ > 0) {
      Matrix A(rows_, other.columns_);
      for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < other.columns_; j++) {
          for (size_t k = 0; k < other.rows_; k++) {
            A.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
          }
        }
      }
      CopyMatrix(A);
      A.DeleteMatrix();
    }
  } catch (std::out_of_range &e) {
    std::cout << e.what() << "\n";
  }
}

Matrix Matrix::Transpose() {
  Matrix A(columns_, rows_);
  for (size_t i = 0; i < A.rows_; i++) {
    for (size_t j = 0; j < A.columns_; j++) {
      A.matrix_[i][j] = matrix_[j][i];
    }
  }
  return A;
}

double Matrix::Determinant() {
  double det = 0;
  try {
    if (!SquareMatrix()) {
      throw std::invalid_argument("Invalid value of matrix");
    }
    if (rows_ == 1) {
      det = matrix_[0][0];
    } else if (rows_ == 2) {
      det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
    } else {
      Matrix A(rows_ - 1, columns_ - 1);
      for (size_t i = 0; i < rows_; i++) {
        CreateMinorMatrix(*this, 0, i, A);
        int index = (i % 2 == 0) ? 1 : -1;
        det += index * matrix_[0][i] * A.Determinant();
      }
      A.DeleteMatrix();
    }
  } catch (std::invalid_argument &e) {
    std::cout << e.what();
  }
  return det;
}

Matrix Matrix::CalcComplements() {
  Matrix A(rows_, columns_);
  try {
    if (!SquareMatrix()) {
      A.setRows(1);
      A.setColumns(1);
      throw std::invalid_argument("Invalid value of matrix");
    }
    if (rows_ == 1) {
      A.matrix_[0][0] = 0;
    } else {
      Matrix Minor(rows_ - 1, columns_ - 1);
      for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
          CreateMinorMatrix(*this, i, j, Minor);
          A.matrix_[i][j] = Minor.Determinant() * pow(-1, i + j);
        }
      }
      Minor.DeleteMatrix();
    }
  } catch (std::invalid_argument &e) {
    std::cout << e.what();
  }
  return A;
}

Matrix Matrix::InverseMatrix() {
  Matrix A(rows_, columns_);
  double determinant = 0;
  try {
    determinant = this->Determinant();
    if (fabs(determinant) <= 1e-7) {
      A.setRows(1);
      A.setColumns(1);
      throw std::invalid_argument("Invalid value of matrix");
    }
    A = CalcComplements().Transpose();
    A.MulNumber(1 / determinant);
  } catch (std::invalid_argument &e) {
    std::cout << e.what();
  }
  return A;
}

Matrix Matrix::operator+(const Matrix &A) {
  Matrix result;
  result = *this;
  result.SumMatrix(A);
  return result;
}

Matrix Matrix::operator-(const Matrix &A) {
  Matrix result;
  result = *this;
  result.SubMatrix(A);
  return result;
}

Matrix Matrix::operator*(const Matrix &A) {
  Matrix result;
  result = *this;
  result.MulMatrix(A);
  return result;
}

Matrix Matrix::operator*(const double &value) {
  Matrix result;
  result = *this;
  result.MulNumber(value);
  return result;
}

bool Matrix::operator==(const Matrix &A) { return EqMatrix(A); }

Matrix &Matrix::operator=(const Matrix &matrix) {
  CopyMatrix(matrix);
  return *this;
}

Matrix &Matrix::operator+=(const Matrix &A) {
  SumMatrix(A);
  return *this;
}
Matrix &Matrix::operator-=(const Matrix &A) {
  SubMatrix(A);
  return *this;
}
Matrix &Matrix::operator*=(const Matrix &A) {
  MulMatrix(A);
  return *this;
}
Matrix &Matrix::operator*=(const double &value) {
  MulNumber(value);
  return *this;
}

double Matrix::operator()(const size_t &i, const size_t &j) {
  try {
    if (i >= rows_ || j >= columns_) {
      throw std::invalid_argument(
          "Index should be in the range from 1 to matrix size - 1");
    }
  } catch (std::invalid_argument &e) {
    std::cout << e.what() << std::endl;
    return 0.0;
  }
  return matrix_[i][j];
}
