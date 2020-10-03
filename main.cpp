/*###############################################################################################################
This is a program that solves the Maximum flow Problem, using the Ford-Fulkerson method, using both a greedy
approach to find the augmenting path and BFS (Edmonds-Karp Algorithm).
#################################################################################################################
ISTRUCTIONS: 
In order to create your own flow-network and solve the Maximun flow program -
1. Please create a simple text file called input.txt and place it in the Solution's directory. 
2. First line of the text file will state the number of Vertexes in the graph => n. 
3. Second line will state the number of Edges in the graph => m. 
4. Third line will state the number of the source => s. 
5. Forth line will state the number of the sink => t. 
6. m (number of Edges) lines - each line represents an edge in the graph. The data in each line should be
the source Vertex, Destination Vertex, And the edge's Capacity (Must be Poistive Value!), in this format - 
src dest capacity. Must have spaces between the parameters and they must be in the same line.
##################################################################################################################
The program will bulid the graph according to that data in the text file and run both Algorith Variations to solve 
the Maximum flow Problem. For each run the program will print the Max Flow found, Min cut and number of iterations
################################################################################################################*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "Graph.h"
#include "List.h"
#include "MatrixCell.h"
#include "BFSFF.h"
#include "DijkstraAlgo.h"
#include "TextFileFormatValidator.h"

using namespace std;

void createGraphFromInput(Graph& graphFromInput, string textFileName, int& s, int& t);
void validateEdge(Graph& graphFromInput, int src, int dest, int capacity);
void validateBasicGraphData(int s, int t, int numOfVertexes, int numOfEdges);

int main(int argc, char* argv[])
{
	string textFileName = argv[1];
	TextFileFormatValidator::ValidateFormat(textFileName);			// validating the format
	Graph graphFromInput;
	int s, t;

	createGraphFromInput(graphFromInput, textFileName, s, t);		// creating first graph
	EdmondsKarp(graphFromInput, s - 1, t - 1);						// Edmonds Karp Run
	graphFromInput.~Graph();

	createGraphFromInput(graphFromInput, textFileName, s, t);		// creating second graph
	findMaxFlowWithDijkstra(graphFromInput, s - 1, t - 1);			// greedy algo run

	return 0;
}

void createGraphFromInput(Graph& graphFromInput, string textFileName, int& s, int& t)
{
	ifstream textFile;
	textFile.open(textFileName, ios::in);
	int numOfVertexes, numOfEdges;
	int src, dest, capacity;
	MatrixCell cell1, cell2;
	textFile >> numOfVertexes;
	graphFromInput.MakeEmptyGraph(numOfVertexes);
	textFile >> numOfEdges;
	textFile >> s;
	textFile >> t;
	validateBasicGraphData(s, t, numOfVertexes, numOfEdges);

	for (int i = 0; i < numOfEdges; i++)
	{
		textFile >> src;
		textFile >> dest;
		textFile >> capacity;
		validateEdge(graphFromInput, src, dest, capacity);
		graphFromInput.AddEdge(src - 1, dest - 1, capacity);
	}

	for (int i = 0; i < numOfVertexes; i++)
	{
		for (int j = 0; j < numOfVertexes; j++)
		{
			cell1 = graphFromInput.getCell(i, j);
			cell2 = graphFromInput.getCell(j, i);
			if (cell1.getIsEdge() == true && cell2.getIsEdge() == false)
			{
				graphFromInput.AddEdge(j, i, 0);
			}
		}
	}
	textFile.close();
}

void validateBasicGraphData(int s, int t, int numOfVertexes, int numOfEdges)
{
	if (s == t || s > numOfVertexes || t > numOfVertexes || s <= 0 || t <= 0 || (numOfEdges > numOfVertexes * numOfVertexes))
	{
		cout << "Invalid input";
		exit(1);
	}
}

void validateEdge(Graph& graphFromInput, int src, int dest, int capacity) // validate each edge
{
	bool isValid = true;

	if (src < 0 || src > graphFromInput.GetSize())
	{
	cout << "Invalid input";
	isValid = false;
	}
	else if (dest < 0 || dest > graphFromInput.GetSize())
	{
	cout << "Invalid input";
	isValid = false;
	}
	else if (src == dest || capacity <= 0 || graphFromInput.getCell(src - 1, dest - 1 ).getIsEdge() == true)
	{
		cout << "Invalid input";
		isValid = false;
	}
	if (!isValid)
	{
		exit(1);
	}
}
