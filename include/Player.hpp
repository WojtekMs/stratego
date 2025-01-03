#pragma once
#include <string>
#include <unordered_map>

#include "Board.hpp"
#include "Attack.h"

enum class Turn;
class Player
{
    std::string name;
    Turn player;
    std::unordered_map<std::string, int> units_count;
    Board board;
    
    void set_units_count();
    public:
    Player(std::string n, Turn p): name(n), player(p), units_count(), board() { set_units_count(); };
    int get_units_count(const std::string& type) const { return units_count.at(type); };
    int get_units_count(int idx);
    Turn get_player_number() { return player; };
    std::string get_player_name() { return name; };
    void set_unit(int col, int row, int choice);
    void remove_unit(int col, int row);
    void remove_unit(Tile chosen_unit);
    void reverse_remove_unit(Tile unit);
    bool move_unit(Tile from, Tile to);
    attack::Result attack(Tile attacker, Tile attacked);
    void reverse_move_unit(Tile from, Tile to);
    void update_board(const Board& other_player_board);
    const Board& get_board() { return board; };
    std::string get_tile_info(int col, int row) const;
    std::string get_tile_info(Tile tile) const;
    bool can_move(Tile from, Tile to);
    void set_name(const std::string& n) { name = n; };
};