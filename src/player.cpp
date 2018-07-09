#include "player.hpp"

// O crawl retorna uma copia tail antigo para que ele possa ser processado
void Player::crawl(Point new_coord)
{
    m_snake.push(new_coord);
    m_snake.pop();
}

Point Player::tail() const
{
    // o primeiro que entra eh a calda
    return m_snake.front(); 
}
Point Player::head() const
{
    // o ultimo que entra eh a calda
    return m_snake.back(); 
}

void Player::eat(Point new_coord)
{
    m_snake.push(new_coord);
}

void Player::reset()
{
    while(!m_snake.empty())
        m_snake.pop();
    m_last_move = Direction::N;
}
