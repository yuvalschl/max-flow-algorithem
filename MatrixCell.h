#pragma once

class MatrixCell
{
private:
	int m_ResidualFlow;
	int m_flow;
	int m_capacity;
	bool m_isEdge = false;

public:
	void setCell(int capacity, int flow, bool isEdge);

	const int getFlow() const;
	const int getCapacity() const;
	const bool getIsEdge() const;
	const int getResidualFlow() const;
	void setIsEdge(bool isEdge);
	void setFlow(int flow);
	void setCapacity(int capacity);
	void updateFlow(int addedFlow);
};
