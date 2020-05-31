#include "MinerUnit.hpp"
#include "Board.hpp"

int MinerUnit::player_A_count = 0;
int MinerUnit::player_B_count = 0;

MinerUnit::MinerUnit(TURN player)
    : Unit(3, "miner", player)
{
    if (player == TURN::PLAYER_A) {
        player_A_count++;
    }
    if (player == TURN::PLAYER_B) {
        player_B_count++;
    }
}

MinerUnit::~MinerUnit()
{
    if (get_owner() == TURN::PLAYER_A) {
        player_A_count--;
    }
    if (get_owner() == TURN::PLAYER_B) {
        player_B_count--;
    }
}