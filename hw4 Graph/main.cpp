#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int num_vertex;   // testcase input
int map_time[1000][1000];  // adjacency matrix
double map_rate[1000][1000];
int dist[1000];
double rate[1000];
int parent[1000];
bool visit[1000];
int credit;
int Max_distance = 2000000; // 1e9
int connect[1000];

void Initialize(int num_vertex)
{
	int i, j;
	for(i=0;i<num_vertex;i++){
		dist[i] = Max_distance;
		rate[i] = 0;
		parent[i] = -1;
		visit[i] = false;
		connect[i] = 0;
	}
	for(i=0;i<num_vertex;i++){
		for(j=0;j<num_vertex;j++){
			map_time[i][j] = Max_distance;
			map_rate[i][j] = 0;
		}
	}
}

void Add_edge(int v1, int v2, int time, double rate)
{
	map_time[v1][v2] = time;
	map_time[v2][v1] = time;
	map_rate[v1][v2] = rate;
	map_rate[v2][v1] = rate;
	connect[v1]++;
	connect[v2]++;
}

void Delete_edge(int v1, int v2)
{
	map_time[v1][v2] = Max_distance;
	map_time[v2][v1] = Max_distance;
	map_rate[v1][v2] = 0;
	map_rate[v2][v1] = 0;
	connect[v1]--;
	connect[v2]--;
}

int Choose_Next_Vertex(int num_vertex)
{
	int i, j;
	int a, b, min;

	a = -1;
	b = -1;
	min = Max_distance;

	for(i=0;i<num_vertex;i++){
		if( visit[i]==false  &&  dist[i]<min ){
			min = dist[i];
			a = i;
		}
	}
	return a;
}

void Shortest(int num_vertex, int source, int destination)
{
	int i, j;
	int next_vertex;
	
	for(i=0;i<num_vertex;i++){
		visit[i] = false;
		dist[i] = map_time[source][i];
		parent[i] = -1;
	}
	visit[source] = true;
	dist[source] = 0;

	for(i=0;i<num_vertex-1;i++){
		next_vertex = Choose_Next_Vertex(num_vertex);
		if(next_vertex == -1) break;   // can't find the vertex
		visit[next_vertex] = true;

		for(j=0;j<num_vertex;j++){
			if(visit[j]==false && map_time[next_vertex][j]!=Max_distance
				&& (dist[next_vertex] + map_time[next_vertex][j] < dist[j]) ){
					dist[j] = dist[next_vertex] + map_time[next_vertex][j];
					parent[j] = next_vertex;
			}
		}
	}
	if(dist[destination]==Max_distance) cout << "Error" << endl;
	else cout << dist[destination] << endl;
}

// Map
// int Max_Weight = 1000;
int minKeyExtract(int *key, bool *visit, int size)
{
	int min = Max_distance;  // Max_Weight
	int min_idx = -1;
	int i;

	for(i=0 ; i<size ; i++){
		if(visit[i]==false && key[i]<min){
			min = key[i];
			min_idx = i;
		}
	}
	// visit[min_idx] = true;
	return min_idx;
}

int PrimMST(int start)
{
	int i;
	int w;
	int key[num_vertex];
	int ans = 0;
	
	for(i=0 ; i<num_vertex ; i++){
		key[i] = map_time[start][i];  //Max_Weight
		parent[i] = -1;
		visit[i] = false;
	}
	key[start] = 0;
	visit[start] = true;
	for(i=0 ; i<num_vertex-1 ; i++){
		int u = minKeyExtract(key, visit, num_vertex);
		if(u==-1) break;  // can't find the vertex
		visit[u] = true;
		ans += key[u];
		for(w=0 ; w<num_vertex ; w++){
			if(visit[w]==false && map_time[u][w]!=Max_distance && map_time[u][w]<key[w]){
				parent[w] = u;
				key[w] = map_time[u][w];
			}
		}
	}

	// check whether all the vertices have been traversed
    for (int i=0; i<num_vertex; i++) {
        if (!visit[i]) return -1;
    } 
	for(i=0;i<num_vertex;i++){
		if(connect[i]==0) return -1;
	}
	return ans;
}
// Map

