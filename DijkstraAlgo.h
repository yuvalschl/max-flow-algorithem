#pragma once
#include "List.h"
#include "Graph.h"
#include "Queue.h"
#include "Heap.h"

void findMaxFlowWithDijkstra(Graph& graph, int s, int t);
void Dijkstra(Graph& graph, int s, int t, List<int>& bestPathList, int graphSize);
void relax(Graph& graph, Heap& maxHeap, int u, int v, int* parent, int* vals, bool* visited, int* cellArrIndex);
void initArrays(int graphSize, int* parent, int* vals, int* cellArrIndex, bool* visited, HeapCell* cellArr);
void deleteArrays(int* parent, int* vals, int* cellArrIndex, bool* visited, HeapCell* cellArr);
