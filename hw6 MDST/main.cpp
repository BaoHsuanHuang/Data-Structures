#include <iostream>
#include <string>

using namespace std;

int nvertex;
bool connected;
double ecc;
int vertex_i;
int vertex_j; //if AC is on a vertex, point2 will be -1
double d1; //distant between absolute center and point1
double d2; //distant between absolute center and point2
double sum;
int MAX = 1000;
int flag = MAX;
int Max_distance = 2000000;

int map[1000][1000];
int dist[1000][1000];
int rankk[1000][1000];

void initialize();
void Add(int v1, int v2, int w);
void Delete(int v1, int v2);
void Floyd_Warshall(void);
void BubbleSort(void);
void KarivHakimi(void);
void Find_Absolute_center(void);
void Find_Diameter(void);
void Dijkstra(void);
void shortest_vertex(int source);
void shortest_edge(void);
double shortest[1000];
bool visit[1000];

void initialize()
{
	// map
    for(int i=0; i<nvertex; i++){
        for(int j=0; j<nvertex; j++){
            if(i != j)
                map[i][j] = -1;
            else
                map[i][j] = 0;
        }
    }
    
    // dist
    for(int i=0; i<nvertex; i++){
        for(int j=0; j<nvertex; j++){
        	dist[i][j] = 0;
        }
    }
    
    // rank
    for(int i=0; i<nvertex; i++){
        for(int j=0; j<nvertex; j++){
            rankk[i][j] = j;
        }
    }
    
    for(int i=0; i<nvertex; i++){
    	shortest[i] = Max_distance;
    	visit[i] = false;
	}
} 

void Add(int v1, int v2, int w)
{
    map[v1][v2] = w;
    map[v2][v1] = w;
}

void Delete(int v1, int v2)
{
    map[v1][v2] = -1;
    map[v2][v1] = -1;
}

