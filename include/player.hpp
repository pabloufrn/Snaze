#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <queue>

#include "game_classes.hpp"

class Player
{
    public:
        
        void crawl(Point new_coord);
        void eat(Point new_coord);
        void reset();
        // Its just a normal copy. While the snake is moving the tail and the head are updated.
        Point tail() const;
        Point head() const;
        
        virtual Direction next_move() = 0;
        virtual void update(sf::Event& e) = 0;
        
    protected:
        std::queue<Point> m_snake;
        Direction m_last_move = Direction::N;
};


#endif
