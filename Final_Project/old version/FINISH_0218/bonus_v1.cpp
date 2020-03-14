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
int degree[MAX];
int clique[MAX];

void signalHandler(int signum)
{
    cout << "Get signal " << signum << endl;
    exit(signum);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);
    int u, v;
    string file_name = string(argv[1]);
    string K = string(argv[2]);
    int k = stoi(K);
    fstream file;
    file.open(file_name, ios::in);

    fstream file_out_clique_bonus;
    file_out_clique_bonus.open("clique_bonus.txt", ios::out);

    while(file >> u >> v){
        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }

    int count=0;
    for(int i=0; i<MAX; i++){
        int tmp = Graph[i].size();
        if(tmp >= 1499){
            degree[count] = i;
            count++;
        }
    }
    list<int>::iterator it;
    int num = 0;
    for(int i=0; i<count; i++){
        int point = degree[i];
        for(it=Graph[point].begin(); it!=Graph[point].end(); ++it){
            if(Graph[*it].size() >= 1499){
                clique[num] = *it;
                num++;
            }
        }
        clique[num] = point;
        if(num==1499) break;
        else num=0;
    }
    sort(clique, clique+num+1);
    for(int i=0; i<=num; i++){
        file_out_clique_bonus << clique[i] << '\n';
    }
    return 0;
}