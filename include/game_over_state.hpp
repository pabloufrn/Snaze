#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include <SFML/Graphics.hpp>

#include "state.hpp"

#include "screen.hpp"
#include "button.hpp"
#include "text.hpp"

#include "main_menu_state.hpp"

class MainMenuState;

class GameOverState : public State
{
    public:
        
       GameOverState(sf::RenderTarget& target, StateMachine* state_machine, uint& score);
        
        void init();
        void process_events(sf::Event& e);
        void update();
        void render();
        
        void main_menu();
        
    private:

        sui::Screen m_screen;
        StateMachine* m_machine;
        sf::RenderTarget* m_window;
        uint m_score;
        
};

#endif
