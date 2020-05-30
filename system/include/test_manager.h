#pragma once
#include <vector>
#include <string>

#include "test.h"
#include "test_set.h"

class TestManager {
public:
  TestManager(int argc, char** argv);
  void AddBenchmarkSetTest(TestSet set);
  void AddBenchmarkTest(Test test);
  void AddValidationSetTest(TestSet set);
  void AddValidationTest(Test test);
  void Run();
  void ClearRun();
private:
  std::vector<TestSet> benchmark_sets_;
  std::vector<TestSet> validation_sets_;
};
