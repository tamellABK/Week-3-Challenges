#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(int startingNode, vector<vector<int>>& adjMatrix);

int main()
{
    // BFS doesn't deal with weights, default the connects to 1
    vector<vector<int>> adjMatrix
    {
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0}
    };

    cout << "BFS Order: \n";
    BFS(0, adjMatrix);
}

void BFS(int startingNode, vector<vector<int>>& adjMatrix)
{
    // Create Visited Vector to hold if that 'node' has been visited
    vector<bool> visited;
    visited.resize(adjMatrix.size(), false);

    // Create a queue to enqueue adjacent nodes
    queue<int> queue;

    // Starting Node set to true and push to queue
    visited[startingNode] = true;
    queue.push(startingNode);

    while (!queue.empty())
    {
        startingNode = queue.front();

        // Show Letter equivalent to vector position (0 = A, 1 = B...)
        cout << (char)(startingNode + 65) << " ";
        queue.pop();

        for (int i = 0; i < adjMatrix.size(); i++)
        {
            if (adjMatrix[startingNode][i] != 0 && !visited[i])
            {
                visited[i] = true;
                queue.push(i);
            }
        }
    }
    
}