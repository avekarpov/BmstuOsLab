#pragma once

#include <atomic>
#include <memory>

namespace transaction_memory {

template <class T>
class TransactionObject;

template <class T>
class Transaction {
public:
    Transaction(TransactionObject<T> &object)
    : _object{object}
    , _old_value_ptr{object._atomic_value_ptr.load()}
    , _new_value_ptr{std::make_shared<T>(*_old_value_ptr)}
    {}

    T& get() {
        return *_new_value_ptr;
    }

    bool try_apply() {
        return _object._atomic_value_ptr.compare_exchange_strong(_old_value_ptr, _new_value_ptr);
    }

    void force_apply()
    {
         _object._atomic_value_ptr.store(_new_value_ptr);
    }

private:
    TransactionObject<T> &_object;

    std::shared_ptr<T> _old_value_ptr;
    std::shared_ptr<T> _new_value_ptr;
};

template <class T>
class TransactionObject {
private:
    friend class Transaction<T>;
public:
    TransactionObject() : _atomic_value_ptr{std::make_shared<T>()} {}

    Transaction<T> get_transaction() {
        return *this;
    }

private:
    std::atomic<std::shared_ptr<T>> _atomic_value_ptr;
};

} // namespace tm