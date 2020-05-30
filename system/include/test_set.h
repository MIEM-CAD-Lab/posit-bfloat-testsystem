#pragma once
#include <vector>
#include <functional>
#include <string>
#include "test.h"

class TestSet {
public:
  TestSet();
  TestSet(std::string name);

  void AddTest(Test test);
  std::vector<Test> GetTests() const;
  std::string GetName() const;

private:
  std::vector<Test> tests_;
  std::string name_;
};
