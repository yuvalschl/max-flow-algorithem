#include "MatrixCell.h"

void MatrixCell::setCell(int capacity, int flow, bool isEdge)
{
	m_ResidualFlow = capacity;
	m_capacity = capacity;
	m_flow = 0;
	m_isEdge = isEdge;
}

const int MatrixCell::getFlow() const
{
	return m_flow;
}

const int MatrixCell::getCapacity() const
{
	return m_capacity;
}
 
const bool MatrixCell::getIsEdge() const
{
	return m_isEdge;
}

const int MatrixCell::getResidualFlow() const
{
	return m_ResidualFlow;
}

void MatrixCell::setIsEdge(bool isEdge)
{
	m_isEdge = isEdge;
}

void MatrixCell::setFlow(int flow)
{
	m_flow = flow;
}

void MatrixCell::setCapacity(int capacity)
{
	m_capacity = capacity;
}

void MatrixCell::updateFlow(int addedFlow)
{
	m_flow += addedFlow;
	m_ResidualFlow -= addedFlow;
}



