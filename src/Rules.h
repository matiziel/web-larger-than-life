#ifndef RULES_H
#define RULES_H

enum NeighbourhoodTypes {Moore, Neumann, Circular};

class Rules
{
    typedef unsigned int Uint;
private:

Uint range;
Uint numberOfStates;
bool middleCell;
Uint survivalMin;
Uint survivalMax;
Uint birthMin;
Uint birthMax;
NeighbourhoodTypes neighbourhoodType;

public:
    Rules(Uint rArg = 1, Uint cArg = 2, bool mArg = 0, Uint sMinArg = 2,
    Uint sMaxArg = 3, Uint bMinArg = 3, Uint bMaxArg = 3, NeighbourhoodTypes nArg = Moore):
    range(rArg),
    numberOfStates(cArg),
    middleCell(mArg),
    survivalMin(sMinArg),
    survivalMax(sMaxArg),
    birthMin(bMinArg),
    birthMax(bMaxArg),
    neighbourhoodType(nArg) {}

    const Uint GetRange() const
    {
        return range;
    }
    const Uint GetStates() const
    {
        return numberOfStates;
    }
    const Uint GetMiddle() const
    {
        return middleCell;
    }
    const Uint GetSMin() const
    {
        return survivalMin;
    }
    const Uint GetSMax() const
    {
        return survivalMax;
    }
    const Uint GetBMin() const
    {
        return birtMin;
    }
    const Uint GetBMax() const
    {
        return birthMax;
    }
    const Uint GetN() const
    {
        return neighbourhoodType;
    }

    ~Rules();
};
#endif