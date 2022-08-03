// Adopted From: https://favtutor.com/blogs/dijkstras-algorithm-cpp#:~:text=Algorithm%20for%20Dijkstra's%20in%20C%2B%2B

#include <iostream>

using namespace std;

int const DIMENSION_SIZE = 4;

void Dijkstra(int matrix[DIMENSION_SIZE][DIMENSION_SIZE], int nodeToFind);
int MinimumDist(int dist[], bool visited[]);
void PrintNodeDistances(int dist[]);
char LetterEquiv(int val);

int main()
{
    // Representing Given Map in Adjacency Matrix
    // - A B C D
    // A
    // B
    // C
    // D
    int adjMatrix[DIMENSION_SIZE][DIMENSION_SIZE]
    {
        {0,5,0,7},
        {5,0,1,0},
        {0,1,0,1},
        {7,0,1,0}
    };

    Dijkstra(adjMatrix, 0);
    return 0;
}

// Dijkstra is similar to an A* algorithm, however, it assumes that the heuristic is 0.
// I think this makes sense in this problem since there is no sense of 'distance'
// between the nodes to define 'closeness' to the goal node
void Dijkstra(int matrix[DIMENSION_SIZE][DIMENSION_SIZE], int startingNode)
{
    // Array to store minimum distance for each node
    int dist[DIMENSION_SIZE];
    // Array to mark visited or unvisited
    bool visited[DIMENSION_SIZE];

    // Fill arrays with Infinite Distance and as unvisited
    fill_n(dist, DIMENSION_SIZE, INT_MAX);
    fill_n(visited, DIMENSION_SIZE, false);

    // Starting Node distance set to 0
    dist[startingNode] = 0;

    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        int min = MinimumDist(dist, visited);
        visited[min] = true;
        for (int i = 0; i < DIMENSION_SIZE; i++)
        {
            // Not Visited, In Matrix, Not Infinite Distance, New Min and lower than Previous Min
            // Update Neighbor Nodes With Minimum Distance
            if (!visited[i] && matrix[min][i] && dist[min] != INT_MAX && dist[min] + matrix[min][i] < dist[i])
                dist[i] = dist[min] + matrix[min][i];
        }
    }
    PrintNodeDistances(dist);
}

// Returns the Index for the node with minimum distance
int MinimumDist(int dist[], bool visited[])
{
    int min = INT_MAX;
    int index = 0;

    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        // If Node not visited and smaller than current min distance
        if (visited[i] == false && dist[i] <= min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void PrintNodeDistances(int dist[])
{
    cout << "Node Distance From Starting Node" << endl;

    for (int i = 0; i < DIMENSION_SIZE; i++)
    {
        cout << LetterEquiv(i) << "   " << dist[i] << endl;
    }
}

// Tying Array Space to Ascii value
char LetterEquiv(int val)
{
    return (char)(val + 65);
}