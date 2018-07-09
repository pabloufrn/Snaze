#ifndef SUI_SCREEN_H
#define SUI_SCREEN_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>

#include "widget.hpp"

namespace sui {
    /// A generic SFML Screen
    class Screen : public sf::Drawable
    {
        public:
            
            Screen(std::string name);
            ~Screen();
            
            void update(sf::Event& e);
            void update_handler(sf::Event& e);
            void set_enable(bool enable);
            bool get_enable() const;
            void add_widget(Widget*);
            void pop_widget();
            std::string get_name() const;
        protected:
            
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            
            bool m_enable = true;
            std::vector<Widget*> m_widgets;
            std::string m_name;
        
    };
}

inline sui::Screen::Screen(std::string name): m_enable(true), m_name(name)
{
}
inline sui::Screen::~Screen()
{
    for(auto w : m_widgets)
    {
        delete w;
    }
    m_widgets.clear();
//    std::vector<Widget*>().swap(m_widgets);
}
inline void sui::Screen::update(sf::Event& e)
{
    if(!m_enable)
        return;
    return update_handler(e);
}
inline void sui::Screen::update_handler(sf::Event& e)
{
    for(auto w : m_widgets)
    {
        if(w->update(e))
            break;
    }
}
inline void sui::Screen::set_enable(bool enable)
{
    m_enable = enable; 
}
inline bool sui::Screen::get_enable() const
{
    return m_enable;
}
inline void sui::Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto w : m_widgets)
    {
        target.draw(*w, states);
    }
}
inline std::string sui::Screen::get_name() const
{
    return m_name;
}
inline void sui::Screen::add_widget(Widget* widget)
{
    m_widgets.push_back(widget);
}
inline void sui::Screen::pop_widget()
{
    if(m_widgets.empty())
        return;
    m_widgets.pop_back();
}
#endif
