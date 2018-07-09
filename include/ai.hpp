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
        bool is_valid(Point p);
        bool is_unblocked(Point p);
        bool is_destination(Point p);
        void trace_path();
        uint calculate_h_value(Point p);
        bool a_star_search();

        void reset();

        std::shared_ptr<Level> m_level;
        Size m_level_size;

        std::stack<Direction> m_path;
        std::vector< std::vector<Cell> > m_cell_board;
        Point m_goal;
};

#endif

