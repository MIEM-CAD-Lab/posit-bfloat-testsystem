#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_mult {

template <typename DataType>
std::vector<std::vector<DataType>> MatrixMult(const std::vector<std::vector<DataType>>& a, const std::vector<std::vector<DataType>>& b) {
	assert(a.size() > 0 && a[0].size() > 0 && b.size() > 0 && b[0].size() > 0);
	assert(a[0].size() == b.size()); 
	int row1 = a.size();
	int col1 = a[0].size();
	int col2 = b[0].size();
	std::vector<std::vector<DataType>> c(row1, std::vector<DataType>(col2, 0));
	for (size_t i = 0; i < row1; ++i)
	{
		for (size_t j = 0; j < col2; ++j)
		{
			c[i][j] = 0;
			for (size_t k = 0; k < col1; ++k)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
	return c;
}
template <typename DataType>
Test MatrixMulTest(const std::vector<std::vector<float >>& A, const std::vector<std::vector<float >>& B) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  std::vector<std::vector<DataType>> b(B.size(), std::vector<DataType>(B.front().size(), 0.0));
  for (size_t i = 0; i < B.size(); ++i) {
    for (size_t j = 0; j < B[i].size(); ++j) {
      b[i][j] = B[i][j];
    }
  }
  std::string name = "MatrixMul" + std::to_string(A.size()) + "x" + std::to_string(B.front().size());
  return Test(name, [a, b](){MatrixMult<DataType>(a, b);}, format_type<DataType>::format_name);
}

void CreateMatrixMulTest(TestSet& test, size_t x) {
  size_t y = x;
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(x, y);
  std::vector<std::vector<float>> b = generator.GetRandomMatrix<float>(x, y);
  test.AddTest(MatrixMulTest<Posit16>(a, b));
  test.AddTest(MatrixMulTest<Posit32>(a, b));
  test.AddTest(MatrixMulTest<bfloat16>(a, b));
  test.AddTest(MatrixMulTest<Float32>(a, b));
  test.AddTest(MatrixMulTest<float>(a, b));
}

template <typename DataType>
void MatrixMulInvoke(const std::vector<std::vector<float >>& A, const std::vector<std::vector<float >>& B) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  std::vector<std::vector<DataType>> b(B.size(), std::vector<DataType>(B.front().size(), 0.0));
  for (size_t i = 0; i < B.size(); ++i) {
    for (size_t j = 0; j < B[i].size(); ++j) {
      b[i][j] = B[i][j];
    }
  }
  MatrixMult<DataType>(a, b);
}

void InvokeMatrixMulTest(size_t x, size_t y) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(x, y);
  std::vector<std::vector<float>> b = generator.GetRandomMatrix<float>(x, y);
  MatrixMulInvoke<Posit16>(a, b);
  MatrixMulInvoke<Posit32>(a, b);
  MatrixMulInvoke<bfloat16>(a, b);
  MatrixMulInvoke<Float32>(a, b);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Multiplication");
  CreateMatrixMulTest(test, 5);
  CreateMatrixMulTest(test, 10);
  CreateMatrixMulTest(test, 25);
  CreateMatrixMulTest(test, 50);
  CreateMatrixMulTest(test, 100);
  CreateMatrixMulTest(test, 150);
  CreateMatrixMulTest(test, 200);
  CreateMatrixMulTest(test, 250);
  CreateMatrixMulTest(test, 500);
  CreateMatrixMulTest(test, 750);
  CreateMatrixMulTest(test, 1000);
  CreateMatrixMulTest(test, 1500);
  CreateMatrixMulTest(test, 2000);
  CreateMatrixMulTest(test, 2500);
  return test;
}

TestSet CreatePositTestSet() {
  TestSet test("Matrix Multiplication");
  CreateMatrixMulTest(test, 10);
  CreateMatrixMulTest(test, 50);
  CreateMatrixMulTest(test, 100);
  CreateMatrixMulTest(test, 200);
  CreateMatrixMulTest(test, 500);
  return test;
}
}
}

