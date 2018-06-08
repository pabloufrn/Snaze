#ifndef PAUSE_GAME_STATE_H
#define PAUSE_GAME_STATE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#include "main_game_state.hpp"
#include "state_machine.hpp"
#include "state.hpp"
#include "text.hpp"
#include "button.hpp"
#include "screen.hpp"

class PauseGameState : public State
{
    public:
        
        PauseGameState(sf::RenderTarget& target, StateMachine* state_machine, State& game_state);
        
        void init();
        void process_events(sf::Event&);
        void update();
        void render();
        
        // --- Callbacks ---
        void resume_game();
        
    private:

        sf::RenderTarget* m_window;
        StateMachine* m_machine;
        sui::Screen m_screen;
        State* m_game_state;

};

#endif
