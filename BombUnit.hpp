#pragma once
#include "Unit.hpp"

enum class TURN;
class BombUnit :public Unit 
{

    public:
    BombUnit(const Unit& rhs);
    BombUnit(TURN player); 
    ~BombUnit();
    virtual bool can_move(int col, int row) { return false; };

};

