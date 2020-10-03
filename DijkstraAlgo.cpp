#include "DijkstraAlgo.h"
#include "Heap.h"
#include "HeapCell.h"
#include <iostream> 
using namespace std;


void findMaxFlowWithDijkstra(Graph& graph, int s, int t)
{
     int graphSize = graph.GetSize();
     List<int> bestPathList;
     Dijkstra(graph, s, t, bestPathList, graphSize);                                    // Dijkstra returns a list of the shortest path
     int minFlow, iterationCounter = 0, maxFlow = 0;
     bool* cut;

     while (graph.getMinimumCapacityForPath(bestPathList) != 0)                         // while there is an augmenting path, update Residual flow in graph 
     {
          minFlow = graph.getMinimumCapacityForPath(bestPathList);
          maxFlow += minFlow;
          graph.updateGraph(bestPathList, minFlow);                                     // update graph according to the augmenting path found
          bestPathList.makeEmpty();
          Dijkstra(graph, s, t, bestPathList, graphSize);                                          // look for the next path
          iterationCounter++;
     }
     cut = graph.FindCut(s);                                                            // find Min cut using BFS run
     cout << "Greedy Method:" << endl;
     graph.printRunSummery(maxFlow, cut, iterationCounter);
}

void Dijkstra(Graph& graph, int s, int t, List<int>& bestPathList,int graphSize)
{
     int* parent = new int[graphSize];                                                  // parent array
     int* vals = new int[graphSize];                                                    // the vaule(residual flow) of an edge                                    
     int* cellArrIndex = new int[graphSize];                                            // index in array of heap
     bool* visited = new bool[graphSize];                                               
     Heap maxHeap(graph.GetSize());
     HeapCell* cellArr = new HeapCell[graphSize];                                       // the array used by the heap
    
     initArrays(graphSize, parent, vals, cellArrIndex, visited, cellArr);

     vals[s] = 0;
     visited[s] = true;
     cellArr[s].setKey(0);
     maxHeap.Build(cellArr, graphSize, cellArrIndex);                                   // build the heap using Floyd's Algorithm

     List<int> sNodeAdj = graph.GetAdjList(s);
     HeapCell currentCell = maxHeap.DeleteMax(cellArrIndex);                            // get the Max and do first itaeration
     while (!sNodeAdj.isEmpty())
     {
          int v = sNodeAdj.popHead();
          vals[v] = graph.getCell(s, v).getResidualFlow();
          parent[v] = s;
          int keyIndex = cellArrIndex[v];
          maxHeap.IncreaseKey(keyIndex, vals[v], cellArrIndex);
     }

     while (!maxHeap.isEmpty())                                                         // while heap is not empty
     {
          currentCell = maxHeap.DeleteMax(cellArrIndex);
          int u = currentCell.getData();
          visited[u] = true;
          List<int> currentNodeAdj = graph.GetAdjList(u);                               // get adjList and perform relax for each

          while (!currentNodeAdj.isEmpty())
          {
               int v = currentNodeAdj.popHead();
               relax(graph, maxHeap, u, v, parent, vals, visited, cellArrIndex);        
          }
     }
     graph.getShortestPathFromArray(parent, t, bestPathList);
     deleteArrays(parent, vals, cellArrIndex, visited, cellArr);
}

void initArrays(int graphSize, int* parent, int* vals, int* cellArrIndex, bool* visited, HeapCell* cellArr)
{
     for (int i = 0; i < graphSize; i++)
     {
          parent[i] = -1;
          vals[i] = -1;
          cellArrIndex[i] = i;
          visited[i] = false;
          cellArr[i] = HeapCell(-1, i);
     }
}

void deleteArrays(int* parent, int* vals, int* cellArrIndex, bool* visited, HeapCell* cellArr)
{
     delete[] parent;
     delete[] vals;
     delete[] cellArrIndex;
     delete[] visited;
     delete[] cellArr;
}

void relax(Graph& graph, Heap& maxHeap, int u, int v, int* parent, int* vals, bool* visited, int* cellArrIndex)     // Relax using IncreaseKey
{
     if (vals[v] < min(vals[u], graph.getCell(u, v).getResidualFlow()) && visited[v] == false)
     {
          vals[v] = min(vals[u], graph.getCell(u, v).getResidualFlow());
          parent[v] = u;
          maxHeap.IncreaseKey(maxHeap.findKeyInArr(v), vals[v], cellArrIndex);
     }
}