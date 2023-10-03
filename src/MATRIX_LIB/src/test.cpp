#include <gtest/gtest.h>

#include "matrix_oop.h"

TEST(Getters, Rows) {
  Matrix matrix_1(3, 4);
  ASSERT_EQ(matrix_1.getRows(), 3);
  Matrix matrix_2;
  ASSERT_EQ(matrix_2.getRows(), 1);
}

TEST(Getters, Columns) {
  Matrix matrix_1(6, 6);
  ASSERT_EQ(matrix_1.getColumns(), 6);
  Matrix matrix_2;
  ASSERT_EQ(matrix_2.getColumns(), 1);
  Matrix matrix_3(0, 0);
}

TEST(Getters, Matrix) {
  Matrix matrix_1;
  ASSERT_NEAR(matrix_1.getMatrix(0, 0), 0, 1e-7);
  matrix_1.setMatrixValue(0, 0, 2.2);
  ASSERT_NEAR(matrix_1.getMatrix(0, 0), 2.2, 1e-7);
}

TEST(Constructors, Copy) {
  Matrix a(3, 3);
  a.setMatrixValue(0, 0, 1.1);
  a.setMatrixValue(0, 1, 2.1);
  a.setMatrixValue(0, 2, 3.1);
  a.setMatrixValue(1, 0, 4.1);
  a.setMatrixValue(1, 1, 5.1);
  a.setMatrixValue(1, 2, 6.1);
  a.setMatrixValue(2, 0, 7.1);
  a.setMatrixValue(2, 1, 8.1);
  a.setMatrixValue(2, 2, 9.1);

  Matrix b(a);
  ASSERT_TRUE(a == b);
}

TEST(Constructors, Move) {
  Matrix a(4, 3);
  Matrix a_copy;
  a.setMatrixValue(0, 0, 2.3);
  a_copy = a;
  Matrix b = (Matrix &&) a;
  ASSERT_TRUE(a_copy == b);
  ASSERT_TRUE(a.getRows() == 0);
  ASSERT_TRUE(a.getColumns() == 0);
}

TEST(Setters, Rows) {
  Matrix a;
  a.setRows(0);
  ASSERT_EQ(a.getRows(), 1);
  a.setRows(2);
  ASSERT_EQ(a.getRows(), 2);
  ASSERT_EQ(a.getMatrix(1, 0), 0);
}

TEST(Setters, Columns) {
  Matrix a;
  a.setColumns(0);
  ASSERT_EQ(a.getColumns(), 1);
  a.setColumns(6);
  ASSERT_EQ(a.getColumns(), 6);
  for (size_t i = 0; i < a.getRows(); i++) {
    for (size_t j = 0; j < a.getColumns(); j++) {
      ASSERT_EQ(a.getMatrix(i, j), 0);
    }
  }
}

TEST(Setters, Matrix) {
  Matrix b(2, 2);
  b.setMatrixValue(2, 1, 2.2);
  b.setMatrixValue(1, 3, 3.3);
  b.setMatrixValue(1, 1, 9.1);
  ASSERT_NEAR(b.getMatrix(1, 1), 9.1, 1e-7);
}

TEST(Function, Eq) {
  Matrix a(3, 2);
  Matrix b(4, 4);
  Matrix c(3, 5);
  Matrix d(3, 2);
  d.setMatrixValue(0, 0, 2.2);
  ASSERT_TRUE(!a.EqMatrix(b));
  ASSERT_TRUE(!a.EqMatrix(c));
  ASSERT_TRUE(!b.EqMatrix(c));
  ASSERT_TRUE(!a.EqMatrix(d));
  d.setMatrixValue(0, 0, 0);
  ASSERT_TRUE(a.EqMatrix(d));
}

