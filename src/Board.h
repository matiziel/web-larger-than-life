#ifndef BOARD_H
#define BOARD_H
#include "boost/multi_array.hpp"
#include <thread>


enum {DEAD, ALIVE};
const unsigned int DEFAULT_SIZE = 256;


class Board
{
	typedef boost::multi_array<int, 2> MultiArray;
public:
	// Board()=delete;
	// Board(const Board& arg)=delete;
	// Board& operator=(const Board& arg)=delete;
	Board(const unsigned int height = DEFAULT_SIZE, const unsigned int width = DEFAULT_SIZE) : gridA(boost::extents[height+2][width+2]), gridB(boost::extents[height+2][width+2])
	{
		//plus dwa aby nie trzeba było sprawdzać za kazdym razem 
		//czy można sie odwołać do nastepnego czy poprzedniego
		//numerujemy pozniej od 1 do size-1

		for(unsigned int i = 0; i < height; ++i)
		{
			for(unsigned int k = 0; k < width; ++k)
			{
				gridA[i][k] = gridB[i][k] = DEAD;
			}
		}
		current = &gridA;
		next = &gridB;
	}
	void SetRandomBoard()
	{
		srand (time(NULL)); //ja bym srandował gdzie indziej, np w konstruktorze
		for(unsigned int i = 0; i < this->Height(); ++i)
		{
			for(unsigned int k = 0; k < this->Width(); ++k)
			{
				(*current)[i+1][k+1] = (rand() % 5) / 4;; //80% jest zerami
			}
		}
	}

	void SetConstBoard()
	{
		unsigned int k = Width()/2;
		unsigned int i = Height()/2;
		(*current)[i][k] = ALIVE;
		(*current)[i][k+1] = ALIVE;
		(*current)[i+1][k] = ALIVE;
		(*current)[i+1][k+1] = ALIVE;

		k = Width()/4;
		i = Height()/4;
		(*current)[i][k] = ALIVE;
		(*current)[i+1][k] = ALIVE;
		(*current)[i+2][k] = ALIVE;

	}

	unsigned int Width() const 
	{
		return (*current).shape()[1] - 2;
	}

	unsigned int Height() const 
	{
		return (*current).shape()[0] - 2;
	}

	int GetPixelState(const unsigned int heightArg, const unsigned int widthArg) const 
	{
		if(heightArg >= this->Height() || widthArg >= this->Width())
			throw std::invalid_argument("Board overflow");
		return static_cast<int>((*current)[heightArg+1][widthArg+1]);
	}
	// void Update()
	// {
	// 	//tu potem beda dwie tablice zeby mniej kopiowac
	// 	MultiArray other = grid;
	// 	std::thread t1(&Board::UpdateThread, this, std::ref(other), 0, this->Height()/4 );
	// 	std::thread t2(&Board::UpdateThread, this, std::ref(other), this->Height()/4, this->Height()/2 );
	// 	std::thread t3(&Board::UpdateThread, this, std::ref(other), this->Height()/2, 3*this->Height()/4 );
	// 	std::thread t4(&Board::UpdateThread, this, std::ref(other), 3*this->Height()/4, this->Height() );
	// 	t1.join();
	// 	t2.join();
	// 	t3.join();
	// 	t4.join();
	// }
void Update()
{
	for(unsigned int i = 1; i < this->Height(); ++i)
	{
		for(unsigned int k = 1; k < this->Width(); ++k)
		{
			unsigned short sum = SumOfNeighbors(*current, i, k);
			if((*current)[i][k] == DEAD)
			{
				if(sum == 3) 
					(*next)[i][k] = ALIVE;
				else 
					(*next)[i][k] = DEAD;
			}
			else 
			{
				if(sum < 2 || sum > 3) 
					(*next)[i][k] = DEAD;
				else 
					(*next)[i][k] = ALIVE;
			}
		}
	} 
	MultiArray* temp = current;
	current = next;
	next = temp;
}
	


private:
	MultiArray gridA;
	MultiArray gridB;
	MultiArray* current;
	MultiArray* next;


	unsigned short SumOfNeighbors(const MultiArray& gridArg, const unsigned int heightArg, const unsigned int widthArg) const
	{
		//to potem do wywalenia i petelka zalezna od zasady
		//TODO wywalic argument grid_arg i wywołać na obiekcie

		unsigned short sum = 0;
		sum += ALIVE == gridArg[heightArg - 1][widthArg - 1];
		sum += ALIVE == gridArg[heightArg - 1][widthArg];
		sum += ALIVE == gridArg[heightArg - 1][widthArg + 1];
		sum += ALIVE == gridArg[heightArg][widthArg - 1];
		sum += ALIVE == gridArg[heightArg][widthArg + 1];
		sum += ALIVE == gridArg[heightArg + 1][widthArg - 1];
		sum += ALIVE == gridArg[heightArg + 1][widthArg];
		sum += ALIVE == gridArg[heightArg + 1][widthArg + 1];
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