#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "TicTacToe.hpp"
#include "game_state.hpp"

sf::Vector2f get_mouse_position(sf::RenderWindow &window);

void apply_hoever_effect(Square &s, TicTacToe &t, sf::RenderWindow &window);
void hoever_effect(sf::RenderWindow &window, TicTacToe &t);

void handle_player_move(sf::Event &event, sf::RenderWindow &window, GameState &curr_state, TicTacToe &t);
void handle_text_box_sel(text_box &t, sf::RenderWindow &window);