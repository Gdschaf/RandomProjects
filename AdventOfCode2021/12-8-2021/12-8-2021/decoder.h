#pragma once

#include <unordered_map>

#include "utils.h"

#define SEVENDIGITS 3
#define ONEDIGITS 2
#define FOURDIGITS 4
#define EIGHTDIGITS 7

class decoder
{
public:
  decoder(std::string inputLine);
  int getNumber();
private:
  std::string numberString;
  std::unordered_map<int, unsigned char> numberToBitMap = std::unordered_map<int, unsigned char>();
  std::unordered_map<unsigned char, int> bitToNumberMap = std::unordered_map<unsigned char, int>();
  std::vector<unsigned char> numbersToFigureOut = std::vector<unsigned char>();

  unsigned char numberToBits(std::string);
  unsigned char findNine();
  unsigned char findZero();
  unsigned char findSix();
  unsigned char findThree();
  unsigned char findTwo();
  unsigned char findFive();
  int getBitCount(unsigned char num);
};