#include "GameView.hpp"

GameView::GameView(Player& pA, Player& pB) 
:playerA(pA),
playerB(pB)
{
    if (!board_border_texture.loadFromFile("/home/wojtek/cpp/Programowanie/Obiektowe/Studia_projekt/stratego/images/board/border_scaled.png")) {
        std::cerr << "board border error loading from file!\n";
        abort();
    }

    board_border.setTexture(board_border_texture);
}


void GameView::draw(sf::RenderWindow& win) {
    win.draw(board_border);

}