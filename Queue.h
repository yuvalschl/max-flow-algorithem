#pragma once
#include "MatrixCell.h"
#include "List.h"
using namespace std;

class Queue
{
private:
	List<int> m_CellQueue;
public:

	Queue();
	~Queue();
	bool isEmpty();
	void EnQueue(int cell); 
	int DeQueue();  
	void makeEmpty(); 
};

