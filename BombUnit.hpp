#pragma once
#include "Unit.hpp"

enum class TURN;
class BombUnit :public Unit 
{
    static int player_A_count;
    static int player_B_count;

    public:
    BombUnit(TURN player); 
    ~BombUnit();
    BombUnit(const BombUnit&) = delete;
    BombUnit& operator=(const BombUnit&) = delete;
    virtual bool can_move(int col, int row) { return false; };

};

