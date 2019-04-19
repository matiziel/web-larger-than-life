#ifndef GRID_H
#define GRID_H
#include "boost/multi_array.hpp"
#include <thread>




enum {DEAD, ALIVE};
const unsigned int DEFAULT_SIZE = 256;


class Grid
{
	typedef boost::multi_array<int, 2> MultiArray;
public:
	// Grid()=delete;
	// Grid(const Grid& arg)=delete;
	// Grid& operator=(const Grid& arg)=delete;
	Grid(const unsigned int height, const unsigned int width) : grid(boost::extents[height+2][width+2])
	{
		//plus dwa aby nie trzeba było sprawdzać za kazdym razem 
		//czy można sie odwołać do nastepnego czy poprzedniego
		//numerujemy pozniej od 1 do size-1
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
		srand (time(NULL)); //ja bym srandował gdzie indziej, np w konstruktorze
		for(unsigned int i = 0; i < this->Height(); ++i)
		{
			for(unsigned int k = 0; k < this->Width(); ++k)
			{
				grid[i][k] = (rand() % 5) / 4;
			}
		}
	}

	unsigned int Width() const 
	{
		return grid.shape()[1] - 2;
	}

	unsigned int Height() const 
	{
		return grid.shape()[0] - 2;
	}

	int GetPixelState(const unsigned int heightArg, const unsigned int widthArg) const 
	{
		if(heightArg >= this->Height() || widthArg >= this->Width())
			throw std::invalid_argument("Grid overflow");
		return static_cast<int>(grid[heightArg+1][widthArg+1]);
	}
	// void Update()
	// {
	// 	//tu potem beda dwie tablice zeby mniej kopiowac
	// 	MultiArray other = grid;
	// 	std::thread t1(&Grid::UpdateThread, this, std::ref(other), 0, this->Height()/4 );
	// 	std::thread t2(&Grid::UpdateThread, this, std::ref(other), this->Height()/4, this->Height()/2 );
	// 	std::thread t3(&Grid::UpdateThread, this, std::ref(other), this->Height()/2, 3*this->Height()/4 );
	// 	std::thread t4(&Grid::UpdateThread, this, std::ref(other), 3*this->Height()/4, this->Height() );
	// 	t1.join();
	// 	t2.join();
	// 	t3.join();
	// 	t4.join();
	// }
	void Update()
	{
		//tu potem beda dwie tablice zeby mniej kopiowac
		MultiArray other = grid;
		for(unsigned int i = 0; i < this->Height(); ++i)
		{
			for(unsigned int k = 0; k < this->Width(); ++k)
			{
				unsigned short sum = SumOfNeighbors(other, i+1, k+1);
				if(other[i+1][k+1] == DEAD && sum == 3) grid[i+1][k+1] = ALIVE;
				if(other[i+1][k+1] == ALIVE && (sum < 2 || sum > 3)) grid[i+1][k+1] = DEAD;
			}
		}

	}
	


private:
	MultiArray grid;

	unsigned short SumOfNeighbors(const MultiArray& grid, const unsigned int heightArg, const unsigned int widthArg)
	{
		//to potem do wywalenia i petelka zalezna od zasady

		unsigned short sum = 0;
		sum += ALIVE == grid[heightArg - 1][widthArg - 1];
		sum += ALIVE == grid[heightArg - 1][widthArg];
		sum += ALIVE == grid[heightArg - 1][widthArg + 1];
		sum += ALIVE == grid[heightArg][widthArg - 1];
		sum += ALIVE == grid[heightArg][widthArg + 1];
		sum += ALIVE == grid[heightArg + 1][widthArg - 1];
		sum += ALIVE == grid[heightArg + 1][widthArg];
		sum += ALIVE == grid[heightArg + 1][widthArg + 1];
		return sum;
	}

	// void UpdateThread(const MultiArray& other, const unsigned int begin, const unsigned int end )
	// {
	// 	for(unsigned int i = begin; i < end; ++i)
	// 	{
	// 		for(unsigned int k = 0; k < this->Width(); ++k)
	// 		{
	// 			unsigned short sum = SumOfNeighbors(other, i+1, k+1);
	// 			if(other[i+1][k+1] == DEAD && sum == 3) grid[i+1][k+1] = ALIVE;
	// 			if(other[i+1][k+1] == ALIVE && (sum < 2 || sum > 3)) grid[i+1][k+1] = DEAD;
	// 		}
	// 	}

	// }

};

#endif