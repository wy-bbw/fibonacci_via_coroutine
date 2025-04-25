#include <iostream>
#include <fibo.h>

int main()
{
    Fibo f;
    for (int i = 0; i < 15; ++i)
    {
        std::cout << "hello world. Next fibonacci number: " << f.next() << std::endl;
    }
}
