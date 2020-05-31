#include "RegularUnit.hpp"
#include "Board.hpp"

int RegularUnit::player_A_count = 0;
int RegularUnit::player_B_count = 0;


RegularUnit::RegularUnit(int v, TURN player)
    : Unit(v, "regular", player)
{
    if (player == TURN::PLAYER_A)
        player_A_count++;
    if (player == TURN::PLAYER_B)
        player_B_count++;
}

RegularUnit::~RegularUnit()
{
    if (get_owner() == TURN::PLAYER_A) {
        player_A_count--;
    }
    if (get_owner() == TURN::PLAYER_B) {
        player_B_count--;
    }
}