#ifndef GAME_AI_H
#define GAME_AI_H

#include <stack>
#include <climits>
#include <set>
#include <cstring>
#include <vector>
#include <memory>

#include "game_classes.hpp"
#include "player.hpp"
#include "level.hpp"

struct Cell
{
    Point parent;
    uint f, g, h, i;

    Cell() = default;
    Cell(Point p);
};

class AI : public Player
{
    public:
        
        AI(Level& level);
        
        void update(sf::Event&);
        Direction next_move();
        
    private:
        
        Direction goto_free_way();
        // -- Astar algorithm funcions --
        bool isValid(Point p);
        bool isUnBlocked(Point p);
        bool isDestination(Point p);
        double calculateHValue(Point p);
        void tracePath();
        bool aStarSearch();
        
        std::shared_ptr<Level> m_level;
        Size m_level_size;
        
        std::stack<Direction> m_path;
        std::vector< std::vector<Cell> > m_cellDetails;
        Point m_goal;
        
        Direction m_last_move = Direction::S;
        
       
};

#endif
