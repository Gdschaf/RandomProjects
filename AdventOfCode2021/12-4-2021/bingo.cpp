#include "bingo.h"

void bingoBoard::addRow(std::string input)
{
  board.push_back(stringToRow(input));
  hitBoard.push_back(std::vector<bool>(BOARDWIDTH));
}

bool bingoBoard::play(int number)
{
  return setHit(number);
}

int bingoBoard::getScore(int lastCalled)
{
  int unmarkedNumbers = 0;
  for (int y = 0; y < BOARDHEIGHT; ++y)
  {
    for (int x = 0; x < BOARDWIDTH; ++x)
    {
      if (!hitBoard[y][x])
        unmarkedNumbers += board[y][x];
    }
  }
  return unmarkedNumbers * lastCalled;
}

bool bingoBoard::hasWin(int lastX, int lastY)
{
  for (int x = 0; x < BOARDWIDTH; ++x)
  {
    if (!hitBoard[lastY][x])
      break;
    if (x == BOARDWIDTH - 1)
      return true;
  }
  for (int y = 0; y < BOARDHEIGHT; ++y)
  {
    if (!hitBoard[y][lastX])
      break;
    if (y == BOARDHEIGHT - 1)
      return true;
  }
  return false;
}

bool bingoBoard::setHit(int number)
{
  bool winnerwinner = false;
  for (int y = 0; y < BOARDHEIGHT; ++y)
  {
    for (int x = 0; x < BOARDWIDTH; ++x)
    {
      if (number == board[y][x])
      {
        hitBoard[y][x] = true;
        winnerwinner = hasWin(x, y);
      }
    }
  }
  hasWon = winnerwinner;
  return winnerwinner;
}

std::vector<int> bingoBoard::stringToRow(std::string input)
{
  std::vector<std::string> split = splitString(input, ' ');
  std::vector<int> row = std::vector<int>();
  for (int i = 0; i < split.size(); ++i)
  {
    row.push_back(std::stoi(split[i]));
  }
  return row;
}
