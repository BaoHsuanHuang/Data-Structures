#include <iostream>
#include <string>
#include <set>
#include <vector>

#define total_vertex 82168

using namespace std;

typedef struct _node{
    set<int>s;
}Node;

Node index_is_ID[total_vertex];
Node index_is_degree[total_vertex];


int main(void)
{
    int u, v;
    char K;
    int k_core;

    while(cin >> u >> v){
        index_is_ID[u].s.insert(v);
        index_is_ID[v].s.insert(u);
    }
    cin >> K >> k_core;

    for(int i=0; i<total_vertex; i++){
        int tmp;
        tmp = index_is_ID[i].s.size();
        index_is_degree[tmp].s.insert(i);
    }

    for(int i=1; i<k_core; i++){
        int VertexId;
        VertexId = index_is_degree[i].s.begin();
        for(int j=0; j<index_is_ID[VertexId].s.size(); j++){
            int tmp = index_is_ID[VertexId].s.begin();
            index_is_ID[VertexId].s.erase(tmp);
            index_is_ID[tmp].s.erase(VertexId);
            if(index_is_ID[tmp].s.size() > i){
                index_is_degree[index_is_ID[tmp].s.size()].s.insert(tmp);
            }
        }
    }

    for(int i=k_core; i<8; i++){
        for(int j=0; j<index_is_degree[i].s.size(); j++){
            int tmp = index_is_degree[i].s.begin();
            index_is_degree[i].s.erase(tmp);
            cout << tmp << " " << index_is_ID[tmp].s.size() << endl;
        }
    }

    return 0;
}
