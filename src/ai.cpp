#include "ai.hpp"

/// === ALIASES ===

using WayPoint = std::pair<uint, Point>;

/// == STRUCTURES ==

/// A Cell with 'f', 'g', 'h' and 'i' values
Cell::Cell(Point p): parent(p), f(0u), g(0u), h(0u), i(0u)
{   }

/// Methods

/// Constructor
AI::AI(Level& level): m_level(&level)
{
}
/// Check bounds
bool AI::is_valid(Point p)
{
    return p.y < m_level_size.x and p.x < m_level_size.y;
}
/// Check if point is not blocked
bool AI::is_unblocked(Point p)
{
    auto object = m_level->get_object(p);
    return object != Level::WALL and object != Level::INV_WALL;
}
/// check if snake (in simulations) get into food
bool AI::is_destination(Point p)
{
    return p == m_goal;
}
/// Heuristic value based on Manhattan distance
uint AI::calculate_h_value(Point p)
{
     return abs(int(p.x - m_goal.x)) +
            abs(int(p.y - m_goal.y));
}
/// Store final path in m_path
void AI::trace_path()
{
    Cell current_cell = Cell(m_goal);
    Cell current_parent = m_cell_board[m_goal.x][m_goal.y];
    while (!(current_cell.parent == current_parent.parent))
    {
        m_path.push(current_parent.parent*current_cell.parent);
        current_cell = current_parent;
        current_parent = m_cell_board[current_cell.parent.x][current_cell.parent.y];
    }
}
// Run A* Search Algorithm
bool AI::a_star_search()
{

    Point src = head();

    // Either the source or the destination is blocked
    if (!is_unblocked(src) or !is_unblocked(m_goal))
        throw std::runtime_error("Source or the destination is blocked\n");

    bool closed_list[m_level_size.y][m_level_size.x];
    memset(closed_list, false, sizeof(closed_list));

    m_cell_board.resize(m_level_size.y);

    for (uint i = 0; i < m_level_size.y; ++i)
    {
        m_cell_board[i].resize(m_level_size.x);
        for (uint j = 0; j < m_level_size.x; ++j)
        {
            m_cell_board[i][j].f = UINT_MAX;
            m_cell_board[i][j].g = UINT_MAX;
            m_cell_board[i][j].h = UINT_MAX;
        }
    }
    uint g_cost, h_cost, f_cost, i_cost;

    /*
     * The i cost means how many moves to any direction the snake need to do before going through some position, for instance:
     * the snake can not find a way through its tail original position, unless the snake has made at least one movement and,
     * for each point p, which is a part of the snake body, distant x positions from its tail, the snake will need to perform
     * x + 1 moves before going to p.
     * Note that the head has 0 cost.
    */
    std::queue<Point> snake_copy = m_snake;
    uint snake_size = snake_copy.size();
    for(uint i = 1; i < snake_size; i++)
    {
        Point p = snake_copy.front();
        m_cell_board[p.x][p.y].i = i;
        snake_copy.pop();
    }

    m_cell_board[src.x][src.y].f = 0;
    m_cell_board[src.x][src.y].g = 0;
    m_cell_board[src.x][src.y].h = 0;
    m_cell_board[src.x][src.y].parent = src;

    // Ensures the order of points
    auto Comp = [](const WayPoint& lhs, const WayPoint& rhs)->bool
    {
        if(lhs.first < rhs.first)
            return true;
        if(rhs.first < lhs.first)
            return false;
        if(lhs.second.x < rhs.second.x)
            return true;
        if(rhs.second.x < lhs.second.x)
            return false;
        return lhs.second.y < rhs.second.y;

    };
    std::set<WayPoint, decltype(Comp)> open_list(Comp);
    open_list.insert(std::make_pair(0, src));

    while (!open_list.empty())
    {
        WayPoint wp = *open_list.begin();
        open_list.erase(open_list.begin());
        const Point& p = wp.second;
        closed_list[p.x][p.y] = true;
        Point points[4] = {Point(p.x, p.y+1), Point(p.x, p.y-1), Point(p.x+1, p.y), Point(p.x-1, p.y)};
        for(uint c = 0; c < 4; ++c)
        {
            Point& current_point = points[c];
            if (is_valid(current_point))
            {
                if (is_destination(current_point))
                {
                    m_cell_board[current_point.x][current_point.y].parent = p;
                    trace_path();
                    return true;
                }
                else if (   !closed_list[current_point.x][current_point.y] and   \
                            is_unblocked(current_point)                          )
                {

                    g_cost = m_cell_board[p.x][p.y].g + 1;
                    h_cost = calculate_h_value(current_point);
                    f_cost = g_cost + h_cost;
                    i_cost = m_cell_board[current_point.x][current_point.y].i;

                    if  ( ( g_cost > i_cost ) and                                               \
                          (m_cell_board[current_point.x][current_point.y].f == UINT_MAX or  \
                           m_cell_board[current_point.x][current_point.y].f > f_cost          ) )
                    {
                        open_list.insert(std::make_pair(f_cost, current_point));
                        // Update cell board
                        m_cell_board[current_point.x][current_point.y].f = f_cost;
                        m_cell_board[current_point.x][current_point.y].g = g_cost;
                        m_cell_board[current_point.x][current_point.y].h = h_cost;
                        m_cell_board[current_point.x][current_point.y].parent = p;
                    }
                }
            }
        }
    }

    return false;
}
/// The IA does not receive user input events
void AI::update(sf::Event&)
{
    return;
}
/// Go to the next free direction
Direction AI::goto_free_way()
{
    auto comp =
            [](std::pair<uint, Direction> p1, std::pair<uint, Direction> p2)
            {
                return p1.first > p2.first;
            };
    std::set<std::pair<uint, Direction>, decltype(comp)> priority_direction(comp);
    Point src = head();
    Point points[] = {Point(src.x-1, src.y), Point(src.x+1, src.y), Point(src.x, src.y-1), Point(src.x, src.y+1)};
    priority_direction.insert(std::make_pair<uint, Direction>(0, std::move(++m_last_move)));
    uint c;
    for(c = 0; c < 4; ++c)
    {
        auto object = m_level->get_object(points[c]);
        if(object != Level::WALL and object != Level::WALL and object != Level::SNAKE)
        {
            Direction dir = src*points[c];
            if(dir == !m_last_move and m_snake.size() == 1)
                continue;
            auto h = calculate_h_value(points[c]);
            priority_direction.insert(std::make_pair<uint, Direction>(std::move(h), std::move(dir)));
        }
    }
    m_last_move = (priority_direction.begin())->second;
    return m_last_move;
}
/// Compute next direction of the Player (IA)
Direction AI::next_move()
{
    m_goal = m_level->get_apple_location();
    Point src = head();
    if(is_destination(src))
    {
        return goto_free_way();
    }
    if(!m_path.empty())
    {
        auto dir = m_path.top();
        m_path.pop();
        return dir;
    }
    m_level_size = m_level->get_size();
    m_cell_board.clear();
    if(a_star_search())
    {
        auto dir = m_path.top();
        m_path.pop();
        return dir;
    }
    auto dir = goto_free_way();
    return dir;
}

void AI::reset()
{
    Player::reset();
    while(m_path.empty())
        m_path.pop();

}
