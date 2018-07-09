#ifndef SUI_TEXT_H
#define SUI_TEXT_H

#include <SFML/Graphics.hpp>

#include "widget.hpp"

namespace sui 
{
    class Text : public sui::Widget
    {
        public:
            Text(std::string text, const sf::Vector2f& position);
            bool update_handler(sf::Event&);
            void set_position(const sf::Vector2f& position);
            const sf::Vector2f& get_size()  const;
            const sf::Vector2f& get_position() const;
            void set_string(std::string str);
        private:
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            
            sf::Text m_text;
            sf::Font m_font;
            sf::Vector2f m_size;
            int m_offset_x;
            int m_offset_y;
    };
}
inline sui::Text::Text(std::string text, const sf::Vector2f& position)
{
    m_font.loadFromFile("font/arial.ttf");
    
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(30);
    m_text.setString(text);
    m_text.setPosition(position.x, position.y);
    
    sf::FloatRect text_rect{ m_text.getGlobalBounds() };
    m_offset_x = position.x - text_rect.left;
    m_offset_y = position.y - text_rect.top;
    m_text.move(m_offset_x, m_offset_y);

    m_size = sf::Vector2f(text_rect.width, text_rect.height);
}
inline bool sui::Text::update_handler(sf::Event&)
{
    return false;
}
inline void sui::Text::set_position(const sf::Vector2f& position)
{
    m_text.setPosition({position.x + m_offset_x, position.y + m_offset_y});
}
inline const sf::Vector2f& sui::Text::get_size()  const
{
    return m_size;
}
inline const sf::Vector2f& sui::Text::get_position() const
{
    return m_text.getPosition();
}

inline void sui::Text::draw(sf::RenderTarget& target, sf::RenderStates) const
{
    target.draw(m_text);
}
inline void sui::Text::set_string(std::string str)
{
    m_text.setString(str);
}
#endif
