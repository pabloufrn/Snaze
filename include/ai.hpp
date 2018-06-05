#ifndef GAME_AI_H
#define GAME_AI_H

#include <iostream>
#include <stack>
#include <climits>
#include <set>
#include <cstring>
#include <vector>
#include <memory>
#include <deque>

#include "game_classes.hpp"
#include "player.hpp"
#include "level.hpp"

struct Cell
{
    Point parent;
    bool HasParent;
    uint f, g, h, i;
    // i é valor de custo adicional para que essa não colida com a cauda 

    
    Cell() = default;
    Cell(Point p);
};

class AI : public Player
{
    public:
        
        AI(Level& level);
        
        void update(sf::Event&);
        Direction next_move();
        Direction goto_free_way();
        
        
    private:
        
        // -- Astar algorithm funcions
        bool isValid(Point p);
        bool isUnBlocked(Point p);
        uint risk(Point p, Point parent);
        bool isDestination(Point p);
        double calculateHValue(Point p);
        void tracePath();
        bool aStarSearch();
        
        
        std::shared_ptr<Level> m_level;
        Size m_level_size;
        
        std::stack<Direction> m_path;
        std::vector< std::vector<Cell> > m_cellDetails;
        
        Point m_goal;
        Point m_critical_point;
        Direction m_last_move = Direction::S;
        
        bool m_collision;
        uint m_attempts_left;
        
       
};

#endif
