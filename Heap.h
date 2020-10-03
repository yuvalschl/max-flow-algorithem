#pragma once
#include <iostream>
#include <stdlib.h>
#include "HeapCell.h"
using namespace std;

class Heap
{
private:
	HeapCell* m_cellArr = NULL;
	bool m_allocated;
	int m_maxSize;	
	int m_heapSize; 

	static int Left(int node);
	static int Right(int node);
	static int Parent(int node);
	void FixHeap(int node, int* cellArrIndex);

public:
	Heap(int max);	
	~Heap();		

	void Build(HeapCell* arr, int n, int* cellArrIndex);
	HeapCell Max() const;
	HeapCell DeleteMax(int* cellArrIndex);
	void IncreaseKey(int place, int newKey, int* cellArrIndex);
	void swap(int node, int min);
	bool isEmpty() const;
	int findKeyInArr(int key) const;
};