#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_lu_decomposition {

template <typename DataType>
void MatrixLUDecomposition(const std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	assert(a.size() == a[0].size());
	std::vector<std::vector<DataType>> l(a.size(), std::vector<DataType>(a[0].size(), 0));
	std::vector<std::vector<DataType>> u(a.size(), std::vector<DataType>(a[0].size(), 0));

	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < a[0].size(); ++j)
			u[i][j] = a[i][j];

	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = i; j < a[0].size(); ++j)
			l[j][i] = u[j][i] / u[i][i];

	for (size_t k = 1; k < a.size(); k++)
	{
		for (size_t i = k - 1; i < a.size(); ++i)
			for (size_t j = i; j < a.size(); ++j)
				l[j][i] = u[j][i] / u[i][i];

		for (size_t i = k; i < a.size(); ++i)
			for (size_t j = k - 1; j < a.size(); ++j)
				u[i][j] = u[i][j] - l[i][k - 1] * u[k - 1][j];
	}
}

template <typename DataType>
Test MatrixLUDecompositionTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixLU" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixLUDecomposition<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixLUDecompositionTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixLUDecompositionTest<Posit16>(a));
  test.AddTest(MatrixLUDecompositionTest<Posit32>(a));
  test.AddTest(MatrixLUDecompositionTest<bfloat16>(a));
  test.AddTest(MatrixLUDecompositionTest<Float32>(a));
  test.AddTest(MatrixLUDecompositionTest<float>(a));
}

template <typename DataType>
void InvokeMatrixLUDecomposition(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixLUDecomposition<DataType>(a);
}

void InvokeMatrixLUDecompositionTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  InvokeMatrixLUDecomposition<Posit16>(a);
  InvokeMatrixLUDecomposition<Posit32>(a);
  InvokeMatrixLUDecomposition<bfloat16>(a);
  InvokeMatrixLUDecomposition<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix LU Decomposition");
  CreateMatrixLUDecompositionTest(test, 5);
  CreateMatrixLUDecompositionTest(test, 10);
  CreateMatrixLUDecompositionTest(test, 25);
  CreateMatrixLUDecompositionTest(test, 50);
  CreateMatrixLUDecompositionTest(test, 100);
  CreateMatrixLUDecompositionTest(test, 150);
  CreateMatrixLUDecompositionTest(test, 200);
  CreateMatrixLUDecompositionTest(test, 250);
  CreateMatrixLUDecompositionTest(test, 500);
  CreateMatrixLUDecompositionTest(test, 750);
  CreateMatrixLUDecompositionTest(test, 1000);
  CreateMatrixLUDecompositionTest(test, 1500);
  CreateMatrixLUDecompositionTest(test, 2000);
  CreateMatrixLUDecompositionTest(test, 2500);
  return test;
}
}
}

