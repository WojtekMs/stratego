#pragma once
#include <string>

enum class TURN;
class Unit
{
    int value;
    std::string name;
    TURN owner;
    int x;
    int y;
    
    public:
    Unit(int v, std::string n, TURN player) :value(v), name(n), owner(player) { x = -1; y = -1; };
    inline virtual bool can_move(int col, int row) = 0;
    int get_value() const { return value; };
    std::string get_type() const { return name; };
    int get_x() const { return x; };
    int get_y() const { return y; };
    TURN get_owner() const { return owner; };
    inline void set_position(int Ax, int Ay);
    virtual int get_player_A_count() = 0;
    virtual int get_player_B_count() = 0; 
    virtual ~Unit() {};

};

void Unit::set_position(int Ax, int Ay) {
    x = Ax;
    y = Ay;

}

bool Unit::can_move(int col, int row) {
    if (col > get_x() + 1 || col < get_x() - 1) {
        return false;
    }
    if (row > get_y() + 1 || row < get_y() - 1) {
        return false;
    }
}
