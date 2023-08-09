#include <fstream>
#include <iostream>

#include "CaveMap.h"

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if (file.is_open())
  {
    std::string line;
    CaveMap caveMap = CaveMap();
    while (std::getline(file, line))
    {
      caveMap.AddConnection(line);
    }
    std::vector<std::string> allPaths = std::vector<std::string>();
    std::vector<std::string> path = std::vector<std::string>();
    caveMap.GetAllPaths(allPaths, path, caveMap.GetNode("start"));

    for (int i = 0; i < allPaths.size(); ++i)
    {
      std::cout << allPaths[i] << std::endl;
    }
    std::cout << "The total number of paths is " << allPaths.size() << std::endl;

    file.close();
  }
}