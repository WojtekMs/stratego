#pragma once
#include "Unit.hpp"


enum class TURN;
class RegularUnit : public Unit
{
    static int player_A_count;
    static int player_B_count;

public:
    RegularUnit(int v, TURN player);
    virtual bool can_move(int col, int row) { Unit::can_move(col, row); };
    ~RegularUnit();
    int get_player_A_count() { return player_A_count; };
    int get_player_B_count() { return player_B_count; };
    RegularUnit(const RegularUnit &) = delete;
    RegularUnit& operator=(const RegularUnit &) = delete;

};


