#pragma once

#include <iostream>

//TEMPLATED CLASSES ARE LITERALLY AIDS

template <typename T>
class LoopedLinkedList
{
protected:
	class Node
	{
	public:
		Node(T d) : data(d) { }
		T data;
		Node * next;
		Node * previous;
	};

	Node * startingNode;
	int listCount = 0;
public:
	~LoopedLinkedList();
	LoopedLinkedList();

	LoopedLinkedList<T> & operator=(const LoopedLinkedList<T> & rhs);
	T & operator[](int index);
	const T & operator[](int index) const;

	template <typename T> //this is dumb.
	friend std::ostream & operator<<(std::ostream & os, LoopedLinkedList<T> & rhs);

	void push_back(T data);
	void rotate(int offset);
	void clear_list();
	void reverse();
	const int size() { return listCount; }
};


template <typename T>
LoopedLinkedList<T>::~LoopedLinkedList()
{
	clear_list();
}

template <typename T>
LoopedLinkedList<T>::LoopedLinkedList()
{
	startingNode = NULL;
	listCount = 0;
}

template <typename T>
LoopedLinkedList<T> & LoopedLinkedList<T>::operator=(const LoopedLinkedList<T> & rhs)
{
	//we gotta do a deep copy here, delete ol' list, etc
	clear_list();
	for (int i = 0; i < rhs.listCount; ++i)
	{
		push_back(rhs[i]);
	}
	return *this;
}

template <typename T>
T & LoopedLinkedList<T>::operator[](int index)
{
	Node * returnPointer = startingNode;
	for (int i = 0; i < index; ++i)
	{
		returnPointer = returnPointer->next;
	}
	return returnPointer->data;
}

template <typename T>
const T & LoopedLinkedList<T>::operator[](int index) const
{
	Node * returnPointer = startingNode;
	for (int i = 0; i < index; ++i)
	{
		returnPointer = returnPointer->next;
	}
	return returnPointer->data;
}

template <typename T>
void LoopedLinkedList<T>::push_back(T data)
{
	Node * newNode = new Node(data);
	if (listCount == 0 || startingNode == nullptr) //these should always be true at the same time but just incase?
	{
		newNode->next =  newNode;
		newNode->previous = newNode;
		startingNode = newNode;
		++listCount;
	}
	else
	{
		Node * lastNode = startingNode->previous;
		lastNode->next = newNode;
		newNode->previous = lastNode;
		newNode->next = startingNode;
		startingNode->previous = newNode;
		++listCount;
	}
}

template <typename T>
void LoopedLinkedList<T>::reverse()
{
	Node * currentNode = startingNode;
	for (int i = 0; i < listCount; ++i)
	{
		Node * tempNode = currentNode->next;
		currentNode->next = currentNode->previous;
		currentNode->previous = tempNode;
		currentNode = currentNode->next;
	}
}

template <typename T>
void LoopedLinkedList<T>::clear_list()
{
	Node * currentNode = startingNode;
	for (int i = 0; i < listCount; ++i)
	{
		Node * deleteNode = currentNode;
		currentNode = currentNode->next;
		delete deleteNode;
	}

	startingNode = nullptr;
	listCount = 0;
}

template <typename T>
void LoopedLinkedList<T>::rotate(int offset)
{
	if (offset == 0) //LOLE WHY
		return;

	if (offset < 0)
	{
		for (int i = 0; i > offset; --i)
		{
			startingNode = startingNode->previous;
		}
	}
	else if (offset > 0)
	{
		for (int i = 0; i < offset; ++i)
		{
			startingNode = startingNode->next;
		}
	}
}

template <typename T>
std::ostream & operator<<(std::ostream & os, LoopedLinkedList<T> & rhs)
{
	for (int i = 0; i < rhs.size(); ++i)
	{
		os << rhs[i] << '\t';
	}
	return os;
}