#include "line.h"

Line::Line(std::string input)
{
  //446, 679 -> 446, 594
  int p1x, p1y, p2x, p2y;
  if (sscanf_s(input.c_str(), "%d, %d -> %d, %d", &p1x, &p1y, &p2x, &p2y) == 4)
  {
    p1 = Point(p1x, p1y);
    p2 = Point(p2x, p2y);
  }
  else
  {
    std::cout << "All 4 values weren't read in correctly" << std::endl;
  }
}

bool Line::isHorizontal()
{
  return p1._y == p2._y;
}

bool Line::isVertical()
{
  return p1._x == p2._x;
}

std::string Line::getOrientationString()
{
  if (isHorizontal())
    return "horizontal";
  else if (isVertical())
    return "vertical";
  return "Diagonal";
}
