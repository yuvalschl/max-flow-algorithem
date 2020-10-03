#include "Heap.h"

Heap::Heap(int max)
{  
	m_maxSize = max;
	m_heapSize = 0;
	m_allocated = true;
}

void Heap::Build(HeapCell* arr, int n, int* cellArrIndex)
{
	m_heapSize = m_maxSize = n;
	m_cellArr = arr;
	m_allocated = false;												// did not allocate

	for (int i = n / 2 - 1; i >= 0; i--)
		FixHeap(i, cellArrIndex);
}

Heap::~Heap()
{
	if (m_allocated)													// no allocation in this exe, only in main
	{
		delete[] m_cellArr;
	}
	m_cellArr = nullptr;
}

int Heap::Left(int node)
{
	return (2 * node + 1);												// get left index
}

int Heap::Right(int node)
{
	return (2 * node + 2);												// get right index
}

int Heap::Parent(int node)
{
	return (node - 1) / 2;												// get parent index
}
																		//Fixes the heap that has node as root
void Heap::FixHeap(int node, int* cellArrIndex)
{
	int max;
	int left = Left(node);
	int right = Right(node);

	if ((left < m_heapSize) && (m_cellArr[left].getKey() > m_cellArr[node].getKey()))
	{
		max = left;
	}
	else
	{
		max = node;
	}

	if ((right < m_heapSize) && (m_cellArr[right].getKey() > m_cellArr[max].getKey()))
	{
		max = right;
	}
	// Swap values if necessary, and continue
	// fixing the heap towards the leaves
	if (max != node)
	{
		swap(node, max);
		//int temp = cellArrIndex[node];
		cellArrIndex[m_cellArr[node].getData()] = node;
		cellArrIndex[m_cellArr[max].getData()] = max;
		
		FixHeap(max, cellArrIndex);
	}
}

int Heap::findKeyInArr(int key) const
{
	for (int i = 0; i < m_heapSize; i++)
	{
		if (key == m_cellArr[i].getData())
		{
			return i;
		}
	}

	return -1;
}


HeapCell Heap::Max() const // return the first element (min)
{
	return m_cellArr[0];
}
//Delete the minimal element in the heap and Fix the heap
HeapCell Heap::DeleteMax(int* cellArrIndex)
{
	if (m_heapSize < 1)
	{
		cout << "Error: Empty Heap!" << endl;
		exit(1);
	}

	HeapCell max = m_cellArr[0];
	m_heapSize--;
	m_cellArr[0] = m_cellArr[m_heapSize];
	FixHeap(0, cellArrIndex);
	return(max);
}

void Heap::IncreaseKey(int place, int newData, int* cellArrIndex)
{
	m_cellArr[place].setKey(newData);
	while (place != 0 && m_cellArr[Parent(place)].getKey() < m_cellArr[place].getKey())
	{
		swap(place, Parent(place));

		cellArrIndex[m_cellArr[place].getData()] = place;
		cellArrIndex[m_cellArr[Parent(place)].getData()] = Parent(place);
		place = Parent(place);
	}
}

void Heap::swap(int node1, int node2)
{
	HeapCell temp;
	temp = m_cellArr[node1];
	m_cellArr[node1] = m_cellArr[node2];
	m_cellArr[node2] = temp;
}
// check if empty heap
bool Heap::isEmpty() const
{
	return m_heapSize == 0;
}
