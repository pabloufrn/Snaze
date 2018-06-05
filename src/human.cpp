#include "human.hpp"

void Human::update(sf::Event&)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_next_direction = Direction::W;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_next_direction = Direction::E;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_next_direction = Direction::N;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_next_direction = Direction::S;
    }
}

Direction Human::next_move()
{
    if(m_next_direction == !m_last_direction)
        m_next_direction = m_last_direction;
    m_last_direction = m_next_direction;
    return m_next_direction;
}
