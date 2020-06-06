#include "MinerUnit.hpp"
#include "Board.hpp"


MinerUnit::MinerUnit(TURN player)
    : Unit(3, "miner", player)
{
}

MinerUnit::~MinerUnit()
{
}

MinerUnit::MinerUnit(const Unit& rhs)
:Unit(rhs)
{

}

bool MinerUnit::can_move(int col, int row) {
    return false;
}
