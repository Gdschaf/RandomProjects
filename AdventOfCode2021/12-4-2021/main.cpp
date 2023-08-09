#include <fstream>

#include "bingo.h"

std::vector<int> getInput(std::string input)
{
  std::vector<int> intInput = std::vector<int>();
  std::vector<std::string> split = splitString(input, ',');
  for (int i = 0; i < split.size(); ++i)
  {
    intInput.push_back(std::stoi(split[i]));
  }
  return intInput;
}

void part1(std::vector<bingoBoard> bingoBoards, std::vector<int> input);
void part2(std::vector<bingoBoard> bingoBoards, std::vector<int> input);

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::string line;
    bool inputSet = false;
    bool buildingBoard = false;
    std::vector<int> input;
    bingoBoard currentBoard = bingoBoard();
    std::vector<bingoBoard> bingoBoards = std::vector<bingoBoard>();
    while (std::getline(file, line))
    {
      if (!inputSet)
      {
        input = getInput(line);
        inputSet = true;
      }
      else
      {
        if (line == "" && buildingBoard)
        {
          //here is where we add the board to our list of boards as it's complete
          bingoBoards.push_back(currentBoard);
          //create a new, empty board
          currentBoard = bingoBoard();
          buildingBoard = false;
        }
        else if (line != "")
        {
          currentBoard.addRow(line);
          buildingBoard = true;
        }
      }
    }
    bingoBoards.push_back(currentBoard);
    file.close();

    std::cout << "Part 1: " << std::endl;
    part1(bingoBoards, input);
    std::cout << "\n\nPart 2: " << std::endl;
    part2(bingoBoards, input);
  }
}


void part1(std::vector<bingoBoard> bingoBoards, std::vector<int> input)
{
  for (int i = 0; i < input.size(); ++i)
  {
    int calledNumber = input[i];
    std::cout << "Calling number " << calledNumber << std::endl;
    bool winner = false;
    for (int j = 0; j < bingoBoards.size(); ++j)
    {
      if (bingoBoards[j].play(calledNumber))
      {
        std::cout << "Score of the winning board is " << bingoBoards[j].getScore(calledNumber) << std::endl;
        std::cout << bingoBoards[j];
        winner = true;
        break;
      }
    }
    if (winner)
      break;
  }
}

void part2(std::vector<bingoBoard> bingoBoards, std::vector<int> input)
{
  bingoBoard lastWin;
  int calledNumber;
  int winningBoards = 0;
  for (int i = 0; i < input.size(); ++i)
  {
    calledNumber = input[i];
    std::cout << "Calling number " << calledNumber << std::endl;
    int remainingBoards = 0;
    bool weWon = false;
    for (int j = 0; j < bingoBoards.size(); ++j)
    {
      if (bingoBoards[j].checkHasWon())
        continue;
      ++remainingBoards;
      if (bingoBoards[j].play(calledNumber))
      {
        weWon = true;
        ++winningBoards;
        lastWin = bingoBoards[j];
        std::cout << std::endl << "Winning board number " << winningBoards << " is" << std::endl;
        std::cout << bingoBoards[j] << std::endl << std::endl;
      }
    }
    if (remainingBoards == 1 && weWon)
      break;
  }

  std::cout << "Score of the last winning board is " << lastWin.getScore(calledNumber) << std::endl;
  std::cout << lastWin;
}