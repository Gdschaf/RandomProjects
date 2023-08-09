#pragma once

class DoubleLinkedList
{
public:
  DoubleLinkedList() : head(nullptr), tail(nullptr) { }
  ~DoubleLinkedList();

  class Node
  {
  public:
    Node(char x) : c(x), next(nullptr) { }
    Node* next;
    char c;
  };

  void AddNode(char c);
  void InsertAfter(Node* n, char c);
  unsigned long long GetCount() { return count; }
  Node* GetHead() { return head; }
private:
  Node* head;
  Node* tail;
  unsigned long long count;
};
