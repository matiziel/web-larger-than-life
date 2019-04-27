#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Board.h"


std::clock_t test(unsigned const int tableSize,unsigned const int range)
{
        Board grid(tableSize,tableSize);
        grid.SetRandomBoard();
        std::clock_t time;
        time = std::clock();
        for (unsigned int i = 0; i < 5; ++i) 
        {
            grid.Update(range);
        }
        time = std::clock() - time;
        return time;
}




int main(int argc, char** argv)
{

    std::cout<<"Update() tableSize: 250, range: 1, result: "<<static_cast<int>(test(10,1))<<std::endl;
    std::cout<<"Update() tableSize: 250, range: 3, result: "<<static_cast<int>(test(10,3))<<std::endl;
    std::cout<<"Update() tableSize: 250, range: 5, result: "<<static_cast<int>(test(10,5))<<std::endl;
    std::cout<<"Update() tableSize: 250, range: 10, result: "<<static_cast<int>(test(20,10))<<std::endl;
    return 0;
}

