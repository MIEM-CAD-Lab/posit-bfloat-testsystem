#pragma once
#include "test_type.h"
template <typename DataType>
DataType abs(DataType x) {
  float bufer(x);
  float res = std::abs(bufer);
  return DataType(res);
}

template <typename DataType>
DataType exp(DataType x) {
  float bufer(x);
  float res = std::exp(bufer);
  return DataType(res);
}

template <typename DataType>
DataType sqrt(DataType x) {
  float bufer(x);
  float res = std::sqrt(bufer);
  return DataType(res);
}

template<typename DataType>
DataType pow(DataType x, DataType y) {
  return DataType(std::pow(double(x), double(y)));
}

