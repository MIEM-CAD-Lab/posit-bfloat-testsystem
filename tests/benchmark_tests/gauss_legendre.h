#pragma once
#include "test_type.h"
#include "bench_math.h"
namespace benchmark {
namespace test_gauss_legendre {

template <typename DataType>
DataType GaussLegendre(size_t n) {
	DataType next_a, a = 1.0f;
	DataType next_b, b = 1.0f / sqrt(2);
	DataType next_tt, t = 1.0f / 4.0f;
	DataType next_p, p = 1.0f;

	for (int i = 0; i < n; ++i) {
	    auto div = DataType(2.0);
		next_a = (a + b) / div;
		next_b = sqrt(a * b);
		next_tt = t - p * DataType(pow(a - next_a, DataType(2.0)));
		next_p = DataType(2.0) * p;
		a = next_a;
		b = next_b;
		t = next_tt;
		p = next_p;
	}
	return DataType(pow(a + b, DataType(2))) / (DataType(4) * t);
}

template <typename DataType>
Test GaussLegendreTest(size_t size) {
  auto name = "GaussLegendre" + std::to_string(size);
  return Test(name, [size](){GaussLegendre<DataType>(size);}, format_type<DataType>::format_name);
}

void  CreateGaussLegendreTest(TestSet& test, size_t size) {
  test.AddTest(GaussLegendreTest<Posit16>(size));
  test.AddTest(GaussLegendreTest<Posit32>(size));
  test.AddTest(GaussLegendreTest<bfloat16>(size));
  test.AddTest(GaussLegendreTest<Float32>(size));
  test.AddTest(GaussLegendreTest<float>(size));
}

template <typename DataType>
void InvokeGaussLegendre(size_t size) {
  GaussLegendre<DataType>(size);
}

void InvokeGaussLegendreTest(size_t size) {
  InvokeGaussLegendre<Posit16>(size);
  InvokeGaussLegendre<Posit32>(size);
  InvokeGaussLegendre<bfloat16>(size);
  InvokeGaussLegendre<Float32>(size);
}

TestSet CreateTestSet() {
  TestSet test("Gauss Legendre");
  CreateGaussLegendreTest(test, 10);
  CreateGaussLegendreTest(test, 100);
  CreateGaussLegendreTest(test, 1000);
  CreateGaussLegendreTest(test, 10000);
  CreateGaussLegendreTest(test, 100000);
  CreateGaussLegendreTest(test, 1000000);
  CreateGaussLegendreTest(test, 10000000);
  CreateGaussLegendreTest(test, 100000000);
  CreateGaussLegendreTest(test, 1000000000);
  return test;
}

}
}

