#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_normalize {
template <typename DataType>
void MatrixSquareNormalize(const std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	assert(a.size() == a[0].size());

	std::vector<std::vector<DataType>> norm_a(a.size(), std::vector<DataType>(a[0].size(), 0));
	DataType aij, k;

	std::vector<DataType> square(a.size(), 0);

	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 1; j < a[0].size(); ++j) {
			aij = a[i][j];
			square[i] += aij * aij;
		}
	}

	for (size_t i = 0; i < a.size(); ++i) {
		k = 1.0 / sqrt(square[i]);
		for (size_t j = 0; j < a[0].size(); ++j) {
			norm_a[i][j] = k * a[i][j];
		}
	}
}
template <typename DataType>
Test MatrixSquareNormalizeTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixNormalize" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixSquareNormalize<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixSquareNormalizeTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixSquareNormalizeTest<Posit16>(a));
  test.AddTest(MatrixSquareNormalizeTest<Posit32>(a));
  test.AddTest(MatrixSquareNormalizeTest<bfloat16>(a));
  test.AddTest(MatrixSquareNormalizeTest<Float32>(a));
  test.AddTest(MatrixSquareNormalizeTest<float>(a));
}

template <typename DataType>
void InvokeMatrixSquareNormalize(const std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixSquareNormalize<DataType>(a);
}

void InvokeMatrixSquareNormalizeTest(size_t x, size_t y) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(x, y);
  InvokeMatrixSquareNormalize<Posit16>(a);
  InvokeMatrixSquareNormalize<Posit32>(a);
  InvokeMatrixSquareNormalize<bfloat16>(a);
  InvokeMatrixSquareNormalize<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Normalize");
  CreateMatrixSquareNormalizeTest(test, 5);
  CreateMatrixSquareNormalizeTest(test, 10);
  CreateMatrixSquareNormalizeTest(test, 25);
  CreateMatrixSquareNormalizeTest(test, 50);
  CreateMatrixSquareNormalizeTest(test, 100);
  CreateMatrixSquareNormalizeTest(test, 150);
  CreateMatrixSquareNormalizeTest(test, 200);
  CreateMatrixSquareNormalizeTest(test, 250);
  CreateMatrixSquareNormalizeTest(test, 500);
  CreateMatrixSquareNormalizeTest(test, 750);
  CreateMatrixSquareNormalizeTest(test, 1000);
  CreateMatrixSquareNormalizeTest(test, 1500);
  CreateMatrixSquareNormalizeTest(test, 2000);
  CreateMatrixSquareNormalizeTest(test, 2500);
  return test;
}

TestSet CreatePositTestSet() {
  TestSet test("Matrix Normalize");
  CreateMatrixSquareNormalizeTest(test, 100);
  CreateMatrixSquareNormalizeTest(test, 250);
  CreateMatrixSquareNormalizeTest(test, 500);
  return test;
}
}
}

