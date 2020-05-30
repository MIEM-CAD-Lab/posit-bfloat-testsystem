#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_sum_sub {
template <typename DataType>
std::vector<std::vector<DataType>> MatrixSumSub(const std::vector<std::vector<DataType>>& a, const std::vector<std::vector<DataType>>& b, bool sign) {
	assert(a.size() > 0 && a[0].size() > 0 && b.size() > 0 && b[0].size() > 0);
	assert(a.size() == b.size() && a[0].size() == b[0].size());
	int row = a.size();
	int col = a[0].size();
	std::vector<std::vector<DataType>> c(row, std::vector<DataType>(col, 0));
	for (size_t i = 0; i < row; ++i)
	{
		for (size_t j = 0; j < col; ++j)
		{
			if (sign)
				c[i][j] = a[i][j] + b[i][j];
			else 
				c[i][j] = a[i][j] - b[i][j];
		}
	}
	return c;
}
template <typename DataType>
Test MatrixSumSubTest(const std::vector<std::vector<float >>& A, const std::vector<std::vector<float >>& B, bool sign) {
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
  std::string sign_name = sign ? "Sum" : "Sub";
  auto name = sign_name + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a, b, sign](){MatrixSumSub<DataType>(a, b, sign);}, format_type<DataType>::format_name);
}
void CreateMatrixSumSubTest(TestSet& test, size_t size, bool sign) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  std::vector<std::vector<float>> b = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixSumSubTest<Posit16>(a, b, sign));
  test.AddTest(MatrixSumSubTest<Posit32>(a, b, sign));
  test.AddTest(MatrixSumSubTest<bfloat16>(a, b, sign));
  test.AddTest(MatrixSumSubTest<Float32>(a, b, sign));
  test.AddTest(MatrixSumSubTest<float>(a, b, sign));
}

template <typename DataType>
void InvokeMatrixSumSub(const std::vector<std::vector<float >>& A, const std::vector<std::vector<float >>& B, bool sign) {
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
  MatrixSumSub<DataType>(a, b, sign);
}

void InvokeMatrixSumSubTest(size_t size, bool sign) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  std::vector<std::vector<float>> b = generator.GetRandomMatrix<float>(size, size);
  InvokeMatrixSumSub<Posit16>(a, b, sign);
  InvokeMatrixSumSub<Posit32>(a, b, sign);
  InvokeMatrixSumSub<bfloat16>(a, b, sign);
  InvokeMatrixSumSub<Float32>(a, b, sign);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Sum and Sub");
  CreateMatrixSumSubTest(test, 10, true);
  CreateMatrixSumSubTest(test, 50, true);
  CreateMatrixSumSubTest(test, 100, true);
  CreateMatrixSumSubTest(test, 250, true);
  CreateMatrixSumSubTest(test, 500, true);
  CreateMatrixSumSubTest(test, 1000, true);
  CreateMatrixSumSubTest(test, 1500, true);
  CreateMatrixSumSubTest(test, 2000, true);
  CreateMatrixSumSubTest(test, 10, false);
  CreateMatrixSumSubTest(test, 50, false);
  CreateMatrixSumSubTest(test, 100, false);
  CreateMatrixSumSubTest(test, 250, false);
  CreateMatrixSumSubTest(test, 500, false);
  CreateMatrixSumSubTest(test, 1000, false);
  CreateMatrixSumSubTest(test, 1500, false);
  CreateMatrixSumSubTest(test, 2000, false);
  return test;
}

TestSet CreatePositTestSet() {
  TestSet test("Matrix Sum and Sub");
  CreateMatrixSumSubTest(test, 10, true);
  CreateMatrixSumSubTest(test, 50, true);
  CreateMatrixSumSubTest(test, 100, true);
  CreateMatrixSumSubTest(test, 250, true);
  CreateMatrixSumSubTest(test, 500, true);
  CreateMatrixSumSubTest(test, 10, false);
  CreateMatrixSumSubTest(test, 50, false);
  CreateMatrixSumSubTest(test, 100, false);
  CreateMatrixSumSubTest(test, 250, false);
  CreateMatrixSumSubTest(test, 500, false);
  return test;
}
}
}
