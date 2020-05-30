#pragma once
#include "test_type.h"
#include "bench_math.h"
namespace benchmark {
namespace test_matrix_qr_decomposition {
template <typename DataType>
std::vector<std::vector<DataType>> MatrixMult(const std::vector<std::vector<DataType>>& a, const std::vector<std::vector<DataType>>& b) {
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
std::vector<std::vector<DataType>> MatrixTranspose(std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	std::vector<std::vector<DataType>> trans_a(a.size(), std::vector<DataType>(a[0].size(), 0));
	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < a[0].size(); ++j)
			trans_a[j][i] = a[i][j];
	return trans_a;
}

template <typename DataType>
std::vector<std::vector<DataType>> HouseholderFactor(const std::vector<DataType>& v)
{
	std::vector<std::vector<DataType>> a(v.size(), std::vector<DataType>(v.size(), 0));
	for (size_t i = 0; i < v.size(); ++i)
		for (size_t j = 0; j < v.size(); ++j)
			a[i][j] = DataType(-2) * v[i] * v[j];
	for (size_t i = 0; i < v.size(); ++i)
		a[i][i] += 1;
	return a;
}

// L2-norm ||A-B||^2
template <typename DataType>
DataType CompareMatrix(const std::vector<std::vector<DataType>>& a, std::vector<std::vector<DataType>>& b) {
	if (a.size() == 0 || b.size() == 0) return 0.0;
	if (a.size() != b.size() or a[0].size() != b[0].size())
		return std::numeric_limits<DataType>::max();

	DataType res = 0;
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 0; j < a[0].size(); ++j) {
			res += (a[i][j] - b[i][j]) * (a[i][j] - b[i][j]);
		}
	}

	res /= a.size() * a[0].size();
	return res;
}

template <typename DataType>
std::vector<std::vector<DataType>> MatrixMinor(const std::vector<std::vector<DataType>>& a, size_t d) {

	std::vector<std::vector<DataType>> b(a.size(), std::vector<DataType>(a[0].size(), 0));

	for (size_t i = 0; i < d; ++i)
		b[i][i] = 1.0;
	for (size_t i = d; i < a.size(); ++i)
		for (size_t j = d; j < a[0].size(); ++j)
			b[i][j] = a[i][j];

	return b;
}

template <typename DataType>
DataType VectorNorm(std::vector<DataType>& v) {
	DataType sum = 0;
	for (size_t i = 0; i < v.size(); ++i)
		sum += v[i] * v[i];
	return sqrt(sum);
}

template <typename DataType>
void VmAdd(const std::vector<DataType>& a, const std::vector<DataType>& b, DataType& s, std::vector<DataType>& c) {
	assert(c.size() == a.size() and c.size() == b.size());
	for (size_t i = 0; i < c.size(); ++i)
		c[i] = a[i] + s * b[i];
}

template <typename DataType>
void MatrixQRDecomposition(const std::vector<std::vector<DataType>>& a) {
	assert(a.size() > 0 && a[0].size() > 0);
	assert(a.size() == a[0].size());
	std::vector<std::vector<DataType>> q(a.size(), std::vector<DataType>(a[0].size(), 0));
	std::vector<std::vector<DataType>> r(a.size(), std::vector<DataType>(a[0].size(), 0));

	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < a[0].size(); ++j)
			q[i][j] = a[i][j];

	int m = a.size();
	int n = a[0].size();

	std::vector<std::vector<std::vector<DataType>>> qv(m);
	std::vector<std::vector<DataType>> z(a);
	std::vector<std::vector<DataType>> z1;

	for (size_t k = 0; k < n && k < m - 1; ++k) {
		std::vector<DataType> e(m), x(m);
		DataType c;

		z1 = MatrixMinor(z, k);
		x = z1[k];
		c = VectorNorm(x);
		if (a[k][k] > DataType(0)) c = -c;

		for (size_t i = 0; i < e.size(); ++i)
			e[i] = (i == k) ? 1.0 : 0.0;

		VmAdd(x, e, c, e);
		qv[k] = HouseholderFactor(e);
		z = MatrixMult(qv[k], z1);

	}

	q = qv[0];

	for (int i = 1; i < n && i < m - 1; ++i) {

		z1 = MatrixMult(qv[i], q);
		q = z1;

	}

	r = MatrixMult(q, a);
	MatrixTranspose(q);
}
template <typename DataType>
Test MatrixQRDecompositionTest(const std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  auto name = "MatrixQR" + std::to_string(a.size()) + "x" + std::to_string(a.front().size());
  return Test(name, [a](){MatrixQRDecomposition<DataType>(a);}, format_type<DataType>::format_name);
}

void CreateMatrixQRDecompositionTest(TestSet& test, size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  test.AddTest(MatrixQRDecompositionTest<Posit16>(a));
  test.AddTest(MatrixQRDecompositionTest<Posit32>(a));
  test.AddTest(MatrixQRDecompositionTest<bfloat16>(a));
  test.AddTest(MatrixQRDecompositionTest<Float32>(a));
  test.AddTest(MatrixQRDecompositionTest<float>(a));
}

template <typename DataType>
void InvokeMatrixQRDecomposition(const std::vector<std::vector<float>>& A) {
  std::vector<std::vector<DataType>> a(A.size(), std::vector<DataType>(A.front().size(), 0.0));
  for (size_t i = 0; i < A.size(); ++i) {
    for (size_t j = 0; j < A[i].size(); ++j) {
      a[i][j] = A[i][j];
    }
  }
  MatrixQRDecomposition<DataType>(a);
}

void InvokeMatrixQRDecompositionTest(size_t size) {
  std::vector<std::vector<float>> a = generator.GetRandomMatrix<float>(size, size);
  InvokeMatrixQRDecomposition<Posit16>(a);
  InvokeMatrixQRDecomposition<Posit32>(a);
  InvokeMatrixQRDecomposition<bfloat16>(a);
  InvokeMatrixQRDecomposition<Float32>(a);
}

TestSet CreateTestSet() {
  TestSet test("Matrix QR Decomposition");
  CreateMatrixQRDecompositionTest(test, 5);
  CreateMatrixQRDecompositionTest(test, 10);
  CreateMatrixQRDecompositionTest(test, 25);
  CreateMatrixQRDecompositionTest(test, 50);
  CreateMatrixQRDecompositionTest(test, 100);
  CreateMatrixQRDecompositionTest(test, 250);
  CreateMatrixQRDecompositionTest(test, 500);
  return test;
}
}
}
