#ifndef QUADBOARD_H
#define QUADBOARD_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "widget.hpp"

class QuadBoard : public sui::Widget
{
public:
    
    QuadBoard(sf::Vector2f position, uint quad_size, sf::Vector2u dimensions, uint margin, const std::string & tileset_file, sf::Vector2u tileset_dimesions, uint default_texture);
    ~QuadBoard();

    void set_quad_texture(uint x, uint y, uint tileNumber);
    void rotate_quad_texture(uint x, uint y, uint rotation);
    
    size_t get_quad_size(){return m_quad_size;}
    size_t get_margin(){return m_margin;}
    
    bool update_handler(sf::Event& e);
    void set_position(const sf::Vector2f& position);
    const sf::Vector2f& get_size()  const;
    const sf::Vector2f& get_position() const;
    
private:
    /// Draw methode, check SFML docs
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    size_t m_quad_size;
    sf::Vector2u m_dimensions;
    sf::Vector2u m_tile_size;
    size_t m_margin;
    
    sf::Vector2f m_position;
    sf::Vector2f m_size;
    
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;

    
};
#endif
