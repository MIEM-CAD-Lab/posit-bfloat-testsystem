#include <utility>
#include <benchmark/benchmark.h>
#include "test_manager.h"

TestManager::TestManager(int argc, char** argv) {
  benchmark_sets_.emplace_back(TestSet("No category"));
  validation_sets_.emplace_back(TestSet("No category"));
  benchmark::Initialize(&argc, argv);
}

void TestManager::AddBenchmarkTest(Test test) {
  benchmark_sets_[0].AddTest(std::move(test));
}

void TestManager::AddBenchmarkSetTest(TestSet set) {
  benchmark_sets_.push_back(std::move(set));
}

void TestManager::AddValidationTest(Test test) {
  validation_sets_[0].AddTest(std::move(test));
}

void TestManager::AddValidationSetTest(TestSet set) {
  validation_sets_.push_back(std::move(set));
}

void TestManager::Run() {
  for (const auto& set : benchmark_sets_) {
    for (const auto& test : set.GetTests()) {
      auto test_for_benchmark = [test](benchmark::State& state) {
        state.SetLabel(test.GetLabel());
        for (auto _ : state) {
          test.GetFunction()();
        }
      };
      auto final_name = test.GetName();
      benchmark::RegisterBenchmark(final_name.c_str(),
          test_for_benchmark)->Unit(benchmark::TimeUnit::kMicrosecond);

    }
  }

  benchmark::RunSpecifiedBenchmarks();
}

void TestManager::ClearRun() {
  for (const auto& set : benchmark_sets_) {
    for (const auto& test : set.GetTests()) {
      test.GetFunction()();
    }
  }
}