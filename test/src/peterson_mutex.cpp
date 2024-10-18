#include <peterson_mutex.hpp>

#include <thread>
#include <iostream>

#include <catch2/catch_all.hpp>

#include "tools.hpp"

TEST_CASE("base")
{
    pm::PetersonMutex mutex;
    int value = 0;

    const auto work = [&mutex, &value]
    (const unsigned thread_id, const size_t count_iterations, const auto sleep_period)
    {
        for (size_t i = 0; i < count_iterations; ++i)
        {
            mutex.lock(thread_id);

            value++;

            busy();

            value++;

            mutex.unlock(thread_id);
        }
    };

    const size_t thread_1_iterations { 200 };
    const unsigned thread_1_sleep_period_ms { 3 };
    std::thread thread_1 {
        work, 0,
        thread_1_iterations,
        std::chrono::milliseconds { thread_1_sleep_period_ms }
    };

    const unsigned thread_2_sleep_period_ms { 1 };
    const size_t thread_2_iterations { thread_1_iterations  };
    std::thread thread_2 {
        work, 1,
        thread_2_iterations,
        std::chrono::milliseconds { thread_2_sleep_period_ms }
    };

    const auto expected_value = (thread_1_iterations + thread_2_iterations) * 2;

    thread_1.join();
    thread_2.join();

    CHECK(value == expected_value);
}
