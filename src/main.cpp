#include <iostream>
#include "Board.hpp"
#include "RegularUnit.hpp"
#include "Player.hpp"
#include "test.hpp"
#include "Game.hpp"

int main() {
    Board board;
    Player playerA("Red-A", TURN::PLAYER_A);
    Player playerB("Blue-B", TURN::PLAYER_B);
    GameView game_view(playerA, playerB);
    GameController game_controller(playerA, playerB, game_view);
    Game game(game_view, game_controller);
    game.run();
    

    // testing(board, playerA, playerB);
    
}
