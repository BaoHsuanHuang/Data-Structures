#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>
#include <signal.h>
#include <algorithm>
#include <time.h>
#define MAX 82168

using namespace std;

list<int> Graph[MAX];
list<int> Degree[MAX];
int arr[MAX] = {0};
list<int> Graph2[MAX];
int clique_arr[MAX] = {0};
int count2 = 0;
int k2;

void signalHandler(int signum)
{
    cout << "Get signal " << signum << endl;
    // fstream file_out_kcore;
    // file_out_kcore.open("kcore.txt", ios::out);
    // for(int i=0; i<MAX; i++){
    //     if(arr[i] >= k2){
    //         file_out_kcore << i << " " << arr[i] << '\n';
    //     }
    // }
    // fstream file_out_clique;
    // file_out_clique.open("clique.txt", ios::out);
    // for(int i=0; i<count2; i++){
    //     file_out_clique << clique_arr[i] << '\n';
    // }
    exit(signum);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);
    // clock_t start, end;
    // start = clock();
    int u, v;
    string file_name = string(argv[1]);
    string K = string(argv[2]);
    int k = stoi(K);
    k2 = k;
    fstream file;
    file.open(file_name, ios::in);

    fstream file_out_kcore;
    file_out_kcore.open("kcore.txt", ios::out);

    fstream file_out_clique;
    file_out_clique.open("clique.txt", ios::out);

    int point;
    
    while(file >> u >> v){
        Graph[u].push_back(v);
        Graph[v].push_back(u);
        Graph2[u].push_back(v);
        Graph2[v].push_back(u);
    }
    for(int i=0; i<MAX; i++){
        int tmp = Graph[i].size();
        arr[i] = tmp;
        Degree[tmp].push_back(i);
    }
    for(int i=1; i<MAX; i++){
        while(Degree[i].empty()!=1){
            int vertex = Degree[i].front();
            while(Graph[vertex].empty()!=1){
                int a = Graph[vertex].front();
                Graph[vertex].remove(a);
                Graph[a].remove(vertex);
                arr[a]--;
                int size = Graph[a].size();
                if(size >= i){
                    Degree[size+1].remove(a);
                    Degree[size].push_back(a);
                }else if(size < i){
                    arr[a] = i;
                }
            }
            Degree[i].remove(vertex);
        }
    }
    for(int i=0; i<MAX; i++){
        if(arr[i] >= k){
            file_out_kcore << i << " " << arr[i] << '\n';
        }
        // if(arr[i]==1499){
        //     file_out_clique << i << '\n';
        // }
        if(arr[i]==1499){
            point = i;
        }
    }
    list<int>::iterator it;
    int count=0;
    for(it=Graph2[point].begin(); it!=Graph2[point].end(); ++it){
        if(arr[*it]==1499){
            clique_arr[count] = *it;
            count++;
        }
    }
    clique_arr[count] = point;
    count = count + 1;
    count2 = count;
    sort(clique_arr, clique_arr+count);
    for(int i=0; i<count; i++){
        file_out_clique << clique_arr[i] << '\n';
    }
    // end = clock();
    // cout << (double)(end - start)/CLOCKS_PER_SEC << endl;
    return 0;
}