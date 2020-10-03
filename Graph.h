#pragma once
#include "MatrixCell.h"
#include "List.h"

using namespace std;
/*
We chose to represent both the Flow Network and the Risedual graph in the same Graph class
MatrixCell contains all the needed information for each edge in the graph represented by a matrix.
*/
class Graph
{
private:
	int m_size;
	MatrixCell** m_GraphMatrix;
public:
	Graph();
	~Graph();
	int GetSize();
	void MakeEmptyGraph(int n);
	bool IsAdjacent(int u, int v) const;
	List<int> GetAdjList(int u) const;
	MatrixCell getCell(int u, int v) const;
	void AddEdge(int u, int v, int c);
	void RemoveEdge(int u, int v);
	void updateFlow(int u, int v, int flow);
	void updateFlowHelper(int u, int v, int flow);

	void getShortestPathFromArray(int* parentArr, int t, List<int>& shortestPathList) const;
	int getMinimumCapacityForPath(List<int>& shortestPathList) const;
	void updateGraph(List<int>& shortestPathList, int flowToAdd);
	bool* FindCut(int s) const;
	void printCutLine(bool* cut, bool sOrT, int size) const;
	void printRunSummery(int maxFlow, bool* cut, int iterationCounter) const;
	void isValidEdge(int v, int u) const;
};

