#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "Board.h"


std::clock_t test(unsigned const int tableSize,unsigned const int amountOfIter)
{
        Board grid(tableSize,tableSize);
        grid.SetRandomBoard();
        std::clock_t time;
        time = std::clock();
        for (unsigned int i = 0; i < amountOfIter; ++i) 
        {
            grid.Update();
        }
        time = std::clock() - time;
        return time;
}




int main(int argc, char** argv)
{

    std::cout<<"Update() tableSize: 25, amount of iter: 10000, result: "<<static_cast<int>(test(25,10000))<<std::endl;
    // std::cout<<"Update() tableSize: 500, amount of iter: 50,  result: "<<static_cast<int>(test(500,50))<<std::endl;
    // std::cout<<"Update() tableSize: 1000, amount of iter: 10, result: "<<static_cast<int>(test(1000,10))<<std::endl;
    // std::cout<<"Update() tableSize: 10000, amount of iter: 1, result: "<<static_cast<int>(test(10000,1))<<std::endl;
    // return 0;
}

