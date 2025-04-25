#include <coroutine>
#include <iostream>
#include <utility>


#include <fibo.h>


namespace {

// return type
struct FiboGenerator {
    struct promise_type;
    std::coroutine_handle<promise_type> handle;
    struct promise_type{
        // start
        FiboGenerator get_return_object() {
            return std::coroutine_handle<promise_type>::from_promise(*this);
        }

        std::suspend_never initial_suspend() {
            return {};
        }



        // end
        void unhandled_exception() {}
        //void return_value(int v) {
        //    val = v;
        //}
        //

        std::suspend_always yield_value(int v)
        {
            val = v;
            return {};
        }
        std::suspend_always final_suspend() noexcept {
            return {};
        }

        int val{};
    };

    FiboGenerator(std::coroutine_handle<promise_type> handle) 
    {
        this->handle = handle;
    }

    FiboGenerator(const FiboGenerator& rhs) = delete;
    FiboGenerator(FiboGenerator&& rhs) {
        if (handle)
        {
            handle.destroy();
        }
        handle = rhs.handle;
        rhs.handle = nullptr;
    }

    virtual ~FiboGenerator() 
    {
        if (handle) 
        {
            handle.destroy();
        }
    }

    void resume()
    {
        if (handle)
        {
            handle.resume();
        }
    }

    int getValue()
    {
        return handle.promise().val;
    }
};

struct Awaitable {
    Awaitable(int val) : value{val} {}
    bool await_ready() {
        return false;
    }

    void await_suspend(std::coroutine_handle<FiboGenerator::promise_type> h)
    {
        h.promise().val = value;
    }

    void await_resume()
    {
        // invoked before resume
    }

    const int value{};
};
    
FiboGenerator makeFiboGenerator() {
    std::cout << "generator invoked" << std::endl;
    int i1 = 1;
    int i2 = 1;
    while(true)
    {
        co_yield i1;
        i1 = std::exchange(i2, i1 + i2);
    }
}
}

struct Fibo::FiboImpl {
    FiboImpl()
    {
        coroutineReturnTypePtr = std::make_unique<FiboGenerator>(makeFiboGenerator());
    }

    int next()
    {
        if (invoked)
        {
            coroutineReturnTypePtr->resume();
        }
        invoked |= true;
        return coroutineReturnTypePtr->getValue();
    }

    std::unique_ptr<FiboGenerator> coroutineReturnTypePtr;
    bool invoked = false;
};

Fibo::Fibo()
{
    this->implPtr = std::make_shared<FiboImpl>();
}

int Fibo::next() {
    return implPtr->next();
}
