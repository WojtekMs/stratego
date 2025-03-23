#include "unit/UnitModel.hpp"

UnitModel::UnitModel(int value, std::string type, Turn player) 
: value_(value),
  type_(std::move(type)),
  owner_(player) {} 


int UnitModel::get_value() const noexcept { return value_; }
[[deprecated("Future refactoring will remove get_type()")]] 
std::string UnitModel::get_type() const noexcept { return type_; }
Turn UnitModel::get_owner() const noexcept { return owner_; }