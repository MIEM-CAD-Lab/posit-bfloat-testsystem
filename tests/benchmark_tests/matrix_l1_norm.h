#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_l1_norm {

template <typename DataType>
DataType MatrixL1Norm(const std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	DataType norm = 0.0;
	for (size_t j = 0; j < a[0].size(); ++j)
	{
		DataType current = 0.0; 
		for (size_t i = 0; i < a.size(); ++i)
			current += abs(a[i][j]);
		if (current > norm) 
			norm = current;
	}
	return norm;
}

template <typename DataType>
Test MatrixL1NormTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixL1" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixL1Norm<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixL1NormTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixL1NormTest<Posit16>(a));
  test.AddTest(MatrixL1NormTest<Posit32>(a));
  test.AddTest(MatrixL1NormTest<bfloat16>(a));
  test.AddTest(MatrixL1NormTest<Float32>(a));
  test.AddTest(MatrixL1NormTest<float>(a));
}

template <typename DataType>
void InvokeMatrixL1Norm(const std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixL1Norm<DataType>(a);
}

void InvokeMatrixL1NormTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  InvokeMatrixL1Norm<Posit16>(a);
  InvokeMatrixL1Norm<Posit32>(a);
  InvokeMatrixL1Norm<bfloat16>(a);
  InvokeMatrixL1Norm<Float32>(a);
  InvokeMatrixL1Norm<float>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix L1 Norm");
  CreateMatrixL1NormTest(test, 5);
  CreateMatrixL1NormTest(test, 10);
  CreateMatrixL1NormTest(test, 25);
  CreateMatrixL1NormTest(test, 50);
  CreateMatrixL1NormTest(test, 100);
  CreateMatrixL1NormTest(test, 150);
  CreateMatrixL1NormTest(test, 200);
  CreateMatrixL1NormTest(test, 250);
  CreateMatrixL1NormTest(test, 500);
  CreateMatrixL1NormTest(test, 750);
  CreateMatrixL1NormTest(test, 1000);
  CreateMatrixL1NormTest(test, 1500);
  CreateMatrixL1NormTest(test, 2000);
  CreateMatrixL1NormTest(test, 2500);
  return test;
}
}
}

