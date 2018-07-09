#include "quadboard.hpp"

QuadBoard::QuadBoard(sf::Vector2f position, uint quad_size, sf::Vector2u dimensions, uint margin, const std::string & tileset_file, sf::Vector2u tileset_dimesions, uint default_texture)
{
    
    // --- proprieters
    // -- texture
    if (!m_tileset.loadFromFile(tileset_file))
            throw std::runtime_error("Nao foi possivel criar a textura.");
    m_tileset.setSmooth(true);
    m_tile_size.x = m_tileset.getSize().x / tileset_dimesions.x;
    m_tile_size.y = m_tileset.getSize().y / tileset_dimesions.y;
    // -- size
    m_quad_size = quad_size;
    m_dimensions= dimensions;
    m_margin = margin;
    m_size = sf::Vector2f(m_dimensions.x * m_quad_size + m_dimensions.x * m_margin, m_dimensions.y * m_quad_size + m_dimensions.y * m_margin);
    // -- position
    m_position = position;    
    // -- vertices
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(dimensions.x * dimensions.y * 4);
    
    // --- populate data
    // -- initial conditions
    // - get texture relative coordinates
    uint tu = default_texture / (m_tileset.getSize().x / m_tile_size.x);
    uint tv = default_texture % (m_tileset.getSize().x / m_tile_size.x);
    // -- go through vertex array
    for (uint i = 0; i < dimensions.y; ++i)
    {
        for (uint j = 0; j < dimensions.x; ++j)
        {
            // get a pointer to the current board's quad
            uint index = (i * dimensions.x + j) * 4;
            sf::Vertex* quad = &m_vertices[index];
            // define vetices position
            quad[0].position = sf::Vector2f(position.x  + (j * m_quad_size + j * m_margin )     , position.y  + (i * m_quad_size + i * m_margin));
            quad[1].position = sf::Vector2f(position.x  + ((j + 1) * m_quad_size + j * m_margin), position.y  + (i * m_quad_size + i * m_margin));
            quad[2].position = sf::Vector2f(position.x  + ((j + 1) * m_quad_size + j * m_margin), position.y  + ((i + 1) * m_quad_size + i * m_margin));
            quad[3].position = sf::Vector2f(position.x  + (j * m_quad_size + j * m_margin)      , position.y  + ((i + 1) * m_quad_size + i * m_margin));
            // define vertices texture
            quad[0].texCoords = sf::Vector2f(tv * m_tile_size.x, tu * m_tile_size.y);
            quad[1].texCoords = sf::Vector2f((tv + 1) * m_tile_size.x, tu * m_tile_size.y);
            quad[2].texCoords = sf::Vector2f((tv + 1) * m_tile_size.x, (tu + 1) * m_tile_size.y);
            quad[3].texCoords = sf::Vector2f(tv * m_tile_size.x, (tu + 1) * m_tile_size.y);
        }
    }
}

void QuadBoard::set_position(const sf::Vector2f& position)
{
    m_position = position; 
    for (uint i = 0; i < m_dimensions.y; ++i)
    {
        for (uint j = 0; j < m_dimensions.x; ++j)
        {
            uint index = (i * m_dimensions.x + j) * 4;
            sf::Vertex* quad = &m_vertices[index];
            quad[0].position = sf::Vector2f(position.x  + (j * m_quad_size + j * m_margin )     , position.y  + (i * m_quad_size + i * m_margin));
            quad[1].position = sf::Vector2f(position.x  + ((j + 1) * m_quad_size + j * m_margin), position.y  + (i * m_quad_size + i * m_margin));
            quad[2].position = sf::Vector2f(position.x  + ((j + 1) * m_quad_size + j * m_margin), position.y  + ((i + 1) * m_quad_size + i * m_margin));
            quad[3].position = sf::Vector2f(position.x  + (j * m_quad_size + j * m_margin)      , position.y  + ((i + 1) * m_quad_size + i * m_margin));
        }
    }
}

void QuadBoard::set_quad_texture(uint x, uint y, uint tileNumber)
{
    // get texture relative coordinates
    unsigned int tu = tileNumber / (m_tileset.getSize().x / m_tile_size.x);
    unsigned int tv = tileNumber % (m_tileset.getSize().x / m_tile_size.x);

    // get a pointer to the current tile's quad
    sf::Vertex* quad = &m_vertices[(x * m_dimensions.x + y) * 4];

    // define its 4 texture coordinates
    quad[0].texCoords = sf::Vector2f(tv * m_tile_size.x, tu * m_tile_size.y);
    quad[1].texCoords = sf::Vector2f((tv + 1) * m_tile_size.x, tu * m_tile_size.y);
    quad[2].texCoords = sf::Vector2f((tv + 1) * m_tile_size.x, (tu + 1) * m_tile_size.y);
    quad[3].texCoords = sf::Vector2f(tv * m_tile_size.x, (tu + 1) * m_tile_size.y);
    
}

void QuadBoard::rotate_quad_texture(uint x, uint y, uint rotation)
{
    sf::Vertex* quad = &m_vertices[(x * m_dimensions.x + y) * 4];
    sf::Vertex aux_quad[4];
    aux_quad[0] = quad[0];
    aux_quad[1] = quad[1];
    aux_quad[2] = quad[2];
    aux_quad[3] = quad[3];
    
    for(auto i(0u); i < 4; ++i, ++rotation)
    {
        if(rotation > 3)
        {
            quad[i].texCoords = aux_quad[rotation-4].texCoords;
        }
        else
        {
            quad[i].texCoords = aux_quad[rotation].texCoords;
        }
    }
}

const sf::Vector2f& QuadBoard::get_size() const
{
    return m_size;
}

const sf::Vector2f& QuadBoard::get_position() const
{
    return m_position;
}

void QuadBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // apply texture
    states.texture = &m_tileset;
    // draw the vertex array
    target.draw(m_vertices, states);
}

bool QuadBoard::update_handler(sf::Event&)
{
    // even though the QuadBoard is a widget, it has no interaction with the user.
    return false;
}

QuadBoard::~QuadBoard()
{
    m_vertices.clear();
}






