#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

class State
{
    public:
        
        virtual void init() = 0;
        virtual void process_events(sf::Event& e) = 0;
        virtual void update() = 0;
        virtual void render() = 0;

};

#endif
