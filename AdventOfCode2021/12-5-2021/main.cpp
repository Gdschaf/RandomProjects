#include <fstream>
#include <vector>

#include "line.h"

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::vector<Line> lines = std::vector<Line>();
    int maxX, maxY;
    maxX = maxY = 0;
    std::string line;
    while (std::getline(file, line))
    {
      Line l = Line(line);
      //if (l.isHorizontal() || l.isVertical())
      //{
        maxX = std::max(maxX, l.largestX());
        maxY = std::max(maxY, l.largestY());
        lines.push_back(l);
        std::cout << "Line " << l << " is " << l.getOrientationString() << std::endl;
      //}
    }
    std::cout << "There's a total of " << lines.size() << " vertical and horizontal lines." << std::endl;
    std::cout << "The board dimensions are (" << maxX << ", " << maxY << ")" << std::endl;
    file.close();

    int** board = new int*[maxX];
    for (int i = 0; i < maxX; ++i)
    {
      board[i] = new int[maxY];
      memset(board[i], 0, sizeof(int) * maxY);
    }

    std::vector<Line>::iterator itEnd = lines.end();
    for (std::vector<Line>::iterator it = lines.begin(); it != itEnd; ++it)
    {
      if (it->isHorizontal())
      {
        //loop between the x values, incrementing the values at that spot on the board
        int small = std::min(it->p1._x, it->p2._x);
        int large = std::max(it->p1._x, it->p2._x);
        int yValue = it->p1._y - 1;
        for (int i = small - 1; i < large; ++i)
        {
          ++board[i][yValue];
        }
      }
      else if (it->isVertical())
      {
        //loop between the y values, incrementing the values at that spot on the board
        int small = std::min(it->p1._y, it->p2._y);
        int large = std::max(it->p1._y, it->p2._y);
        int xValue = it->p1._x - 1;
        for (int i = small - 1; i < large; ++i)
        {
          ++board[xValue][i];
        }
      }
      else //it's diagonal at a 45 degree angle
      {
        int small = std::min(it->p1._x, it->p2._x);
        int large = std::max(it->p1._x, it->p2._x);
        int difference = large - small;
        bool subtractX = it->p1._x > it->p2._x;
        bool subtractY = it->p1._y > it->p2._y;
        int startingX = it->p1._x - 1;
        int startingY = it->p1._y - 1;
        //std::cout << "Diagonal line: " << *it << std::endl;
        for (int i = 0; i <= difference; ++i)
        {
          int x = subtractX ? startingX - i : startingX + i;
          int y = subtractY ? startingY - i : startingY + i;
          //std::cout << "(" << x << ", " << y << ")" << std::endl;
          ++board[x][y];
        }
      }
    }

    int intersectCount = 0;
    for (int x = 0; x < maxX; ++x)
    {
      for (int y = 0; y < maxY; ++y)
      {
        if (board[x][y] > 1)
          ++intersectCount;
      }
    }

    for (int i = 0; i < maxX; ++i)
      delete[] board[i];
    delete[] board;

    std::cout << "Whew, I think we made it. Number of line intersections are " << intersectCount << std::endl;
  }
}