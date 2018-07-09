#ifndef LEVEL_H
#define LEVEL_H

#include <fstream>
#include <string>
#include <random>
#include <vector>

#include "definitions.hpp"
#include "game_classes.hpp"

using Size = Point;

class Level
{
    public:
        // the client (player) can 'see' the map through public methods
        enum MapObject
        {
            GROUND,
            WALL,
            INV_WALL,
            SNAKE,
            APPLE
        };
        
        void load_map(std::string filename);
        void set_object(Point p, MapObject obj);
        const Point& place_random_apple();
        
        const MapObject& get_object(Point p) const;
        const Size& get_size() const;
        const Point& get_spawn() const;
        
        const Point& get_apple_location() const;
        
    private:
        
        // por comodidade, os elementos de enum serão caracteres.
        

        std::vector<MapObject> m_map;
        Size m_map_size;
        Point m_spawn_location;
        Point m_apple_location;
};

inline void Level::load_map(std::string filename)
{
    // --- Load file
    
    std::ifstream file(DATA_FILE_PATH + filename);
    
    if(file.fail())
        throw std::runtime_error("[ERROR](" + filename + "): " + "Could not load level map.");
    
    // --- Populate array
    
    // -- Load Config
    m_map_size = Size(0, 0);

    file >> m_map_size.x >> m_map_size.y;
    
    if(file.fail() or m_map_size.x == 0 or m_map_size.y == 0)
        throw std::runtime_error("[ERROR]: Invalid map file.");
    m_map.clear();
    std::vector<MapObject>().swap(m_map);
    m_map.reserve(m_map_size.x * m_map_size.y);
    auto capacity = m_map.capacity();

    // -- go through array
    char ch;
    for(uint c = 0; c < capacity;)
    {
        file.get(ch);
        if(ch == '\n')
            continue;
        if(file.fail())
            throw std::runtime_error("[ERROR](" + filename + "): " + "Error loading the map.");
        switch(ch)
        {
            case '\n':
            case ' ':
                m_map.push_back(GROUND);
                break;
            case '#':
                m_map.push_back(WALL);
                break;
            case '.':
                m_map.push_back(INV_WALL);
                break;
            case '*':
                m_spawn_location = {c / m_map_size.x, c % m_map_size.x };
                m_map.push_back(GROUND);
                break;
            default:
                throw std::runtime_error("[ERROR](" + std::string(1, ch) + "): Invalid map object.");
        }
        ++c;
    }

}
inline const Level::MapObject& Level::get_object(Point p) const
{
    return m_map[p.x * m_map_size.x + p.y];
}
inline void Level::set_object(Point p, Level::MapObject obj)
{
    m_map[p.x * m_map_size.x + p.y] = obj;
}
inline const Point& Level::get_size() const
{
    return m_map_size;
}
inline const Point& Level::get_spawn() const
{
    return m_spawn_location;
}
inline const Point& Level::place_random_apple()
{
    std::random_device rd;
	std::mt19937 mersenne(rd());
    uint last_i = (m_map_size.x-1)*(m_map_size.y) - 1;
	std::uniform_int_distribution<uint> gen(m_map_size.x+2, last_i);
    
    uint inicial_i = gen(mersenne);
    uint final_i = inicial_i;
    
    while(m_map[final_i] != Level::GROUND)
    {
        ++final_i;
        if(final_i == inicial_i)
        {
            throw std::runtime_error("[ERROR]: Was not posible generating apple. The map is fully filled.");
        }
        if(final_i > last_i)
        {
            final_i = m_map_size.x+1;
        }
    }
    
    m_map[final_i] = Level::APPLE;
    /* 
     * NOTE Um problema desse algoritmo é que ele tende a gerar maçãs à direita das paredes.
     */
    m_apple_location = Point(final_i / m_map_size.x, final_i % m_map_size.x);
    return m_apple_location;
}
inline const Point& Level::get_apple_location() const
{
    return m_apple_location;
}

#endif


