bool ImportantBus(int num_vertex)
{
	// int i, j;
	// int count = 0;

	// for(i=0 ; i<num_vertex; i++){
	// 	count = 0;
	// 	for(j=0 ; j<num_vertex; j++){
	// 		if(map_time[i][j] != Max_distance) count++;
	// 	}
	// }
	// if(count == 1) cout << "Yes" << endl;
	// else cout << "No" << endl;
	int i;
	for(i=0;i<num_vertex;i++){
		if(connect[i]==1 || connect[i]==0){
			return true;
		}
	}
	return false;
}

int choose_max_credit(int *credit, bool *visit)
{
	int max_credit = 0;
	int u = -1;
	for(int i=0;i<num_vertex;i++){
		if(!visit[i] && credit[i]>max_credit){
			u = i;
			max_credit = credit[i];
		}
	}
	return u;
}

void CreditExchange(int v1, int v2, int c)
{
	int credit[num_vertex];
	bool visit[num_vertex];

	for(int i=0;i<num_vertex;i++){
		visit[i] = false;
		credit[i] = (int)(map_rate[v1][i]*c);
	}

	visit[v1] = true;
	credit[v1] = c;

	for(int i=0;i<num_vertex;i++){
		int u = choose_max_credit(credit, visit);
		if(u==-1) break;
		visit[u] = true;
		for(int w=0;w<num_vertex;w++){
			if(!visit[w] && map_time[u][w]!=Max_distance && (int)(credit[u]*map_rate[u][w])>credit[w])
				credit[w] = (int)(credit[u]*map_rate[u][w]);
		}
	}
	cout << credit[v2] << endl;
}


int link[1000][1000]={0};
int Max_Credit = 0;
void CreditExchange2(int v1, int v2, int c, int limit)
{
	int next;
	
	if(c >= Max_Credit && v1==v2){
		Max_Credit = c;
	}
	if(limit==0) return;

	if(limit>0){
		for(int i=0; i<num_vertex;i++){
			if(map_time[v1][i]!=Max_distance && link[v1][i]==0){
				next = i;
				int tmp = (int)(c*map_rate[v1][next]);
	
				link[v1][next] = 1;
				link[next][v1] = 1;
				CreditExchange2(next, v2, tmp, limit-1);
				link[v1][next] = 0;	
				link[next][v1] = 0;			
			}
		}
	}
}


int main(void)
{
	string cmd;
	
	cin >> num_vertex;

	Initialize(num_vertex);

	while(cin >> cmd){
		if(cmd == "Add"){
			int v1, v2;
			int w;
			double r;
			cin >> v1 >> v2 >> w >> r;
			Add_edge(v1, v2, w, r);
		}else if(cmd == "Delete"){
			int v1, v2;
			cin >> v1 >> v2;
			Delete_edge(v1, v2);
		}else if(cmd == "Shortest"){
			int v1, v2;
			int ans;
			cin >> v1 >> v2;
			Shortest(num_vertex, v1, v2);
		}else if(cmd == "Map"){
			int min;
			min = PrimMST(0);
			if(min==-1) cout << "Error" << endl;
			else cout << min << endl;
		}else if(cmd == "ImportantBus"){
			bool flag = 0;
			flag = ImportantBus(num_vertex);
			if(flag==true) cout << "Yes" << endl;
			else cout << "No" << endl;
		}else if(cmd == "CreditExchange"){
			int v1, v2;
			int c;
			cin >> v1 >> v2 >> c;
			// r = CreditExchange(num_vertex, v1, v2);
			// ans = (int)(c * r);
			// cout << ans << endl;
			CreditExchange(v1, v2, c);
		}else if(cmd == "CreditExchange2"){
			int v1, v2;
			int c;
			int limit;
			cin >> v1 >> v2 >> c >> limit;
			for(int a=0;a<num_vertex;a++){
				for(int b=0;b<num_vertex;b++){
					link[a][b] = 0;
				}
			}
			Max_Credit = 0;
			CreditExchange2(v1, v2, c, limit);
			cout << Max_Credit << endl;
		}
	}
}




