#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int depthIncreasesPart1();
int depthSumOfMeasurements();

int main(void)
{
  int numberOfIncreases = depthIncreasesPart1();
  std::cout << "The number of increases was " << numberOfIncreases << std::endl;

  int numberOfSumMeasurementIncreases = depthSumOfMeasurements();
  std::cout << "The number of sum measurement increases was " << numberOfSumMeasurementIncreases << std::endl;

  return 0;
}


int depthIncreasesPart1()
{
  std::ifstream file;
  file.open("input.txt");
  int increaseCount = 0;
  if (file.is_open())
  {
    std::string line;
    bool firstValue = true;
    int lastValue;
    while (getline(file, line))
    {
      int value = std::stoi(line);
      if (firstValue)
      {
        lastValue = value;
        firstValue = false;
        std::cout << value << " (N/A - no previous measurement)" << std::endl;
      }
      else
      {
        bool increase = value > lastValue;
        if (increase)
        {
          ++increaseCount;
        }
        lastValue = value;
        std::cout << value << (increase ? " (increased)" : " (decreased)") << "\t total increases: " << increaseCount << std::endl;
      }
    }
    file.close();
  }
  return increaseCount;
}

int depthSumOfMeasurements()
{
  std::ifstream file;
  file.open("input-part2.txt");
  int increaseCount = 0;
  if (file.is_open())
  {
    std::string line;
    std::vector<int> inputList = std::vector<int>();
    while (getline(file, line))
    {
      int value = std::stoi(line);
      inputList.push_back(value);
    }
    file.close();

    std::vector<int> sumMeasurementsList = std::vector<int>();
    for (int i = 2; i < inputList.size(); ++i)
    {
      int sum = inputList[i] + inputList[i - 1] + inputList[i - 2];
      sumMeasurementsList.push_back(sum);
    }

    for (int i = 1; i < sumMeasurementsList.size(); ++i)
    {
      if (sumMeasurementsList[i] > sumMeasurementsList[i - 1])
        ++increaseCount;
    }
  }
  return increaseCount;
}