#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <string>
#include <signal.h>
#include <algorithm>
#include <time.h>
#include <set>
#include <vector>
#include <iterator>
#define MAX 82168

using namespace std;

set<int> neighbor[MAX];
int Degree[MAX] = {0};
int has_visited = 0;
bool visited[MAX];
int coreness[MAX]={0};

set<int> max_clique;
vector<int> degeneracy_order;

void Find_kcore();
void BronKerbosch2(set<int> R, set<int> P, set<int> X);
void find_BronKerbosch3();
bool compare(int a, int b);

void create_file_clique();


void signalHandler(int signum)
{
    cout << "Get signal " << signum << endl;
    // fstream file_out_clique;
    // file_out_clique.open("clique.txt", ios::out);
    // set<int>::iterator it;
    // for(it=max_clique.begin(); it!=max_clique.end(); it++){
    //     file_out_clique << *it << '\n';
    // }
    create_file_clique();
    exit(signum);
}

void create_file_clique()
{
	fstream file_out_clique;
	file_out_clique.open("clique.txt", ios::out);
	//set<int> output_clique;
	set<int>::iterator it;
	for(it=max_clique.begin(); it!=max_clique.end(); it++){
		file_out_clique << *it << endl;
	}
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
    fstream file;
    file.open(file_name, ios::in);

    fstream file_out_kcore;
    file_out_kcore.open("kcore.txt", ios::out);

    fstream file_out_clique;
    file_out_clique.open("clique.txt", ios::out);

    while(file >> u >> v){
        neighbor[u].insert(v);
        neighbor[v].insert(u);
        Degree[u]++;
        Degree[v]++;
    }
    for(int i=0; i<MAX; i++){
        visited[i] = false;
    }

    Find_kcore();
    for(int i=0; i<MAX; i++){
        if(coreness[i] >= k){
            file_out_kcore << i << " " << coreness[i] << endl;
        }
    }

    find_BronKerbosch3();
    
    set<int>::iterator it;
    for(it=max_clique.begin(); it!=max_clique.end(); it++){
        file_out_clique << *it << '\n';
    }
    // end = clock();
    // cout << (double)(end - start)/CLOCKS_PER_SEC << endl;
    return 0;
}


void Find_kcore()
{
    int min = 82200;
    int new_min = 82200;
    set<int> delete_vertex;

    // find min degree
    for(int i=0; i<MAX; i++){
        if(visited[i]==false && min>Degree[i]){
            min = Degree[i];
        }
    }

    while(has_visited < MAX){
        for(int i=0; i<MAX; i++){
            if(visited[i]==false && min>=Degree[i]){
                has_visited++;
                visited[i] = true;
                // delete_vertex.push_back(i);
                delete_vertex.insert(i);
                Degree[i] = 0;
                coreness[i] = min;
            }
        }
        set<int>::iterator it;
        for(it=delete_vertex.begin(); it!=delete_vertex.end(); ++it){
            int tmp = *it;
            set<int>::iterator m;
            for(m=neighbor[tmp].begin(); m!=neighbor[tmp].end(); ++m){
                if(visited[*m]==false){
                    Degree[*m]--;
                }
            }
        }
        delete_vertex.clear();
        new_min = 82200;
        for(int i=0; i<MAX; i++){
            if(visited[i]==false && new_min>Degree[i]){
                new_min = Degree[i];
            }
        }
        if(new_min > min){
            min = new_min;
        }
    }
}

int max2 = 0;
void BronKerbosch2(set<int> R, set<int> P, set<int> X){
    set<int> P_union_X;
    set<int> P_diff_Nu;
    if(P.empty()==1 && X.empty()==1){
        int size = R.size();
        if(size >= max2){
            max2 = size;
            max_clique.clear();
            max_clique = R;
            
            // if(max2 == 1500) cout << "done" << endl;
        }
        return;
    }
    set_union(P.begin(), P.end(), X.begin(), X.end(), inserter(P_union_X, P_union_X.begin()));
    int u = *P_union_X.begin();
    set_difference(P.begin(),P.end(),neighbor[u].begin(),neighbor[u].end(),inserter(P_diff_Nu,P_diff_Nu.begin()));
    for(auto v : P_diff_Nu){
    // set<int>::iterator it;
    // for(it=P_diff_Nu.begin(); it!=P_diff_Nu.end(); ++it){
        // int v = *it;
        set<int> P_intersection_Nv;
        set<int> X_intersection_Nv;
        set<int> R_union_V;
        set<int> V;
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

void find_BronKerbosch3()
{
    set<int> R;
    set<int> P;
    set<int> X;
    for(int i=0; i<MAX; i++){
        P.insert(i);
        degeneracy_order.push_back(i);
    }
    sort(degeneracy_order.begin(), degeneracy_order.end(), compare);
    R.clear();
    X.clear();
    vector<int>::iterator it;
    for(it=degeneracy_order.begin(); it!=degeneracy_order.end(); ++it){
        int v = *it;
        set<int> V;
        set<int> P_intersection_Nv;
        set<int> X_intersection_Nv;
        V.insert(v);
        set_intersection(P.begin(), P.end(), neighbor[v].begin(), neighbor[v].end(), inserter(P_intersection_Nv, P_intersection_Nv.begin()));
        set_intersection(X.begin(), X.end(), neighbor[v].begin(), neighbor[v].end(), inserter(X_intersection_Nv, X_intersection_Nv.begin()));
        BronKerbosch2(V, P_intersection_Nv, X_intersection_Nv);
        set_difference(P.begin(),P.end(),V.begin(),V.end(),inserter(P, P.begin()));
        set_union(X.begin(), X.end(), V.begin(), V.end(), inserter(X, X.begin()));
        if(max2 == 1500){
            break;
        }
    }
}

bool compare(int a, int b)
{
    if(coreness[a] > coreness[b])
        return 1;
    else
        return 0;
}