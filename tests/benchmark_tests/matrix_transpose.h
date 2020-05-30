#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_transpose {

template <typename DataType>
std::vector<std::vector<DataType>> MatrixTranspose(const std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	std::vector<std::vector<DataType>> trans_a(a.size(), std::vector<DataType>(a[0].size(), 0));
	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < a[0].size(); ++j)
			trans_a[j][i] = a[i][j];
	return trans_a;
}

template <typename DataType>
Test MatrixTransposeTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixTranspose" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixTranspose<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixTransposeTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixTransposeTest<Posit16>(a));
  test.AddTest(MatrixTransposeTest<Posit32>(a));
  test.AddTest(MatrixTransposeTest<bfloat16>(a));
  test.AddTest(MatrixTransposeTest<Float32>(a));
  test.AddTest(MatrixTransposeTest<float>(a));
}

template <typename DataType>
void InvokeMatrixTranspose(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixTranspose<DataType>(a);
}

void InvokeMatrixTransposeTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  InvokeMatrixTranspose<Posit16>(a);
  InvokeMatrixTranspose<Posit32>(a);
  InvokeMatrixTranspose<bfloat16>(a);
  InvokeMatrixTranspose<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Transpose");
  CreateMatrixTransposeTest(test, 5);
  CreateMatrixTransposeTest(test, 50);
  CreateMatrixTransposeTest(test, 100);
  CreateMatrixTransposeTest(test, 200);
  CreateMatrixTransposeTest(test, 250);
  CreateMatrixTransposeTest(test, 500);
  CreateMatrixTransposeTest(test, 1000);
  CreateMatrixTransposeTest(test, 1500);
  return test;
}
}
}
