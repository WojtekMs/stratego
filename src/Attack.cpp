#include "Attack.h"

#include <iostream>
#include <optional>
#include <concepts>
#include <functional>

namespace attack::details {
template <typename Lhs, typename Rhs>
requires std::derived_from<Lhs, Unit> && std::derived_from<Rhs, Unit>
std::optional<Result> conditional_call(const std::shared_ptr<Unit>& lhs, const std::shared_ptr<Unit>& rhs, std::function<Result(Lhs&, Rhs&)> fun) {
    Lhs* lptr = dynamic_cast<Lhs*>(lhs.get()); 
    Rhs* rptr = dynamic_cast<Rhs*>(rhs.get());
    if (lptr && rptr) {
        return fun(*lptr, *rptr);
    }
    return std::nullopt;
}

Result basicAttack(Unit& lhs, Unit& rhs) {
    if (lhs.get_value() > rhs.get_value())
    {
        return Result::Won;
    }
    if (lhs.get_value() == rhs.get_value())
    {
        return Result::Draw;
    }
    return Result::Lost;
}

Result attackMinerBomb(MinerUnit& lhs, BombUnit& rhs) {
    return Result::Won;
}

Result attackUnitBomb(Unit& lhs, BombUnit& rhs) {
    return Result::Lost;
}

Result attackSpyRegular(SpyUnit& lhs, RegularUnit& rhs) {
    if (rhs.get_value() == Unit::MARSHAL_VALUE) {
        return Result::Won;
    }
    return Result::Lost;
}
}

namespace attack
{
    std::string toString(Result result) {
        switch(result) {
            case Result::Lost:
                return "Result::Lost";
            case Result::Won:
                return "Result::Won";
            case Result::Draw:
                return "Result::Draw";
        }
        throw std::invalid_argument("Unknown enum Result value");
    }

    void validateUnits(const std::shared_ptr<Unit> &lhs, const std::shared_ptr<Unit> &rhs)
    {
        if (!lhs || !rhs)
        {
            throw std::invalid_argument("Attack.cpp attack: one of the units is nullptr");
        }
    }

    Result attack(const std::shared_ptr<Unit> &lhs, const std::shared_ptr<Unit> &rhs)
    {
        validateUnits(lhs, rhs);
        if(auto result = details::conditional_call<MinerUnit, BombUnit>(lhs, rhs, details::attackMinerBomb); result) {
            return result.value();
        }
        if(auto result = details::conditional_call<Unit, BombUnit>(lhs, rhs, details::attackUnitBomb); result) {
            return result.value();
        }
        if(auto result = details::conditional_call<SpyUnit, RegularUnit>(lhs, rhs, details::attackSpyRegular); result) {
            return result.value();
        }
        return details::basicAttack(*lhs, *rhs);
    }
}