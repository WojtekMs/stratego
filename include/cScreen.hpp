#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class cScreen
{
    public:
    virtual std::string run(sf::RenderWindow& win) = 0;
};