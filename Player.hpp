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
    int get_units_count(const std::string& type) const { return units_count.at(type); };
    int get_units_count(int idx);
    TURN get_player_number() { return player; };
    void set_unit(int col, int row, int choice);
    void remove_unit(int col, int row);
    void move_unit(Board::Tile from, Board::Tile to);
    void update_board(const Board& other_player_board);
    const Board& get_board() { return board; };
    bool can_move(int col, int row);
    std::string get_tile_info(int col, int row);
};