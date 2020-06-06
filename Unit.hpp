#pragma once
#include <string>

enum class TURN;
class Unit
{
    int value;
    std::string type;
    TURN owner;
    int x;
    int y;
    
    public:
    Unit() {};
    Unit(int v, const std::string& t, TURN player) :value(v), type(t), owner(player) { x = -1; y = -1; };
    inline Unit(const Unit& rhs);
    inline virtual bool can_move(int col, int row) = 0;
    int get_value() const { return value; };
    std::string get_type() const { return type; };
    int get_x() const { return x; };
    int get_y() const { return y; };
    TURN get_owner() const { return owner; };
    inline void set_position(int Ax, int Ay);
    virtual ~Unit() {};

};

Unit::Unit(const Unit& rhs) {
    value = rhs.value;
    type = rhs.type;
    owner = rhs.owner;
    x = rhs.x;
    y = rhs.y;
}

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

    
