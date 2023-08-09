#include <string>
#include <iostream>
#include <fstream>
#include <vector>

class binaryNumber
{
public:
  binaryNumber(std::string input)
  {
    for (int i = 0; i < input.length(); ++i)
    {
      unsigned short bit = 0;
      if (input[i] == '1')
        bit = 1;
      else if(input[i] != '0')
        std::cout << "For some reason, we have a bit that isn't 0 or 1. Input: " << input << " at index: " << i << std::endl;
      inputBits.push_back(bit);
    }
  }

  binaryNumber() { }

  std::vector<unsigned short> inputBits = std::vector<unsigned short>();

  unsigned int getNumberInDecimal()
  {
    int step = 1;
    int result = 0;
    for (int i = inputBits.size() - 1; i >= 0; --i)
    {
      if (inputBits[i] == 1)
        result += step;
      step *= 2;
    }
    return result;
  }

  std::string getBinaryString()
  {
    std::string output;
    std::vector<unsigned short>::iterator itEnd = inputBits.end();
    for (std::vector<unsigned short>::iterator it = inputBits.begin(); it != itEnd; ++it)
    {
      output.push_back((char)(48 + *it));
    }
    return output;
  }

  friend std::ostream& operator<<(std::ostream& os, binaryNumber& dt);
};

std::ostream& operator<< (std::ostream& out, binaryNumber& num)
{
  out << num.getBinaryString() << " : " << num.getNumberInDecimal();
  return out;
}

enum bitComparison
{
  ONE,
  ZERO,
  SAME
};

void Part1();
void Part2();

int main(void)
{
  Part1();
  std::cout << std::endl << std::endl << std::endl;
  Part2();
  std::cout << std::endl << std::endl << std::endl;
}

bitComparison getBitComparison(std::vector<binaryNumber> input, int index)
{
  std::vector<binaryNumber>::iterator itEnd = input.end();
  int ones, zeros;
  ones = zeros = 0;
  for (std::vector<binaryNumber>::iterator it = input.begin(); it != itEnd; ++it)
  {
    if (it->inputBits[index] == 1)
      ++ones;
    else if (it->inputBits[index] == 0)
      ++zeros;
    else
      std::cout << "We got a problem, one of the bit wasn't a 1 or 0" << std::endl;
  }
  //std::cout << "There were " << ones << " ones and " << zeros << " zeros." << std::endl;
  if (ones > zeros)
    return bitComparison::ONE;
  else if (zeros > ones)
    return bitComparison::ZERO;
  else
    return bitComparison::SAME;
}

std::vector<binaryNumber> calculateOxygenRate(std::vector<binaryNumber> input, int index, int length)
{
  if (index == length || input.size() == 1)
    return input;

  std::vector<binaryNumber> newInput = std::vector<binaryNumber>();
  bitComparison comparison = getBitComparison(input, index);
  std::vector<binaryNumber>::iterator itEnd = input.end();
  for (std::vector<binaryNumber>::iterator it = input.begin(); it != itEnd; ++it)
  {
    if ((comparison == ONE || comparison == SAME) && it->inputBits[index] == 1)
      newInput.push_back(*it);
    else if (comparison == ZERO && it->inputBits[index] == 0)
      newInput.push_back(*it);
  }

  return calculateOxygenRate(newInput, index + 1, length);
}

std::vector<binaryNumber> calculateCO2Rate(std::vector<binaryNumber> input, int index, int length)
{
  if (index == length || input.size() == 1)
    return input;

  std::vector<binaryNumber> newInput = std::vector<binaryNumber>();
  bitComparison comparison = getBitComparison(input, index);
  std::vector<binaryNumber>::iterator itEnd = input.end();
  for (std::vector<binaryNumber>::iterator it = input.begin(); it != itEnd; ++it)
  {
    if ((comparison == ONE || comparison == SAME) && it->inputBits[index] == 0)
      newInput.push_back(*it);
    else if (comparison == ZERO && it->inputBits[index] == 1)
      newInput.push_back(*it);
  }

  return calculateCO2Rate(newInput, index + 1, length);
}

void Part2()
{
  std::fstream file;
  file.open("part2.txt");
  if (file.is_open())
  {
    std::vector<binaryNumber> inputBinary = std::vector<binaryNumber>();
    std::string line;
    int length = 0;
    while (std::getline(file, line))
    {
      if (line.length() > length)
      {
        length = line.length();
        std::cout << "Setting length to " << length << " from input " << line << std::endl;
      }
      inputBinary.push_back(binaryNumber(line));
    }
    file.close();

    std::vector<binaryNumber> oxygenResult = calculateOxygenRate(inputBinary, 0, length);
    std::vector<binaryNumber> co2Result = calculateCO2Rate(inputBinary, 0, length);
    binaryNumber oxygen = oxygenResult[0];
    binaryNumber co2 = co2Result[0];
    int result = oxygen.getNumberInDecimal() * co2.getNumberInDecimal();
    std::cout << "The oxygen rate is " << oxygen << "\nThe co2 rate is " << co2 << "\nThe result of the two is " << result;
  }
}

void Part1()
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::vector<binaryNumber> inputBinary = std::vector<binaryNumber>();
    std::string line;
    int length = 0;
    while (std::getline(file, line))
    {
      if (line.length() > length)
      {
        length = line.length();
        std::cout << "Setting length to " << length << " from input " << line << std::endl;
      }
      inputBinary.push_back(binaryNumber(line));
    }
    file.close();

    binaryNumber gammaRate = binaryNumber();
    binaryNumber epsilonRate = binaryNumber();
    std::vector<binaryNumber>::iterator itEnd = inputBinary.end();
    for (int i = 0; i < length; ++i)
    {
      int ones, zeros;
      ones = zeros = 0;
      for (std::vector<binaryNumber>::iterator it = inputBinary.begin(); it != itEnd; ++it)
      {
        if (it->inputBits[i] == 1)
          ++ones;
        else if (it->inputBits[i] == 0)
          ++zeros;
        else
          std::cout << "We got a problem, one of the bit wasn't a 1 or 0" << std::endl;
      }
      if (ones > zeros)
      {
        gammaRate.inputBits.push_back(1);
        epsilonRate.inputBits.push_back(0);
      }
      else if (zeros > ones)
      {
        gammaRate.inputBits.push_back(0);
        epsilonRate.inputBits.push_back(1);
      }
      else
      {
        std::cout << "The number of ones and zeros is the same, idk what to do." << std::endl;
      }
    }

    int gRate = gammaRate.getNumberInDecimal();
    int eRate = epsilonRate.getNumberInDecimal();

    int result = gRate * eRate;

    std::cout << "The result we're looking for is " << result << ".\t gamma rate is: " << gRate << ".\t epsilon rate is: " << eRate << std::endl;
  }
}