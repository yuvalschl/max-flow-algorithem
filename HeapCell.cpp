#include "HeapCell.h"

HeapCell::HeapCell()
{
	this->m_key = 0;
	this->m_data = 0;
}

HeapCell::HeapCell(int key, int data)
{
	this->m_key = key;
	this->m_data = data;
}

int HeapCell::getKey() const
{
	return this->m_key;
}

int HeapCell::getData() const
{
	return this->m_data;
}

void HeapCell::setKey(int key)
{
	this->m_key = key;
}

void HeapCell::setData(int data)
{
	this->m_data = data;
}
