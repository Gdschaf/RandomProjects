#include "CaveMap.h"
#include "utils.h"

CaveMap::~CaveMap()
{
  //delete all nodes
  std::unordered_map<std::string, Node*>::iterator itEnd = allNodes.end();
  for (std::unordered_map<std::string, Node*>::iterator it = allNodes.begin(); it != itEnd; ++it)
  {
    delete it->second;
  }
  allNodes.clear();
  startNode = nullptr;
}

void CaveMap::AddConnection(std::string input)
{
  std::vector<std::string> nodeNames = splitString(input, '-');
  Node* firstNode = GetNode(nodeNames[0]);
  Node* secondNode = GetNode(nodeNames[1]);
  firstNode->AttachNode(secondNode);
  secondNode->AttachNode(firstNode);
}

CaveMap::Node* CaveMap::GetNode(std::string nodeID)
{
  if (allNodes.find(nodeID) == allNodes.end())
  {
    //create new node and return it
    Node* newNode = new Node(nodeID);
    if (nodeID == "start")
      startNode = newNode;
    allNodes[nodeID] = newNode;
    return newNode;
  }
  
  return allNodes[nodeID];
}

void CaveMap::GetAllPaths(std::vector<std::string>& paths, std::vector<std::string>& currentPath, Node* node, bool duplicateSmall)
{
  currentPath.push_back(node->ID);

  if (node->ID == "end")
  {
    //add a path to the paths vector, but build it first I guess
    std::string path;
    for (int i = 0; i < currentPath.size(); ++i)
    {
      path += currentPath[i];
      if (i != currentPath.size() - 1)
        path += ",";
    }
    paths.push_back(path);
    currentPath.pop_back();
    return;
  }

  std::unordered_set<Node*>::iterator itEnd = node->connectedNodes.end();
  for (std::unordered_set<Node*>::iterator it = node->connectedNodes.begin(); it != itEnd; ++it)
  {
    bool dup = std::find(currentPath.begin(), currentPath.end(), (*it)->ID) != currentPath.end();
    bool smallCave = !(*it)->largeCave;
    if (smallCave && dup && duplicateSmall || (*it)->ID == "start")
      continue;
    GetAllPaths(paths, currentPath, *it, (smallCave && dup) ? true : duplicateSmall);
  }

  currentPath.pop_back();
}

CaveMap::Node::Node(std::string caveID)
{
  ID = caveID;
  //figure out if it's a large cave here
  largeCave = uppercase(caveID[0]);
}

void CaveMap::Node::AttachNode(Node* n)
{
  connectedNodes.insert(n);
}
