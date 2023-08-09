#include "LinkedList2D.h"

void LinkedList2D::AddRow(std::string input)
{
  Node* newRow = nullptr;
  for (int i = 0; i < input.size(); ++i)
  {
    Node* newNode = new Node(input[i]);
    if (newRow == nullptr)
    {
      newRow = newNode;
    }
    else
    {
      newRow->right = newNode;
      newNode->left = newRow;
      newRow = newNode;
    }
  }
  if (newRow != nullptr)
  {
    while (newRow->left != NULL)
      newRow = newRow->left;

    //back to the beginning of the row here
    if (lastRow == nullptr)
    {
      head = lastRow = newRow;
    }
    else
    {
      Node* lastRowNode = lastRow;
      Node* newRowNode = newRow;
      while (newRowNode != nullptr)
      {
        lastRowNode->down = newRowNode;
        newRowNode->up = lastRowNode;
        lastRowNode = lastRowNode->right;
        newRowNode = newRowNode->right;
      }
      lastRow = newRow;
    }
  }
}

LinkedList2D::~LinkedList2D()
{
  Node* currentRow = head;
  while(currentRow != nullptr)
  {
    Node* currentNode = currentRow;
    currentRow = currentNode->down;
    while (currentNode != nullptr)
    {
      Node* nodeToDelete = currentNode;
      currentNode = currentNode->right;
      delete nodeToDelete;
    }
  }
}
