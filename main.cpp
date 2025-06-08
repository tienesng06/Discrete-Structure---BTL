#include "tsm.h"
#include "bellman.h"


// int edgeListGen(int edgeList[][3],int numEdges,int numVertices,int initlimit=1){
//     /*
//     edgeList: output generated edgeList
//     numEdges: number of edges
//     numVertices: number vertices
//     initlimit: if <=1 all edges weight is 1, else, edges weight random int [1,initlimit]
//     */
    
//     //random generator init
//     random_device rd;
//     mt19937 gen(rd());
    
//     //exception
//     if(numEdges>(numVertices*(numVertices-1))/2){
//         cout<<"cannot create simple graph";
//         return -1;
//     }
//     if(numEdges<numVertices-1){
//         cout<<"cannot create a connected (weak) graph";
//         return -1;
//     }
    
//     //generate random vertices' names
//     int* verList=new int[numVertices];
//     vector<int> verName;
//     for(int i=33;i<=126;i++){verName.push_back(i);}
//     shuffle(verName.begin(),verName.end(),gen);
//     for(int i=0;i<numVertices;i++){verList[i]=verName[i];}
    
//     //generate random edges, ensure that each vertices will have at least 1 edges;
//     bool flag=0;
//     vector<pair<int,int>> fullList;
//     for(int i=0;i<numVertices;i++){
//         for(int j=0;j<numVertices;j++){
//             if(i==j) break;
//             fullList.push_back({verList[i],verList[j]});
//         }
//     }
//     int* checkList=new int[numVertices];
//     while (!flag){
//         shuffle(fullList.begin(),fullList.end(),gen);    
//         for(int i=0;i<numEdges;i++){
//             edgeList[i][0]=fullList[i].first;
//             edgeList[i][1]=fullList[i].second;
//         }
//         int count=0;
        
//         for(int i=0;i<numEdges;i++){
//             if(count==numVertices) {
//                 flag=1; break;
//             }
//             bool found0=0;
//             bool found1=0;
//             for(int j=0;j<count;j++){
//                 if(!found0&&edgeList[i][0]==checkList[j]){
//                     found0=1;
//                 }
//                 if(!found1&&edgeList[i][1]==checkList[j]){
//                     found1=1;
//                 }
//                 if(found0&&found1) break;
//             }
//             if(!found0){
//                 checkList[count++]=edgeList[i][0];
//             }
//             if(!found1){
//                 checkList[count++]=edgeList[i][1];
//             }
//             //cout<<"reshuffle edgeList\n";
//         }
//     }
//     delete[] checkList;
    
//     ofstream fout("EdgeList.txt");
//     //generate the weights
//     if(initlimit<=1){//All the weights will be 1
//         for(int i=0;i<numEdges;i++){
//             edgeList[i][2]=1;            
//         }
//     }
//     else{//randomize edges' weights
//         uniform_int_distribution<int> dist(0,initlimit);
//         for(int i=0;i<numEdges;i++){
//             edgeList[i][2]=dist(gen);            
//             fout<<edgeList[i][0]<<" "<<edgeList[i][1]<<" "<<edgeList[i][2]<<endl;
//         }
//     }
//     fout.close();
//     delete []verList;
//     return 1;
// }

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