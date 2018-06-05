#ifndef PLAYER_HUMAN_H
#define PLAYER_HUMAN_H

#include "game_classes.hpp"
#include "player.hpp"

class Human : public Player
{
    public:
       Direction next_move();
       void update(sf::Event& e);
    private:
        Direction m_next_direction = Direction::S;
        Direction m_last_direction = Direction::N;
};

#endif
