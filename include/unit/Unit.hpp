#pragma once

#include <memory>
#include <string>
#include "Tile.hpp"

enum class Turn;

class Unit
{
private:
    int value_{};
    std::string type_{};
    Turn owner_{};

public:
    static constexpr int MARSHAL_VALUE{10};
    Unit() = default;
    Unit(int value, std::string type, Turn player);

    int get_value() const noexcept;
    [[deprecated("Future refactoring will remove get_type()")]] std::string get_type() const noexcept;
    Turn get_owner() const noexcept;

    virtual bool can_move(const Tile &from, const Tile &to) const;

    virtual ~Unit() = default;
};
