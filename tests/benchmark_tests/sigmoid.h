#pragma once
#include "test_type.h"
#include "bench_math.h"
namespace benchmark {
namespace test_sigmoid {

template <typename DataType>
DataType Sigmoid(int t) {
	return 1 / (1 + exp(-t));
}

template <typename DataType>
Test SigmoidTest(int size) {
  auto name = "Sigmoid" + std::to_string(size);
  return Test(name, [size](){Sigmoid<DataType>(size);}, format_type<DataType>::format_name);
}

void CreateSigmoidTest(TestSet& test, size_t size) {
  test.AddTest(SigmoidTest<Posit16>(size));
  test.AddTest(SigmoidTest<Posit32>(size));
  test.AddTest(SigmoidTest<bfloat16>(size));
  test.AddTest(SigmoidTest<Float32>(size));
  test.AddTest(SigmoidTest<float>(size));
}

template <typename DataType>
void InvokeSigmoid(int size) {
  Sigmoid<DataType>(size);
}

void InvokeSigmoidTest(int size) {
  InvokeSigmoid<Posit16>(size);
  InvokeSigmoid<Posit32>(size);
  InvokeSigmoid<bfloat16>(size);
  InvokeSigmoid<Float32>(size);
}

TestSet CreateTestSet() {
  TestSet test("Sigmoid");
  CreateSigmoidTest(test, 1);
  CreateSigmoidTest(test, 10);
  CreateSigmoidTest(test, 100);
  CreateSigmoidTest(test, 1000);
  CreateSigmoidTest(test, 10000);
  CreateSigmoidTest(test, 100000);
  CreateSigmoidTest(test, 1000000);
  CreateSigmoidTest(test, 10000000);
  CreateSigmoidTest(test, 100000000);
  return test;
}
}
}

