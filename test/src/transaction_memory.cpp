#include <transaction_memory.hpp>

#include <thread>

#include <catch2/catch_all.hpp>

#include "tools.hpp"

TEST_CASE("Transaction memory")
{
    transaction_memory::TransactionObject<int> object;

    const auto work = [&object](const size_t iteration_count, const size_t busy_count)
    {
        for (size_t i = 1; i <= iteration_count; ++i)
        {
            auto transaction = object.get_transaction();
            auto &value = transaction.get();

            value++;

            for (size_t j = 0; j < busy_count; ++j)
            {
                busy();
            }

            value++;

            if (not transaction.try_apply())
            {
                --i;
            }
        }
    };

    std::thread thread_1 {work, 2000, 1};
    std::thread thread_2 {work, 1000, 2};

    thread_1.join();
    thread_2.join();

    CHECK(object.get_transaction().get() == 6000);
}
