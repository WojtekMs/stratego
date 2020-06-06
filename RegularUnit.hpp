#pragma once
#include "Unit.hpp"


enum class TURN;
class RegularUnit : public Unit
{

public:
    RegularUnit(int v, TURN player);
    RegularUnit(const Unit& rhs);
    RegularUnit(const RegularUnit& rhs);
    virtual bool can_move(int col, int row) { Unit::can_move(col, row); };
    ~RegularUnit();

};