TEST(Functions, SumMatrix) {
  Matrix a(3, 2);
  Matrix a_copy{a};
  Matrix b(4, 4);
  a.SumMatrix(b);
  ASSERT_TRUE(a == a_copy);

  a.setMatrixValue(0, 0, 3.2);
  a.setMatrixValue(0, 1, 4.6);
  a.setMatrixValue(1, 0, 1.5);
  a.setMatrixValue(1, 1, 3.7);
  a.setMatrixValue(2, 0, 12.0);
  a.setMatrixValue(2, 1, 9.8);

  a_copy.setMatrixValue(0, 0, 2.8);
  a_copy.setMatrixValue(0, 1, 7.0);
  a_copy.setMatrixValue(1, 0, 2.6);
  a_copy.setMatrixValue(1, 1, 3.2);
  a_copy.setMatrixValue(2, 0, 5.5);
  a_copy.setMatrixValue(2, 1, 2.1);

  a.SumMatrix(a_copy);

  ASSERT_NEAR(a.getMatrix(0, 0), 6, 1e-7);
  ASSERT_NEAR(a.getMatrix(0, 1), 11.6, 1e-7);
  ASSERT_NEAR(a.getMatrix(1, 0), 4.1, 1e-7);
  ASSERT_NEAR(a.getMatrix(1, 1), 6.9, 1e-7);
  ASSERT_NEAR(a.getMatrix(2, 0), 17.5, 1e-7);
  ASSERT_NEAR(a.getMatrix(2, 1), 11.9, 1e-7);
}

TEST(Functions, SubMatrix) {
  Matrix a(3, 2);
  Matrix a_copy{a};
  Matrix b(4, 4);
  a.SubMatrix(b);
  ASSERT_TRUE(a == a_copy);

  a.setMatrixValue(0, 0, 3.2);
  a.setMatrixValue(0, 1, 4.6);
  a.setMatrixValue(1, 0, 1.5);
  a.setMatrixValue(1, 1, 3.7);
  a.setMatrixValue(2, 0, 12.0);
  a.setMatrixValue(2, 1, 9.8);

  a_copy.setMatrixValue(0, 0, 2.8);
  a_copy.setMatrixValue(0, 1, 7.0);
  a_copy.setMatrixValue(1, 0, 2.6);
  a_copy.setMatrixValue(1, 1, 3.2);
  a_copy.setMatrixValue(2, 0, 5.5);
  a_copy.setMatrixValue(2, 1, 2.1);

  a.SubMatrix(a_copy);

  ASSERT_NEAR(a.getMatrix(0, 0), 0.4, 1e-7);
  ASSERT_NEAR(a.getMatrix(0, 1), -2.4, 1e-7);
  ASSERT_NEAR(a.getMatrix(1, 0), -1.1, 1e-7);
  ASSERT_NEAR(a.getMatrix(1, 1), 0.5, 1e-7);
  ASSERT_NEAR(a.getMatrix(2, 0), 6.5, 1e-7);
  ASSERT_NEAR(a.getMatrix(2, 1), 7.7, 1e-7);
}

TEST(Functions, MulMatrix) {
  Matrix a(3, 2);
  Matrix a_copy{a};
  Matrix b(4, 4);
  a.MulMatrix(b);
  ASSERT_TRUE(a == a_copy);
  a_copy.setRows(2);

  a.setMatrixValue(0, 0, 3.2);
  a.setMatrixValue(0, 1, 4.6);
  a.setMatrixValue(1, 0, 1.5);
  a.setMatrixValue(1, 1, 3.7);
  a.setMatrixValue(2, 0, 12.0);
  a.setMatrixValue(2, 1, 9.8);

  a_copy.setMatrixValue(0, 0, 2.8);
  a_copy.setMatrixValue(0, 1, 7.0);
  a_copy.setMatrixValue(1, 0, 2.6);
  a_copy.setMatrixValue(1, 1, 3.2);

  a.MulMatrix(a_copy);

  ASSERT_NEAR(a.getMatrix(0, 0), 20.92, 1e-2);
  ASSERT_NEAR(a.getMatrix(0, 1), 37.12, 1e-2);
  ASSERT_NEAR(a.getMatrix(1, 0), 13.82, 1e-2);
  ASSERT_NEAR(a.getMatrix(1, 1), 22.34, 1e-2);
  ASSERT_NEAR(a.getMatrix(2, 0), 59.08, 1e-2);
  ASSERT_NEAR(a.getMatrix(2, 1), 115.36, 1e-2);
}

