#include <iostream>
#include <string>

using namespace std;

int n;
int w[1000][1000];
int r[1000][1000];
int parent[1000];
int d[1000];
bool visit[1000];
int total_credit;
int MAX = 1e9;

void initial(int n)
{
	int i, j;
	for(i=0;i<n;i++){
        parent[i] = 0;
		visit[i] = false;
		d[i] = MAX;
	}
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            w[i][j] = MAX;
            r[i][j] = MAX;
        }
    }
}


void Add(int v1, int v2, int weight, float rate)
{
	w[v1][v2] = weight;
	w[v2][v1] = weight;
	r[v1][v2] = rate;
	r[v2][v1] = rate;
}

void Delete(int v1, int v2)
{
	w[v1][v2] = MAX;
	w[v2][v1] = MAX;
	r[v1][v2] = MAX;
	r[v2][v1] = MAX;
}



int choose(int n);
void Shortest(int n, int v1, int v2)
{
	int i, j;
	int p;
	int next;

	for(i=0;i<n;i++){
		visit[i] = false;
		d[i] = w[v1][i];
		parent[i] = MAX;  	// NULL 
	}
	visit[v1] = true;
	d[v1] = 0;

	for(i=0;i<n-1;i++){
		next = choose(n);
		visit[next] = true;

		for(p=0; p<n; p++){
			if(visit[p]==false && d[next] + w[next][p] < d[p]){
				d[p] = d[next] + w[next][p];
				parent[p] = next;
			}
		}
	}
}

int choose(int n)
{
	int i, j;
	int a, b, min;

	// for(i=0;i<n;i++){
	a = -1;
	b = -1;
	min = MAX;
	for(j=0;j<n;j++){
		if(visit[j]==false && d[j]<min){
			a = j;
			min = d[j];
		}
	}
	//if(a==-1) break;
	// if(a==-1) return;
	visit[a] = true;
	// }
	return a;
}




int Map(int n)
{
	int i, j;
	int p;
	int next;
	int min_time = 0;

	for(i=0;i<n;i++){
		visit[i] = false;
		d[i] = w[0][i];
		parent[i] = MAX;  	// NULL 
	}
	visit[0] = true;
	d[0] = 0;

	for(i=0;i<n-1;i++){
		next = choose(n);
		visit[next] = true;

		for(p=0; p<n; p++){
			if(visit[p]==false && d[next] + w[next][p] < d[p]){
				d[p] = d[next] + w[next][p];
				parent[p] = next;
			}
		}
	}	
}

int ImportantBus(int n)
{
	int i, j;
	int count = 0;

	for(i=0;i<n;i++){
		count = 0;
		for(j=0;j<n;j++){
			if(w[i][j] != MAX) count++;
		}
		if(count==1) break;
	}
	if(count == 1) cout << "Yes" << endl;
	else cout << "No" << endl;
}



//CreditExchange
//CreditExchange2




int main(void)
{
	string cmd;
	int v1, v2;
	int min_time;
	
	cin >> n;
	
	initial(n);
	
	while(cin >> cmd){
		if(cmd == "Add"){
			int w;
			float r;
			cin >> v1 >> v2 >> w >> r;
			Add(v1, v2, w, r);
		}else if(cmd == "Delete"){
			cin >> v1 >> v2;
			Delete(v1, v2);
		}else if(cmd == "Shortest"){
			cin >> v1 >> v2;
			Shortest(n, v1, v2);
			cout << d[v2] << endl;
		}
		else if(cmd == "Map"){
			min_time = Map(n);
		}else if(cmd == "ImportantBus"){
			ImportantBus(n);
		}else if(cmd == "CreditExchange"){
			int credit;
			cin >> v1 >> v2 >> credit;
			CredirExchange(v1, v2, credit);
		}else if(cmd == "CreditExchange2"){
			int credit, limit;
			cin >> v1 >> v2 >> credit >> limit;
			CreditExchange2(v1, v2, credit, limit);
		}
		// else if(cmd == "show") show(n);
	}
	
} 

// void show(int n)
// {
// 	int i, j;
// 	for(i=0;i<n;i++){
// 		for(j=0;j<n;j++){
// 			cout << w[i][j] << " " ;
// 		}
// 		cout << endl;
// 	}
// }
