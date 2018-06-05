#include "button.hpp"
using namespace sui;

Button::Button(std::string textstr, const sf::Vector2f &position, size_t font_size, std::function<void()> on_press, sf::Color default_color)
{
    /// text config
    
    m_font.loadFromFile("font/arial.ttf");
    
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(font_size);
    m_text.setString(textstr);
    m_text.setPosition(position.x, position.y);
    
    sf::FloatRect text_rect{ m_text.getGlobalBounds() };
    m_offset_x = position.x - text_rect.left;
    m_offset_y = position.y - text_rect.top;
    m_text.move(m_offset_x, m_offset_y);
    
    /// rectangle config
   
    m_bgarea.setFillColor(default_color);
    
    // coloca o retangulo de acordo com a posição final do texto
   
    m_bgarea.setPosition(position.x, position.y);
    m_bgarea.setSize({text_rect.width, text_rect.height});
    
    /// other configs
    
    m_state = BT_NORMAL;
    m_on_press = on_press;
}
Button::~Button()
{
    m_on_press = nullptr;
}
void Button::set_padding(uint left, uint top, uint right, uint bottom)
{
    
    sf::FloatRect text_rect =  m_text.getGlobalBounds();
    // altera o tamanho do retangulo (depende do tamanho do texto)
    m_bgarea.setSize({text_rect.width + left + right, text_rect.height + top + bottom});
    // altera a posicao do texto (depende da posição retângulo)
    sf::Vector2f button_pos = m_bgarea.getPosition();
    m_text.setPosition(button_pos.x + left + m_offset_x, button_pos.y + top + m_offset_y);
    
}

/// draw methode of Button. Check the SFML Documentation
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw button
    target.draw(m_bgarea, states);
    target.draw(m_text, states);
}

/// update state
bool Button::update_handler(sf::Event& e)
{
    /// check if the mouse is over button
    if(e.type == sf::Event::MouseMoved)
    {
        // verifica logo se o mouse estava sobre o botão
        if(m_state == BT_HOVER)
        {
                // se ainda estiver não faz nada
                if(m_bgarea.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y))
                    return false;
                // se saiu, atualiza
                m_state = BT_NORMAL;
                sf::Color color = m_bgarea.getFillColor();
                color.a = 255;
                m_bgarea.setFillColor(color);
        }
        // verifica se entrou agora na area
        else 
        {
            // se não entrou não faz nada
            if(!m_bgarea.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y))
                return false;
            // se entrou, atualiza
            m_state = BT_HOVER;
            sf::Color color = m_bgarea.getFillColor();
            color.a = 100;
            m_bgarea.setFillColor(color);
        }
    }
    else if(e.type == sf::Event::MouseButtonPressed and e.mouseButton.button == sf::Mouse::Left)
    {
        // se o mouse não tá no botão, não faz nada
        if(!m_bgarea.getGlobalBounds().contains(e.mouseButton.x, e.mouseButton.y))
                return false;
        // se tiver, pressione
        
        if(m_on_press)
            m_on_press();
    }
    return true;
}


void Button::set_position(const sf::Vector2f& position)
{
    
    sf::Vector2f text_position = m_text.getPosition();
    sf::Vector2f rect_position = m_bgarea.getPosition();
    
    m_text.setPosition(position.x + (text_position.x - rect_position.x), position.y + (text_position.y - rect_position.y));
    
    /// Rectangle position
   
    m_bgarea.setPosition(position.x, position.y);
    
}
const sf::Vector2f& Button::get_size() const
{
    return m_bgarea.getSize();
}
const sf::Vector2f& Button::get_position() const
{
    return m_bgarea.getPosition();
}
/// Limitations
/*!
 * The button is not a transformable class, so you cannot change its scale or rotation 
 */

// TODO: remover limitações











