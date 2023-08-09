#pragma once

#include <iostream>
#include <string>

class Point
{
public:
  Point(int x = 0, int y = 0) : _x(x), _y(y) { }
  int _x, _y;

  friend std::ostream& operator<<(std::ostream& out, Point& dt);
};

inline std::ostream& operator<< (std::ostream& out, Point& p)
{
  out << "(" << p._x << ", " << p._y << ")";
  return out;
}