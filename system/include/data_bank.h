#pragma once
#include <unordered_map>
#include <vector>

struct DataBank {
  DataBank() {}
  using Vector = std::vector<float>;
  using Matrix = std::vector<Vector>;
  std::unordered_map<size_t, std::vector<std::vector<float>>> vectors;
  std::unordered_map<size_t, std::unordered_map<size_t, std::vector<Matrix>>> matrix;
};

