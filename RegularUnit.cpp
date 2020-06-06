#include "RegularUnit.hpp"

#include "Board.hpp"


RegularUnit::RegularUnit(int v, TURN player)
    : Unit(v, "regular", player) {
}

RegularUnit::RegularUnit(const RegularUnit& rhs)
    : Unit(rhs) {
}

RegularUnit::RegularUnit(const Unit& rhs) 
:Unit(rhs)
{


}


RegularUnit::~RegularUnit() {
}