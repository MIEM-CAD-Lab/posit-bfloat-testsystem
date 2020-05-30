#pragma once
#include <string>
#include <functional>
#include <utility>

class Test {
public:
  Test() = delete;
  template <typename FunctionType>
  Test(std::string str, FunctionType func, std::string label_) : func_(func), name_(std::move(str)), label(std::move(label_)) {}
  std::string GetName() const;
  std::function<void()> GetFunction() const;
  std::string GetLabel() const;
private:
  std::function<void()> func_;
  std::string name_;
  std::string label;
};

