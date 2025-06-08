#include "tsm.h"

string convertToLabel(int index) {
    string label;
    if (index < 26) {
        // A-Z
        label = string(1, 'A' + index);
    } else if (index < 26 * 2) {
        // AA-AZ
        label = "A" + string(1, 'A' + (index - 26));
    } else {
        // For larger numbers: A1, A2, A3, etc.
        label = "A" + to_string(index - 26);
    }
    return label;
}

void Traveling(const vector<vector<int>>& graph, int numEdges, char startVertex) {
    int n = graph.size();  // number of vertices
    int start = startVertex - 'A';  // Convert char to index
    vector<int> vertices;

    // Fill the list with vertices except the starting one
    for (int i = 0; i < n; ++i) {
        if (i != start)
            vertices.push_back(i);
    }

    int minPathCost = INT_MAX;
    vector<int> bestPath;

    // Try all permutations
    do {
        int currentCost = 0;
        int k = start;

        // Path from start to each vertex in permutation
        for (int i : vertices) {
            currentCost += graph[k][i];
            k = i;
        }
        // Return to start
        currentCost += graph[k][start];

        // Update best
        if (currentCost < minPathCost) {
            minPathCost = currentCost;
            bestPath = vertices;
        }

    } while (next_permutation(vertices.begin(), vertices.end()));

    // Print best path
    cout << "Path: " << startVertex;
    for (int v : bestPath) {
        cout << " -> " << char('A' + v);
    }
    cout << " -> " << startVertex << endl;
    cout << "Total cost: " << minPathCost << endl;
}

void TravelingLarge(const vector<vector<int>>& graph, int numEdges, char startVertex) {
    int n = graph.size();
    int start = startVertex - 'A';
    vector<bool> visited(n, false);
    vector<int> path;
    int totalCost = 0;
    
    // Start from the first vertex
    path.push_back(start);
    visited[start] = true;
    
    // Nearest neighbor algorithm
    int current = start;
    for(int i = 0; i < n-1; i++) {
        int nearest = -1;
        int minDist = INF;
        
        // Find nearest unvisited vertex
        for(int j = 0; j < n; j++) {
            if(!visited[j] && graph[current][j] < minDist) {
                minDist = graph[current][j];
                nearest = j;
            }
        }
        
        if(nearest == -1) break; // Error check
        
        // Add to path
        path.push_back(nearest);
        visited[nearest] = true;
        totalCost += minDist;
        current = nearest;
    }
    
    // Return to start
    if(current != start) {
        totalCost += graph[current][start];
        path.push_back(start);
    }
    
    // Print result (using numbers instead of characters for large n)
    cout << "Path: " << start;
    for(size_t i = 1; i < path.size(); i++) {
        cout << " -> " << path[i];
    }
    cout << "\nTotal cost: " << totalCost << endl;
}