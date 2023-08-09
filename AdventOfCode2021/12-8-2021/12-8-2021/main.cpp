#include <fstream>
#include <iostream>

#include "decoder.h"

#define SEVENDIGITS 3
#define ONEDIGITS 2
#define FOURDIGITS 4
#define EIGHTDIGITS 7

void part1(void);
void part2(void);

int main(void)
{
  //part1();
  part2();
}

void part1(void)
{
  std::fstream file;
  file.open("input.txt");
  std::vector<std::string> input = std::vector<std::string>();
  if (file.is_open())
  {
    std::string inputLine;
    while (std::getline(file, inputLine))
    {
      input.push_back(splitString(inputLine, '|')[1]);
    }
    file.close();
  }

  if (input.empty())
    return;

  int ones, fours, sevens, eights, total;
  ones = fours = sevens = eights = total = 0;
  for (int i = 0; i < input.size(); ++i)
  {
    std::vector<std::string> numbers = splitString(input[i], ' ');
    for (int j = 0; j < numbers.size(); ++j)
    {
      switch (numbers[j].size())
      {
      case SEVENDIGITS:
        ++sevens;
        ++total;
        break;
      case ONEDIGITS:
        ++ones;
        ++total;
        break;
      case FOURDIGITS:
        ++fours;
        ++total;
        break;
      case EIGHTDIGITS:
        ++eights;
        ++total;
        break;
      }
    }
  }

  std::cout << "We did it, number of 7s: " << sevens << "\t4s: " << fours << "\t1s: " << ones << "\t8s: " << eights << std::endl;
  std::cout << "Total number of 7, 8, 1, and 4s is " << total << std::endl;
}

void part2(void)
{
  std::fstream file;
  file.open("input.txt");
  int bigNumber = 0;
  if (file.is_open())
  {
    std::string line;
    while (std::getline(file, line))
    {
      bigNumber += decoder(line).getNumber();
    }
  }

  std::cout << "Holy shit does this work? Number: " << bigNumber << std::endl;
}