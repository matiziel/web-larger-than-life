#ifndef RULES_H
#define RULES_H

#include <iostream>

class Rules
{
    typedef unsigned short UShort;

    UShort range;
    UShort numberOfStates;
    bool middleCell;
    UShort survivalMin;
    UShort survivalMax;
    UShort birthMin;
    UShort birthMax;
    UShort neighbourhoodType;
public:
    Rules(
        UShort rArg = 1,
        UShort cArg = 2,
        bool mArg = 0,
        UShort sMinArg = 2,
        UShort sMaxArg = 3,
        UShort bMinArg = 3,
        UShort bMaxArg = 3,
        UShort nArg = 0
        ):
            range(rArg),
            numberOfStates(cArg),
            middleCell(mArg),
            survivalMin(sMinArg),
            survivalMax(sMaxArg),
            birthMin(bMinArg),
            birthMax(bMaxArg),
            neighbourhoodType(nArg) {}

    const UShort GetRange() const
    {
        return range;
    }
    const UShort GetStates() const
    {
        return numberOfStates;
    }
    const UShort GetMiddle() const
    {
        return middleCell;
    }
    const UShort GetSMin() const
    {
        return survivalMin;
    }
    const UShort GetSMax() const
    {
        return survivalMax;
    }
    const UShort GetBMin() const
    {
        return birthMin;
    }
    const UShort GetBMax() const
    {
        return birthMax;
    }
    const UShort GetN() const
    {
        return neighbourhoodType;
    }

    void SetRules(UShort rArg = 1, UShort cArg = 2, bool mArg = 0, UShort sMinArg = 2,
    UShort sMaxArg = 3, UShort bMinArg = 3, UShort bMaxArg = 3, UShort nArg = 0)
    {
        if(rArg < 1 || rArg > 500) throw std::invalid_argument("Invalid range parameter");
        if(cArg < 0 || cArg > 255) throw std::invalid_argument("Invalid number of states parameter");
        if(sMinArg < 0 || sMinArg > sMaxArg) throw std::invalid_argument("Invalid survival parameters");
        if(bMinArg < 1 || bMinArg > bMaxArg) throw std::invalid_argument("Invalid birth parameters");
	if(nArg < 0 || nArg > 2 ) throw std::invalid_argument("Invalid neighbourhood type parameter");

        range = rArg;
        numberOfStates = cArg;
        middleCell = mArg;
        survivalMin = sMinArg;
        survivalMax = sMaxArg;
        birthMin = bMinArg;
        birthMax = bMaxArg;
        neighbourhoodType = nArg;

        if(numberOfStates<2) numberOfStates = 2;
    }
};
#endif
