#pragma once

#include <memory>

class Fibo
{
public:
    Fibo();
    int next();
private:
    struct FiboImpl;
    std::shared_ptr<FiboImpl> implPtr;
};
