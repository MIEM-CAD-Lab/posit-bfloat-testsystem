#include "test_set.h"

TestSet::TestSet() : name_("default_name_set") {}

TestSet::TestSet(std::string name) : name_(name) {}

void TestSet::AddTest(Test test) {
  tests_.push_back(std::move(test));
}

std::vector<Test> TestSet::GetTests() const {
  return tests_;
}

std::string TestSet::GetName() const {
  return name_;
}