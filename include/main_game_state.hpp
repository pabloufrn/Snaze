#ifndef MAIN_GAME_STATE_H
#define MAIN_GAME_STATE_H

#include <iostream>
#include <string>
#include <queue>
#include <SFML/Graphics.hpp>

#include "definitions.hpp"
#include "game_classes.hpp"

#include "state.hpp"
#include "state_machine.hpp"

#include "level.hpp"
#include "screen.hpp"
#include "button.hpp"
#include "quadboard.hpp"
#include "player.hpp"
#include "human.hpp"
#include "ai.hpp"
#include "background_widget.hpp"

#include "pause_game_state.hpp"
#include "game_over_state.hpp"

enum InternalState
{
    CRAWLED,
    ATE_APPLE,
    DIED,
    PAUSED
};

class MainGameState : public State
{
    public:
        
        MainGameState(sf::RenderTarget& target, StateMachine* state_machine, bool ai = false);
        
        void init();
        void process_events(sf::Event&);
        void update();
        void render();
        
        void game_over();
        void next_level();
        void respawn();

    private:
        uint m_score;
        uint m_lifes;
        uint m_apples;
        
        sui::Screen m_game_screen;
        sui::Screen m_status_screen;
        StateMachine* m_machine;
        sf::RenderTarget* m_window;
        QuadBoard *m_quadboard;
        std::queue<std::string> m_mapcycle;
        Level m_current_level;
        Player* m_player;
        sf::View m_view;
        sf::Clock m_clock;
        sf::Time m_update_period = sf::milliseconds(170);
        bool m_paused = true;

        sui::Text* m_tscore;
        sui::Text* m_tapples;
        sui::Text* m_tlifes;
};


#endif
