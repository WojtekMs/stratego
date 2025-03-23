#pragma once 

#include <string>
#include <variant>
#include <optional>

#include "Tile.hpp"
#include "unit/Unit.hpp"
#include "unit/UnitConcepts.hpp"

namespace attack {
enum class Result
{
    Lost,
    Draw,
    Won,
};

class InvalidUnitError : public std::exception {
    public:
    const char* what() const noexcept override { return "Invalid unit attacked or was being attacked\n"; }
};

} // namespace attack


class Attack {
    template <unit::Attackable T, unit::Attackable U>
    attack::Result regular_attack(const T& lhs, const U& rhs) {
        if (lhs.get_value() > rhs.get_value())
        {
            return attack::Result::Won;
        }
        if (lhs.get_value() == rhs.get_value())
        {
            return attack::Result::Draw;
        }
        return attack::Result::Lost;
    }
public:
    attack::Result operator()(const SpyUnit&, const RegularUnit& rhs) {
        if (rhs.get_value() == UnitModel::MARSHAL_VALUE) {
            return attack::Result::Won;
        }
        return attack::Result::Lost;
    }
    attack::Result operator()(const MinerUnit&, const BombUnit&) {
        return attack::Result::Won;
    }
    template <unit::Attackable T>
    attack::Result operator()(const T&, const BombUnit&) {
        return attack::Result::Lost;
    }
    template <unit::Attackable T, unit::Attackable U>
    attack::Result operator()(const T& lhs, const U& rhs) {
        return regular_attack(lhs, rhs);
    }
    template <typename T, typename U>
    attack::Result operator()(const T& lhs, const U& rhs) {
        throw attack::InvalidUnitError();
    }
};