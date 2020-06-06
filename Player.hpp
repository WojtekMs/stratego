#pragma once
#include <string>
#include <unordered_map>

#include "Board.hpp"

enum class TURN;
class Player
{
    std::string name;
    TURN player;
    std::unordered_map<std::string, int> units_count;
    Board board;
    
    void set_units_count();
    public:
    Player(std::string n, TURN p): name(n), player(p), units_count(), board() { set_units_count(); };
    int get_units_count(const std::string& type) { return units_count[type]; };
    TURN get_player_number() { return player; };
    void set_unit(int col, int row, int choice);
    void remove_unit(int col, int row);
    void move_unit(std::pair<int, int> from, std::pair<int, int> to);
    void update_board(const Board& other_player_board);
    const Board& get_board() { return board; };
};