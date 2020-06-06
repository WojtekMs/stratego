#pragma once
#include "Unit.hpp"

enum class TURN;
class MinerUnit :public Unit 
{

    public:
    MinerUnit(const Unit& rhs);
    MinerUnit(TURN player);
    ~MinerUnit();
    virtual bool can_move(int col, int row) override;

};