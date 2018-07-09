#include "game_over_state.hpp"

GameOverState::GameOverState(sf::RenderTarget& target, StateMachine* state_machine, uint &score):
m_screen("Game over screen"), m_machine(state_machine),  m_window(&target), m_score(score)
{
}
void GameOverState::init()
{
    m_window->setView(m_window->getDefaultView());
    
    sui::Text* go_text = new sui::Text("Game over", {0.0, 100.0});
    sui::Text* score_text = new sui::Text("Your final score is: " + std::to_string(m_score), {0.0, 150.0});
    sui::Button* rg_button = new sui::Button("Main Menu", {0, 300} , 30, std::bind(&GameOverState::main_menu, this), sf::Color(0, 200, 0));
    
    rg_button->set_padding(30, 10, 30, 10);
    
    sf::Vector2u window_size = m_window->getSize();
    
    go_text->align(window_size, sui::Widget::CENTER_X);
    score_text->align(window_size, sui::Widget::CENTER_X);
    rg_button->align(window_size, sui::Widget::CENTER_X);
    
    m_screen.add_widget(go_text);
    m_screen.add_widget(score_text);
    m_screen.add_widget(rg_button);
}
void GameOverState::main_menu()
{
    m_machine->add_state(StateRef(new MainMenuState(*m_window, m_machine)));
    m_machine->get_active_state()->init();
}
void GameOverState::process_events(sf::Event& e)
{
    m_screen.update(e);
    return;
}
void GameOverState::update()
{
    return;
}
void GameOverState::render()
{
    m_window->draw(m_screen);
    return;
}