void Floyd_Warshall(void)
{
    //initialize
    int i, j, k;
    
    for(i=0; i<nvertex; i++){
    	for(j=0; j<nvertex; j++){
    		dist[i][j] = map[i][j];
		}
	}
	
    //All-pairs shortest path
    for(k=0; k<nvertex; k++){
    	for(i=0; i<nvertex; i++){
    		for(j=0; j<nvertex; j++){
    			if(i!=j){
    				if( (dist[i][j]>dist[i][k]+dist[k][j]) && dist[i][k]!=-1 && dist[k][j]!=-1){
    					dist[i][j] = dist[i][k] + dist[k][j];
					}else if(dist[i][j]==-1 && dist[i][k]!=-1 && dist[k][j]!=-1){
						dist[i][j] = dist[i][k] + dist[k][j];
					}
				}
			}
		}
	}
    for (int k = 0; k < nvertex; k++){
        for (int i = 0; i < nvertex; i++){
            for (int j = 0; j < nvertex; j++){
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
    }
//	for(i=0; i<nvertex; i++){
//		for(j=0; j<nvertex; j++){
//			cout << dist[i][j] << " ";
//		}
//		cout << endl;
//	}
}


void BubbleSort(void)
{
	int i, j, k;
	int tmp;
	
    // initialize
    for(i=0; i<nvertex; i++){
        for(int j=0; j<nvertex; j++){
            rankk[i][j] = j;
        }
    }
    // bubble sort
    for(k=0; k<nvertex ;k++){
    	for(i=nvertex-1; i>0 ;i--){
    		for(j=0; j<nvertex ;j++){
    			if(dist[k][rankk[k][j+1]] > dist[k][rankk[k][j]]){
    				tmp = rankk[k][j];
    				rankk[k][j] = rankk[k][j+1];
    				rankk[k][j+1] = tmp;
				}
			}
		}
	}
//    for(i=0; i<nvertex; i++){
//        for(int j=0; j<nvertex; j++){
//            cout << rankk[i][j] << " ";
//        }
//        cout << endl;
//    }
}


void KarivHakimi(void)
{
	int i, j;
   	connected = true;
    Floyd_Warshall();
    BubbleSort();
    ecc = MAX;
    vertex_i = 0;
    vertex_j = -1;
    
    for(i=0 ;i<nvertex ;i++){
    	for(j=0 ;j<nvertex ;j++){
    		if(dist[i][j]==-1){
    			connected = false;
    			return;  // means the graph is not connected
			}
			if(dist[i][rankk[i][0]] < ecc){
				ecc = dist[i][rankk[i][0]];
				vertex_i = i;
				vertex_j = -1;
			}
			if(dist[j][rankk[j][0]] < ecc){
				ecc = dist[j][rankk[j][0]];
				vertex_i = j;
				vertex_j = -1;
			}
			
			// intersection
			int a, b;
			for(a=0,b=1; b<nvertex; b++){
				if(dist[j][rankk[i][b]] > dist[j][rankk[i][a]]){  // mean intersection
	                if(((double)(dist[i][rankk[i][b]] + dist[j][rankk[i][a]] + dist[i][j]))/2 < ecc){
	                    ecc = (double)(dist[i][rankk[i][b]] + dist[j][rankk[i][a]] + dist[i][j])/2;
	                    vertex_i = i;
	                    vertex_j = j;
	                    d1 = ecc-(double)dist[i][rankk[i][b]];
	                    d2 = ecc-(double)dist[j][rankk[i][a]];
	                }
	                a = b;
				}
			}
		}
	}
}



void Find_Absolute_center(void)
{
	KarivHakimi();
	if(flag==3){
		if(connected==false){
	        cout << "Not connected graph\n";
	        return;
		}
		if(vertex_j==-1){ // absolute center is on vertex
			cout << vertex_i << endl;
		}else{
			if(vertex_i < vertex_j){
				cout << vertex_i << " " << vertex_j << endl;
			}else if(vertex_i > vertex_j){
				cout << vertex_j << " " << vertex_i << endl; 
			}
		}
	}
}

void Find_Diameter()
{
	int diameter;
	Find_Absolute_center();
	if(flag==4){
		if(connected==false){
	        cout << "Not connected graph\n";
	        return;
		}
		if(connected==true){
			diameter = 2*ecc;
			cout << diameter << endl;
		}	
	}
}



int Choose_Next_Vertex()
{
	int i, j;
	int a, b, min;
	a = -1;
	b = -1;
	min = Max_distance;
	for(i=0;i<nvertex;i++){
		if( visit[i]==false  &&  shortest[i]<min ){
			min = shortest[i];
			a = i;
		}
	}
	return a;
}


void shortest_vertex(int source)
{
	int i, j;
	int next_vertex;
	
	for(i=0;i<nvertex;i++){
		visit[i] = false;
		shortest[i] = map[source][i];
	}
	visit[source] = true;
	shortest[source] = 0;

	for(i=0;i<nvertex-1;i++){
		next_vertex = Choose_Next_Vertex();
		if(next_vertex == -1) break;   // can't find the vertex
		visit[next_vertex] = true;

		for(j=0;j<nvertex;j++){
			if(visit[j]==false && map[next_vertex][j]!=-1
				&& (shortest[next_vertex] + map[next_vertex][j] < shortest[j]) ){
					shortest[j] = shortest[next_vertex] + map[next_vertex][j];
			}
		}
	}
	
	for(i=0; i<nvertex; i++){
		sum += shortest[i];
	}
	cout << sum << endl;
}

void shortest_edge()
{
	int i, j;
	int next_vertex;
	
	for(i=0;i<nvertex;i++){
		visit[i] = false;
		shortest[i] = Max_distance;
	}
	shortest[vertex_i] = d1;
	shortest[vertex_j] = d2;

	for(i=0;i<nvertex-1;i++){
		next_vertex = Choose_Next_Vertex();
		if(next_vertex == -1) break;   // can't find the vertex
		visit[next_vertex] = true;

		for(j=0;j<nvertex;j++){
			if(visit[j]==false && map[next_vertex][j]!=-1
				&& (shortest[next_vertex] + map[next_vertex][j] < shortest[j]) ){
					shortest[j] = shortest[next_vertex] + map[next_vertex][j];
			}
		}
	}
	
	for(i=0; i<nvertex; i++){
		sum += shortest[i];
	}
	cout << sum << endl;
}

void Dijkstra()
{
	Find_Absolute_center();
	sum = 0;
	if(flag==5){
		if(connected==false){
	        cout << "Not connected graph\n";
	        return;
		}
		if(vertex_j==-1){  // absolute center is on vertex
			shortest_vertex(vertex_i);
		}else{  // absolute center is on the edge
			shortest_edge();
		}		
	}
} 

int main()
{
	string cmd;
	int v1, v2, w;
	
	cin >> nvertex;
	initialize();
	while(cin >> cmd){
		if(cmd=="Add"){
			cin >> v1 >> v2 >> w;
			Add(v1, v2, w);
		}else if(cmd=="Delete"){
			cin >> v1 >> v2;
			Delete(v1, v2);
		}else if(cmd=="AC"){
			flag = 3;
			Find_Absolute_center();
		}else if(cmd=="Diameter"){
			flag = 4;
			Find_Diameter();
		}else if(cmd=="SOSPD"){
			flag = 5;
			Dijkstra();
		}
	}
	
	return 0;
}
