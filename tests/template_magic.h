#pragma once
#include "test_type.h"
#include <string>

template <typename first>
struct format_type {
  static constexpr char* format_name = "unknown";
};
template<>
struct format_type<format::posit_type::Posit16> {
  static constexpr char* format_name = "Posit16";
};
template <>
struct format_type<format::posit_type::Posit32> {
  static constexpr char* format_name = "Posit32";
};
template <>
struct format_type<format::float_type::Float<7, 8>> {
  static constexpr char* format_name = "bfloat16";
};
template <>
struct format_type<format::float_type::Float<23, 8>> {
  static constexpr char* format_name = "Float32";
};
template <>
struct format_type<float> {
  static constexpr char* format_name = "float";
};
template <>
struct format_type<double> {
  static constexpr char* format_name = "double";
};
