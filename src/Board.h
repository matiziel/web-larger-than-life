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
		//Initialize();
	}
	void SetRandomBoard(int percentAlive)
	{
		srand (time(NULL)); //ja bym srandowal gdzie indziej, np w konstruktorze
		for(UShort i = 0; i < this->Height(); ++i)
		{
			for(UShort k = 0; k < this->Width(); ++k)
			{
				(*current)[i][k] = 0==((rand() % 100) / percentAlive); //percentAlive procent jest zywe
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
	// void SetRules(Ushort rArg = 1, Ushort cArg = 2, bool mArg = 0, Ushort sMinArg = 2,
    // Ushort sMaxArg = 3, Ushort bMinArg = 3, Ushort bMaxArg = 3, NeighbourhoodTypes nArg = Moore)
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
	for(UShort i = 0; i < this->Height(); ++i)
	{
		for(UShort k = 0; k < this->Width(); ++k)
		{
			UShort sum = SumOfNeighboursMoore(i, k);
			// UShort sum = SumOfNeighboursNeumann(i, k);
			// UShort sum = SumOfNeighbours(i, k); // tak powinno być ale nie działa
			if((*current)[i][k] == DEAD)
			{
				if(sum >= rules.GetBMin() && sum <= rules.GetBMax()) 
					(*next)[i][k] = ALIVE;
				else 
					(*next)[i][k] = DEAD;
			}
			else 
			{
				if(sum >= rules.GetSMin() && sum <= rules.GetSMax()) 
					(*next)[i][k] = ALIVE;
				else 
					(*next)[i][k] = DEAD;
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
	// const UShort (*SumOfNeighbours) (const UShort, const UShort) const;
	// function pointer przechowujacy pointer do odpowiedniej funckji sumowania sąsiedztwa ale nie działa

	const UShort SumOfNeighboursMoore(const UShort heightArg, const UShort widthArg) const
	{
		UShort sum = 0;
		
		for(int arrY = heightArg - rules.GetRange(); arrY <= static_cast<int>(heightArg + rules.GetRange()); ++arrY)
		{
			for(int arrX = widthArg - rules.GetRange(); arrX <= static_cast<int>(widthArg + rules.GetRange()); ++arrX)
			{
				if(arrX < 0 || static_cast<UShort>(arrX) >= Width() || arrY < 0 || static_cast<UShort>(arrY) >= Height()) continue;
				sum += ALIVE == (*current)[arrY][arrX];
			}
		}
		if(!rules.GetMiddle()) sum -= ALIVE == (*current)[heightArg][widthArg];
		return sum;
	}

	const UShort SumOfNeighboursNeumann(const UShort heightArg, const UShort widthArg) const
	{
		UShort sum = 0;
		
		for(int arrY = heightArg - rules.GetRange(); arrY <= static_cast<int>(heightArg + rules.GetRange()); ++arrY)
		{
			for(int arrX = widthArg + abs(arrY - heightArg) - rules.GetRange(); arrX <= widthArg - abs(arrY - heightArg) + rules.GetRange(); ++arrX)
			{
				if(arrX < 0 || static_cast<UShort>(arrX) >= Width() || arrY < 0 || static_cast<UShort>(arrY) >= Height()) continue;
				sum += ALIVE == (*current)[arrY][arrX];
			}
		}
		if(!rules.GetMiddle()) sum -= ALIVE == (*current)[heightArg][widthArg];
		return sum;
	}

	// void Initialize() //metoda do ustawiania potrzebnych rzeczy z reguł, wywoływana w konstruktorze i w razie zmiany zasad
	// {
	// 	if(rules.GetN() == Moore) SumOfNeighbours = SumOfNeighboursMoore;
	// 	else if(rules.GetN() == Neumann) SumOfNeighbours = SumOfNeighboursNeumann;
	// 	else if(rules.GetN==Circular) sumOfNeighbours = SumOfNeighboursCircular;
	// }
};

#endif