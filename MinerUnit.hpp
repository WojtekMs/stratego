#pragma once
#include "Unit.hpp"

enum class TURN;
class MinerUnit :public Unit 
{
    static int player_A_count;
    static int player_B_count;

    public:
    MinerUnit(TURN player);
    ~MinerUnit();
    MinerUnit(const MinerUnit&) = delete;
    MinerUnit& operator=(const MinerUnit&) = delete;

};