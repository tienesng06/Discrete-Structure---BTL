 #include "bellman.h"

void BF(int edge[MAX][3], int numberOfEdges, char start_Ver, int value_arr[], int prev_arr[]) {
    vector<char> vertices;
    for (int i = 0; i < numberOfEdges; i++) {
        vertices.push_back(edge[i][0]);
        vertices.push_back(edge[i][1]);
    }
    sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());
    
    int num_vertices = vertices.size();
    int start = lower_bound(vertices.begin(), vertices.end(), start_Ver) - vertices.begin();
    
    bool needInit = false;
    for (int i = 0; i < num_vertices; i++) {
        if (value_arr[i] == -1) {
            needInit = true;
            break;
        }
    }
    
    if (needInit) {
        for (int i = 0; i < num_vertices; i++) {
            value_arr[i] = -1;
            prev_arr[i] = -1;
        }
        
        value_arr[start] = 0;
        
        for (int i = 0; i < numberOfEdges; i++) {
            int u = lower_bound(vertices.begin(), vertices.end(), edge[i][0]) - vertices.begin();
            int v = lower_bound(vertices.begin(), vertices.end(), edge[i][1]) - vertices.begin();
            if (u == start && v != start) {
                value_arr[v] = edge[i][2];
                prev_arr[v] = start;
            }
        }
    } else {
        vector<int> old_value(value_arr, value_arr + num_vertices);
        
        for (int u = 0; u < num_vertices; u++) {
            if (old_value[u] != -1) {
                for (int i = 0; i < numberOfEdges; i++) {
                    int src = lower_bound(vertices.begin(), vertices.end(), edge[i][0]) - vertices.begin();
                    int dest = lower_bound(vertices.begin(), vertices.end(), edge[i][1]) - vertices.begin();
                    if (src == u) {
                        int new_dist = old_value[u] + edge[i][2];
                        if (value_arr[dest] == -1 || new_dist < value_arr[dest] ||
                           (new_dist == value_arr[dest] && u < prev_arr[dest])) {
                            value_arr[dest] = new_dist;
                            prev_arr[dest] = u;
                        }
                    }
                }
            }
        }
    }
}

string BF_Path(int edge[MAX][3], int numberOfEdges, char startVertex, char goalVertex) {
    // Extract and sort all unique vertices from the edge list
    vector<char> vertices;
    for (int i = 0; i < numberOfEdges; i++) {
        vertices.push_back(edge[i][0]);
        vertices.push_back(edge[i][1]);
    }
    sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());
    
    int num_vertices = vertices.size();
    
    // Create mapping functions
    auto getIndex = [&](char c) -> int {
        return lower_bound(vertices.begin(), vertices.end(), c) - vertices.begin();
    };
    auto getChar = [&](int i) -> char {
        return vertices[i];
    };
    
    int value_arr[20];
    int prev_arr[20];
    for (int i = 0; i < num_vertices; i++) {
        value_arr[i] = -1;
        prev_arr[i] = -1;
    }

    // Run Bellman-Ford algorithm (n-1 iterations)
    for (int i = 0; i < num_vertices - 1; i++) {
        BF(edge, numberOfEdges, startVertex, value_arr, prev_arr);
    }

    int goal = getIndex(goalVertex);
    if (value_arr[goal] == -1) return "NO PATH";

    vector<char> path;
    int current = goal;
    while (current != -1) {
        path.push_back(getChar(current));
        current = prev_arr[current];
    }
    
    reverse(path.begin(), path.end());
    
    string result = "";
    for (int i = 0; i < path.size(); i++) {
        if (i > 0) result += " ";
        result += path[i];
    }
    
    return result;
}
