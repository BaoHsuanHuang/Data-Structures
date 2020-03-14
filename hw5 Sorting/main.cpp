#include <iostream>
#include <math.h>

using namespace std;

long long int A[1000000];
long long int B[1000000];
long long int C[1000000];


long long int merge(long long int tmp[], long long int left, long long int mid, long long int right) 
{ 
    long long int i, j, k; 
    long long int inv_count = 0; 
    i = left;
    j = mid;
    k = left; 
    while((i <= mid - 1) && (j <= right)){ 
        if (A[i] <= A[j]) { 
            tmp[k++] = A[i++]; 
        } 
        else { 
            tmp[k++] = A[j++]; 
            inv_count = inv_count + (mid - i); 
        } 
    } 
    while (i <= mid - 1) 
        tmp[k++] = A[i++]; 
    while (j <= right) 
        tmp[k++] = A[j++]; 
    for (i = left; i <= right; i++) 
        A[i] = tmp[i]; 
    return inv_count; 
}

long long int _mergeSort(long long int tmp[], long long int left, long long int right) 
{ 
    long long int mid, inv_count = 0; 
    if(right>left){ 
        mid = (right + left) / 2; 
        inv_count += _mergeSort(tmp, left, mid); 
        inv_count += _mergeSort(tmp, mid + 1, right); 
        inv_count += merge(tmp, left, mid + 1, right); 
    } 
    return inv_count; 
}

long long int MergeSort(long long int n) 
{ 
    long long int tmp[n]; 
    return _mergeSort(tmp, 0, n-1); 
} 




void countSort(long long int n, long long int r, long long int exp) 
{ 
    long long int output[n]; // output array 
    long long int i, count[r] = {0}; 
    for (i = 0; i < n; i++) 
        count[ (B[i]/exp)%r ]++; 
    for (i = 1; i < r; i++) 
        count[i] += count[i - 1]; 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (B[i]/exp)%r ] - 1] = B[i]; 
        count[ (B[i]/exp)%r ]--; 
    } 
    for (i = 0; i < n; i++){
        B[i] = output[i];
	}
	cout << B[0] << " " << B[n-1] << endl;
} 
  
void RadixSort(long long int n, long long int r, long long int m) 
{ 
	long long int exp;
    for (exp = 1; m/exp > 0; exp *= r){
    	countSort(n, r, exp); 
	}
} 


int main()
{
	long long int n, r;
	long long int inversion_pair = 0;
	long long int max = 0;
	long long int max_index = 0;
	long long int max2;
	long long int count = 0;
	
	while(cin >> n >> r){
		inversion_pair = 0;
		max = 0;
		max_index = 0;
		max2 = 0;
		for(long long int i=0; i<n ;i++){
			cin >> A[i];
			B[i] = A[i];
			if(A[i] > max){
				max = A[i];
				max_index = i;
				max2 = A[i];//add
			}
		}
		inversion_pair = MergeSort(n);
		cout << inversion_pair << endl;
		
		RadixSort(n, r, max2);	
//		for(int i=0; i<n; i++){
//			long long int num = B[i];
//			long long int p = 0;
//			long long int change = 0;
//			while(num > 0){
//				long long int a = num % r;
//				change += a * pow(10, p);
//				num = num / r;
//				p++;
//			}
//			C[i] = change;
//		}
//		max2 = C[max_index];	
	}
	return 0;
} 





