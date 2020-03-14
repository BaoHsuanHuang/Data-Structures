#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int num_vertex;   // testcase input
int map_time[1000][1000];  // adjacency matrix
float map_rate[1000][1000];
//int distance[1000];
int dist[1000];
float rate[1000];
int parent[1000];
bool visit[1000];
int credit;
int Max_distance = 1e9;


void Initialize(int num_vertex);
void Add_edge(int v1, int v2, int time, float rate);
void Delete_edge(int v1, int v2);
int Choose_Next_Vertex(int num_vertex);
int Shortest(int num_vertex, int source, int destination);


void Initialize(int num_vertex)
{
	int i, j;
	for(i=0;i<num_vertex;i++){
		dist[i] = Max_distance;
		rate[i] = 0;
		parent[i] = -1;
		visit[i] = false;
	}
	for(i=0;i<num_vertex;i++){
		for(j=0;j<num_vertex;j++){
			map_time[i][j] = Max_distance;
			map_rate[i][j] = 0;
		}
	}
}

void Add_edge(int v1, int v2, int time, float rate)
{
	map_time[v1][v2] = time;
	map_time[v2][v1] = time;
	map_rate[v1][v2] = rate;
	map_rate[v2][v1] = rate;
}

void Delete_edge(int v1, int v2)
{
	map_time[v1][v2] = Max_distance;
	map_time[v2][v1] = Max_distance;
	map_rate[v1][v2] = 1;
	map_rate[v2][v1] = 1;
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
	visit[a] = true;
	return a;
}

int Shortest(int num_vertex, int source, int destination)
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
		if(next_vertex==-1) break;  // can't find the vertex
		visit[next_vertex] = true;

		for(j=0;j<num_vertex;j++){
			if(visit[j]==false 
				&& (dist[next_vertex] + map_time[next_vertex][j] < dist[j]) ){
					dist[j] = dist[next_vertex] + map_time[next_vertex][j];
					parent[j] = next_vertex;
			}
		}
	}
	return dist[destination];
}



// Map
struct Edge{
	int from;
	int to;
	int weight;
	Edge(){};
	Edge(int a, int b, int c) : from(a), to(b), weight(c){};	
};

bool WeightComp(struct Edge e1, struct Edge e2)
{
	return (e1.weight < e2.weight);
}

void GetSortedEdge(vector<struct Edge> &edgearray)
{
	int i, j;
	for(i=0;i<num_vertex-1;i++){
		for(j=i+1 ; j<num_vertex ; j++){
			if(map_time[i][j]!=Max_distance){  //map_time[i][j]!=0
				edgearray.push_back(Edge(i, j, map_time[i][j]));
			}
		}
	}
	sort(edgearray.begin(), edgearray.end(), WeightComp);
}

int FindSetCollapsing(int *subset, int i)
{
	int root;
	int parent;

	for(root=i; subset[root]>=0; root=subset[root]);

	while(i != root){
		parent = subset[i];
		subset[i] = root;
		i = parent;
	}

	return root;
}

void UnionSet(int *subset, int x, int y)
{
	int xroot = FindSetCollapsing(subset, x);
	int yroot = FindSetCollapsing(subset, y);

	if(subset[xroot] <= subset[yroot]){  // x has more elements
		subset[xroot] += subset[yroot];
		subset[yroot] = xroot;
	}else{  // y has more elements
		subset[yroot] += subset[xroot];
		subset[xroot] = yroot;
	}
}

int Kruskal_MST()
{
	int i;
	int min = 0;

	struct Edge *edgesetMST = new struct Edge[num_vertex-1];
	int edgesetcount = 0;
	
	int subset[num_vertex];
	for(i=0;i<num_vertex;i++){
		subset[i] = -1;	  // initialize
	}

	vector<struct Edge> increaseWeight;
	GetSortedEdge(increaseWeight);

	for(i=0;i<increaseWeight.size();i++){
		if(FindSetCollapsing(subset, increaseWeight[i].from != FindSetCollapsing(subset, increaseWeight[i].to))){
			edgesetMST[edgesetcount] = increaseWeight[i];
			edgesetcount++;
			UnionSet(subset, increaseWeight[i].from, increaseWeight[i].to);
		}
	}
	for(i=0;i<num_vertex;i++){
		cout << i << " : " << edgesetMST[i].weight << endl; 
		min += edgesetMST[i].weight;
	}
	for(i=0;i<num_vertex;i++){
		cout << i << " : " << increaseWeight[i].weight << endl; 
	}
	return min;
}
// Map


void ImportantBus(int num_vertex)
{
	int i, j;
	int count = 0;

	for(i=0 ; i<num_vertex; i++){
		count = 0;
		for(j=0 ; j<num_vertex; j++){
			if(map_time[i][j] != Max_distance) count++;
		}
	}
	if(count == 1) cout << "Yes" << endl;
	else cout << "No" << endl;
}


int Choose_Next_Vertex_rate(int num_vertex)
{
	int i,j;
	int a, b;
	float max;
	
	a = -1;
	b = -1;
	max = 0;

	for(i=0;i<num_vertex;i++){
		if(visit[i]==false && rate[i]>max){
			max = rate[i];
			a = i;
		}
	}
	visit[a] = true;
	return a;
}

float CreditExchange(int num_vertex, int source, int destination)
{
	int i,j;
	int next_vertex;

	for(i=0;i<num_vertex;i++){
		visit[i] = false;
		rate[i] = map_rate[source][i];
		parent[i] = -1;
	}
	visit[source] = true;
	rate[source] = 0;

	for(i=0;i<num_vertex-1;i++){
		next_vertex = Choose_Next_Vertex_rate(num_vertex);
		visit[next_vertex] = true;

		for(j=0;j<next_vertex;j++){
			if(visit[j]==false && (rate[next_vertex]*map_rate[next_vertex][j]) > rate[j]){
				rate[j] = rate[next_vertex]*map_rate[next_vertex][j];
				parent[j] = next_vertex;
			}
		}
	}
	// for(i=0;i<num_vertex;i++){
	// 	cout << i << " : " << rate[i] << endl;
	// }
	return rate[destination];
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
			float r;
			cin >> v1 >> v2 >> w >> r;
			Add_edge(v1, v2, w, r);
		}else if(cmd == "Delete"){
			int v1, v2;
			Delete_edge(v1, v2);
		}else if(cmd == "Shortest"){
			int v1, v2;
			int ans;
			cin >> v1 >> v2;
			ans = Shortest(num_vertex, v1, v2);
			cout << ans << endl;
		}else if(cmd == "Map"){
			int min;
			min = Kruskal_MST();
			cout << min << endl;
		}else if(cmd == "ImportantBus"){
			ImportantBus(num_vertex);
		}else if(cmd == "CreditExchange"){
			int v1, v2;
			int c;
			float rate;
			int ans;
			cin >> v1 >> v2 >> c;
			rate = CreditExchange(num_vertex, v1, v2);
			ans = (int)(c * rate);
			// CreditExchange(num_vertex, v1, v2);
			// ans = (int)(c * rate[v2]);
			cout << ans << endl;
		}else if(cmd == "CreditExchange2"){
			int v1, v2;
			int c;
			float rate;
			int ans;
			cin >> v1 >> v2 >> c;
			rate = CreditExchange(num_vertex, v1, v2);
			ans = (int)(c * rate);
			// CreditExchange(num_vertex, v1, v2);
			// ans = (int)(c * rate[v2]);
			cout << ans << endl;
		}
	}
}




