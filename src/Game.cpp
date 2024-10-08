#include "Game.hpp"

static const sf::Vector2u s_window_size(1680, 900);

// Constructor
Game::Game() : m_window(sf::VideoMode(1680, 900), "Super Tic Tac Toe", sf::Style::Close), 
                m_game_menu(s_window_size), m_credits_menu(s_window_size), m_name_input_menu(s_window_size), m_end_screen_menu(s_window_size)
{
    m_window.setFramerateLimit(60);

    m_lines.reserve(4);

    m_vertical_line.setSize(sf::Vector2f(10.f, 790.f));
    m_vertical_line.setFillColor(BLACK);

    m_horizontal_line.setSize(sf::Vector2f(790.f, 10.f));
    m_horizontal_line.setFillColor(BLACK);
    set_board_position();
}

/* will set the position of all the 9x9 board. */
void Game::set_board_position()
{
    // seting the board's position
    float x = 500.f, y = 100.f;
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            m_tic_tac_toe.get_board_at(i, j).rect.setPosition({x + j * 75, y + i * 75});
    
    // vertical lines
    for (int i = 0; i < 2; i++)
    {
        m_vertical_line.setPosition({720 + static_cast<float>(225 * i), y-60});
        m_lines.push_back(m_vertical_line);
    }
    
    // horizontal lines
    for (int i = 0; i < 2; i++)
    {
        m_horizontal_line.setPosition({x-55, y + 220 + static_cast<float>(225 * i)});
        m_lines.push_back(m_horizontal_line);
    }
}

void Game::update_poll_events()
{
    while (m_window.pollEvent(m_event))
    {
        switch (m_event.type)
        {
            case sf::Event::Closed:
                m_window.close();
                break;
            
            // pressing Esc to close
            case sf::Event::KeyPressed:
                if (m_event.key.code == sf::Keyboard::Escape)
                    m_window.close();
                break;
            
            // Click on available squares to play
            case sf::Event::MouseButtonPressed:
                handle_player_move(m_event, m_window, m_current_state, m_tic_tac_toe);
                handle_text_box_sel(m_name_input_menu.get_text_box(), m_window);
                break;
                
            case sf::Event::TextEntered:
                if (m_current_state == GameState::NAME_INPUT)
                {
                    auto unicode = m_event.text.unicode;
                    auto &text_box = m_name_input_menu.get_text_box();
                    text_box.typed(unicode);
                    
                    if(unicode == ENTER)
                    {
                        if(text_box.is_valid() && (m_player1_name_turn || m_players_name[0] != m_players_name[1]))
                        {
                            if(m_player1_name_turn)
                            {
                                m_players_name[0] = text_box.get_text_string();
                                m_name_input_menu.set_type_message("O's Name:");
                                m_player1_name_turn = false;
                            }
                            else
                            {
                                m_players_name[1] = text_box.get_text_string();
                                m_current_state = GameState::WAITING_INPUT;
                                m_tic_tac_toe.set_players_name(m_players_name);
                            }

                            text_box.clear();
                            m_name_input_menu.enable_error_message(false);
                        }
                        else
                            m_name_input_menu.enable_error_message(true);
                    }
                    break;
                }

            default:
                break;
        }   
    }
}

/* Renders all the squares and lines of the board. */
void Game::draw_board()
{
    for (const auto &i : m_tic_tac_toe.get_board())
        for (const auto &s : i)
            m_window.draw(s.rect);
    
    for (const auto &l : m_lines)
        m_window.draw(l);
}

void Game::state_manager()
{
    switch (m_current_state)
    {
        case GameState::MENU:
            m_game_menu.draw(m_window);

            if (m_game_menu.start_button_clicked(m_window))
                m_current_state = GameState::NAME_INPUT;
            else if (m_game_menu.exit_button_clicked(m_window))
                m_window.close();
            else if (m_game_menu.credits_button_clicked(m_window))
                m_current_state = GameState::CREDITS;
            break;
        
        case GameState::CREDITS:
            m_credits_menu.draw(m_window);
            
            if (m_credits_menu.back_button_clicked(m_window))
            {
                m_timer.restart();
                while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

                m_current_state = GameState::MENU;
            }
            break;
        
        case GameState::NAME_INPUT:
            m_name_input_menu.draw(m_window);
            break;
        
        case GameState::WAITING_INPUT: case GameState::PLAYING:
            draw_board();
            m_tic_tac_toe.get_text().draw(m_window);
            break;

        case GameState::END_SCREEN:
        {

            Status game_status =  m_tic_tac_toe.get_victory();
            if(game_status == Status::TIE)
                m_end_screen_menu.set_result("It's a Tie!!!", m_window);
            else
                m_end_screen_menu.set_result(m_players_name[(uint8_t)game_status] + " Win!!!", m_window);

            m_end_screen_menu.draw(m_window);

            if (m_end_screen_menu.menu_button_clicked(m_window))
            {
                m_players_name[0] = m_players_name[1] = "";

                m_name_input_menu.set_type_message("X's Name:");
                m_name_input_menu.get_text_box().clear_deselect();
                
                m_tic_tac_toe.reset();
                m_timer.restart();
                while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

                m_current_state = GameState::MENU;
            }
            else if (m_end_screen_menu.rematch_button_clicked(m_window))
            {
                m_tic_tac_toe.reset();
                m_timer.restart();
                while (m_timer.getElapsedTime().asMilliseconds() < 300) {};

                m_current_state = GameState::WAITING_INPUT;
            }
            break;
        }

        default:
            break;
    }
}

// Accessors
bool Game::running() const
{
    return m_window.isOpen();
}

// Public Functions:

void Game::update()
{
    update_poll_events();

    // hoever effect
    if (m_current_state == GameState::WAITING_INPUT)
        hoever_effect(m_window, m_tic_tac_toe);
}

/* Will render and display the objects in the screen. */
void Game::render()
{
    m_window.clear(sf::Color::White); // clear old frame

    // Draw game objects
    state_manager();
    
    m_window.display(); // done drawing
}