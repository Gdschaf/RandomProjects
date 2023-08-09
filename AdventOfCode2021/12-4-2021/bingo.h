#pragma once

#include <iostream>

#include "utils.h"

#define BOARDWIDTH 5
#define BOARDHEIGHT 5

class bingoBoard
{
public:
  bingoBoard() { } 
  void addRow(std::string input);
  bool play(int number);
  int getScore(int lastCalled);
  bool checkHasWon() { return hasWon; }
private:
  bool hasWin(int x, int y);
  bool setHit(int number);
  std::vector<int> stringToRow(std::string input);

  std::vector<std::vector<int>> board;
  std::vector<std::vector<bool>> hitBoard;
  bool hasWon = false;

  friend std::ostream& operator<<(std::ostream& out, bingoBoard& dt);
};

inline std::ostream& operator<< (std::ostream& out, bingoBoard& b)
{
  for (int y = 0; y < BOARDHEIGHT; ++y)
  {
    for (int x = 0; x < BOARDWIDTH; ++x)
    {
      out << b.board[y][x] << "  ";
    }
    out << "\t";
    for (int x = 0; x < BOARDWIDTH; ++x)
    {
      out << b.hitBoard[y][x] << "  ";
    }
    out << std::endl;
  }
  return out;
}