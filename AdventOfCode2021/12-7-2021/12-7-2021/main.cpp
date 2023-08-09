#include <fstream>
#include <iostream>

#include "utils.h"

std::vector<int> getInputList(std::string input)
{
  std::vector<std::string> inputStrings = splitString(input, ',');
  std::vector<int> returnList = std::vector<int>();
  std::vector<std::string>::iterator itEnd = inputStrings.end();
  for (std::vector<std::string>::iterator it = inputStrings.begin(); it != itEnd; ++it)
  {
    returnList.push_back(std::stoi(*it));
  }
  return returnList;
}

void YOLO(std::vector<int> inputPositions);

int main(void)
{
  std::string input;
  std::fstream file;
  //file.open("example.txt");
  file.open("input.txt");
  if (file.is_open())
  {
    std::getline(file, input);
    file.close();
  }

  if (input.empty())
  {
    std::cout << "Input wasn't read correctly, exiting..." << std::endl;
    return 1;
  }

  std::vector<int> inputPositions = getInputList(input);

  YOLO(inputPositions);
}

int calculateFuel(int x, int y)
{
  int n = y - x;
  if (x > y)
    n = x - y;
  return(((n + 1) * n) / 2);
}

void YOLO(std::vector<int> inputPositions)
{
  int max, min;
  max = INT_MIN;
  min = INT_MAX;
  for (unsigned i = 0; i < inputPositions.size(); ++i)
  {
    if (inputPositions[i] < min)
      min = inputPositions[i];
    else if (inputPositions[i] > max)
      max = inputPositions[i];
  }

  int minimumFuel = INT_MAX;
  int optimalPosition = 0;
  for (int i = min; i <= max; ++i)
  {
    int currentFuel = 0;
    for (unsigned j = 0; j < inputPositions.size(); ++j)
    {
      currentFuel += calculateFuel(inputPositions[j], i);
    }

    if (currentFuel < minimumFuel)
    {
      minimumFuel = currentFuel;
      optimalPosition = i;
    }
  }

  std::cout << "Uhhhh, we made it, did we get the right answer? Optimal Position: " << optimalPosition << "\t Fuel Usage: " << minimumFuel << std::endl;
}