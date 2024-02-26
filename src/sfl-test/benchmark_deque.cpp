#include "common.hpp"

#include <deque>

BENCHMARK_TEMPLATE(BM_push_back, std::deque<TestStruct>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_push_front, std::deque<TestStruct>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_erase_random, std::deque<TestStruct>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_iterate, std::deque<TestStruct>)->Unit(benchmark::kMicrosecond);