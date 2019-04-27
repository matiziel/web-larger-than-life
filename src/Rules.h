#ifndef RULES_H
#define RULES_H

enum NeighbourhoodTypes {Moore, Neumann, Circular};

class Rules
{
    typedef unsigned short UShort;
private:

UShort range;
UShort numberOfStates;
bool middleCell;
UShort survivalMin;
UShort survivalMax;
UShort birthMin;
UShort birthMax;
NeighbourhoodTypes neighbourhoodType;

public:
    Rules(UShort rArg = 1, UShort cArg = 2, bool mArg = 0, UShort sMinArg = 2,
    UShort sMaxArg = 3, UShort bMinArg = 3, UShort bMaxArg = 3, NeighbourhoodTypes nArg = Moore):
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

    //~Rules();
};
#endif