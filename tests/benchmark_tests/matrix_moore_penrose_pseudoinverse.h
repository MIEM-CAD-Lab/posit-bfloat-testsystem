#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_moore_penrose_pseudoinverse {

template <typename DataType>
std::vector<std::vector<DataType>> MatrixMul(std::vector<std::vector<DataType>>& a, std::vector<std::vector<DataType>>& b) {
  assert(a.size() > 0 && a[0].size() > 0 && b.size() > 0 && b[0].size() > 0);
  assert(a[0].size() == b.size());
  int row1 = a.size();
  int col1 = a[0].size();
  int col2 = b[0].size();
  std::vector<std::vector<DataType>> c(row1, std::vector<DataType>(col2, 0));
  for (int i = 0; i < row1; ++i)
  {
    for (int j = 0; j < col2; ++j)
    {
      c[i][j] = 0;
      for (int k = 0; k < col1; ++k)
        c[i][j] += a[i][k] * b[k][j];
    }
  }
  return c;
}

template <typename DataType>
DataType MatrixDeterminant(std::vector<std::vector<DataType>>& a)
{
  assert(a.size() > 0 && a[0].size() > 0);
  DataType det = 0;
  std::vector<std::vector<DataType>> temp_a(a.size() - 1, std::vector<DataType>(a[0].size() - 1, 0));

  if (a.size() == 2)
  {
    return((a[0][0] * a[1][1]) - (a[1][0] * a[0][1]));
  }
  else
  {
    for (size_t c = 0; c < a.size(); ++c)
    {
      int subi = 0;
      for (size_t i = 1; i < a.size(); ++i)
      {
        int subj = 0;
        for (size_t j = 0; j < a.size(); ++j)
        {
          if (j == c)
          {
            continue;
          }
          temp_a[subi][subj] = a[i][j];
          ++subj;
        }
        ++subi;
      }
      det = det + (DataType)(DataType(pow(-1, c)) * a[0][c] * MatrixDeterminant(temp_a));
    }
  }
  return det;
}

template <typename DataType>
std::vector<std::vector<DataType>> MatrixTranspose(std::vector<std::vector<DataType>>& a) {
  assert(a.size() > 0 && a[0].size() > 0);
  std::vector<std::vector<DataType>> trans_a(a.size(), std::vector<DataType>(a[0].size(), 0));
  for (size_t i = 0; i < a.size(); ++i)
    for (size_t j = 0; j < a[0].size(); ++j)
      trans_a[j][i] = a[i][j];
  return trans_a;
}

template <typename DataType>
void getCofactor(std::vector<std::vector<DataType>>& a, std::vector<std::vector<DataType>>& temp, int p, int q)
{
  size_t i = 0, j = 0;
  for (size_t row = 0; row < a.size(); ++row)
  {
    for (size_t col = 0; col < a[0].size(); ++col)
    {
      if (row != p && col != q)
      {
        temp[i][j++] = a[row][col];
        if (j == a.size() - 1)
        {
          j = 0;
          ++i;
        }
      }
    }
  }
}

template <typename DataType>
std::vector<std::vector<DataType>> adjoint(std::vector<std::vector<DataType>>& a)
{
  std::vector<std::vector<DataType>> adj_a(a.size(), std::vector<DataType>(a[0].size(), 0));
  if (a.size() == 1 && a[0].size() == 1)
  {
    adj_a[0][0] = 1;
    return adj_a;
  }

  int sign = 1;
  std::vector<std::vector<DataType>> temp(a.size(), std::vector<DataType>(a[0].size(), 0));

  for (int i = 0; i < a.size(); ++i)
  {
    for (int j = 0; j < a[0].size(); ++j)
    {
      getCofactor(a, temp, i, j);
      sign = ((i + j) % 2 == 0) ? 1 : -1;
      adj_a[j][i] = (DataType(sign))*(MatrixDeterminant(temp));
    }
  }
  return adj_a;
}

template <typename DataType>
bool MatrixInverse(std::vector<std::vector<DataType>>& a, std::vector<std::vector<DataType>>& inv_a)
{
  DataType det = MatrixDeterminant(a);
  if ((int)det == 0)
  {
    return false;
  }

  std::vector<std::vector<DataType>> adj_a = adjoint(a);

  for (int i = 0; i < a.size(); ++i)
    for (int j = 0; j < a[0].size(); ++j)
      inv_a[i][j] = adj_a[i][j] / det;

  return true;
}

template <typename DataType>
void MatrixMoorePenrosePseudoinverse(const std::vector<std::vector<DataType>>& A) {
  assert(A.size() > 0 && A[0].size() > 0);
  assert(A.size() == A[0].size());
  auto a = A;
  std::vector<std::vector<DataType>> t_a = MatrixTranspose(a);

  std::vector<std::vector<DataType>> m_a = MatrixMul(t_a, a);
  std::vector<std::vector<DataType>> inv_a(a.size(), std::vector<DataType>(a[0].size(), 0));
  MatrixInverse(m_a, inv_a);

  std::vector<std::vector<DataType>> pseudoinversed_a = MatrixMul(inv_a, t_a);
}

template <typename DataType>
Test MatrixMoorePenrosePseudoinverseTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixMoorePenrosePseudoinverse" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixMoorePenrosePseudoinverse<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixMoorePenrosePseudoinverseTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixMoorePenrosePseudoinverseTest<Posit16>(a));
  test.AddTest(MatrixMoorePenrosePseudoinverseTest<Posit32>(a));
  test.AddTest(MatrixMoorePenrosePseudoinverseTest<bfloat16>(a));
  test.AddTest(MatrixMoorePenrosePseudoinverseTest<Float32>(a));
  test.AddTest(MatrixMoorePenrosePseudoinverseTest<float>(a));
}

template <typename DataType>
void InvokeMatrixMoorePenrosePseudoinverse(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixMoorePenrosePseudoinverse<DataType>(a);
}

void InvokeMatrixMoorePenrosePseudoinverseTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  InvokeMatrixMoorePenrosePseudoinverse<Posit16>(a);
  InvokeMatrixMoorePenrosePseudoinverse<Posit32>(a);
  InvokeMatrixMoorePenrosePseudoinverse<bfloat16>(a);
  InvokeMatrixMoorePenrosePseudoinverse<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Moore Penrose Pseudoinverse");
  CreateMatrixMoorePenrosePseudoinverseTest(test, 4);
  CreateMatrixMoorePenrosePseudoinverseTest(test, 6);
  CreateMatrixMoorePenrosePseudoinverseTest(test, 8);
  CreateMatrixMoorePenrosePseudoinverseTest(test, 10);
  CreateMatrixMoorePenrosePseudoinverseTest(test, 12);
  return test;
}
}
}
