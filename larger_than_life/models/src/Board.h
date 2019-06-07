#ifndef BOARD_H
#define BOARD_H
#include "boost/multi_array.hpp"
#include <thread>
#include "Rules.h"
#include <cmath>
#include <iostream>
#include <functional>

const unsigned short DEFAULT_SIZE = 256; 

class Board
{
	typedef boost::multi_array<int, 2> MultiArray;
	typedef unsigned short UShort;
public:
	Board(const UShort height = DEFAULT_SIZE, const UShort width = DEFAULT_SIZE) 
	: gridA(boost::extents[height][width]), gridB(boost::extents[height][width])
	{
		for(UShort i = 0; i < height; ++i)
		{
			for(UShort k = 0; k < width; ++k)
			{
				gridA[i][k] = gridB[i][k] = 0;
			}
		}
		current = &gridA;
		next = &gridB;
		sumOfNeighbours = std::bind(&Board::SumOfNeighboursMoore, this, std::placeholders::_1, std::placeholders::_2);
	}
	///
	///SetRandomBoard sets the initial content of the grid to random values
	///percentAlive variable determines how much of the grid will be alive
	///
	void SetRandomBoard(int percentAlive)
	{
		srand (time(NULL));
		for(UShort i = 0; i < this->Height(); ++i)
		{
			for(UShort k = 0; k < this->Width(); ++k)
			{
				(*current)[i][k] = 0==((rand() % 100) / percentAlive);
			}
		}
	}
	///
	///SetConstBoard sets the initial content of the grid to a block in the middle and a blinker
	///This configuration is useful for debugging and checking many diffrent rules
	///
	void SetConstBoard()
	{
		UShort k = Width()/2;
		UShort i = Height()/2;
		(*current)[i][k] = 1;
		(*current)[i][k-1] = 1;
		(*current)[i-1][k] = 1;
		(*current)[i-1][k-1] = 1;

		k = Width()/4;
		i = Height()/4;
		(*current)[i][k] = 1;
		(*current)[i+1][k] = 1;
		(*current)[i+2][k] = 1;

	}
	///
	///SetRules sets the game rules according to the RCMSBN standard
	///
	///the arguments are respevtively: range, number of cells, middle inclusion, survival lower bound, 
	///survival upper bound, birth lower bound, birth upper bound, neighbourhood type
	///
	void SetRules(UShort rArg = 1, UShort cArg = 2, bool mArg = 0, UShort sMinArg = 2,
    UShort sMaxArg = 3, UShort bMinArg = 3, UShort bMaxArg = 3, UShort nArg = 0)
	{
		rules.SetRules(rArg, cArg, mArg, sMinArg, sMaxArg, bMinArg, bMaxArg, nArg);			
		if(rules.GetN() == 1) 
			sumOfNeighbours = std::bind(&Board::SumOfNeighboursNeumann, this, std::placeholders::_1, std::placeholders::_2);
		else if(rules.GetN() == 2) 
			sumOfNeighbours = std::bind(&Board::SumOfNeighboursCircular, this, std::placeholders::_1, std::placeholders::_2);


	}
	///
	///GetPixelState returns current value of a grid element.
	///
	int GetPixelState(const UShort heightArg, const UShort widthArg) const 
	{
		if(heightArg >= this->Height() || widthArg >= this->Width())
			throw std::out_of_range("Board overflow");
		return static_cast<int>((*current)[heightArg][widthArg]);
	}
	UShort Width() const 
	{
		return (*current).shape()[1];
	}

	UShort Height() const 
	{
		return (*current).shape()[0];
	}

void Update()
{
	std::thread t0(&Board::UpdatePart, this, 0);
	std::thread t1(&Board::UpdatePart, this, 1);
	std::thread t2(&Board::UpdatePart, this, 2);
	std::thread t3(&Board::UpdatePart, this, 3);
	t0.join();
	t1.detach();
	t2.join();
	t3.join();
	MultiArray* temp = current;
	current = next;
	next = temp;
}

void UpdatePart(const int partInd)
{
	const int start = this->Height() * partInd / 4;
	const int end   = this->Height() * (partInd + 1) / 4;
	for(UShort i = start; i < end; ++i)
	{
		for(UShort k = 0; k < this->Width(); ++k)
		{
			UShort sum = sumOfNeighbours(i,k);
			
			if((*current)[i][k] == 0) //If dead, stays dead or becomes alive
			{
				if(sum >= rules.GetBMin() && sum <= rules.GetBMax()) 
					(*next)[i][k] = 1;
				else 
					(*next)[i][k] = 0;
			}
			else if((*current)[i][k] == 1) //If alive, stays alive or starts to decay
			{
				if(sum >= rules.GetSMin() && sum <= rules.GetSMax()) 
					(*next)[i][k] = 1;
				else 
					(*next)[i][k] = 2%rules.GetStates();
			}
			else (*next)[i][k] = (1+(*current)[i][k])%rules.GetStates(); //Decays
		}
	}
}

private:
	MultiArray gridA;
	MultiArray gridB;
	MultiArray* current;
	MultiArray* next;

	std::function<int(int, int)> sumOfNeighbours;
	Rules rules;

	const UShort SumOfNeighboursMoore(const UShort heightArg, const UShort widthArg) const
	{
		UShort sum = 0;
		
		for(int arrY = heightArg - rules.GetRange(); arrY <= static_cast<int>(heightArg + rules.GetRange()); ++arrY)
		{
			for(int arrX = widthArg - rules.GetRange(); arrX <= static_cast<int>(widthArg + rules.GetRange()); ++arrX)
			{
				if(arrX < 0 || static_cast<UShort>(arrX) >= Width() || arrY < 0 || static_cast<UShort>(arrY) >= Height()) continue;
				sum += 1 == (*current)[arrY][arrX];
			}
		}
		if(!rules.GetMiddle()) sum -= 1 == (*current)[heightArg][widthArg];
	

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
				sum += 1 == (*current)[arrY][arrX];
			}
		}
		if(!rules.GetMiddle()) sum -= 1 == (*current)[heightArg][widthArg];
		return sum;
	}

	const UShort SumOfNeighboursCircular(const UShort heightArg, const UShort widthArg) const
	{
		UShort sum = 0;
		float rangeSquared = (rules.GetRange()+0.5)*(rules.GetRange()+0.5);
		for(int arrY = heightArg - rules.GetRange(); arrY <= static_cast<int>(heightArg + rules.GetRange()); ++arrY)
		{
			for(int arrX = widthArg - rules.GetRange(); arrX <= static_cast<int>(widthArg + rules.GetRange()); ++arrX)
			{
				if(arrX < 0 || static_cast<UShort>(arrX) >= Width() || arrY < 0 || static_cast<UShort>(arrY) >= Height()) continue;
				if((arrX-widthArg) * (arrX-widthArg) + (arrY-heightArg) * (arrY-heightArg) > rangeSquared) continue;
				sum += 1 == (*current)[arrY][arrX];
			}
		}
		if(!rules.GetMiddle()) sum -= 1 == (*current)[heightArg][widthArg];
		return sum;
	}
};
#endif