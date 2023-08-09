#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <queue>

#define RESET   "\033[0m"
#define BOLD  "\033[1m\033[33m"      /* Bold Yellow */

void printBoard(int(&b)[10][10])
{
  for (int i = 0; i < 10; ++i)
  {
    for (int j = 0; j < 10; ++j)
    {
      if (b[i][j] == 0)
        std::cout << BOLD << b[i][j] << RESET;
      else
        std::cout << b[i][j];
    }
    std::cout << std::endl;
  }
}

bool validSpot(int i, int j)
{
  return i >= 0 && i <= 9 && j >= 0 && j <= 9;
}

void recursiveFlash(int(&b)[10][10], int i, int j)
{
  for (int x = -1; x <= 1; ++x)
  {
    for (int y = -1; y <= 1; ++y)
    {
      if (y == 0 && x == 0)
        continue;
      if (validSpot(i + x, j + y))
      {
        ++b[i + x][j + y];
        if (b[i + x][j + y] == 10)
          recursiveFlash(b, i + x, j + y);
      }
    }
  }
}

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::string line;
    int board[10][10];
    int lineNumber = 0;
    while (std::getline(file, line))
    {
      for (int i = 0; i < line.size(); ++i) //you better not be larger then 10...
      {
        board[lineNumber][i] = line[i] - '0';
      }
      ++lineNumber;
    }
    file.close();

    int totalFlashes = 0;
    int step = 0;
    bool allFlashed = false;
    while(!allFlashed)
    {
      for (int i = 0; i < 10; ++i)
      {
        for (int j = 0; j < 10; ++j)
        {
          ++board[i][j];
          if (board[i][j] == 10) //we haven't flashed yet, do it nao!
          {
            recursiveFlash(board, i, j);
          }
        }
      }

      int stepFlashCount = 0;
      for (int i = 0; i < 10; ++i)
      {
        for (int j = 0; j < 10; ++j)
        {
          if (board[i][j] > 9)
          {
            ++stepFlashCount;
            board[i][j] = 0;
          }
        }
      }

      if (stepFlashCount == 100)
        allFlashed = true;

      totalFlashes += stepFlashCount;
      printBoard(board);
      std::cout << "On step " << step << ", flashed " << stepFlashCount << " times. Total: " << totalFlashes << std::endl << std::endl;
      ++step;
    }
  }
}