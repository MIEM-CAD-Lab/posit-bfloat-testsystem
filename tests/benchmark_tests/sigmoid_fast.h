#pragma once
#include "test_type.h"
#include "bench_math.h"
namespace benchmark {
namespace test_sigmoid_fast {

template <typename DataType>
DataType SigmoidFast(DataType x) {
	return x / (DataType(1) + abs(x));
}

template <typename DataType>
Test SigmoidFastTest(int size) {
  auto name = "SigmoidFast" + std::to_string(size);
  return Test(name, [size](){SigmoidFast<DataType>(float(size));}, format_type<DataType>::format_name);
}

void CreateSigmoidFastTest(TestSet& test, size_t size) {
  test.AddTest(SigmoidFastTest<Posit16>(size));
  test.AddTest(SigmoidFastTest<Posit32>(size));
  test.AddTest(SigmoidFastTest<bfloat16>(size));
  test.AddTest(SigmoidFastTest<Float32>(size));
  test.AddTest(SigmoidFastTest<float>(size));
}

template <typename DataType>
void InvokeSigmoidFast(int size) {
  SigmoidFast<DataType>(size);
}

void InvokeSigmoidFastTest(int size) {
  InvokeSigmoidFast<Posit16>(size);
  InvokeSigmoidFast<Posit32>(size);
  InvokeSigmoidFast<bfloat16>(size);
  InvokeSigmoidFast<Float32>(size);
}

TestSet CreateTestSet() {
  TestSet test("Sigmoid");
  CreateSigmoidFastTest(test, 1);
  CreateSigmoidFastTest(test, 10);
  CreateSigmoidFastTest(test, 100);
  CreateSigmoidFastTest(test, 1000);
  CreateSigmoidFastTest(test, 10000);
  CreateSigmoidFastTest(test, 100000);
  CreateSigmoidFastTest(test, 1000000);
  CreateSigmoidFastTest(test, 10000000);
  CreateSigmoidFastTest(test, 100000000);
  return test;
}
}
}
