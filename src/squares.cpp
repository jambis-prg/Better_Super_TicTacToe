#include "../include/squares.hpp"

/* Sets the configuration that is used for all the squares in the board. */
void set_square(sf::RectangleShape &square)
{
    square.setSize(sf::Vector2f(75.f, 75.f));
    square.setFillColor(sf::Color::Blue);
    square.setOutlineThickness(2.f);
}