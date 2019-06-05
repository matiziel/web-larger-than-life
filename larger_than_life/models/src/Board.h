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
	void SetRules(UShort rArg = 1, UShort cArg = 2, bool mArg = 0, UShort sMinArg = 2,
    UShort sMaxArg = 3, UShort bMinArg = 3, UShort bMaxArg = 3, UShort nArg = 0)
	{
		rules.SetRules(rArg, cArg, mArg, sMinArg, sMaxArg, bMinArg, bMaxArg, nArg);			
		if(rules.GetN() == 1) 
			sumOfNeighbours = std::bind(&Board::SumOfNeighboursCircular, this, std::placeholders::_1, std::placeholders::_2);
		else if(rules.GetN() == 2) 
			sumOfNeighbours = std::bind(&Board::SumOfNeighboursNeumann, this, std::placeholders::_1, std::placeholders::_2);


	}

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
			throw std::out_of_range("Board overflow");
		return static_cast<int>((*current)[heightArg][widthArg]);
	}

void Update()
{
	for(UShort i = 0; i < this->Height(); ++i)
	{
		for(UShort k = 0; k < this->Width(); ++k)
		{
			UShort sum = sumOfNeighbours(i,k);
			
			if((*current)[i][k] == 0) //Jeżeli martwe to ożywa albo zostaje martwe
			{
				if(sum >= rules.GetBMin() && sum <= rules.GetBMax()) 
					(*next)[i][k] = 1;
				else 
					(*next)[i][k] = 0;
			}
			else if((*current)[i][k] == 1) //Jeżeli żywe to przeżywa albo zaczyna się starzeć
			{
				if(sum >= rules.GetSMin() && sum <= rules.GetSMax()) 
					(*next)[i][k] = 1;
				else 
					(*next)[i][k] = 2%rules.GetStates();
			}
			else (*next)[i][k] = (1+(*current)[i][k])%rules.GetStates(); //Starzeje się
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

	std::function<int(int, int)> sumOfNeighbours;
	Rules rules;

	const UShort SumOfNeighboursMoore(const UShort heightArg, const UShort widthArg) const
	{
		// if(heightArg < 0 || heightArg > this->Height() || widthArg < 0 || widthArg > this->Width())
		// 	throw std::out_of_range("Moore Neighbours overflow");
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
		// if(heightArg < 0 || heightArg > this->Height() || widthArg < 0 || widthArg > this->Width())
		// 	throw std::out_of_range("Neumann Neighbours overflow");
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
		// if(heightArg < 0 || heightArg > this->Height() || widthArg < 0 || widthArg > this->Width())
		// 	throw std::out_of_range("Circular Neighbours overflow");

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