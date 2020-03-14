#include <iostream>

using namespace std;

int main(void)
{
	int x, y;
	int i;
	int num;
	int count=0;
	int max = 0;
	int cal;
	
	while(cin >> x >> y){
		max = 0;
		for(num=x ; num<=y ; num++){
			count = 0;
			cal = num;
			
			while(cal != 1){
				if(cal%2 == 0){
					cal = cal / 2;
					count++;
				}else if(cal%2 == 1){
					cal = cal*3 + 1;
					count++;
				}
			}
			count++;
			if(count>max) max = count;
		}
		cout << max << endl;	
	}
} 
