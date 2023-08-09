#include "DoubleLinkedList.h"

DoubleLinkedList::~DoubleLinkedList()
{
  Node* n = head;
  while (n != nullptr)
  {
    Node* next = n->next;
    delete n;
    n = next;
  }
}

void DoubleLinkedList::AddNode(char c)
{
  Node* n = new Node(c);
  if (head == nullptr)
  {
    head = tail = n;
  }
  else
  {
    tail->next = n;
    tail = n;
  }
  ++count;
}

void DoubleLinkedList::InsertAfter(Node* n, char c)
{
  Node* newNode = new Node(c);
  Node* tempNext = n->next;
  newNode->next = tempNext;
  n->next = newNode;
  ++count;
}
