#ifndef SUI_BUTTON_H
#define SUI_BUTTON_H

#include <cstring>
#include <functional>
#include <SFML/Graphics.hpp>
#include "widget.hpp"

/// state of the button
enum BT_STATE
{
    BT_NORMAL,
    BT_HOVER
};
/// A generic SFML Button

namespace sui {
    class Button : public Widget
    {
        public:
            /// Button constructor
            /*!
            * \param textstr button text
            * \param position position (x, y) vector
            * \param font_size size of the text's font
            * \param on_press fuction that will be called when button is pressed
            * \param default_color background button color
            */
            Button(std::string textstr, const sf::Vector2f &position, size_t font_size, std::function<void()> on_press = nullptr, sf::Color default_color = sf::Color(200, 200, 200));
            ~Button();
            /// Event handler and updater methode.
            /*!
            *\param e event passed by the game loop.
            */
            bool update_handler(sf::Event& e);
            /// set padding at all the side of the button.
            /*!
            * \param left padding left.
            * \param top padding top.
            * \param right padding right.
            * \param bottom padding bottom.
            */
            void set_padding(uint left, uint top, uint right, uint bottom);
            void set_position(const sf::Vector2f& position);
            const sf::Vector2f& get_size() const;
            const sf::Vector2f& get_position() const;
            
        private:
            /// draw methode of Button. Check the SFML Documentation
            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            /// background rectangle
            sf::RectangleShape m_bgarea;
            /// used font
            sf::Font m_font;
            /// text of the button
            sf::Text m_text;
            /// on_press action function
            std::function<void()>  m_on_press;
            /// state of the button
            BT_STATE m_state;
            // offset necessário, pois a posição do texto é alterada pelas transformações
            /// text position offset 
            int m_offset_x, m_offset_y;
    };
}

#endif
