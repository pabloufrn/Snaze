#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <iostream>
#include <SFML/Graphics.hpp>

#include "state.hpp"

#include "screen.hpp"
#include "button.hpp"

#include "main_game_state.hpp"

class MainMenuState : public State
{
    public:
        
        MainMenuState(sf::RenderTarget& target, StateMachine* state_machine);
        
        void init();
        void process_events(sf::Event&);
        void update();
        void render();
        
        // --- Callbacks ---
        void start_game();
        void start_game_ai();
        void exit_game();
//         void about_game();
//         void help_game();
        
    private:
        sui::Screen m_menu_screen;
        StateMachine* m_machine;
        sf::RenderTarget* m_window;
};



#endif
