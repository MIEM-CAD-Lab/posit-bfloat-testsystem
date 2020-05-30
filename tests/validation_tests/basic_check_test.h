#pragma once
#include <gtest/gtest.h>
#include "../test_type.h"
#include "../benchmark_tests/basic_test.h"
namespace validation {
namespace basic_check_test {
// Пример полностью ручного теста
TEST(BasicTestPosit16, Test1){
  Posit16 a = 1.0, b = 2.0;
  float c = 1.0, d = 2.0;
  // Не останавливает программу
  EXPECT_EQ(a + b, c + d);
  // Останавливает программу
  Posit16 res_p = a + b;
  float res_f = c + d;
  EXPECT_FLOAT_EQ(c + d, float(a + b));
  ASSERT_FLOAT_EQ(res_f, float(res_p));
}

TEST(SumTest, TestPosit16) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  auto res_float = benchmark::basic_test::Sum<float>(a, b);
  auto res = benchmark::basic_test::Sum<Posit16>(a, b);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(SumTest, TestPosit32) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  auto res_float = benchmark::basic_test::Sum<float>(a, b);
  auto res = benchmark::basic_test::Sum<Posit32>(a, b);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(SumTest, TestBfloat16) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  auto res_float = benchmark::basic_test::Sum<float>(a, b);
  auto res = benchmark::basic_test::Sum<bfloat16>(a, b);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(SumTest, TestFloat32) {
  float a = generator.GetRandomFloat();
  float b = generator.GetRandomFloat();
  auto res_float = benchmark::basic_test::Sum<float>(a, b);
  auto res = benchmark::basic_test::Sum<Float32>(a, b);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(SumTest, TestFloat32_1) {
  float a = 130.532;
  float b = 130.7245;
  auto res_float = benchmark::basic_test::Sum<float>(a, b);
  auto res = benchmark::basic_test::Sum<Float32>(a, b);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(SumTest, TestFloat32_2) {
  float a = 150.532;
  float b = -130.4512;
  auto res_float = benchmark::basic_test::Sum<float>(a, b);
  auto res = benchmark::basic_test::Sum<Float32>(a, b);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

template <typename DataType>
DataType MullerRecurrence(size_t n = 80) {
  DataType x0 = 4.0;
  DataType x1 = 17.0 / 4.0;
  DataType xn = 108 - (815 - 1500 / x0) / x1;

  for (size_t i = 1; i < n; ++i) {
    x0 = x1;
    x1 = xn;
    xn = 108 - (815 - 1500 / x0) / x1;
  }
  return xn;
}

TEST(RecurrenceTest, TestPosit16) {
  auto res_float = MullerRecurrence<float>();
  auto res = MullerRecurrence<Posit16>();
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestPosit16_2) {
  size_t a = 63;
  auto res_float = MullerRecurrence<float>(a);
  auto res = MullerRecurrence<Posit16>(a);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestPosit32) {
  auto res_float = MullerRecurrence<float>();
  auto res = MullerRecurrence<Posit32>();
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestPosit32_2) {
  size_t a = 63;
  auto res_float = MullerRecurrence<float>(a);
  auto res = MullerRecurrence<Posit32>(a);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestBfloat16) {
  auto res_float = MullerRecurrence<float>();
  auto res = MullerRecurrence<bfloat16>();
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestBfloat16_2) {
  size_t a = 63;
  auto res_float = MullerRecurrence<float>(a);
  auto res = MullerRecurrence<bfloat16>(a);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestFloat32) {
  auto res_float = MullerRecurrence<float>();
  auto res = MullerRecurrence<Float32>();
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(RecurrenceTest, TestFloat32_2) {
  size_t a = 63;
  auto res_float = MullerRecurrence<float>(a);
  auto res = MullerRecurrence<Float32>(a);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

// Evaluataion of a polynomial in the neighborhood of one of its roots: p(x) = x^3 - 3 * x^2 + 3 * x - 1.
// Inaccuracies introduced by computer arithmetic may lead to wrong conclusions.
template <typename DataType>
DataType ThirdPolynomial(float x) {
  return x * x * x - 3 * x * x + 3 * x - 1;
}

TEST(PolynomialTest, TestPosit16) {
  float x = generator.GetRandomFloat();
  auto res_float = ThirdPolynomial<float>(x);
  auto res = ThirdPolynomial<Posit16>(x);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(PolynomialTest, TestPosit32) {
  float x = generator.GetRandomFloat();
  auto res_float = ThirdPolynomial<float>(x);
  auto res = ThirdPolynomial<Posit32>(x);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(PolynomialTest, TestBfloat16) {
  float x = generator.GetRandomFloat();
  auto res_float = ThirdPolynomial<float>(x);
  auto res = ThirdPolynomial<bfloat16>(x);
  EXPECT_FLOAT_EQ(res_float, float(res));
}

TEST(PolynomialTest, TestFloat32) {
  float x = generator.GetRandomFloat();
  auto res_float = ThirdPolynomial<float>(x);
  auto res = ThirdPolynomial<Float32>(x);
  EXPECT_FLOAT_EQ(res_float, float(res));
}
}
}