TEST(Functions, MulNumber) {
  Matrix a(2, 2);

  a.setMatrixValue(0, 0, 3.2);
  a.setMatrixValue(0, 1, 4.6);
  a.setMatrixValue(1, 0, 1.5);
  a.setMatrixValue(1, 1, 3.7);

  Matrix a_copy{a};

  a.MulNumber(6.6);
  for (size_t i = 0; i < a.getRows(); i++) {
    for (size_t j = 0; j < a.getColumns(); j++) {
      ASSERT_NEAR(a.getMatrix(i, j), a_copy.getMatrix(i, j) * 6.6, 1e-6);
    }
  }
}

TEST(Functions, Transpose) {
  Matrix a(3, 2);
  a.setMatrixValue(0, 0, 3.2);
  a.setMatrixValue(0, 1, 4.6);
  a.setMatrixValue(1, 0, 1.5);
  a.setMatrixValue(1, 1, 3.7);
  a.setMatrixValue(2, 0, 12.0);
  a.setMatrixValue(2, 1, 9.8);

  Matrix b = a.Transpose();

  ASSERT_EQ(b.getRows(), 2);
  ASSERT_EQ(b.getColumns(), 3);
  ASSERT_EQ(b.getMatrix(0, 0), 3.2);
  ASSERT_EQ(b.getMatrix(0, 1), 1.5);
  ASSERT_EQ(b.getMatrix(0, 2), 12.0);
  ASSERT_EQ(b.getMatrix(1, 0), 4.6);
  ASSERT_EQ(b.getMatrix(1, 1), 3.7);
  ASSERT_EQ(b.getMatrix(1, 2), 9.8);
}

TEST(Functions, Determinant) {
  Matrix a(2, 3);
  double det = a.Determinant();
  ASSERT_EQ(det, 0);
  Matrix b(2, 2);
  b.setMatrixValue(0, 0, 2.8);
  b.setMatrixValue(0, 1, 7.0);
  b.setMatrixValue(1, 0, 2.6);
  b.setMatrixValue(1, 1, 3.2);
  det = b.Determinant();
  ASSERT_NEAR(det, -9.24, 1e-2);

  Matrix c;
  c.setMatrixValue(0, 0, 3.6);
  det = c.Determinant();
  ASSERT_NEAR(det, 3.6, 1e-7);

  Matrix d(3, 3);
  d.setMatrixValue(0, 0, 3.2);
  d.setMatrixValue(0, 1, 4.6);
  d.setMatrixValue(0, 2, 5.5);
  d.setMatrixValue(1, 0, 1.5);
  d.setMatrixValue(1, 1, 3.7);
  d.setMatrixValue(1, 2, 12.0);
  d.setMatrixValue(2, 0, 9.8);
  d.setMatrixValue(2, 1, 0.1);
  d.setMatrixValue(2, 2, 6.4);

  det = d.Determinant();
  ASSERT_NEAR(det, 370.13, 1e-2);
}

TEST(Functions, CalcComplements) {
  Matrix a(2, 3);
  Matrix b = a.CalcComplements();
  ASSERT_EQ(b.getRows(), 1);
  ASSERT_EQ(b.getColumns(), 1);
  ASSERT_EQ(b.getMatrix(0, 0), 0);

  b.setMatrixValue(0, 0, 3.6);

  Matrix c = b.CalcComplements();
  ASSERT_EQ(c.getRows(), 1);
  ASSERT_EQ(c.getColumns(), 1);
  ASSERT_EQ(c.getMatrix(0, 0), 0);

  Matrix d(3, 3);
  d.setMatrixValue(0, 0, 1.0);
  d.setMatrixValue(0, 1, 2.0);
  d.setMatrixValue(0, 2, 3.0);
  d.setMatrixValue(1, 0, 0.0);
  d.setMatrixValue(1, 1, 4.0);
  d.setMatrixValue(1, 2, 2.0);
  d.setMatrixValue(2, 0, 5.0);
  d.setMatrixValue(2, 1, 2.0);
  d.setMatrixValue(2, 2, 1.0);

  Matrix res = d.CalcComplements();

  ASSERT_EQ(res.getRows(), 3);
  ASSERT_EQ(res.getColumns(), 3);
  ASSERT_EQ(res.getMatrix(0, 0), 0);
  ASSERT_EQ(res.getMatrix(0, 1), 10);
  ASSERT_EQ(res.getMatrix(0, 2), -20);
  ASSERT_EQ(res.getMatrix(1, 0), 4);
  ASSERT_EQ(res.getMatrix(1, 1), -14);
  ASSERT_EQ(res.getMatrix(1, 2), 8);
  ASSERT_EQ(res.getMatrix(2, 0), -8);
  ASSERT_EQ(res.getMatrix(2, 1), -2);
  ASSERT_EQ(res.getMatrix(2, 2), 4);
}

