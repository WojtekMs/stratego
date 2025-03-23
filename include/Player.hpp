#pragma once
#include <string>
#include <unordered_map>

#include "Board.hpp"
#include "unit/visit/Attack.hpp"

enum class Turn;
class Player
{
    std::string name;
    Turn player;
    Board board;
    
    public:
    Player(std::string n, Turn p): name(n), player(p), board() { };
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