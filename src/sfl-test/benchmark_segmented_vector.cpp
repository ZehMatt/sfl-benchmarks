#include "common.hpp"

#include <sfl/segmented_vector.hpp>

BENCHMARK_TEMPLATE(BM_push_back, sfl::segmented_vector<TestStruct, 4096>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_push_front, sfl::segmented_vector<TestStruct, 4096>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_erase_random, sfl::segmented_vector<TestStruct, 4096>)->Unit(benchmark::kMicrosecond);
BENCHMARK_TEMPLATE(BM_iterate, sfl::segmented_vector<TestStruct, 4096>)->Unit(benchmark::kMicrosecond);