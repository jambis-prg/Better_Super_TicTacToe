#pragma once

#include <vector>
#include <fstream>
#include "buttons.hpp"

class main_menu
{
    private:
        game_text m_title;
        button m_start_button, m_exit_button, m_credits_button;

    public:
        main_menu(sf::Vector2u windowSize);

        bool start_button_clicked(sf::RenderWindow &window);
        bool exit_button_clicked(sf::RenderWindow &window);
        bool credits_button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};

class credits_menu
{
    private:
        button m_return_button;
        std::ifstream m_credits_file;
        std::vector<game_text> m_credits_text;

    public:
        credits_menu(sf::Vector2u windowSize);

        bool back_button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};

class name_input_menu
{
    private:
        game_text m_type_message, m_error_message;
        text_box m_player_name_box;
        bool m_error_message_enabled = false;
    public:
        name_input_menu(sf::Vector2u windowSize);

        text_box& get_text_box();
        void set_type_message(const std::string &message);
        void set_box_text(const std::string &text);

        void enable_error_message(bool value);
        void draw(sf::RenderWindow &window);
};

class end_screen_menu
{
    private:
        game_text m_result_text;
        button m_rematch_button, m_menu_button;

    public:
        end_screen_menu(sf::Vector2u windowSize);

        void set_result(const std::string &result_message, sf::RenderWindow &window);
        bool menu_button_clicked(sf::RenderWindow &window);
        bool rematch_button_clicked(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
};