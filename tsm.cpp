#include "tsm.h"

string Traveling(int edgeList[][3], int numEdge, char startChar) {
    vector<char> int_to_char_vec;
    for (int i = 0; i < numEdge; ++i) {
        int_to_char_vec.push_back((char)edgeList[i][0]);
        int_to_char_vec.push_back((char)edgeList[i][1]);
    }
    sort(int_to_char_vec.begin(), int_to_char_vec.end());
    int_to_char_vec.erase(unique(int_to_char_vec.begin(), int_to_char_vec.end()), int_to_char_vec.end());
    
    int num_vertices = int_to_char_vec.size();

    vector<int> char_to_int_lookup(256, -1);
    for(int i=0; i < num_vertices; ++i) {
        char_to_int_lookup[int_to_char_vec[i]] = i;
    }

    vector<vector<int>> dist(num_vertices, vector<int>(num_vertices, INF));
    for (int i = 0; i < numEdge; ++i) {
        char u = (char)edgeList[i][0];
        char v = (char)edgeList[i][1];
        int weight = edgeList[i][2];
        dist[char_to_int_lookup[u]][char_to_int_lookup[v]] = weight;
    }

    int start_node_int = char_to_int_lookup[startChar];

    int num_subsets = 1 << num_vertices;
    vector<vector<int>> dp(num_subsets, vector<int>(num_vertices, INF));
    vector<vector<int>> path(num_subsets, vector<int>(num_vertices, -1));

    dp[1 << start_node_int][start_node_int] = 0;

    for (int mask = 1; mask < num_subsets; ++mask) {
        for (int u = 0; u < num_vertices; ++u) {
            if (mask & (1 << u)) {
                for (int v = 0; v < num_vertices; ++v) {
                    if (v != u && (mask & (1 << v))) {
                        int prev_mask = mask ^ (1 << u);
                        if (dp[prev_mask][v] != INF && dist[v][u] != INF) {
                            if (dp[prev_mask][v] + dist[v][u] < dp[mask][u]) {
                                dp[mask][u] = dp[prev_mask][v] + dist[v][u];
                                path[mask][u] = v;
                            }
                        }
                    }
                }
            }
        }
    }

    int final_mask = num_subsets - 1;
    int min_cost = INF;
    int last_node = -1;

    for (int i = 0; i < num_vertices; ++i) {
        if (i != start_node_int) {
             if (dp[final_mask][i] != INF && dist[i][start_node_int] != INF) {
                 if (dp[final_mask][i] + dist[i][start_node_int] < min_cost) {
                     min_cost = dp[final_mask][i] + dist[i][start_node_int];
                     last_node = i;
                 }
             }
        }
    }

    if (num_vertices == 1) {
        if(dist[start_node_int][start_node_int] != INF) {
            min_cost = dist[start_node_int][start_node_int];
            last_node = start_node_int;
        } else {
             min_cost = INF;
        }
    }

    if (min_cost == INF) {
        return "";
    }

    vector<char> final_path;
    int current_mask = final_mask;
    int current_node = last_node;

    while (current_node != -1) {
        final_path.push_back(int_to_char_vec[current_node]);
        int prev_node = path[current_mask][current_node];
        current_mask ^= (1 << current_node);
        current_node = prev_node;
    }
    
    reverse(final_path.begin(), final_path.end());
    final_path.push_back(startChar);

    string result = "";
    for (size_t i = 0; i < final_path.size(); ++i) {
        result += final_path[i];
        if (i < final_path.size() - 1) {
            result += " ";
        }
    }

    return result;
}
