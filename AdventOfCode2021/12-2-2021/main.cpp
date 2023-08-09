#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#define FORWARD_TEXT "forward"
#define UP_TEXT "up"
#define DOWN_TEXT "down"

std::vector<std::string> splitString(std::string input, char splitCharacter)
{
  std::vector<std::string> returnList = std::vector<std::string>();
  int startIndex = 0;
  for (int i = 0; i < input.length(); ++i)
  {
    if (input[i] == splitCharacter)
    {
      returnList.push_back(input.substr(startIndex, i - startIndex));
      startIndex = i + 1;
    }
  }
  returnList.push_back(input.substr(startIndex));
  return returnList;
}

enum direction
{
  FORWARD,
  UP,
  DOWN,
  BACK //I don't think we ever use back...
};

class move
{
public:
  move(std::string dir, std::string steps)
  {
    initVariables(dir, steps);
  }  

  move(std::string input)
  {
    std::vector<std::string> inputs = splitString(input, ' ');
    initVariables(inputs[0], inputs[1]);
  }

  move(const move & rhs)
  {
    stepCount = rhs.stepCount;
    moveDirection = rhs.moveDirection;
  }

  direction moveDirection;
  int stepCount;

private:
  void initVariables(std::string dir, std::string steps)
  {
    stepCount = std::stoi(steps);
    if (dir.compare(FORWARD_TEXT) == 0)
      moveDirection = FORWARD;
    else if (dir.compare(UP_TEXT) == 0)
      moveDirection = UP;
    else if (dir.compare(DOWN_TEXT) == 0)
      moveDirection = DOWN;
    else
      std::cout << "Unknown Direction: " << dir << std::endl;
  }
};

void stepOne(std::vector<move> listOfMoves);
void stepTwo(std::vector<move> listOfMoves);

int main(void)
{
  std::vector<move> listOfMoves = std::vector<move>();
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::string inputLine;
    while (std::getline(file, inputLine))
    {
      listOfMoves.push_back(move(inputLine));
    }
    file.close();
  }

  std::cout << "STEP 1:" << std::endl;
  stepOne(listOfMoves);
  std::cout << std::endl << std::endl << "STEP 2:" << std::endl;
  stepTwo(listOfMoves);
}

void stepOne(std::vector<move> listOfMoves)
{
  int position = 0;
  int depth = 0;
  std::vector<move>::iterator itEnd = listOfMoves.end();
  for (std::vector<move>::iterator it = listOfMoves.begin(); it != itEnd; ++it)
  {
    switch (it->moveDirection)
    {
    case FORWARD:
      position += it->stepCount;
      break;
    case UP:
      depth -= it->stepCount;
      if (depth < 0)
        std::cout << "UUUUH HUSTON, WE HAVE A PROBLEM" << std::endl;
      break;
    case DOWN:
      depth += it->stepCount;
      break;
    }
  }

  std::cout << "The final position is " << position << ".\t The final depth is " << depth << "." << std::endl;
  std::cout << "The answer to the problem is " << position * depth << "." << std::endl;
}

void stepTwo(std::vector<move> listOfMoves)
{
  int position = 0;
  int depth = 0;
  int aim = 0;
  std::vector<move>::iterator itEnd = listOfMoves.end();
  for (std::vector<move>::iterator it = listOfMoves.begin(); it != itEnd; ++it)
  {
    switch (it->moveDirection)
    {
    case FORWARD:
      position += it->stepCount;
      depth += (aim * it->stepCount);
      break;
    case UP:
      aim -= it->stepCount;
      if (depth < 0)
        std::cout << "UUUUH HUSTON, WE HAVE A PROBLEM" << std::endl;
      break;
    case DOWN:
      aim += it->stepCount;
      break;
    }
  }

  std::cout << "The final position is " << position << ".\t The final depth is " << depth << ".\t The final aim is: " << aim << "." << std::endl;
  std::cout << "The answer to the problem is " << position * depth << "." << std::endl;
}