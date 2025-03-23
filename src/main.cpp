#include <iostream>
#include <map>

#include "Board.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "unit/RegularUnit.hpp"

int main() {
  Board board;
  Player playerA("Red-A", Turn::PlayerA);
  Player playerB("Blue-B", Turn::PlayerB);
  GameView game_view(playerA, playerB);
  GameController game_controller(playerA, playerB, game_view);
  Game game(game_view, game_controller);
  MainMenu menu(playerA, playerB);
  std::map<std::string, cScreen *> screens;
  screens["menu"] = &menu;
  screens["game"] = &game;
  std::string screen = "menu";
  const unsigned int width =
      static_cast<unsigned int>(game_view.get_window_size().x);
  const unsigned int height =
      static_cast<unsigned int>(game_view.get_window_size().y);
  sf::RenderWindow window(sf::VideoMode(width, height), "stratego");
  while (screen != "exit") {
    screen = screens[screen]->run(window);
  }
}
