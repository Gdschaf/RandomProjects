#pragma once

#include <math.h>

#include "Point.h"

class Line
{
public:
  Line(std::string input);
  bool isHorizontal();
  bool isVertical();
  int largestX() { return std::max(p1._x, p2._x); }
  int largestY() { return std::max(p1._y, p2._y); }
  std::string getOrientationString();
  Point p1, p2;

  friend std::ostream& operator<<(std::ostream& out, Line& l);
};

inline std::ostream& operator<< (std::ostream& out, Line& l)
{
  out << l.p1 << " -> " << l.p2;
  return out;
}