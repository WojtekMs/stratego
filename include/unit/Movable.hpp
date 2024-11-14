#pragma once

#include <memory>
#include "Tile.hpp"

enum class RESULT {
    LOST,
    DRAW,
    WON,
};

class Unit;

class Movable {
public:
    class Delegate {
    public:
        virtual int get_value() const = 0;
        ~Delegate(){};
    };

private:
    Delegate* delegate;

public:
    explicit Movable(Delegate* del);
    virtual bool can_move(int from_x, int from_y, int to_x, int to_y) const = 0;
    virtual bool can_move(const Tile& from, const Tile& to) const { return can_move(from.x, from.y, to.x, to.y); };
    virtual RESULT attack(const std::shared_ptr<Unit>& rhs) const = 0;

    virtual ~Movable(){};
};
