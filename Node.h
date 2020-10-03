#pragma once
#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T>* next = NULL;

	Node();
	Node(T i_data) : data(i_data) {}
};

template<class T>
Node<T>::Node()
{

}