TEST(Functions, InverseMatrix) {
  Matrix a(3, 3);
  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);
  a.setMatrixValue(2, 0, 7.0);
  a.setMatrixValue(2, 1, 8.0);
  a.setMatrixValue(2, 2, 9.0);

  Matrix b = a.InverseMatrix();
  ASSERT_EQ(b.getRows(), 1);
  ASSERT_EQ(b.getColumns(), 1);
  ASSERT_EQ(b.getMatrix(0, 0), 0);

  Matrix matr(3, 3);
  matr.setMatrixValue(0, 0, 2.0);
  matr.setMatrixValue(0, 1, 5.0);
  matr.setMatrixValue(0, 2, 7.0);
  matr.setMatrixValue(1, 0, 6.0);
  matr.setMatrixValue(1, 1, 3.0);
  matr.setMatrixValue(1, 2, 4.0);
  matr.setMatrixValue(2, 0, 5.0);
  matr.setMatrixValue(2, 1, -2.0);
  matr.setMatrixValue(2, 2, -3.0);

  Matrix c = matr.InverseMatrix();
  ASSERT_EQ(c.getRows(), 3);
  ASSERT_EQ(c.getColumns(), 3);
  ASSERT_EQ(c.getMatrix(0, 0), 1);
  ASSERT_EQ(c.getMatrix(0, 1), -1);
  ASSERT_EQ(c.getMatrix(0, 2), 1);
  ASSERT_EQ(c.getMatrix(1, 0), -38);
  ASSERT_EQ(c.getMatrix(1, 1), 41);
  ASSERT_EQ(c.getMatrix(1, 2), -34);
  ASSERT_EQ(c.getMatrix(2, 0), 27);
  ASSERT_EQ(c.getMatrix(2, 1), -29);
  ASSERT_EQ(c.getMatrix(2, 2), 24);
}

