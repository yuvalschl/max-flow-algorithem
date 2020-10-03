#pragma once
#include "List.h"
#include "Graph.h"
#include "Queue.h"

void Bfs(Graph& graph, int s, int t, List<int>& shortestPathList, int graphSize);
void EdmondsKarp(Graph& graph, int s, int t);
