#include "BombUnit.hpp"
#include "Board.hpp"


BombUnit::BombUnit(TURN player)
: Unit(0, "bomb", player)
{
  
} 

BombUnit::~BombUnit()
{
   

}

BombUnit::BombUnit(const Unit& rhs)
:Unit(rhs)
{

}