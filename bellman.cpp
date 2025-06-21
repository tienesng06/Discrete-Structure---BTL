 #include "bellman.h"


void BF(int edge[][3], int numEdges, char start, int value[], int prev[])
{
    vector<int> vertices;
    for (int i = 0; i < numEdges; ++i) {
        vertices.push_back(edge[i][0]);
        vertices.push_back(edge[i][1]);
    }
    sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

    static int V = vertices.size();
    vector<vector<int>> G(V, vector<int>(V, -1));

    const int MAX_VERTEX = 128;
    int vertexToIndex[MAX_VERTEX];
    fill(vertexToIndex, vertexToIndex + MAX_VERTEX, -1);
    int indexToVertex[V];

    for (int i = 0; i < V; ++i) {
        vertexToIndex[vertices[i]] = i;
        indexToVertex[i] = vertices[i];
    }

    for (int i = 0; i < numEdges; ++i) {
        int u = vertexToIndex[edge[i][0]];
        int v = vertexToIndex[edge[i][1]];
        G[u][v] = edge[i][2];
    }

    int startVertex = static_cast<int>(start);
    int startIdx = vertexToIndex[startVertex];

    if (startIdx < 0 || startIdx >= V) {
        for (int i = 0; i < V; i++) {
            prev[i] = -1;
        }
        return;
    }

    static bool initialized[MAX_VERTEX] = { false };

    if (!initialized[startVertex]) {
        value[startIdx] = 0;
        for (int i = 0; i < V; i++) {
            if (G[startIdx][i] != -1) {
                value[i] = G[startIdx][i];
                prev[i] = startIdx;
            } else {
                prev[i] = -1;
            }
        }
        initialized[startVertex] = true;
        return;
    }

    int tempValue[V];
    int tempPrev[V];
    for (int i = 0; i < V; i++) {
        tempValue[i] = value[i];
        tempPrev[i] = prev[i];
    }

    for (int u = 0; u < V; u++) {
        if (tempValue[u] == -1) continue;
        for (int v = 0; v < V; v++) {
            if (G[u][v] != -1) {
                int dis = tempValue[u] + G[u][v];
                if (tempValue[v] == -1 || dis < tempValue[v]) {
                    if (value[v] == -1 || dis < value[v]) {
                        value[v] = dis;
                        prev[v] = u;
                    }
                }
            }
        }
    }
}


string BF_Path(int edge[][3], int numberOfEdges, char startVertex, char goalVertex) {
    vector<int> vertices;
    for (int i = 0; i < numberOfEdges; ++i) {
        vertices.push_back(edge[i][0]);
        vertices.push_back(edge[i][1]);
    }
    sort(vertices.begin(), vertices.end());
    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());

    int V = vertices.size();

    const int MAX_VERTEX = 128;
    int vertexToIndex[MAX_VERTEX];
    int indexToVertex[MAX_VERTEX];
    for (int i = 0; i < MAX_VERTEX; ++i) vertexToIndex[i] = -1;

    for (int i = 0; i < V; ++i) {
        vertexToIndex[vertices[i]] = i;
        indexToVertex[i] = vertices[i];
    }

    int value[128];
    int prev[128];
    for (int i = 0; i < 128; ++i) {
        value[i] = -1;
        prev[i] = -1;
    }

    int startIdx = vertexToIndex[(int)startVertex];
    if (startIdx == -1) return "No path exists";
    value[startIdx] = 0;

    for (int i = 0; i < V - 1; ++i) {
        BF(edge, numberOfEdges, startVertex, value, prev);
    }

    int goalIdx = vertexToIndex[(int)goalVertex];
    if (goalIdx == -1 || value[goalIdx] == -1) {
        return "No path exists";
    }

    vector<char> path;
    int current = goalIdx;
    while (current != -1) {
        path.push_back((char)indexToVertex[current]);
        current = prev[current];
    }

    reverse(path.begin(), path.end());

    string result;
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) result += " ";
        result += path[i];
    }

    return result;
}
