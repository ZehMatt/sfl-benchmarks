#pragma once

#include <deque>
#include <numeric>
#include <random>
#include "benchmark/benchmark.h"

static constexpr auto kTestSize = 200'000;

struct TestStruct
{
    int a{ 0 };
    int b{ 1 };
    int c{ 2 };
    int d{ 3 };
    int e{ 4 };
    int f{ 5 };
    int g{ 6 };
    int h{ 7 };

    int sum() const
    {
        return a + b + c + d + e + f + g + h;
    }
};

template<typename T>
static void container_push_back(T& container)
{
    for (auto i = 0; i < kTestSize; ++i)
    {
        container.push_back(TestStruct{});
    }
}

template <typename T>
struct has_push_front
{
    template <typename U>
    static auto test(U* u) -> decltype(u->push_front(TestStruct{}), std::true_type{});

    template <typename U>
    static auto test(...) -> std::false_type;

    static constexpr bool value = decltype(test<T>(nullptr))::value;
};

template<typename T>
static void container_push_front(T& container)
{
    for (auto i = 0; i < kTestSize; ++i)
    {
        if constexpr (has_push_front<T>::value)
        {
            container.push_front(TestStruct{});
        }
        else
        {
            container.insert(container.begin(), TestStruct{});
        }
    }
}

template<typename TContainer>
static void BM_push_back(benchmark::State& state)
{
    size_t numElements = 0;

    for (auto _ : state)
    {
        TContainer container;
        container_push_back(container);
        numElements += container.size();

        auto count = container.size();
        benchmark::DoNotOptimize(count);
    }

    state.counters["Elements"] = numElements;
}

template<typename TContainer>
static void BM_push_front(benchmark::State& state)
{
    size_t numElements = 0;

    for (auto _ : state)
    {
        TContainer container;
        container_push_front(container);
        numElements += container.size();

        auto count = container.size();
        benchmark::DoNotOptimize(count);
    }

    state.counters["Elements"] = numElements;
}

template<typename TContainer>
static void BM_erase_random(benchmark::State& state)
{
    size_t numElements = 0;

    for (auto _ : state)
    {
        state.PauseTiming();
        TContainer container;
        container_push_back(container);
        state.ResumeTiming();

        std::mt19937 rng(1);
        while (!container.empty())
        {
            auto index = rng() % container.size();
            container.erase(container.begin() + index);

            numElements++;
        }

        auto count = container.size();
        benchmark::DoNotOptimize(count);
    }

    state.counters["Elements"] = numElements;
}

template<typename TContainer>
static void BM_iterate(benchmark::State& state)
{
    size_t numElements = 0;

    TContainer container;
    container_push_back(container);

    for (auto _ : state)
    {
        auto sum = std::accumulate(container.begin(), container.end(), 0, [](int sum, const TestStruct& value) {
            return sum + value.sum();
            });

        benchmark::DoNotOptimize(sum);

        numElements++;
    }

    state.counters["Elements"] = numElements;
}