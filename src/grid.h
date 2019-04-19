#ifndef GRID_H
#define GRID_H
#include "boost/multi_array.hpp"
#include <iostream>



enum {DEAD, ALIVE};
const unsigned int DEFAULT_SIZE = 256;


class Grid
{
	typedef boost::multi_array<int, 2> MultiArray;
public:
	// Grid()=delete;
	// Grid(const Grid& arg)=delete;
	// Grid& operator=(const Grid& arg)=delete;
	Grid(const unsigned int height, const unsigned int width) : grid(boost::extents[height][width])
	{
		for(unsigned int i = 0; i < height; ++i)
		{
			for(unsigned int k = 0; k < width; ++k)
			{
				grid[i][k] = DEAD;
			}
		}
	}
	void SetRandomGrid()
	{
		srand (time(NULL));
		for(unsigned int i = 0; i < this->Height(); ++i)
		{
			for(unsigned int k = 0; k < this->Width(); ++k)
			{
				grid[i][k] = rand() % 2 + 1;
			}
		}
	}
	void Display() const 
	{

	}
	unsigned int Width() const 
	{
		return grid.shape()[1];
	}

	unsigned int Height() const 
	{
		return grid.shape()[0];
	}

	int GetPixelState(const unsigned int heightArg, const unsigned int widthArg) const 
	{
		if(heightArg >= this->Height() || widthArg >= this->Width())
			throw std::invalid_argument("Grid overflow");
		return static_cast<int>(grid[heightArg][widthArg]);
	}
	// }
	// void Update()
	// {
	// 	MultiArray other = grid;
	// 	for(unsigned int i = 0; i<grid.shape()[0]; ++i)
	// 	{
	// 		for(unsigned int k = 0; k<grid.shape()[0]; ++k)
	// 		{
	// 			if(grid[i][k] == DEAD)
	// 			{

	// 			}

	// 		}
	// 	}

	// }
	// void Initialize();
private:
	MultiArray grid;


};

#endif