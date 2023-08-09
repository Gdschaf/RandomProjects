#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

#include "LinkedList2D.h"

#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */

std::vector<int> stringToIntVector(std::string input)
{
  std::vector<int> returnVector = std::vector<int>();
  for (int i = 0; i < input.size(); ++i)
  {
    returnVector.push_back(input[i] = '0');
  }
  return returnVector;
}

void recursiveBasinSearch(std::unordered_set<LinkedList2D::Node*> &nodesInBasin, LinkedList2D::Node* node)
{
  nodesInBasin.insert(node);
  if (node->down != nullptr && node->down->value != 9 && nodesInBasin.find(node->down) == nodesInBasin.end())
  {
    recursiveBasinSearch(nodesInBasin, node->down);
  }
  if (node->left != nullptr && node->left->value != 9 && nodesInBasin.find(node->left) == nodesInBasin.end())
  {
    recursiveBasinSearch(nodesInBasin, node->left);
  }
  if (node->up != nullptr && node->up->value != 9 && nodesInBasin.find(node->up) == nodesInBasin.end())
  {
    recursiveBasinSearch(nodesInBasin, node->up);
  }
  if (node->right != nullptr && node->right->value != 9 && nodesInBasin.find(node->right) == nodesInBasin.end())
  {
    recursiveBasinSearch(nodesInBasin, node->right);
  }
}

int main(void)
{
  std::fstream file;
  file.open("input.txt");
  if(file.is_open())
  {
    std::string line;
    LinkedList2D depthMap = LinkedList2D();
    while (std::getline(file, line))
    {
      depthMap.AddRow(line);
    }
    file.close();

    int value = 0;
    std::vector<LinkedList2D::Node*> lowestNodes = std::vector<LinkedList2D::Node*>();
    LinkedList2D::Node* currentRow = depthMap.head;
    while (currentRow != nullptr)
    {
      LinkedList2D::Node* currentNode = currentRow;
      while (currentNode != nullptr)
      {
        bool lowest = true;
        int currentValue = currentNode->value;
        if (currentNode->right != nullptr && currentNode->right->value <= currentValue)
          lowest = false;
        if (currentNode->down != nullptr && currentNode->down->value <= currentValue)
          lowest = false;
        if (currentNode->left != nullptr && currentNode->left->value <= currentValue)
          lowest = false;
        if (currentNode->up != nullptr && currentNode->up->value <= currentValue)
          lowest = false;
        if (lowest)
        {
          value += currentValue + 1;
          std::cout << GREEN << currentValue << RESET;
          lowestNodes.push_back(currentNode);
        }
        else
        {
          if (currentValue == 9)
            std::cout << CYAN << currentValue << RESET;
          else
            std::cout << BLUE << currentValue << RESET;
        }
        currentNode = currentNode->right;
      }
      std::cout << std::endl;
      currentRow = currentRow->down;
    }

    std::cout << "Wow, did we get a value? This is it!: " << value << std::endl << std::endl << std::endl;

    std::vector<int> basinCounts = std::vector<int>();
    for (int i = 0; i < lowestNodes.size(); ++i)
    {
      std::unordered_set<LinkedList2D::Node*> basinNodes;
      recursiveBasinSearch(basinNodes, lowestNodes[i]);
      basinCounts.push_back(basinNodes.size());
    }

    std::sort(basinCounts.begin(), basinCounts.end(), std::greater<int>());

    std::cout << "The total number of basins is: " << basinCounts.size() << std::endl;
    for (int i = 0; i < basinCounts.size(); ++i)
    {
      std::cout << "Basin " << i << " size: " << basinCounts[i] << std::endl;
    }

    int total = 1;
    for (int i = 0; i < 3; ++i)
    {
      total *= basinCounts[i];
    }
    std::cout << "The answer to part 2 is: " << total << std::endl;
  }
}