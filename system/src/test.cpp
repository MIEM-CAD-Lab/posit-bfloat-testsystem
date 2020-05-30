#include "test.h"

//Test::Test() : name_("default") {}

std::string Test::GetName() const {
  return name_;
}

std::function<void ()> Test::GetFunction() const {
  return func_;
}

std::string Test::GetLabel() const {
  return label;
}