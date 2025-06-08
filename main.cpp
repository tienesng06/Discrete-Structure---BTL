#include "tsm.h"
#include "bellman.h"


vector<vector<int>> generateLargeTestCase(int n) {
    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000); // distances between 1 and 1000

    // Create n x n matrix
    vector<vector<int>> graph(n, vector<int>(n, 0));
    
    // Fill matrix with random distances
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            int distance = dis(gen);
            graph[i][j] = distance;
            graph[j][i] = distance; // Make graph symmetric
        }
    }

    return graph;
}

int main()
{

    vector<vector<int>> graph = {
        {0, 76, 95, 70, 68, 55, 61},
        {61, 0, 87, 16, 53, 42, 19},
        {42, 5, 0, 11, 2, 0, 83},
        {55, 3, 89, 0, 68, 34, 26},
        {55, 26, 89, 51, 0, 30, 62},
        {87, 59, 10, 58, 27, 0, 65},
        {19, 41, 5, 87, 94, 99, 0}
    };

    int num_vertices = graph.size();
    char vertex[num_vertices] = {'A', 'B', 'C', 'D', 'E','F','G'};

    // Convert to edge list
    int edge1[num_vertices*num_vertices][3];
    int numberOfEdges1 = 0;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            if (graph[i][j] > 0)
            {
                edge1[numberOfEdges1][0] = vertex[i];
                edge1[numberOfEdges1][1] = vertex[j];
                edge1[numberOfEdges1][2] = graph[i][j];
                numberOfEdges1++;
            }
        }
    }

    string start = "A";
    string end = "B";

    //Test BF
    int BellmanFordValue[20];
    int BellmanFordPrevious[20];

    for(int i = 0; i < num_vertices; i++){
        BellmanFordValue[i] = -1;
        BellmanFordPrevious[i] = -1;
    }

    for(int i = 0; i < num_vertices; i++){
        BF(edge1, numberOfEdges1, 'A', BellmanFordValue, BellmanFordPrevious);
        cout << "step " << i+1 << ":" << endl;
        for(int j = 0; j < num_vertices; j++){
            cout << BellmanFordValue[j] << " ";
        }
        cout << endl;
        for(int j = 0; j < num_vertices; j++){
            cout << BellmanFordPrevious[j] << " ";
        }
        cout << endl;
    }
    
    // Test BF_Path
    string result = BF_Path(edge1, numberOfEdges1, start[0], end[0]);
    cout << result << endl;

    //Test Traveling
    const int NUM_CITIES = 1000;
    
    // Generate test case
    vector<vector<int>> largeGraph = generateLargeTestCase(NUM_CITIES);
    
    // Test with small subset first
    cout << "Testing with first 10 cities:" << endl;
    vector<vector<int>> smallTest(10, vector<int>(10));
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            smallTest[i][j] = largeGraph[i][j];
        }
    }
    
    // Try small test first
    Traveling(smallTest, 10, 'A');

    // Run TravelingLarge algorithm
    cout << "Test case with " << NUM_CITIES << " cities:" << endl;
    TravelingLarge(largeGraph, NUM_CITIES * (NUM_CITIES - 1) / 2, 'A');

    cout << "\nFull test case has been generated" << endl;    

}   
