#include "ai.hpp"

/// === ALIASES ===

using pPair = std::pair<uint, std::pair<uint, uint>>;

/// == STRUCTURES ==

/// A Cell with 'f', 'g', 'h' and 'i' values.
Cell::Cell(Point p): parent(p), f(0u), g(0u), h(0u) , i(0u)
{   }

/// Methods

/// Constructor
AI::AI(Level& level): m_level(&level)
{
}
/// Check bounds
bool AI::isValid(Point p)
{
    return p.y < m_level_size.x and p.x < m_level_size.y;
}
/// Check if point is not blocked
bool AI::isUnBlocked(Point p)
{
    auto object = m_level->get_object(p);
    return object != Level::WALL and object != Level::INV_WALL;

}
/// check if snake (in simulations) get into food
bool AI::isDestination(Point p)
{
    return p == m_goal;
}
/// Heuristic value based on Manhattan distance
double AI::calculateHValue(Point p)
{
     return abs(int(p.x - m_goal.x)) +
            abs(int(p.y - m_goal.y)); 
}
/// Store final path in m_path
void AI::tracePath()
{
    Cell current_cell = Cell(m_goal);
    Cell current_parent = m_cellDetails[m_goal.x][m_goal.y];

    while (!(current_cell.parent == current_parent.parent))
    {
        m_path.push(current_parent.parent*current_cell.parent);
        current_cell = current_parent;
        current_parent = m_cellDetails[current_cell.parent.x][current_cell.parent.y];
    }
}

// Run A* Search Algorithm
bool AI::aStarSearch()
{
    
    Point src = head();
    // If the source is out of range
    if (!isValid(src))
        throw std::runtime_error("Source is invalid.");
    // If the destination is out of range
    if (!isValid(m_goal))
        throw std::runtime_error("Destination is invalid.");
    // Either the source or the destination is blocked
    if (!isUnBlocked(src) or !isUnBlocked(m_goal))
        throw std::runtime_error("Source or the destination is blocked\n");
    
    bool closedList[m_level_size.y][m_level_size.x];
    memset(closedList, false, sizeof (closedList));
    
    // Add snake coords to closed list 
    std::queue<Point> snake_copy = m_snake;
    
    m_cellDetails.resize(m_level_size.y);
 
    uint i, j;
 
    for (i = 0; i < m_level_size.y; ++i)
    {
        m_cellDetails[i].resize(m_level_size.x);
        for (j = 0; j < m_level_size.x; ++j)
        {
            m_cellDetails[i][j].f = UINT_MAX;
            m_cellDetails[i][j].g = UINT_MAX;
            m_cellDetails[i][j].h = UINT_MAX;
            m_cellDetails[i][j].i = 0;

        }
    }
    snake_copy = m_snake;
    auto snake_size = m_snake.size();
    if(snake_size > 1)
    {
        if(snake_size < 4)
        {
            if(snake_size == 3)
                snake_copy.pop();
            auto p = snake_copy.front();
            m_cellDetails[p.x][p.y].i = 1 + 100;
            m_cellDetails[p.x][p.y].f = calculateHValue(p) + m_cellDetails[p.x][p.y].i;
        }
        else
        {
            auto limit = snake_size - 1;
            uint iNew;
            for(uint c = 1; c < limit; c++)
            {
                auto p = snake_copy.front();
                iNew = c;
                m_cellDetails[p.x][p.y].i = iNew - 1;
                m_cellDetails[p.x][p.y].f = calculateHValue(p);
                snake_copy.pop();
            }
            auto p = snake_copy.front();
            m_cellDetails[p.x][p.y].i = 1;
            m_cellDetails[p.x][p.y].f = calculateHValue(p);
            snake_copy.pop();
        }
    }
    
    
    i = src.x, j = src.y;
    m_cellDetails[i][j].f = 0;
    m_cellDetails[i][j].g = 0;
    m_cellDetails[i][j].h = 0;
    m_cellDetails[i][j].parent = src;

    std::set<pPair> openList;

    openList.insert(std::make_pair(0.0, std::make_pair (i, j)));
    
    while (!openList.empty())
    {
        pPair  p = *openList.begin();
 
        openList.erase(openList.begin());
 
        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;
        
      
        uint gNew, hNew, fNew, iNew;
 
        
        Point points[4] = {Point(i, j+1), Point(i, j-1), Point(i+1, j), Point(i-1, j)};
        uint c;
        for(c = 0; c < 4; c++)
        {
            Point& current_point = points[c];
            
            if (    isValid(current_point)  )    
            {
                if (isDestination(current_point))
                {
                    m_cellDetails[current_point.x][current_point.y].parent = Point(i, j);
                    tracePath();
                    return true;
                }
                else if (   !closedList[current_point.x][current_point.y] and   \
                            isUnBlocked(current_point)                          )
                {
                    
                    gNew = m_cellDetails[i][j].g + 1;
                    hNew = calculateHValue(current_point);
                    iNew = m_cellDetails[current_point.x][current_point.y].i;
                    fNew = gNew + hNew;

                    if  (   m_cellDetails[current_point.x][current_point.y].f == UINT_MAX or    \
                        (   m_cellDetails[current_point.x][current_point.y].f > fNew + iNew))
                    {
                        
                        openList.insert( std::make_pair(fNew,
                                                std::make_pair(current_point.x, current_point.y)));
    
                        // Update the details of this cell
                        m_cellDetails[current_point.x][current_point.y].f = fNew;
                        m_cellDetails[current_point.x][current_point.y].g = gNew;
                        m_cellDetails[current_point.x][current_point.y].h = hNew;
                        m_cellDetails[current_point.x][current_point.y].parent = Point(i, j);
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
    Point src = head();
    Point points[] = {Point(src.x-1, src.y), Point(src.x+1, src.y), Point(src.x, src.y-1), Point(src.x, src.y+1)};
    uint min_h = UINT_MAX;
    auto min_h_dir =  ++m_last_move;
    uint c;
    for(c = 0; c < 4; ++c)
    {
        auto object = m_level->get_object(points[c]);
        if(object != Level::WALL and object != Level::INV_WALL and object != Level::SNAKE)
        {
            auto dir = src*points[c];
            if(dir == !m_last_move and m_snake.size() == 1)
                continue;
            auto h = calculateHValue(points[c]);
            if(h < min_h)
            {
                min_h = h;
                min_h_dir = dir;
            }
        }
    }
    m_last_move = min_h_dir;
    return m_last_move;
}
/// Compute next direction of the Player (IA)
Direction AI::next_move()
{
    m_goal = m_level->get_apple_location();
    Point src = head(); 
    if(isDestination(src))
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
    m_cellDetails.clear();
    if(aStarSearch())
    {
        auto dir = m_path.top();
        m_path.pop();
        return dir;
    }
    auto dir = goto_free_way();
    return dir;
}
