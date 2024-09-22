#include "peterson_mutex.hpp"

#include <cassert>
#include <thread>

namespace pm {

PetersonMutex::PetersonMutex()
: _want { false, false}
, _waiting { 0 }
{}

void PetersonMutex::lock(unsigned thread_id) {
    assert(thread_id <= 1);

    const auto other_thread_id = 1 - thread_id;

    _want[thread_id].store(true);
    _waiting.store(thread_id);
    while (_want[other_thread_id].load() && _waiting.load() == thread_id) {};
}

void PetersonMutex::unlock(unsigned thread_id) {
    assert(thread_id <= 1);

    _want[thread_id].store(false);
}

} // namespace pm
