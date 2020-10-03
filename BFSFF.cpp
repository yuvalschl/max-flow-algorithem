#include "BFSFF.h"


void EdmondsKarp(Graph& graph, int s, int t)
{
     int graphSize = graph.GetSize();
     List<int> shortestPathList;
     Bfs(graph, s, t, shortestPathList, graphSize);                         // BFS returns a list of the shortest path
     int minFlow, iterationCounter = 0, maxFlow = 0;
     bool* cut;

     while (!shortestPathList.isEmpty())                                    // while there is an augmenting path, update Residual flow in graph              
     {
          minFlow = graph.getMinimumCapacityForPath(shortestPathList);			
          maxFlow += minFlow;
          graph.updateGraph(shortestPathList, minFlow);						// update graph according to the augmenting path found
          shortestPathList.makeEmpty();                                              
          Bfs(graph, s, t, shortestPathList, graphSize);                    // look for the next path
          iterationCounter++;
     }
     cut = graph.FindCut(s);                                                // find Min cut using BFS run
     cout << "BFS Method:" << endl;
     graph.printRunSummery(maxFlow, cut, iterationCounter);
}





void Bfs(Graph& graph, int s, int t, List<int>& shortestPathList, int graphSize)
{
     int* parent = new int[graphSize];
     bool* visited = new bool[graphSize];
     Queue bfsQueue;                                                                        // Queue for BFS
     bfsQueue.EnQueue(s);                                                                   // Enqeqe source

     for (int i = 0; i < graphSize; i++)                                                    // initilize arrays used
     {
          parent[i] = -1;
          visited[i] = false;
     }

     visited[s] = true;

     while (!bfsQueue.isEmpty())                                                            // while Queue is not empty            
     {
          int currentNode = bfsQueue.DeQueue();                                             // current Node in Queue
          List<int> currentNodeAdj = graph.GetAdjList(currentNode);             

          while (!currentNodeAdj.isEmpty())                                     
          {
               int currentAdj = currentNodeAdj.popHead();                                   //current adj of currentNode to check path
               MatrixCell currentVertex = graph.getCell(currentNode, currentAdj);

               if (visited[currentAdj] == false && currentVertex.getResidualFlow() > 0)
               {
                    parent[currentAdj] = currentNode;
                    visited[currentAdj] = true;
                    if (currentAdj == t)                                                     // found path to the sink
                    {
                         graph.getShortestPathFromArray(parent, t, shortestPathList);      
                         delete[] parent;
                         delete[] visited;
                         return;
                    }
                    bfsQueue.EnQueue(currentAdj);
               }
          }
     }
     delete[] parent;
     delete[] visited;
}