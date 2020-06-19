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
    void remove_unit(Board::Tile chosen_unit);
    void reverse_remove_unit(Board::Tile unit);
    bool move_unit(Board::Tile from, Board::Tile to);
    RESULT attack(Board::Tile attacker, Board::Tile attacked);
    void reverse_move_unit(Board::Tile from, Board::Tile to);
    void update_board(const Board& other_player_board);
    const Board& get_board() { return board; };
    std::string get_tile_info(int col, int row) const;
    std::string get_tile_info(Board::Tile tile) const;
    bool can_move(Board::Tile from, Board::Tile to);
};