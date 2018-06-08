#include "main_menu_state.hpp"

MainMenuState::MainMenuState(sf::RenderTarget& target, StateMachine* state_machine) : 
m_menu_screen("Menu Screen"), m_machine(state_machine),  m_window(&target)
{
}
void MainMenuState::init()
{
    
    sui::Button* bt1 = new sui::Button("Normal Game", (sf::Vector2f) {0, 200}, 30, std::bind(&MainMenuState::start_game, this));
    sui::Button* bt2 = new sui::Button("AI Game", (sf::Vector2f) {0, bt1->get_position().y + bt1->get_size().y + 30}, 30, std::bind(&MainMenuState::start_game_ai, this));
    sui::Button* bt3 = new sui::Button("Help", (sf::Vector2f) {0, bt2->get_position().y + bt2->get_size().y + 30}, 30);
    sui::Button* bt4 = new sui::Button("About", (sf::Vector2f) {0, bt3->get_position().y + bt3->get_size().y + 30}, 30);
    sui::Button* bt5 = new sui::Button("Exit", (sf::Vector2f) {0, bt4->get_position().y + bt4->get_size().y + 30}, 30, std::bind(&MainMenuState::exit_game, this));
    
    bt1->set_padding(30, 10, 30, 10);
    bt2->set_padding(30, 10, 30, 10);
    bt3->set_padding(30, 10, 30, 10);
    bt4->set_padding(30, 10, 30, 10);
    
    sf::Vector2u window_size = m_window->getSize();
    
    bt1->align(window_size, sui::Widget::CENTER_X);
    bt2->align(window_size, sui::Widget::CENTER_X);
    bt3->align(window_size, sui::Widget::CENTER_X);
    bt4->align(window_size, sui::Widget::CENTER_X);
    bt5->align(window_size, sui::Widget::CENTER_X);
    
    m_menu_screen.add_widget(bt1);
    m_menu_screen.add_widget(bt2);
    m_menu_screen.add_widget(bt3);
    m_menu_screen.add_widget(bt4);
    m_menu_screen.add_widget(bt4);
    
    
}
void MainMenuState::process_events(sf::Event& e)
{
    m_menu_screen.update(e);
    // verifica se o botao start game foi pressionado
}
void MainMenuState::update()
{
    // se foi pressionado algum botao, muda de tela
}
void MainMenuState::render()
{
    m_window->draw(m_menu_screen);
}

// Callbacks

void MainMenuState::start_game()
{
    m_machine->add_state(StateRef(new MainGameState(*m_window, m_machine)));
    m_machine->get_active_state()->init();
}
void MainMenuState::start_game_ai()
{
    m_machine->add_state(StateRef(new MainGameState(*m_window, m_machine, true)));
    m_machine->get_active_state()->init();
}

void MainMenuState::exit_game()
{
    m_machine->remove_state();
}
