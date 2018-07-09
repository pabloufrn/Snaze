#include "human.hpp"

void Human::update(sf::Event&)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_next_move = Direction::W;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_next_move = Direction::E;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_next_move = Direction::N;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_next_move = Direction::S;
    }
}

Direction Human::next_move()
{
    if(m_next_move == !m_last_move)
        m_next_move = m_last_move;
    m_last_move = m_next_move;
    return m_next_move;
}
