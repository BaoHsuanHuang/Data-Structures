#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <set>
#include <string>
#include <signal.h>
#include <algorithm>
#include <time.h>
#include <iterator>
#define MAX 82168

using namespace std;

set<int> P;
set<int> R;
set<int> X;

set<int> neighbor[MAX];
set<int> clique;

// void BronKerbosch1(set<int> R, set<int> P, set<int> X);
void BronKerbosch2(set<int> R, set<int> P, set<int> X);

void signalHandler(int signum)
{
    cout << "Get signal " << signum << endl;
	fstream file_out_clique_bonus;
    file_out_clique_bonus.open("clique_bonus.txt", ios::out);
    set<int>::iterator it;
    for(it=clique.begin(); it!=clique.end(); it++){
        file_out_clique_bonus << *it << '\n';
    }
    exit(signum);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, signalHandler);
    
    int u, v;
    string file_name = string(argv[1]);
    string NumOfVertex = string(argv[2]);
    int num = stoi(NumOfVertex);
    fstream file;
    file.open(file_name, ios::in);

    fstream file_out_clique_bonus;
    file_out_clique_bonus.open("clique_bonus.txt", ios::out);

    while(file >> u >> v){
        neighbor[u].insert(v);
        neighbor[v].insert(u);
        P.insert(v);
        P.insert(u);
    }

    BronKerbosch2(R, P, X);
    
    set<int>::iterator it;
    for(it=clique.begin(); it!=clique.end(); it++){
        file_out_clique_bonus << *it << '\n';
    }
    return 0;
}


int max2 = 0;
void BronKerbosch2(set<int> R, set<int> P, set<int> X){
    set<int> P_union_X; 
    set<int> P_diff_Nu;
    if(R.size() + P.size() <= max2) return;
    if(P.empty()==1 && X.empty()==1){
        int size = R.size();
        if(size > max2){
            max2 = size;
            clique.clear();
            clique = R;
            return;
        }
    }
    set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(P_union_X, P_union_X.begin()));
    int u = *P_union_X.begin();
    set_difference(P.begin(),P.end(),neighbor[u].begin(),neighbor[u].end(),inserter(P_diff_Nu,P_diff_Nu.begin()));
    set<int>::iterator it;
    // for(it=P_diff_Nu.begin(); it!=P_diff_Nu.end(); ++it){
    //     int v = *it;
    for(auto v:P_diff_Nu){
        set<int> P_intersection_Nv;
        set<int> X_intersection_Nv;
        set<int> R_union_V;
        set<int> V;
        // set<int> P_diff_V;
        // set<int> X_union_V;
        V.clear();
        V.insert(v);
        set_union(R.begin(), R.end(), V.begin(), V.end(), inserter(R_union_V, R_union_V.begin()));
        set_intersection(P.begin(), P.end(), neighbor[v].begin(), neighbor[v].end(), inserter(P_intersection_Nv, P_intersection_Nv.begin()));
        set_intersection(X.begin(), X.end(), neighbor[v].begin(), neighbor[v].end(), inserter(X_intersection_Nv, X_intersection_Nv.begin()));
        BronKerbosch2(R_union_V, P_intersection_Nv, X_intersection_Nv);
        set_difference(P.begin(),P.end(),V.begin(),V.end(),inserter(P, P.begin()));
        set_union(X.begin(), X.end(), V.begin(), V.end(), inserter(X, X.begin()));
    }
}



// void BronKerbosch1(set<int> R, set<int> P, set<int> X)
// {
//     if(P.empty()==1 && X.empty()==1){
//         int size = R.size();
//         if(size > max2){
//             max2 = size;
//             clique.clear();
//             clique = R;
//             return;
//         }
//     }
//     set<int> P_intersection_Nv;
//     set<int> X_intersection_Nv;
//     set<int>::iterator it;
//     // for(it=P.begin(); it!=P.end(); ++it){
//     //     int v = *it;
//     for(auto v : P){
//         R.insert(v);
//         set_intersection(P.begin(), P.end(), neighbor[v].begin(), neighbor[v].end(), inserter(P_intersection_Nv, P_intersection_Nv.begin()));
//         set_intersection(X.begin(), X.end(), neighbor[v].begin(), neighbor[v].end(), inserter(X_intersection_Nv, X_intersection_Nv.begin()));
//         BronKerbosch1(R, P_intersection_Nv, X_intersection_Nv);
//         P.erase(v);
//         X.insert(v);
//     }
// }