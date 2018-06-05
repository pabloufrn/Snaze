#ifndef SUI_WIDGET_H
#define SUI_WIDGET_H

#include <SFML/Graphics.hpp>

namespace sui 
{
    /// A generic SFML Widget
    class Widget : public sf::Drawable
    {
        public:
            enum Alignment
            {
                CENTER,
                CENTER_X,
                CENTER_Y
            };
            
            Widget();
            
            virtual bool update_handler(sf::Event&) = 0;
            virtual void set_position(const sf::Vector2f& position) = 0;
            virtual const sf::Vector2f& get_size()  const = 0;
            virtual const sf::Vector2f& get_position() const = 0;
            
            void align(sf::Vector2u target_size, const Alignment& al);
            bool update(sf::Event& e);
            void set_enable(bool enable);
            bool get_enable() const;
            
        protected:
            
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
            
            bool m_enable = true;
        
    };
}

inline sui::Widget::Widget(): m_enable(true)
{
}

inline void sui::Widget::align(sf::Vector2u target_size, const Alignment& al)
{
    sf::Vector2f widget_size = get_size();
    
    switch(al)
    {
        case CENTER:
            set_position({target_size.x/2 - widget_size.x/2, target_size.y/2 - widget_size.y/2});
        case CENTER_X:
            set_position({target_size.x/2 - widget_size.x/2, get_position().y});
            break;
        case CENTER_Y:
            set_position({get_position().x, target_size.y/2 - widget_size.y/2});
            break;
        default:
            throw std::runtime_error("[ERROR]: invalid Widget alignment.");
    }
}
inline bool sui::Widget::update(sf::Event& e)
{
    if(!m_enable)
        return false;
    return update_handler(e);
}
inline void sui::Widget::set_enable(bool enable)
{
    m_enable = enable; 
}
inline bool sui::Widget::get_enable() const
{
    return m_enable;
}

#endif
