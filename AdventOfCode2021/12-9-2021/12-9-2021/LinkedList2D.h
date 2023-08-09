#pragma once

#include <string>

class LinkedList2D
{
public:
  void AddRow(std::string input);
  ~LinkedList2D();
  class Node
  {
  public:
    Node(int v) { value = v; }
    Node(char c) { value = c - '0'; }
    Node* left = nullptr;
    Node* right = nullptr;
    Node* up = nullptr;
    Node* down = nullptr;
    int value;
  };
  Node* head = nullptr;
  Node* lastRow = nullptr;
};