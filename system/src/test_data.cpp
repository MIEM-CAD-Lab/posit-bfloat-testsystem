#include "test_data.h"

float FloatDataGenerator::GetRandomFloat(float low, float high) {
  return real_dis.Generate(low, high);
}

size_t FloatDataGenerator::GetRandomUInt(size_t low, size_t high) {
  return int_dis.Generate(low, high);
}
