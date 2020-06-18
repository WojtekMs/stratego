#include <iostream>
#include "Board.hpp"
#include "RegularUnit.hpp"
#include "Player.hpp"
#include "test.hpp"

int main() {
    Board board;
    Player playerA("A", TURN::PLAYER_A);
    Player playerB("B", TURN::PLAYER_B);

    testing(board, playerA, playerB);
    
}
