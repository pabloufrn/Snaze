#ifndef BACKGROUND_WIDGET_H
#define BACKGROUND_WIDGET_H

#include <SFML/Graphics.hpp>
#include "widget.hpp"

namespace sui {
    class Background : public sui::Widget
    {
        public:

            Background(sf::Vector2f size, sf::Vector2f position, sf::Color color);

            bool update_handler(sf::Event&);
            void set_position(const sf::Vector2f& position);
            const sf::Vector2f& get_size() const;
            const sf::Vector2f& get_position() const;

        private:

            virtual void draw(sf::RenderTarget& target, sf::RenderStates) const;

            sf::RectangleShape m_bg_rect;
    };
}

using namespace sui;
inline Background::Background(sf::Vector2f size, sf::Vector2f position, sf::Color color)
{
    m_bg_rect.setSize(size);
    m_bg_rect.setPosition(position);
    m_bg_rect.setFillColor(color);
}
inline bool Background::update_handler(sf::Event &)
{
    return false;
}
inline void Background::set_position(const sf::Vector2f &position)
{
    m_bg_rect.setPosition(position);
}
inline const sf::Vector2f& Background::get_size() const
{
    return m_bg_rect.getSize();
}
inline const sf::Vector2f& Background::get_position() const
{
    return m_bg_rect.getPosition();
}
inline void Background::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    target.draw(m_bg_rect);
}
#endif // BACKGROUND_WIDGET_H
