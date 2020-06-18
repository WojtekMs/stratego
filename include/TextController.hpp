#pragma once

#include "Player.hpp"

class TextController
{
    Player& playerA;
    Player& playerB;
    public:
    TextController(Player& pA, Player& pB);
    void play();

};