#pragma once

#include <atomic>
#include <array>

namespace pm {

class PetersonMutex {
public:
    PetersonMutex();

    void lock(unsigned thread_id);

    void unlock(unsigned thread_id);

private:
    std::array<std::atomic<bool>, 2> _want;
    std::atomic<unsigned> _waiting;
};

} // namespace pm
