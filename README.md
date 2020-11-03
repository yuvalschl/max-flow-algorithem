# Max-flow-algorithem

This is a program that solves the Maximum flow Problem, using the Ford-Fulkerson method, using both a greedy
approach to find the augmenting path and BFS (Edmonds-Karp Algorithm).

## Getting Started

1. Download the files and save them a C++ project
2. Click on the project in solution explorer.
3. Click properties.
4. Set one of the test files as input file

The program will bulid the graph according to that data in the text file and run both Algorith Variations to solve 
the Maximum flow Problem. For each run the program will print the Max Flow found, Min cut and number of iterations

## Creating your own graph

-
1. Create a simple text file called input.txt and place it in the Solution's directory. 
2. First line of the text file will state the number of Vertexes in the graph => n. 
3. Second line will state the number of Edges in the graph => m. 
4. Third line will state the number of the source => s. 
5. Forth line will state the number of the sink => t. 
6. m (number of Edges) lines - each line represents an edge in the graph. The data in each line should be
the source Vertex, Destination Vertex, And the edge's Capacity (Must be Poistive Value!), in this format - 
src dest capacity. Must have spaces between the parameters and they must be in the same line.

## Author

* **yuval schlossser** - [yuvalschl](https://github.com/yuvalschl)
