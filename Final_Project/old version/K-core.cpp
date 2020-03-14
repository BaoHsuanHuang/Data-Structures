/*
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <set>
#include <vector>
#include <signal.h>

#define total_vertex 82200

using namespace std;

typedef struct _node{
    set<int>s;
}Node;

Node ID[total_vertex];
Node degree[total_vertex];

// void signalHandler(int signum)
// {
//     cout << "get signal" << signum << '\n';
//     exit(signum);
// }


int main(int argc, char *argv[])
{
    // signal(SIGINT, signalHandler);
    // for(int i=0; i<5000; i++){
    //     cout << i << '\n';
    //     sleep(i);
    // }

    int u, v;
    string file_name = string(argv[1]);
    string K = string(argv[2]);
    int k = stoi(K);

    fstream file;
    // fstream file_out;
    file.open(file_name, ios::in);
    // file1.open("output.txt", ios::out);
    while (file >> u >> v){
        // cout << u << v << "\n";
        // file1 << u << " " << v << "\n";
        ID[u].s.insert(v);
        ID[v].s.insert(u);
    }

    for(int i=0; i<total_vertex; i++){
        int tmp = ID[i].s.size();
        if(ID[i].s.empty()==1){
            degree[0].s.insert(i);
        }else{
            degree[tmp].s.insert(i);
        }
    }

    for(int i=1 ; i<k ; i++){
        for(int m=0 ; degree[i].s.empty()!=1 ; m++){
            set<int>::iterator VertexId = degree[i].s.begin();
            degree[i].s.erase(*VertexId);
            for(int j=0; j<ID[*VertexId].s.size() ; j++){
                set<int>::iterator tmp = ID[*VertexId].s.begin();
                ID[*VertexId].s.erase(*tmp);
                ID[*tmp].s.erase(*VertexId);
                if(ID[*tmp].s.size() >= i){
                    degree[ID[*tmp].s.size()].s.insert(*tmp);
                    degree[ID[*tmp].s.size()+1].s.erase(*tmp);
                }
                // else if(ID[*tmp].s.size() < i){
                    // int capacity = ID[*tmp].s.size();
                    // while(ID[*tmp].s.empty()!=1){
                    //     set<int>::iterator a = ID[*tmp].s.begin();
                    //     degree[ID[*tmp].s.size()+1].s.erase(*tmp);
                    //     ID[*tmp].s.erase(*a);
                    //     ID[*a].s.erase(*tmp);
                    // }
                // }
            }
        }
    }
    // int count=0;
    for(int i=k; i<total_vertex; i++){
        for(int j=0; degree[i].s.empty()!=1 ; j++){
            set<int>::iterator tmp = degree[i].s.begin();
            degree[i].s.erase(*tmp);
            cout << *tmp << " " << i << '\n';
            // count++;
        }
    }
    // cout << count << endl;
    // k-core

    return 0;
}

*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>
#include <string>
#define MAX 82200

using namespace std;

set<int> Graph[MAX];
set<int> Degree[MAX];

int main(int argc, char *argv[])
{
    int u, v;
    string file_name = string(argv[1]);
    string K = string(argv[2]);
    int k = stoi(K);
    fstream file;
    file.open(file_name, ios::in);

    fstream file_out;
    file_out.open("output.txt", ios::out);
    
    while(file >> u >> v){
        Graph[u].insert(v);
        Graph[v].insert(u);
    }
    for(int i=0; i<MAX; i++){
        int tmp = Graph[i].size();
        Degree[tmp].insert(i);
    }
    for(int i=1; i<k; i++){
        while(Degree[i].empty()!=1){
            // cout << "i : " << i << endl;
            set<int>::iterator vertex = Degree[i].begin();
            // cout << "vertex : " << *Degree[2].begin() << endl;
            // while(Graph[*vertex].size() != 0){
            while(Graph[*vertex].empty()!=1){
                set<int>::iterator a = Graph[*vertex].begin();
                // cout << *a << endl;
                Graph[*vertex].erase(*a);
                Graph[*a].erase(*vertex);
                int size = Graph[*a].size();
                // cout << size << endl;
                if(size >= i){
                    Degree[size+1].erase(*a);
                    Degree[size].insert(*a);
                }
                set<int>::iterator iter;
                for(iter = Degree[3].begin() ; iter != Degree[3].end() ; ++iter){
                    cout<<*iter<<" ";
                }
                cout << endl;
            }
            Degree[i].erase(*vertex);
        }
    }
    int count = 0;
    for(int i=0; i<MAX; i++){
        if(Graph[i].size() >= k){
            file_out << i << " " << Graph[i].size() << '\n';
            count++;
        }
    }
    cout << "count : " << count << endl;
    cout << "END" << endl;
    return 0;
    
}