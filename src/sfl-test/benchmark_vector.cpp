#include "common.hpp"

#include <vector>

BENCHMARK_TEMPLATE(BM_push_back, std::vector<TestStruct>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_push_front, std::vector<TestStruct>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_erase_random, std::vector<TestStruct>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_iterate, std::vector<TestStruct>)->Unit(benchmark::kMicrosecond);