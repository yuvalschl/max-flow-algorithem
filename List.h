#pragma once
#include <iostream>
#include "Node.h"
using namespace std;

template <class T>
class List
{
private:
	Node<T> *head;
	Node<T> *tail;

public:

	List();
	List(const List& src);
	~List();
	void addToBack(const T data);
	void addToFront(const T data);
	bool isEmpty() const;
	void makeEmpty();
	T popHead();
	Node<T>* getHead() const;
	const List& operator=(List& src);
};

template<class T>
inline List<T>::List()
{
	head = NULL;
	tail = NULL;
}

template<class T>
inline List<T>::List(const List & src) 
{
	head = NULL;
	tail = NULL;

	Node<T> *node = src.head;

	while (node != NULL)
	{
		addToBack(node->data);
		node = node->next;
	}	
}

template<class T>
const List<T>& List<T>::operator=(List<T>& src)
{
	head = NULL;
	tail = NULL;

	Node<T>* node = src.head;

	while (node != NULL)
	{
		addToBack(node->data);
		node = node->next;
	}

	src.head = NULL;
}

template<class T>
List<T>::~List()
{
	while (head != NULL)
	{
		Node<T> *tmp = head;
		head = head->next;
		delete tmp;
	}
	delete head;
}

template<class T>
void List<T>::addToBack(const T data)
{
	if (head == NULL)
	{
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		tail->next = new Node<T>(data);
		tail = tail->next;
		tail->next = NULL;
	}
}

template<class T>
inline void List<T>::addToFront(const T data)
{
	if (head == NULL)
	{
		head = new Node<T>(data);
		tail = head;
	}
	else
	{
		Node<T> *temp = head;
		head = new Node<T>(data);
		head->next = temp;
	}
}

template<class T>
inline bool List<T>::isEmpty() const
{
	return head == NULL;
}

template<class T>
inline void List<T>::makeEmpty()
{
	this->~List();
}


template<class T>
inline T List<T>::popHead()
{
	if (isEmpty() == false)
	{
		T returnData = head->data;
		Node<T> *temp = head->next;
		delete head;
		head = temp;

		return returnData;
	}
	else
	{
		cout << "list is empty" << endl;
		return NULL;
	}
}

template<class T>
Node<T>* List<T>::getHead() const
{
	return head;
}






