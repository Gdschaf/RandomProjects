#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

int maxX, maxY;
unsigned int lowestRiskFactor = UINT_MAX;
std::vector<std::vector<int>> goodLuck = std::vector<std::vector<int>>();

bool validLocation(std::pair<int, int>& location)
{
  return location.first >= 0 && location.second >= 0 && location.first < maxX && location.second < maxY;
}

bool alreadyVisited(std::pair<int, int>& location, std::vector<std::vector<int>>& visitedMap)
{
  return visitedMap[location.first][location.second] > 0;
}

void printPath(std::vector<std::pair<int, int>>& path, unsigned int& riskFactor)
{
  std::vector<std::pair<int, int>>::iterator itEnd = path.end();
  for (std::vector<std::pair<int, int>>::iterator it = path.begin(); it != itEnd; ++it)
  {
    std::cout << "[" << it->first << ", " << it->second << "] -> ";
  }
  std::cout << "Current risk factor is " << riskFactor << std::endl << std::endl;
}

enum Direction
{
  DOWN,
  RIGHT,
  LEFT,
  UP,
};

struct iHopeThisWorks
{
  iHopeThisWorks(Direction d, int v, std::pair<int, int> l) : deezNuts(d), value(v), location(l) { }
  Direction deezNuts;
  int value;
  std::pair<int, int> location;
};

bool compareThisShit(iHopeThisWorks l, iHopeThisWorks r)
{
  return l.value < r.value;
}

bool compareThisShitAgain(iHopeThisWorks l, iHopeThisWorks r)
{
  return l.deezNuts < r.deezNuts;
}

bool recursiveSearch(std::pair<int, int> location, std::vector<std::vector<int>>& visitedMap, unsigned int& riskFactor, std::vector<std::vector<unsigned int>>& shortestPaths)
{
  riskFactor += goodLuck[location.first][location.second];
  if (location.first == (maxX - 1) && location.second == (maxY - 1))
  {
    if(riskFactor < lowestRiskFactor)
      lowestRiskFactor = riskFactor;
    riskFactor -= goodLuck[location.first][location.second];
    return true;
  }
  //bool shouldContinue = shortestPaths[location.first][location.second] != -1;
  if (riskFactor >= lowestRiskFactor)// || !shouldContinue)
  {
    riskFactor -= goodLuck[location.first][location.second];
    return false;
  }

  if (shortestPaths[location.first][location.second] > 0)
  {
    int tempRiskFactor = shortestPaths[location.first][location.second] + riskFactor;
    if (tempRiskFactor > lowestRiskFactor)
    {
      riskFactor -= goodLuck[location.first][location.second];
      return false;
    }
    else if(tempRiskFactor < lowestRiskFactor)
    {
      lowestRiskFactor = tempRiskFactor;
      riskFactor -= goodLuck[location.first][location.second];
      return true;
    }
  }

  visitedMap[location.first][location.second] = goodLuck[location.first][location.second];

  //printPath(path, riskFactor);

  std::pair<int, int> up(location.first - 1, location.second);
  std::pair<int, int> down(location.first + 1, location.second);
  std::pair<int, int> left(location.first, location.second - 1);
  std::pair<int, int> right(location.first, location.second + 1);

  std::vector<iHopeThisWorks> validMoves = std::vector<iHopeThisWorks>();

  if (validLocation(down) && !alreadyVisited(down, visitedMap))
    validMoves.push_back(iHopeThisWorks(DOWN, goodLuck[down.first][down.second], down));
  if (validLocation(right) && !alreadyVisited(right, visitedMap))
    validMoves.push_back(iHopeThisWorks(RIGHT, goodLuck[right.first][right.second], right));
  //if (validLocation(left) && !alreadyVisited(left, visitedMap))
  //  validMoves.push_back(iHopeThisWorks(LEFT, goodLuck[left.first][left.second], left));
  //if (validLocation(up) && !alreadyVisited(up, visitedMap))
  //  validMoves.push_back(iHopeThisWorks(UP, goodLuck[up.first][up.second], up));

  std::sort(validMoves.begin(), validMoves.end(), compareThisShit);
  std::sort(validMoves.begin(), validMoves.end(), compareThisShitAgain);

  bool foundEnd = false;
  for (int i = 0; i < validMoves.size(); ++i)
  {
    foundEnd |= recursiveSearch(validMoves[i].location, visitedMap, riskFactor, shortestPaths);
  }

  visitedMap[location.first][location.second] = 0;
  if (foundEnd)
  {
    shortestPaths[location.first][location.second] = lowestRiskFactor - riskFactor;
  }
  //else
  //{
  //  shortestPaths[location.first][location.second] = -1;
  //}
  riskFactor -= goodLuck[location.first][location.second];
  return foundEnd;
}

int main(void)
{
  std::fstream file;
  //file.open("example.txt");
  file.open("input.txt");
  if (file.is_open())
  {
    std::string line;
    while (std::getline(file, line))
    {
      std::vector<int> yeahOkay = std::vector<int>();
      for (int i = 0; i < line.size(); ++i)
      {
        yeahOkay.push_back(line[i] - '0');
      }
      goodLuck.push_back(yeahOkay);
    }
    file.close();

    //there's no way in hell this works
    maxX = goodLuck.size();
    maxY = goodLuck[0].size();

    std::vector<std::vector<int>> visitedMap = std::vector<std::vector<int>>();
    std::vector<std::vector<unsigned int>> shortestPaths = std::vector<std::vector<unsigned int>>();
    for (int i = 0; i < maxX; ++i)
    {
      std::vector<int> something = std::vector<int>();
      std::vector<unsigned int> somethingElse = std::vector<unsigned int>();
      for (int j = 0; j < maxY; ++j)
      {
        something.push_back(0);
        somethingElse.push_back(0);
      }
      visitedMap.push_back(something);
      shortestPaths.push_back(somethingElse);
    }

    unsigned int riskFactor = 0;
    recursiveSearch(std::pair<int, int>(0, 0), visitedMap, riskFactor, shortestPaths);

    lowestRiskFactor -= goodLuck[0][0]; //this is some of the shittiest code i've ever written
    std::cout << "The path with the lowest risk factor is " << lowestRiskFactor << std::endl;
  }
}