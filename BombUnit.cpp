#include "BombUnit.hpp"
#include "Board.hpp"

int BombUnit::player_A_count = 0;
int BombUnit::player_B_count = 0;

BombUnit::BombUnit(TURN player)
: Unit(0, "bomb", player)
{
    if(player == TURN::PLAYER_A) {
        player_A_count++;
    }
    if (player == TURN::PLAYER_B) {
        player_B_count++;
    }

} 

BombUnit::~BombUnit()
{
    if(get_owner() == TURN::PLAYER_A) {
        player_A_count--;
    }
    if(get_owner() == TURN::PLAYER_B) {
        player_B_count--;
    }

}