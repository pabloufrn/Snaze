#include "pause_game_state.hpp"


PauseGameState::PauseGameState(sf::RenderTarget& target, StateMachine* state_machine, State& game_state):
    m_window(&target), m_machine(state_machine), m_screen("Pause Game"),
    m_game_state(&game_state)
{

}
void PauseGameState::init()
{
    sui::Button* bt = new sui::Button("Pressione qualquer tecla para iniciar...", sf::Vector2f(0, m_window->getSize().y - 100),
                                     30, nullptr, sf::Color(0, 0, 0, 150));
    bt->align(m_window->getSize(), sui::Widget::CENTER_X);
    bt->set_padding(30, 30, 30, 30);
    bt->set_enable(false);
    m_screen.add_widget(bt);
}

void PauseGameState::process_events(sf::Event& e)
{
    if(e.type == sf::Event::KeyPressed)
        PauseGameState::resume_game();
    // a screen não terá update, pois os eventos serão do teclado
}
void PauseGameState::update()
{
}
void PauseGameState::render()
{
    m_game_state->render();
    m_window->setView(m_window->getDefaultView());
    m_window->draw(m_screen);
}

// Callbacks

void PauseGameState::resume_game()
{
    m_machine->remove_state();
}
