#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

void BFS(int startingNode,int goalNode, vector<vector<int>>& adjMatrix);
vector<int> FindPath(int startingNode, int goalNode, map<int, int> cameFrom);
void PrintVector(vector<int> vectorToPrint);
char LetterEquiv(int val);

int main()
{
    // BFS doesn't deal with weights, default the example connections to 1
    vector<vector<int>> adjMatrix
    {
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0}
    };

    // From A, Find C in adjMatrix
    BFS(0, 2, adjMatrix);
}

void BFS(int startingNode, int goalNode, vector<vector<int>>& adjMatrix)
{
    cout << "BFS From Node " << LetterEquiv(startingNode) << " to Node " << LetterEquiv(goalNode) << endl;

    // Create Visited Vector to hold if that 'node' has been visited
    vector<bool> visited;
    visited.resize(adjMatrix.size(), false);

    // Create a map to pair node with it's previous node
    map<int, int> cameFrom;
    cameFrom[startingNode] = NULL;

    // Create a queue to enqueue adjacent nodes
    queue<int> queue;

    int currentNode = startingNode;

    // Starting Node set to true and push to queue
    visited[currentNode] = true;
    queue.push(currentNode);

    while (!queue.empty())
    {
        currentNode = queue.front();
        queue.pop();

        // Check all adjacent Nodes
        for (int i = 0; i < adjMatrix.size(); i++)
        {
            // If there's a connection and it's not visited
            if (adjMatrix[currentNode][i] != 0 && !visited[i])
            {
                // Visit, Put on Queue, and Map to Previous Node
                visited[i] = true;
                queue.push(i);
                cameFrom[i] = currentNode;
            }
        }
    }

    // Find Goal Node
    vector<int> path = FindPath(startingNode, goalNode, cameFrom);

    // Print
    PrintVector(path);
}

vector<int> FindPath(int startingNode, int goalNode, map<int,int> cameFrom)
{
    vector<int> pathToTake;
    int currentNode = goalNode;
    // Work backwords from goalNode and look at previous Node mappings to startingNode
    while (currentNode != startingNode)
    {
        pathToTake.push_back(currentNode);
        currentNode = cameFrom[currentNode];
    }

    // Push final Node and Reverse vector
    pathToTake.push_back(currentNode);
    reverse(pathToTake.begin(), pathToTake.end());
    return pathToTake;
}

void PrintVector(vector<int> vectorToPrint)
{
    for (auto i : vectorToPrint)
    {
        cout << LetterEquiv(i);
        if (i != vectorToPrint[vectorToPrint.size() - 1]) cout << " -> ";
    }
}

// Misc Function to showcase letter equivalents for array positions
char LetterEquiv(int val)
{
    return (char)(val + 65);
}