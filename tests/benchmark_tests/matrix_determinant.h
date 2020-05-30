#pragma once
#include "test_type.h"
namespace benchmark {
namespace test_matrix_determinant {

template <typename DataType>
DataType MatrixDeterminant(const std::vector<std::vector<DataType>>& a) {
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
Test MatrixDeterminantTest(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixDeterminant" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixDeterminant<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixDeterminantTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixDeterminantTest<Posit16>(a));
  test.AddTest(MatrixDeterminantTest<Posit32>(a));
  test.AddTest(MatrixDeterminantTest<bfloat16>(a));
  test.AddTest(MatrixDeterminantTest<Float32>(a));
  test.AddTest(MatrixDeterminantTest<float>(a));
}

template <typename DataType>
void InvokeMatrixDeterminant(std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixDeterminant<DataType>(a);
}

void InvokeMatrixDeterminantTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  MatrixDeterminantTest<Posit16>(a);
  MatrixDeterminantTest<Posit32>(a);
  MatrixDeterminantTest<bfloat16>(a);
  MatrixDeterminantTest<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix Determinant");
  CreateMatrixDeterminantTest(test, 5);
  CreateMatrixDeterminantTest(test, 8);
  CreateMatrixDeterminantTest(test, 9);
  CreateMatrixDeterminantTest(test, 10);
  CreateMatrixDeterminantTest(test, 11);
  CreateMatrixDeterminantTest(test, 12);
  return test;
}

TestSet CreatePositTestSet() {
  TestSet test("Matrix Determinant");
  CreateMatrixDeterminantTest(test, 5);
  CreateMatrixDeterminantTest(test, 6);
  CreateMatrixDeterminantTest(test, 7);
  CreateMatrixDeterminantTest(test, 8);
  return test;
}
}
}

