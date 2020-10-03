#include "Graph.h"
#include "List.h"
#include "Queue.h"

Graph::Graph()
{
	m_size = 0;
	m_GraphMatrix = NULL;
}

Graph::~Graph()
{
     for (int i = 0; i < m_size; i++) 
     {
          delete[] m_GraphMatrix[i];
     }
     delete[] m_GraphMatrix;
}

int Graph::GetSize()
{
	return m_size;
}

void Graph::MakeEmptyGraph(int n)                   // allocate empty graph
{
	m_size = n;
	m_GraphMatrix = new MatrixCell *[n];

	for (int i = 0; i < n; i++)
	{
		m_GraphMatrix[i] = new MatrixCell[n];
	}
}

bool Graph::IsAdjacent(int u, int v) const          
{
    isValidEdge(u, v);
	return m_GraphMatrix[u][v].getIsEdge();
}

List<int> Graph::GetAdjList(int u) const            // return adj list of ints (vertexes)
{
    isValidEdge(u, u);

	List<int> adjList;
	for (int i = 0; i < m_size; i++)
	{
		if (m_GraphMatrix[u][i].getIsEdge())
		{
			adjList.addToBack(i);
		}
	}
	return adjList;
}

MatrixCell Graph::getCell(int u, int v) const
{
    isValidEdge(u, v);
	return m_GraphMatrix[u][v];
}

void Graph::AddEdge(int u, int v, int c)
{
    isValidEdge(u, v);
	m_GraphMatrix[u][v].setCell(c, 0, true);
}

void Graph::RemoveEdge(int u, int v)
{
    isValidEdge(u, v);
	m_GraphMatrix[u][v].setIsEdge(false);
	m_GraphMatrix[u][v].setCapacity(0);
}

void Graph::updateFlow(int u, int v, int flow)
{
    isValidEdge(u, v);
	updateFlowHelper(u, v, flow);
	flow *= -1;								                        //	decrese from the opposite egde
	updateFlowHelper(v, u, flow);
}

void Graph::updateFlowHelper(int u, int v, int addedFlow)
{
	m_GraphMatrix[u][v].updateFlow(addedFlow);
}
// recursive function to get shortestPathList from parent array
void Graph::getShortestPathFromArray(int* parentArr, int t, List<int>& shortestPathList) const 
{
     shortestPathList.addToFront(t);
     t = parentArr[t];
     if (parentArr[t] == -1)
     {
          shortestPathList.addToFront(t);
          return;
     }
     else
     {
          getShortestPathFromArray(parentArr, t, shortestPathList);
     }
}
// get the minimum capacity in a given augmenting path
int Graph::getMinimumCapacityForPath(List<int>& shortestPathList) const
{
     Node<int>* currVertex = shortestPathList.getHead();
     MatrixCell currentEdge = getCell(currVertex->data, currVertex->next->data);
     int minCapacity = currentEdge.getResidualFlow();
     currVertex = currVertex->next;

     while (currVertex->next != NULL)
     {
          currentEdge = getCell(currVertex->data, currVertex->next->data);
          if (minCapacity > currentEdge.getResidualFlow())
          {
               minCapacity = currentEdge.getResidualFlow();
          }
          currVertex = currVertex->next;
     }

     return minCapacity;
}
// update the path with a given flow to add
void Graph::updateGraph(List<int>& shortestPathList, int flowToAdd)
{
     Node<int>* currVertex = shortestPathList.getHead();

     while (currVertex->next != NULL)
     {
          updateFlow(currVertex->data, currVertex->next->data, flowToAdd);
          currVertex = currVertex->next;
     }
}
// find the cut using a BFS run
bool* Graph::FindCut(int s) const
{
     bool* cut = new bool[m_size];
     bool* visited = new bool[m_size];
     Queue bfsQueue;
     bfsQueue.EnQueue(s);

     for (int i = 0; i < m_size; i++)
     {
          cut[i] = false;
          visited[i] = false;
     }

     visited[s] = true;
     cut[s] = true;

     while (!bfsQueue.isEmpty())
     {
          int currentNode = bfsQueue.DeQueue();                                          // current Node in Queue
          List<int> currentNodeAdj = GetAdjList(currentNode);

          while (!currentNodeAdj.isEmpty())
          {
               int currentAdj = currentNodeAdj.popHead();                               //current adj of currentNode to check path
               MatrixCell currentVertex = getCell(currentNode, currentAdj);

               if (visited[currentAdj] == false && currentVertex.getResidualFlow() > 0)
               {
                    cut[currentAdj] = true;
                    visited[currentAdj] = true;
                    bfsQueue.EnQueue(currentAdj);
               }
          }
     }
     delete[] visited;
     return cut;
}

void Graph::printCutLine(bool* cut, bool isGroupOfSource, int size) const
{
    int counter = 0;

    for (int i = 0; i < size; i++)
    {
        if (cut[i] == isGroupOfSource)
        {
            counter++;
        }
    }

    for (int i = 0; i < size; i++)
    {
        if (cut[i] == isGroupOfSource)
        {
            cout << i + 1;
            counter--;
            if (isGroupOfSource == true && counter == 0)
            {
                cout << ". ";
            }
            else if(counter >= 1)
            {
                cout << ", ";
            }
        }

    }
}

void Graph::printRunSummery(int maxFlow, bool* cut, int iterationCounter) const
{
    cout << "Max Flow = " << maxFlow << endl;
    cout << "Min cut: S = ";
    printCutLine(cut, true, m_size);
    cout << "T = ";
    printCutLine(cut, false, m_size);
    cout << endl;
    cout << "Number of Iterations: " << iterationCounter << endl;
    delete[] cut;
}

void Graph::isValidEdge(int v, int u) const
{
    if (u < 0 || v < 0 || u > m_size || v > m_size)
    {
        cout << "trying to access wrong edge!" << endl;
        exit(1);
    }
}




