#pragma once
#include <vector>
#include <random>
#include <utility>
#include "data_bank.h"

class FloatDataGenerator {
public:
  // Возвращение случайного float из [low, high]
  float GetRandomFloat(float low = MIN_FLOAT, float high = MAX_FLOAT);
  // Возвращение случайного size_t из [low, high]
  size_t GetRandomUInt(size_t low = 0, size_t high = MAX_VECTOR_SIZE);

  // Возвращает случайно-заполненный вектор размера size
  // Если нет аргумента или size = 0, размер случайный
  template <typename DataType>
  std::vector<DataType> GetRandomVector(size_t size = 0) {
    if (!size) {
      size = GetRandomUInt(0, MAX_VECTOR_SIZE);
    }
    std::vector<DataType> result(size, 0);
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = GetRandomFloat(MIN_FLOAT, MAX_FLOAT);
    }
    return result;
  }
  // Возвращает рандомный вектор из банка данных размера size
  // Если вектора нет, вернет пустой вектор
  // Если size = 0, вернет случайный вектор
  template <typename DataType>
  // TODO Привести к возможности использовать датабанк
  std::vector<DataType> GetBankVector(size_t size) {
    if (bank.vectors.empty())
      return {};
    if (bank.vectors.count(size)) {
      return bank.vectors.at(size);
    }
    size_t vec_index = GetRandomUInt(0, bank.vectors.size());
    return bank.vectors[vec_index];
  }

  // Возвращает случайно-заполненную матрицу размера x на y
  // Если x = 0 и y = 0, вернет рандомную квадратную матрицу
  template <typename DataType>
  std::vector<std::vector<DataType>> GetRandomMatrix(size_t x = 0, size_t y = 0) {
    if (!x && !y) x = y = GetRandomUInt(0, MAX_VECTOR_SIZE);
    if (!x) x = GetRandomUInt(0, MAX_VECTOR_SIZE);
    if (!y) y = GetRandomUInt(0, MAX_VECTOR_SIZE);
    std::vector<std::vector<DataType>> result(x, std::vector<DataType>(y, 0));
    for (size_t i = 0; i < result.size(); ++i) {
      result[i] = GetRandomVector<DataType>(result[i].size());
    }
    return result;
  }
  // Возвращает рандомную матрицу из банка данных размером x на y
  // Если нет подходящей матрицы, возвращает пустую матрицу
  // Если x = 0, а y != 0 вернет случайную матрицу с заданным размером y
  // Если х != 0, а y = 0 вернет случайную матрицу с заданными размером х
  // Если x = 0 и y = 0 вернет случайную матрицу
  // TODO Привести к возможности использовать датабанк
  template <typename DataType>
  std::vector<std::vector<DataType>> GetBankMatrix(size_t x, size_t y) {
    if (bank.matrix.empty()) return {};
    if (bank.matrix.count(x) && bank.matrix.at(x).count(y)) {
      return bank.matrix[x][y];
    }
    if (!x) x = GetRandomUInt(0, bank.matrix.size());
    if (!y) y = GetRandomUInt(0, bank.matrix.at(x).size());
    return bank.matrix[x][y];
  }

  static DataBank bank;
private:
  constexpr static size_t MAX_VECTOR_SIZE = 1000;
  constexpr static float MIN_FLOAT = -150.0;
  constexpr static float MAX_FLOAT = 150.0;
  class CacheIntDistribution {
  public:
    CacheIntDistribution() {
      std::random_device rd;
      generator_int = std::mt19937(rd());
      dis = std::uniform_int_distribution<>(0, MAX_VECTOR_SIZE);
    }
    size_t Generate(size_t low, size_t high) {
      if (current_params != std::make_pair(low, high)) {
        dis = std::uniform_int_distribution<>(low, high);
        current_params = {low, high};
      }
      return dis(generator_int);
    }
  private:
    std::mt19937 generator_int;
    std::pair<size_t, size_t> current_params;
    std::uniform_int_distribution<> dis;
  } int_dis;

  class CacheRealDistribution {
  public:
    CacheRealDistribution() {
      std::random_device rd;
      generator_double = std::mt19937(rd());
      dis = std::uniform_real_distribution<>(MIN_FLOAT, MAX_FLOAT);
    }
    float Generate(float low, float high) {
      if (current_params != std::make_pair(low, high)) {
        dis = std::uniform_real_distribution<>(low, high);
        current_params = {low, high};
      }
      return dis(generator_double);
    }
  private:
    std::mt19937 generator_double;
    std::pair<float, float> current_params;
    std::uniform_real_distribution<> dis;
  } real_dis;
};
