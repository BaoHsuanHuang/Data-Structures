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

// bool neighbor[MAX][MAX] = {0};
int _node[MAX] = {0};
list<int> neighbor[MAX];
list<int> total_node;
list<int> potential_clique;
list<int> new_potential_clique;
list<int> remaining_nodes;
list<int> new_remaining_nodes;
list<int> skip_nodes;
list<int> new_skip_nodes;
list<int> all_clique[MAX];

void find_clique(list<int>potential_clique, list<int> remaining_nodes, list<int> skip_nodes);

int main(int argc, char *argv[])
{
    int u, v;
    string file_name = string(argv[1]);
    string K = string(argv[2]);
    int k = stoi(K);
    fstream file;
    file.open(file_name, ios::in);

    fstream file_out_clique_bonus;
    file_out_clique_bonus.open("clique_bonus.txt", ios::out);

    while(file >> u >> v){
        // neighbor[u][v] = 1;
        // neighbor[v][u] = 1;
        neighbor[u].push_back(v);
        neighbor[v].push_back(u);
        // _node[u] = 1;
        // _node[v] = 1;
    }
    // for(int i=0; i<MAX; i++){
    //     if(_node[i]==1){
    //         remaining_nodes.push_back(i);
    //     }
    // }
    // find_clique(potential_clique, remaining_nodes, skip_nodes);

    // file_out_clique_bonus << "!!!" << '\n';

    return 0;
}

// void find_clique(list<int>potential_clique, list<int> remaining_nodes, list<int> skip_nodes)
// {
//     int m=0;
//     if(remaining_nodes.empty()==1 && skip_nodes.empty()==1){
//         all_clique[m] = potential_clique;
//         m++;
//     }
//     list<int>::iterator it;
//     for(it=remaining_nodes.begin(); it!=remaining_nodes.end(); ++it){
//         int node = *it;
//         potential_clique.push_back(node);
//         list<int>::iterator j;
//         for(j=neighbor[node].begin(); j!=neighbor[node].end(); ++j){
//             int n = *j;
//             list<int>::iterator k = find(remaining_nodes.begin(), remaining_nodes.end(), n);
//             if(k!=remaining_nodes.end()){
//                 new_remaining_nodes.push_back(n);
//             }
//             list<int>::iterator k2 = find(skip_nodes.begin(), skip_nodes.end(), n);
//             if(k2!=skip_nodes.end()){
//                 new_skip_nodes.push_back(n);
//             }
//         }
//         // for(int i=0; i<MAX; i++){
//             // if(neighbor[node][i]==1){
//                 // list<int>::iterator k = find(remaining_nodes.begin(), remaining_nodes.end(), i);
//                 // if(k!=remaining_nodes.end()){
//                 //     new_remaining_nodes.push_back(i);
//                 // }
//                 // list<int>::iterator k2 = find(skip_nodes.begin(), skip_nodes.end(), i);
//                 // if(k2!=skip_nodes.end()){
//                 //     new_skip_nodes.push_back(i);
//                 // }
//             // }
//         // }
//         find_clique(potential_clique, new_remaining_nodes, new_skip_nodes);
//         remaining_nodes.remove(node);
//         skip_nodes.push_back(node);
//     }
//     cout << "find_clique" << endl;
// }