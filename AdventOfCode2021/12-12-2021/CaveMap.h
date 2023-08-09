#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>

class CaveMap
{
public:
  class Node
  {
  public:
    Node(std::string caveID);
    void AttachNode(Node* n);
    std::unordered_set<Node*> connectedNodes = std::unordered_set<Node*>();
    bool largeCave = false;
    std::string ID;
  };

  ~CaveMap();
  void AddConnection(std::string input);
  Node* GetNode(std::string nodeID);
  void GetAllPaths(std::vector<std::string>& paths, std::vector<std::string>& currentPath, Node* node, bool duplicateSmall = false);
private:
  Node* startNode = nullptr;
  std::unordered_map<std::string, Node*> allNodes = std::unordered_map<std::string, Node*>();
};
