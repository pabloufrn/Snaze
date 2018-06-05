#include "game_classes.hpp"

Direction operator!(Direction& rhs)
{
    if(rhs == Direction::N)
        return Direction::S;
    if(rhs == Direction::S)
        return Direction::N;
    if(rhs == Direction::W)
        return Direction::E;
    else
        return Direction::W;
}

Direction operator*(Point lhs, Point rhs)
{
    if(lhs.y == rhs.y)
    {
        if(lhs.x > rhs.x)
            return Direction::N;
        else
            return Direction::S;
    }
    else
    {
        if(lhs.y > rhs.y)
            return Direction::W;
        else
            return Direction::E;
    }
}
Direction& operator++(Direction& rhs)
{
    if(rhs == Direction::N)
        rhs = Direction::E;
    else if(rhs == Direction::E)
        rhs = Direction::S;
    else if(rhs == Direction::S)
        rhs = Direction::W;
    else 
        rhs = Direction::N;
    return rhs;
}
std::ostream& operator<<(std::ostream& os, const Direction& rhs)  
{
    if(rhs == Direction::N)
        os << "North";
    else if(rhs == Direction::E)
        os << "East";
    else if(rhs == Direction::S)
        os << "South";
    else if(rhs == Direction::W)
        os << "West";
    return os;
}


Point::Point(uint x_, uint y_):x(x_), y(y_) 
{   }

bool Point::operator==(const Point& rhs) const
{
    return this->x == rhs.x and this->y == rhs.y;
}
bool Point::operator!=(const Point& rhs) const
{
    return this->x != rhs.x or this->y != rhs.y;
}

Point& Point::operator=(const Point& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}
