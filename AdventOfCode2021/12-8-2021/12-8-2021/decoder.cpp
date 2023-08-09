
#include "decoder.h"

decoder::decoder(std::string inputLine)
{
  std::vector<std::string> splitInput = splitString(inputLine, '|');
  numberString = splitInput[1];

  std::vector<std::string> numberCodes = splitString(splitInput[0], ' ');
  for (int i = 0; i < numberCodes.size(); ++i)
  {
    unsigned char bitRepresentation = numberToBits(numberCodes[i]);
    switch (numberCodes[i].size())
    {
    case SEVENDIGITS:
      numberToBitMap[7] = bitRepresentation;
      break;
    case ONEDIGITS:
      numberToBitMap[1] = bitRepresentation;
      break;
    case FOURDIGITS:
       numberToBitMap[4] = bitRepresentation;
      break;
    case EIGHTDIGITS:
      numberToBitMap[8] = bitRepresentation;
      break;
    default:
      numbersToFigureOut.push_back(bitRepresentation);
      break;
    }
  }

  //find the rest of the numbers here
  numberToBitMap[9] = findNine();
  numberToBitMap[0] = findZero();
  numberToBitMap[6] = findSix();
  numberToBitMap[3] = findThree();
  numberToBitMap[5] = findFive();
  numberToBitMap[2] = findTwo();

  for (int i = 0; i < 10; ++i)
  {
    bitToNumberMap[numberToBitMap[i]] = i;
  }
}

int decoder::getNumber()
{
  std::vector<std::string> splitNumber = splitString(numberString, ' ');
  int x = 1000;
  int returnNumber = 0;
  for (int i = 0; i < splitNumber.size(); ++i)
  {
    unsigned char bit = numberToBits(splitNumber[i]);
    int num = bitToNumberMap[bit];
    returnNumber += num * x;
    x /= 10;
  }
  return returnNumber;
}

unsigned char decoder::numberToBits(std::string num)
{
  unsigned char result = 0;
  for (int i = 0; i < num.size(); ++i)
  {
    result |= (1 << (num[i] - 'a'));
  }
  return result;
}

unsigned char decoder::findNine()
{
  unsigned char fourBits = numberToBitMap[4];
  std::vector<unsigned char>::iterator itEnd = numbersToFigureOut.end();
  for (std::vector<unsigned char>::iterator it = numbersToFigureOut.begin(); it != itEnd; ++it)
  {
    if (getBitCount(*it) == 6 && (*it & fourBits) == fourBits)
    {
      unsigned char returnValue = *it;
      numbersToFigureOut.erase(it);
      return returnValue;
    }
  }
}

unsigned char decoder::findZero()
{
  unsigned char sevenBits = numberToBitMap[7];
  std::vector<unsigned char>::iterator itEnd = numbersToFigureOut.end();
  for (std::vector<unsigned char>::iterator it = numbersToFigureOut.begin(); it != itEnd; ++it)
  {
    if (getBitCount(*it) == 6 && (*it & sevenBits) == sevenBits)
    {
      unsigned char returnValue = *it;
      numbersToFigureOut.erase(it);
      return returnValue;
    }
  }
}

unsigned char decoder::findSix()
{
  std::vector<unsigned char>::iterator itEnd = numbersToFigureOut.end();
  for (std::vector<unsigned char>::iterator it = numbersToFigureOut.begin(); it != itEnd; ++it)
  {
    if (getBitCount(*it) == 6)
    {
      unsigned char returnValue = *it;
      numbersToFigureOut.erase(it);
      return returnValue;
    }
  }
}

unsigned char decoder::findThree()
{
  unsigned char sevenBits = numberToBitMap[7];
  std::vector<unsigned char>::iterator itEnd = numbersToFigureOut.end();
  for (std::vector<unsigned char>::iterator it = numbersToFigureOut.begin(); it != itEnd; ++it)
  {
    if (getBitCount(*it) == 5 && (*it & sevenBits) == sevenBits)
    {
      unsigned char returnValue = *it;
      numbersToFigureOut.erase(it);
      return returnValue;
    }
  }
}

unsigned char decoder::findTwo()
{
  return numbersToFigureOut[0];
}

unsigned char decoder::findFive()
{
  unsigned char bits = numberToBitMap[9] - numberToBitMap[7];
  std::vector<unsigned char>::iterator itEnd = numbersToFigureOut.end();
  for (std::vector<unsigned char>::iterator it = numbersToFigureOut.begin(); it != itEnd; ++it)
  {
    if (getBitCount(*it) == 5 && (*it & bits) == bits)
    {
      unsigned char returnValue = *it;
      numbersToFigureOut.erase(it);
      return returnValue;
    }
  }
}

int decoder::getBitCount(unsigned char num)
{
  int count = 0;
  while (num > 0)
  {
    count += num & 1;
    num >>= 1;
  }
  return count;
}

