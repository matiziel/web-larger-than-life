#ifndef RULES_H
#define RULES_H

enum NeighbourhoodTypes {Moore, Neumann, Circular};

struct Rules
{
    typedef unsigned short UShort;

    UShort range;
    UShort numberOfStates;
    bool middleCell;
    UShort survivalMin;
    UShort survivalMax;
    UShort birthMin;
    UShort birthMax;
    NeighbourhoodTypes neighbourhoodType;

    Rules(
        UShort rArg = 1,
        UShort cArg = 2,
        bool mArg = 0,
        UShort sMinArg = 2,
        UShort sMaxArg = 3,
        UShort bMinArg = 3,
        UShort bMaxArg = 3,
        NeighbourhoodTypes nArg = Moore
        ):
            range(rArg),
            numberOfStates(cArg),
            middleCell(mArg),
            survivalMin(sMinArg),
            survivalMax(sMaxArg),
            birthMin(bMinArg),
            birthMax(bMaxArg),
            neighbourhoodType(nArg) {}
};
#endif