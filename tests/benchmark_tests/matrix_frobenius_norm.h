#pragma once
#include "test_type.h"
#include "bench_math.h"
namespace benchmark {
namespace test_matrix_frobenius_norm {

template <typename DataType>
DataType MatrixFrobeniusNorm(const std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	DataType norm = 0.0;
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 0; j < a[0].size(); ++j) {
			norm += pow(a[i][j], DataType(2));
		}
	}
	return sqrt(norm);
}

template <typename DataType>
Test MatrixFrobeniusNormTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixFrobenius" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixFrobeniusNorm<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixFrobeniusNormTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixFrobeniusNormTest<Posit16>(a));
  test.AddTest(MatrixFrobeniusNormTest<Posit32>(a));
  test.AddTest(MatrixFrobeniusNormTest<bfloat16>(a));
  test.AddTest(MatrixFrobeniusNormTest<Float32>(a));
  test.AddTest(MatrixFrobeniusNormTest<float>(a));
}

template <typename DataType>
void InvokeMatrixFrobeniusNorm(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixFrobeniusNorm<DataType>(a);
}

void InvokeMatrixFrobeniusNormTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  MatrixFrobeniusNormTest<Posit16>(a);
  MatrixFrobeniusNormTest<Posit32>(a);
  MatrixFrobeniusNormTest<bfloat16>(a);
  MatrixFrobeniusNormTest<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Frobenius Norm");
  CreateMatrixFrobeniusNormTest(test, 5);
  CreateMatrixFrobeniusNormTest(test, 10);
  CreateMatrixFrobeniusNormTest(test, 25);
  CreateMatrixFrobeniusNormTest(test, 50);
  CreateMatrixFrobeniusNormTest(test, 100);
  CreateMatrixFrobeniusNormTest(test, 150);
  CreateMatrixFrobeniusNormTest(test, 200);
  CreateMatrixFrobeniusNormTest(test, 250);
  CreateMatrixFrobeniusNormTest(test, 500);
  CreateMatrixFrobeniusNormTest(test, 750);
  CreateMatrixFrobeniusNormTest(test, 1000);
  CreateMatrixFrobeniusNormTest(test, 1500);
  CreateMatrixFrobeniusNormTest(test, 2000);
  CreateMatrixFrobeniusNormTest(test, 2500);
  return test;
}

}
}
