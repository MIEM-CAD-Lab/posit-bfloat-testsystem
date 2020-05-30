#pragma once
#include "test_type.h"
namespace benchmark {
namespace basic_test {

template <typename DataType>
DataType Sum(DataType x1, DataType x2) {
  return x1 + x2;
}

template <typename DataType>
DataType Sub(DataType x1, DataType x2) {
  return x1 - x2;
}

template <typename DataType>
DataType Mul(DataType x1, DataType x2) {
  return x1 * x2;
}

template <typename DataType>
DataType Div(DataType x1, DataType x2) {
  return x1 / x2;
}

template <typename DataType>
DataType SumN(DataType main, const std::vector<DataType>& numbers) {
  for (const auto curr : numbers) {
    main += curr;
  }
  return main;
}

template <typename DataType>
DataType SubN(DataType main, const std::vector<DataType>& numbers) {
  for (const auto curr : numbers) {
    main -= curr;
  }
  return main;
}

template <typename DataType>
DataType MulN(DataType main, const std::vector<DataType>& numbers) {
  for (const auto curr : numbers) {
    main *= curr;
  }
  return main;
}

template <typename DataType>
DataType DivN(DataType main, const std::vector<DataType>& numbers) {
  for (const auto curr : numbers) {
    main /= curr;
  }
  return main;
}

template <typename DataType>
Test SumTest(float x1, float x2) {
  DataType a = x1, b = x2;
  return Test("Sum", [a, b](){Sum<DataType>(a, b);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test SubTest(float x1, float x2) {
  DataType a = x1, b = x2;
  return Test("Sub", [a, b](){Sub<DataType>(a, b);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test MulTest(float x1, float x2) {
  DataType a = x1, b = x2;
  return Test("Mul", [a, b](){Mul<DataType>(a, b);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test DivTest(float x1, float x2) {
  DataType a = x1, b = x2;
  return Test("Div", [a, b](){Div<DataType>(a, b);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test SumNTest(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  std::string name = "Sum" + std::to_string(res.size());
  return Test(name, [d_main, res](){SumN<DataType>(d_main, res);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test SubNTest(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  std::string name = "Sub" + std::to_string(res.size());
  return Test(name, [d_main, res](){SubN<DataType>(d_main, res);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test MulNTest(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  std::string name = "Mul" + std::to_string(res.size());
  return Test(name, [d_main, res](){MulN<DataType>(d_main, res);}, format_type<DataType>::format_name);
}

template <typename DataType>
Test DivNTest(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  std::string name = "Div" + std::to_string(res.size());
  return Test(name, [d_main, res](){DivN<DataType>(d_main, res);}, format_type<DataType>::format_name);
}

void CreateSumTest(TestSet& test) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  test.AddTest(SumTest<Posit16>(a, b));
  test.AddTest(SumTest<Posit32>(a, b));
  test.AddTest(SumTest<bfloat16>(a, b));
  test.AddTest(SumTest<Float32>(a, b));
  test.AddTest(SumTest<float>(a, b));
}

void CreateSubTest(TestSet& test) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  test.AddTest(SubTest<Posit16>(a, b));
  test.AddTest(SubTest<Posit32>(a, b));
  test.AddTest(SubTest<bfloat16>(a, b));
  test.AddTest(SubTest<Float32>(a, b));
  test.AddTest(SubTest<float>(a, b));
}

void CreateMulTest(TestSet& test) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  test.AddTest(MulTest<Posit16>(a, b));
  test.AddTest(MulTest<Posit32>(a, b));
  test.AddTest(MulTest<bfloat16>(a, b));
  test.AddTest(MulTest<Float32>(a, b));
  test.AddTest(MulTest<float>(a, b));
}

void CreateDivTest(TestSet& test) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  test.AddTest(DivTest<Posit16>(a, b));
  test.AddTest(DivTest<Posit32>(a, b));
  test.AddTest(DivTest<bfloat16>(a, b));
  test.AddTest(DivTest<Float32>(a, b));
  test.AddTest(DivTest<float>(a, b));
}

void CreateSumNTest(TestSet& test, size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  test.AddTest(SumNTest<Posit16>(main, numbers));
  test.AddTest(SumNTest<Posit32>(main, numbers));
  test.AddTest(SumNTest<bfloat16>(main, numbers));
  test.AddTest(SumNTest<Float32>(main, numbers));
  test.AddTest(SumNTest<float>(main, numbers));
}

void CreateSubNTest(TestSet& test, size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  test.AddTest(SubNTest<Posit16>(main, numbers));
  test.AddTest(SubNTest<Posit32>(main, numbers));
  test.AddTest(SubNTest<bfloat16>(main, numbers));
  test.AddTest(SubNTest<Float32>(main, numbers));
  test.AddTest(SubNTest<float>(main, numbers));
}

void CreateMulNTest(TestSet& test, size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  test.AddTest(MulNTest<Posit16>(main, numbers));
  test.AddTest(MulNTest<Posit32>(main, numbers));
  test.AddTest(MulNTest<bfloat16>(main, numbers));
  test.AddTest(MulNTest<Float32>(main, numbers));
  test.AddTest(MulNTest<float>(main, numbers));
}

void CreateDivNTest(TestSet& test, size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  test.AddTest(DivNTest<Posit16>(main, numbers));
  test.AddTest(DivNTest<Posit32>(main, numbers));
  test.AddTest(DivNTest<bfloat16>(main, numbers));
  test.AddTest(DivNTest<Float32>(main, numbers));
  test.AddTest(DivNTest<float>(main, numbers));
}

template <typename DataType>
void InvokeSum(float x1, float x2) {
  DataType a = x1, b = x2;
  Sum<DataType>(a, b);
}

template <typename DataType>
void InvokeSub(float x1, float x2) {
  DataType a = x1, b = x2;
  Sub<DataType>(a, b);
}

template <typename DataType>
void InvokeMul(float x1, float x2) {
  DataType a = x1, b = x2;
  Mul<DataType>(a, b);
}

template <typename DataType>
void InvokeDiv(float x1, float x2) {
  DataType a = x1, b = x2;
  Div<DataType>(a, b);
}

template <typename DataType>
void InvokeSumN(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  SumN<DataType>(d_main, res);
}

template <typename DataType>
void InvokeSubN(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  SubN<DataType>(d_main, res);
}

template <typename DataType>
void InvokeMulN(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  MulN<DataType>(d_main, res);
}

template <typename DataType>
void InvokeDivN(float main, const std::vector<float>& numbers) {
  DataType d_main = main;
  std::vector<DataType> res;
  res.reserve(numbers.size());
  for (const auto curr : numbers) {
    res.emplace_back(curr);
  }
  DivN<DataType>(d_main, res);
}

void InvokeSumTest() {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  InvokeSum<Posit16>(a, b);
  InvokeSum<Posit32>(a, b);
  InvokeSum<bfloat16>(a, b);
  InvokeSum<Float32>(a, b);
}

void InvokeSubTest() {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  InvokeSub<Posit16>(a, b);
  InvokeSub<Posit32>(a, b);
  InvokeSub<bfloat16>(a, b);
  InvokeSub<Float32>(a, b);
}

void InvokeMulTest() {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  InvokeMul<Posit16>(a, b);
  InvokeMul<Posit32>(a, b);
  InvokeMul<bfloat16>(a, b);
  InvokeMul<Float32>(a, b);
}

void InvokeDivTest() {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  InvokeDiv<Posit16>(a, b);
  InvokeDiv<Posit32>(a, b);
  InvokeDiv<bfloat16>(a, b);
  InvokeDiv<Float32>(a, b);
}

void InvokeSumNTest(size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  InvokeSumN<Posit16>(main, numbers);
  InvokeSumN<Posit32>(main, numbers);
  InvokeSumN<bfloat16>(main, numbers);
  InvokeSumN<Float32>(main, numbers);
}

void InvokeSubNTest(size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  InvokeSumN<Posit16>(main, numbers);
  InvokeSumN<Posit32>(main, numbers);
  InvokeSumN<bfloat16>(main, numbers);
  InvokeSumN<Float32>(main, numbers);
}

void InvokeMulNTest(size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  InvokeSumN<Posit16>(main, numbers);
  InvokeSumN<Posit32>(main, numbers);
  InvokeSumN<bfloat16>(main, numbers);
  InvokeSumN<Float32>(main, numbers);
}

void InvokeDivNTest(size_t size) {
  float main = generator.GetRandomFloat();
  std::vector<float> numbers = generator.GetRandomVector<float>(size);
  InvokeSumN<Posit16>(main, numbers);
  InvokeSumN<Posit32>(main, numbers);
  InvokeSumN<bfloat16>(main, numbers);
  InvokeSumN<Float32>(main, numbers);
}

TestSet CreateTestSet() {
  TestSet test("Basic operation");
  CreateSumTest(test);
  CreateSubTest(test);
  CreateMulTest(test);
  CreateDivTest(test);

  CreateSumNTest(test, 5);
  CreateSumNTest(test, 10);
  CreateSumNTest(test, 15);
  CreateSumNTest(test, 25);
  CreateSumNTest(test, 50);
  CreateSumNTest(test, 100);
  CreateSumNTest(test, 150);
  CreateSumNTest(test, 200);
  CreateSumNTest(test, 250);
  CreateSumNTest(test, 500);
  CreateSumNTest(test, 750);
  CreateSumNTest(test, 1000);

  CreateSubNTest(test, 5);
  CreateSubNTest(test, 10);
  CreateSubNTest(test, 15);
  CreateSubNTest(test, 25);
  CreateSubNTest(test, 50);
  CreateSubNTest(test, 100);
  CreateSubNTest(test, 150);
  CreateSubNTest(test, 200);
  CreateSubNTest(test, 250);
  CreateSubNTest(test, 500);
  CreateSubNTest(test, 750);
  CreateSubNTest(test, 1000);

  CreateMulNTest(test, 5);
  CreateMulNTest(test, 10);
  CreateMulNTest(test, 15);
  CreateMulNTest(test, 25);
  CreateMulNTest(test, 50);
  CreateMulNTest(test, 100);
  CreateMulNTest(test, 150);
  CreateMulNTest(test, 200);
  CreateMulNTest(test, 250);
  CreateMulNTest(test, 500);
  CreateMulNTest(test, 750);
  CreateMulNTest(test, 1000);

  CreateDivNTest(test, 5);
  CreateDivNTest(test, 10);
  CreateDivNTest(test, 15);
  CreateDivNTest(test, 25);
  CreateDivNTest(test, 50);
  CreateDivNTest(test, 100);
  CreateDivNTest(test, 150);
  CreateDivNTest(test, 200);
  CreateDivNTest(test, 250);
  CreateDivNTest(test, 500);
  CreateDivNTest(test, 750);
  CreateDivNTest(test, 1000);
  return test;
}

TestSet CreatePositTestSet() {
  TestSet test("Basic operation");
  CreateSumTest(test);
  CreateSubTest(test);
  CreateMulTest(test);
  CreateDivTest(test);
  CreateSumNTest(test, 10);
  CreateSumNTest(test, 50);
  CreateSumNTest(test, 100);
  CreateSumNTest(test, 150);
  CreateSubNTest(test, 10);
  CreateSubNTest(test, 50);
  CreateSubNTest(test, 100);
  CreateSubNTest(test, 150);
  CreateMulNTest(test, 10);
  CreateMulNTest(test, 50);
  CreateMulNTest(test, 100);
  CreateMulNTest(test, 150);
  CreateDivNTest(test, 10);
  CreateDivNTest(test, 50);
  CreateDivNTest(test, 100);
  CreateDivNTest(test, 150);
  return test;
}

}
}

