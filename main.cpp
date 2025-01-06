#include <iostream>

#include <tr/block_time.hpp>

int main()
{
    tr::BlockTime block_time(__FILE__);

    block_time.set();
    
    std::cout << "Hello, World!" << std::endl;

    block_time.set();

    for (int i = 0; i < 1000; i++)
    {
        int smth = i;
    }

    block_time.set();

    for (int i = 0; i < 10000; i++)
    {
        int smth = i;
    }

    block_time.set();

    for (int i = 0; i < 100000; i++)
    {
        int smth = i;
    }

    block_time.set();
    
    for (int i = 0; i < 100000; i++)
    {
        int smth = i;
    }

    block_time.set();

    for (int i = 0; i < 100000; i++)
    {
        int smth = i;
    }

    block_time.set();

    for (int i = 0; i < 1000000; i++)
    {
        int smth = i;
    }

    block_time.set();

    block_time.print();

    block_time.clear();

    return 0;
}