#include <fstream>
#include <iostream>

#include "utils.h"

enum Direction
{
  Horizontal,
  Vertical
};

int xSize = INT_MIN;
int ySize = INT_MIN;


int getCount(std::vector<std::vector<int>>& board)
{
  int count = 0;
  for (int y = 0; y < ySize; ++y)
  {
    for (int x = 0; x < xSize; ++x)
    {
      count += board[x][y];
    }
  }
  return count;
}

void printBoard(std::vector<std::vector<int>>& board)
{
  for (int y = 0; y < ySize; ++y)
  {
    for (int x = 0; x < xSize; ++x)
    {
      std::cout << ((board[x][y] == 1) ? "#" : ".");
    }
    std::cout << std::endl;
  }
}

std::vector<std::vector<int>> createBoard(int x, int y)
{
  std::vector<std::vector<int>> returnBoard = std::vector<std::vector<int>>();
  for (int i = 0; i < x; ++i)
  {
    returnBoard.push_back(std::vector<int>());
    for (int j = 0; j < y; ++j)
    {
      returnBoard[i].push_back(0);
    }
  }
  return returnBoard;
}

std::vector<std::vector<int>> foldHorizontally(std::vector<std::vector<int>>& board, int index)
{
  int newXSize = std::max(index, xSize - 1 - index);
  std::vector<std::vector<int>> newBoard = createBoard(newXSize, ySize);
  for (int x = 1; x <= newXSize; ++x)
  {
    int leftIndex = index - x;
    int rightIndex = index + x;
    for (int y = 0; y < ySize; ++y)
    {
      if (leftIndex >= 0)
      {
        newBoard[newXSize - x][y] = std::max(newBoard[newXSize - x][y], board[leftIndex][y]);
      }
      if (rightIndex < xSize)
      {
        newBoard[newXSize - x][y] = std::max(newBoard[newXSize - x][y], board[rightIndex][y]);
      }
    }
  }
  xSize = newXSize;
  return newBoard;
}

std::vector<std::vector<int>> foldVertically(std::vector<std::vector<int>>& board, int index)
{
  int newYSize = std::max(index, ySize - 1 - index);
  std::vector<std::vector<int>> newBoard = createBoard(xSize, newYSize);
  for (int y = 1; y <= newYSize; ++y)
  {
    int aboveIndex = index - y;
    int belowIndex = index + y;
    for (int x = 0; x < xSize; ++x)
    {
      if (aboveIndex >= 0)
      {
        newBoard[x][newYSize - y] = std::max(newBoard[x][newYSize - y], board[x][aboveIndex]);
      }
      if (belowIndex < ySize)
      {
        newBoard[x][newYSize - y] = std::max(newBoard[x][newYSize - y], board[x][belowIndex]);
      }
    }
  }
  ySize = newYSize;
  return newBoard;
}

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  //file.open("example.txt");
  if (file.is_open())
  {
    std::string line;
    bool readingPositions = true;
    std::vector<std::pair<int, int>> listOfPositions = std::vector<std::pair<int, int>>();
    std::vector<std::pair<Direction, int>> listOfFolds = std::vector<std::pair<Direction, int>>();
    while (std::getline(file, line))
    {
      if (line.empty())
      {
        readingPositions = false;
        continue;
      }

      if (readingPositions)
      {
        std::vector<std::string> positionString = splitString(line, ',');
        std::pair<int, int> position = std::pair<int, int>(std::stoi(positionString[0]), std::stoi(positionString[1]));
        if (position.first > xSize)
          xSize = position.first;
        if (position.second > ySize)
          ySize = position.second;
        listOfPositions.push_back(position);
      }
      else
      {
        char direction;
        int index;
        line = line.substr(11);
        std::vector<std::string> dumb = splitString(line, '=');
        direction = dumb[0][0];
        index = std::stoi(dumb[1]);
        listOfFolds.push_back(std::pair<Direction, int>(direction == 'x' ? Horizontal : Vertical, index));
      }
    }

    file.close();
    ++ySize;
    ++xSize;

    std::vector<std::vector<int>> board = createBoard(xSize, ySize);

    std::vector<std::pair<int, int>>::iterator itEnd = listOfPositions.end();
    for (std::vector<std::pair<int, int>>::iterator it = listOfPositions.begin(); it != itEnd; ++it)
    {
      board[it->first][it->second] = 1;
    }

    //printBoard(board);

    std::vector<std::pair<Direction, int>>::iterator itEnd2 = listOfFolds.end();
    for (std::vector<std::pair<Direction, int>>::iterator it = listOfFolds.begin(); it != itEnd2; ++it)
    {
      std::cout << "Fold " << (it->first == Horizontal ? "Horizontally" : "Vertically") << " along " << it->second << std::endl;

      if (it->first == Vertical)
        board = foldVertically(board, it->second);
      else if (it->first == Horizontal)
        board = foldHorizontally(board, it->second);
      
      //printBoard(board);

      int count = getCount(board);
      std::cout << "Board has " << count << " dots" << std::endl << std::endl;
    }

    printBoard(board);
  }
}