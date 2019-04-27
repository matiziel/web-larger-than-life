#ifndef BOARD_H
#define BOARD_H
#include "boost/multi_array.hpp"
#include <thread>
#include "Rules.h"
#include <cmath>
#include <iostream>

enum {DEAD, ALIVE};
const unsigned short DEFAULT_SIZE = 256;


class Board
{
	typedef boost::multi_array<int, 2> MultiArray;
	typedef unsigned short UShort;
public:
	// Board()=delete;
	// Board(const Board& arg)=delete;
	// Board& operator=(const Board& arg)=delete;
	Board(const UShort height = DEFAULT_SIZE, const UShort width = DEFAULT_SIZE) 
	: gridA(boost::extents[height][width]), gridB(boost::extents[height][width])
	{
		for(UShort i = 0; i < height; ++i)
		{
			for(UShort k = 0; k < width; ++k)
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
		for(UShort i = 0; i < this->Height(); ++i)
		{
			for(UShort k = 0; k < this->Width(); ++k)
			{
				(*current)[i][k] = (rand() % 5) / 4;; //80% jest zerami
			}
		}
	}
	void SetConstBoard()
	{
		UShort k = Width()/2;
		UShort i = Height()/2;
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
	// void SetRules(Uint rArg = 1, Uint cArg = 2, bool mArg = 0, Uint sMinArg = 2,
    // Uint sMaxArg = 3, Uint bMinArg = 3, Uint bMaxArg = 3, NeighbourhoodTypes nArg = Moore)
	// {
	// 		rules.SetRules(rArg, )
	// }

	UShort Width() const 
	{
		return (*current).shape()[1];
	}

	UShort Height() const 
	{
		return (*current).shape()[0];
	}

	int GetPixelState(const UShort heightArg, const UShort widthArg) const 
	{
		if(heightArg >= this->Height() || widthArg >= this->Width())
			throw std::invalid_argument("Board overflow");
		return static_cast<int>((*current)[heightArg][widthArg]);
	}
	
void Update()
{
	
	for(UShort i = 1; i < this->Height()-1; ++i)
	{
		for(UShort k = 1; k < this->Width()-1; ++k)
		{
			UShort sum = SumOfNeighborsNeumann(i, k);
			//unsigned short sum = SumOfNeighborsMoore(i, k, range);
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


	UShort SumOfNeighborsMoore(const UShort heightArg, const UShort widthArg) const
	{
		UShort sum = 0;
		UShort range = rules.GetRange();
		bool middle = rules.GetMiddle();
		
		for(int arrY = heightArg-range; arrY <= static_cast<int>(heightArg + range); ++arrY)
		{
			for(int arrX = widthArg-range; arrX <= static_cast<int>(widthArg + range); ++arrX)
			{
				if(arrX < 0 || static_cast<UShort>(arrX) >= Width() || arrY < 0 || static_cast<UShort>(arrY) >= Height()) continue;
				sum += ALIVE == (*current)[arrY][arrX];
			}
		}
		if(!middle) sum -= ALIVE == (*current)[heightArg][widthArg];
		return sum;
	}

	unsigned short SumOfNeighborsNeumann(const UShort heightArg, const UShort widthArg) const
	{
		UShort sum = 0;
		UShort range = rules.GetRange();
		bool middle = rules.GetMiddle();
		
		for(int arrY = heightArg-range; arrY <= static_cast<int>(heightArg + range); ++arrY)
		{
			for(int arrX = widthArg + abs(arrY - heightArg) - range - 1; arrX <= widthArg - abs(arrY - heightArg) + range + 1; ++arrX)
			{
				if(arrX < 0 || static_cast<UShort>(arrX) >= Width() || arrY < 0 || static_cast<UShort>(arrY) >= Height()) continue;
				sum += ALIVE == (*current)[arrY][arrX];
			}
		}
		if(!middle) sum -= ALIVE == (*current)[heightArg][widthArg];
		return sum;


		// UShort sum = 0;
		// sum += ALIVE == (*current)[heightArg - 1][widthArg];
		// sum += ALIVE == (*current)[heightArg][widthArg - 1];
		// sum += ALIVE == (*current)[heightArg][widthArg + 1];
		// sum += ALIVE == (*current)[heightArg + 1][widthArg];
		// return sum;
	}

};

#endif