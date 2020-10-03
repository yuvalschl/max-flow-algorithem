#include "Queue.h"
#include <iostream>
using namespace std;


Queue::Queue()
{
	makeEmpty();
}

Queue::~Queue()
{
	m_CellQueue.~List();
}

bool Queue::isEmpty()
{
	return m_CellQueue.isEmpty();
}

void Queue::EnQueue(int Cell)
{
	m_CellQueue.addToBack(Cell);
}

int Queue::DeQueue()
{
	return m_CellQueue.popHead();
}

void Queue::makeEmpty()
{
	this->~Queue();
}