TEST(Operators, sum) {
  Matrix a(2, 3);
  Matrix b(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  b.setMatrixValue(0, 0, 9.0);
  b.setMatrixValue(0, 1, 8.0);
  b.setMatrixValue(0, 2, 7.0);
  b.setMatrixValue(1, 0, 6.0);
  b.setMatrixValue(1, 1, 5.0);
  b.setMatrixValue(1, 2, 4.0);

  Matrix c = a + b;

  ASSERT_EQ(c.getRows(), 2);
  ASSERT_EQ(c.getColumns(), 3);
  for (size_t i = 0; i < c.getRows(); i++) {
    for (size_t j = 0; j < c.getColumns(); j++) {
      ASSERT_EQ(c(i, j), 10.0);
    }
  }
}

TEST(Operators, sub) {
  Matrix a(2, 3);
  Matrix b(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  b.setMatrixValue(0, 0, 9.0);
  b.setMatrixValue(0, 1, 8.0);
  b.setMatrixValue(0, 2, 7.0);
  b.setMatrixValue(1, 0, 6.0);
  b.setMatrixValue(1, 1, 5.0);
  b.setMatrixValue(1, 2, 4.0);

  Matrix c = b - a;

  ASSERT_EQ(c.getRows(), 2);
  ASSERT_EQ(c.getColumns(), 3);
  ASSERT_EQ(c.getMatrix(0, 0), 8.0);
  ASSERT_EQ(c.getMatrix(0, 1), 6.0);
  ASSERT_EQ(c.getMatrix(0, 2), 4.0);
  ASSERT_EQ(c.getMatrix(1, 0), 2.0);
  ASSERT_EQ(c.getMatrix(1, 1), 0.0);
  ASSERT_EQ(c.getMatrix(1, 2), -2.0);
}

TEST(Operators, mult_1) {
  Matrix a(2, 3);
  Matrix b(3, 1);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  b.setMatrixValue(0, 0, 9.0);
  b.setMatrixValue(1, 0, 8.0);
  b.setMatrixValue(2, 0, 7.0);

  Matrix c = a * b;

  ASSERT_EQ(c.getRows(), 2);
  ASSERT_EQ(c.getColumns(), 1);
  ASSERT_EQ(c.getMatrix(0, 0), 46.0);
  ASSERT_EQ(c.getMatrix(1, 0), 118.0);
}

TEST(Operators, mult_2) {
  Matrix a(2, 3);
  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  Matrix b = a * 1.1;

  ASSERT_EQ(b.getRows(), 2);
  ASSERT_EQ(b.getColumns(), 3);
  for (size_t i = 0; i < b.getRows(); i++) {
    for (size_t j = 0; j < b.getColumns(); j++) {
      ASSERT_EQ(b(i, j), a(i, j) * 1.1);
    }
  }
}

TEST(Operators, add) {
  Matrix a(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  Matrix b{a};
  a += b;
  ASSERT_EQ(a.getRows(), 2);
  ASSERT_EQ(a.getColumns(), 3);
  for (size_t i = 0; i < a.getRows(); i++) {
    for (size_t j = 0; j < a.getColumns(); j++) {
      ASSERT_EQ(a(i, j), b(i, j) * 2);
    }
  }
}

TEST(Operators, sum_assign) {
  Matrix a(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  Matrix b{a};
  a += b;
  ASSERT_EQ(a.getRows(), 2);
  ASSERT_EQ(a.getColumns(), 3);
  for (size_t i = 0; i < a.getRows(); i++) {
    for (size_t j = 0; j < a.getColumns(); j++) {
      ASSERT_EQ(a(i, j), b(i, j) * 2);
    }
  }
}

TEST(Operators, sub_assign) {
  Matrix a(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  Matrix b{a};
  a -= b;
  ASSERT_EQ(a.getRows(), 2);
  ASSERT_EQ(a.getColumns(), 3);
  for (size_t i = 0; i < a.getRows(); i++) {
    for (size_t j = 0; j < a.getColumns(); j++) {
      ASSERT_EQ(a(i, j), 0);
    }
  }
}

TEST(Operators, mult_assign_1) {
  Matrix a(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  Matrix b(3, 1);
  b.setMatrixValue(0, 0, 1.0);
  b.setMatrixValue(1, 0, 2.0);
  b.setMatrixValue(2, 0, 3.0);

  a *= b;
  ASSERT_EQ(a.getRows(), 2);
  ASSERT_EQ(a.getColumns(), 1);
  ASSERT_EQ(a(0, 0), 14);
  ASSERT_EQ(a(1, 0), 32);
}

TEST(Operators, mult_assign_2) {
  Matrix a(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);
  Matrix b{a};
  a *= 6.0;

  ASSERT_EQ(a.getRows(), 2);
  ASSERT_EQ(a.getColumns(), 3);
  for (size_t i = 0; i < a.getRows(); i++) {
    for (size_t j = 0; j < a.getColumns(); j++) {
      ASSERT_EQ(a(i, j), b(i, j) * 6.0);
    }
  }
}

TEST(Operators, brackets) {
  Matrix a(2, 3);

  a.setMatrixValue(0, 0, 1.0);
  a.setMatrixValue(0, 1, 2.0);
  a.setMatrixValue(0, 2, 3.0);
  a.setMatrixValue(1, 0, 4.0);
  a.setMatrixValue(1, 1, 5.0);
  a.setMatrixValue(1, 2, 6.0);

  ASSERT_EQ(a(2, 2), 0);
  ASSERT_EQ(a(0, 0), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}