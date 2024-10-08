#pragma once

#include <SFML/Graphics.hpp>
#include "colors.hpp"
#include "status.hpp"

struct Square
{
    int8_t grid;
    int8_t subgrid;
    Status player;
    sf::RectangleShape rect;
};

void set_square(sf::RectangleShape &square);
bool square_clicked(sf::RectangleShape &square, sf::RenderWindow &window);