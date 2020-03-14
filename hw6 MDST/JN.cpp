#include <iostream>
#include <stack>
#include <climits>

using namespace std;

class Graph
{
public:
    Graph(){
        vertex = 0;
    }
    Graph(int n){
        vertex = n;
        not_connected = false;
        node = new int*[n];
        for(int i = 0; i < n; ++i){
            node[i] = new int[n];
        }
        dist = new int*[n];
        for(int i = 0; i < n; ++i){
            dist[i] = new int[n];
        }
        r = new int*[n];
        for(int i = 0; i < n; ++i){
            r[i] = new int[n];
        }
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                if(i != j)
                    node[i][j] = -1;
                else
                    node[i][j] = 0;
            }
        }
    }
    ~Graph(){
    }

    void Add(void);
    void Delete(void);
    void FW(void);
    void sort(void);
    void KH(void);
    void AC(void);
    void Diameter(void);
    void shortest(void);
    void SOSPD(void);

    int **node;
    int **dist;
    int **r;

private:
    int vertex;
    bool not_connected;
    double ecc;
    int point1;
    int point2; //if AC is on a vertex, point2 will be -1
    double d1; //distant between absolute center and point1
    double d2; //distant between absolute center and point2
    double sum;
};

void Graph::Add(void)
{
    int v1, v2, w;
    cin >> v1 >> v2 >> w;
    node[v1][v2] = w;
    node[v2][v1] = w;
}

void Graph::Delete(void)
{
    int v1, v2;
    cin >> v1 >> v2;
    node[v1][v2] = -1;
    node[v2][v1] = -1;
}

void Graph::FW(void)
{
    // cout << "FW\n";
    //initialize
    for (int i = 0; i < vertex; i++){
        for (int j = 0; j < vertex; j++){
            dist[i][j] = node[i][j];
        }
    }
    //FloydWarshall
    for (int k = 0; k < vertex; k++){
        for (int i = 0; i < vertex; i++){
            for (int j = 0; j < vertex; j++){
                if(i != j){
                    if ((dist[i][j] > dist[i][k] + dist[k][j]) && dist[i][k] != -1 && dist[k][j] != -1){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                    else if(dist[i][j] == -1 && dist[i][k] != -1 && dist[k][j] != -1){
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
        // for (int i = 0; i < vertex; i++){
        //     for (int j = 0; j < vertex; j++){
        //         cout << dist[i][j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl;
    }
}

void Graph::sort(void)
{
    // cout << "sort\n";
    //initialize
    for (int i = 0; i < vertex; i++){
        for (int j = 0; j < vertex; j++){
            r[i][j] = j;
        }
    }
    //sort
    for (int i = 0; i < vertex; i++){
        for (int j = 1; j < vertex; j++){
            int k = j - 1;
            int key = r[i][j];
            int d = dist[i][j];
            while(k >= 0 && d > dist[i][r[i][k]]){
                r[i][k + 1] = r[i][k];
                k--;
            }
            r[i][k + 1] = key;
        }
    }
    // for (int i = 0; i < vertex; i++){
    //     for (int j = 0; j < vertex; j++){
    //         cout << r[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}

void Graph::KH(void)
{
    not_connected = false;
    FW();
    sort();
    ecc = INT_MAX;
    point1 = 0;
    point2 = -1;
    for (int i = 0; i < vertex; i++){
        for (int j = 0; j < vertex; j++){ //for every edge in the graph
            if (dist[i][j] == -1){ //check whether the graph is connected
                not_connected = true;
                return;
            }
            //we can assume the graph is connected hereafter
            //first check end point i and j
            if (dist[i][r[i][0]] < ecc){
                ecc = dist[i][r[i][0]];
                point1 = i;
                point2 = -1;
            }
            if (dist[j][r[j][0]] < ecc){
                ecc = dist[j][r[j][0]];
                point1 = j;
                point2 = -1;
            }
            //check intersection
            for (int a = 0, b = 1; b < vertex; b++){
                // cout << "a = " << a << " b = " << b << endl;
                if (dist[j][r[i][b]] > dist[j][r[i][a]]){
                    // cout << "a = " << a << " b = " << b << endl;
                    if (((double)(dist[i][r[i][b]] + dist[j][r[i][a]] + dist[i][j])) / 2 < ecc){
                        ecc = (double)(dist[i][r[i][b]] + dist[j][r[i][a]] + dist[i][j]) / 2;
                        // cout << ecc << endl;
                        point1 = i;
                        point2 = j;
                        d1 = ecc - (double)dist[i][r[i][b]];
                        d2 = ecc - (double)dist[j][r[i][a]];
                    }
                    a = b;
                }
            }
            // cout << endl;
        }
    }
}

void Graph::AC(void)
{
    KH();
    if(not_connected){
        cout << "Not connected graph\n";
        return;
    }
