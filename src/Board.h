#ifndef BOARD_H
#define BOARD_H
#include "boost/multi_array.hpp"
#include <thread>
#include "Rules.h"


enum {DEAD, ALIVE};
const unsigned int DEFAULT_SIZE = 256;


class Board
{
	typedef boost::multi_array<int, 2> MultiArray;
	typedef unsigned int Uint;
public:
	// Board()=delete;
	// Board(const Board& arg)=delete;
	// Board& operator=(const Board& arg)=delete;
	Board(const unsigned int height = DEFAULT_SIZE, const unsigned int width = DEFAULT_SIZE) 
	: gridA(boost::extents[height+2][width+2]), gridB(boost::extents[height+2][width+2])
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

	// void SetRules(Uint rArg = 1, Uint cArg = 2, bool mArg = 0, Uint sMinArg = 2,
    // Uint sMaxArg = 3, Uint bMinArg = 3, Uint bMaxArg = 3, NeighbourhoodTypes nArg = Moore)
	// {
	// 		rules.SetRules(rArg, )
	// }

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
	
void Update()
{
	Uint range=rules.GetRange();
	for(unsigned int i = -range; i <= range; ++i)
	{
		for(unsigned int k = -abs(i) + range + 1; k <= abs(i) - range - 1; ++k)
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
		
void UpdateMoore()
{
	
	for(unsigned int i = 1 i < this->Height(); ++i)
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

	Rules rules;


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

};

#endif