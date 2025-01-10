#include <iostream>

#include <tr/block_time.hpp>    // INCLUDE HEADER FILE

int main()
{
    tr::BlockTime block_time(__FILE__); // INITIALIZE WITH THE SOURCE FILE NAME (__FILE__)

    block_time.set(__LINE__);  /* 
                                * FIRST SETTER
                                * JUST SET START OF DESIRED CODE BLOCK
                                */

    std::cout << "Hello, World!" << std::endl;

    block_time.set(__LINE__);  /* 
                                * SECOND, THIRD AND ETC. SETTERS
                                * WILL SET END OF PREVIOUS CODE BLOCK
                                * & WILL SET START FOR THE NEXT ONE CODE BLOCK
                                */

    int smth = 0;

    block_time.set(__LINE__);  /* 
                                * SO ANOTHER ONE SETTER WILL DO THE SAME
                                * WILL SET END OF PREVIOUS CODE BLOCK
                                * & WILL SET START FOR THE NEXT ONE CODE BLOCK
                                */

    for (int i = 0; i < 10000; i++)
    {
        smth = i;
    }

    block_time.set(__LINE__);

    for (int i = 0; i < 100000; i++)
    {
        smth = i;
    }

    block_time.set(__LINE__);

    for (int i = 0; i < 100000; i++)
    {
        smth = i;
    }

    block_time.set(__LINE__);

    for (int i = 0; i < 100000; i++)
    {
        smth = i;
    }

    block_time.set(__LINE__);

    for (int i = 0; i < 10000000; i++)
    {
        smth = i;
    }

    block_time.set(__LINE__);  /* 
                                * THIS SETTER WILL SET START FOR THE NEXT ONE CODE BLOCK BUT I'M NOT INTRESTED INTO
                                * SO I JUST DON'T SET ANOTHER SETTERS
                                */

    block_time.print(); // PRINT EXECUTION TIMES OF ALL BLOCKS

    block_time.clear(); // CLEAR THE TIMES (IF NEEDED)

    return 0;
}