#include <iostream>
#include <math.h>

using namespace std;

typedef struct _pair{
	long long int original;
	long long int change;
}Pair;

Pair A[1000000];


void countSort(int n, long long int exp) 
{ 
    long long int output[n]; // output array 
    int i, count[10] = {0}; 
    for (i = 0; i < n; i++) 
        count[ (A[i].change/exp)%10 ]++; 

    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (A[i].change/exp)%10 ] - 1] = A[i].change; 
        count[ (A[i].change/exp)%10 ]--; 
    } 
  
    for (i = 0; i < n; i++) 
        A[i].change = output[i];
		 
	
//    cout << A[0].original << " " << A[n-1].original;
} 
  
void radixsort(int n, int m) 
{ 
  
//    int m = getMax(arr, n); 

	long long int exp;
    for (exp = 1; m/exp > 0; exp *= 10){
    	countSort(n, exp); 
	}
	
        
} 
//void BucketSort(int n, int radix, int count)
//{
//	Pair tmp[radix][1000000] = {0};
//	int order[radix] = {0};
//	
//	long long int power = 1;
//	while(count>0){
//		for(int i=0; i<n; i++){
//			long long int lsd = (A[i].change/power)%10;
//			tmp[lsd][order[lsd]] = A[i];
////			tmp[order[lsd]][lsd] = A[i];
//			order[lsd]++;
//		}
//		int k=0;
//		for(int i=0; i<n ;i++){
//			if(order[i]!=0){
//				int j;
//				for(j=0; j<order[i]; j++){
//					A[k] = tmp[i][j];
//					k++;
//				}
//			}
//			order[i] = 0;
//		}
//		cout << A[0].original << " " << A[n-1].original << endl;
//		power *= 10;
//		count--;
//	}
//}





 

int merge(long long int temp[], int left, int mid, int right) 
{ 
    int i, j, k; 
    int inv_count = 0; 
  
    i = left;
    j = mid;
    k = left; 
    while ((i <= mid - 1) && (j <= right)) { 
        if (A[i].original <= A[j].original) { 
            temp[k++] = A[i++].original; 
        } 
        else { 
            temp[k++] = A[j++].original; 
            inv_count = inv_count + (mid - i); 
        } 
    } 

    while (i <= mid - 1) 
        temp[k++] = A[i++].original; 

    while (j <= right) 
        temp[k++] = A[j++].original; 
  
    for (i = left; i <= right; i++) 
        A[i].original = temp[i]; 
    return inv_count; 
}

int _mergeSort(long long int temp[], int left, int right) 
{ 
    int mid, inv_count = 0; 
    if (right > left) { 
        mid = (right + left) / 2; 
  
        inv_count += _mergeSort(temp, left, mid); 
        inv_count += _mergeSort(temp, mid + 1, right); 
  
        inv_count += merge(temp, left, mid + 1, right); 
    } 
    return inv_count; 
}

int mergeSort(int array_size) 
{ 
    long long int temp[array_size]; 
    return _mergeSort(temp, 0, array_size - 1); 
} 


int main()
{
	int n, r;
	int ans = 0;
	long long int max = 0;
	long long int max2 = 0;
	int count = 0;
	
	cin >> n >> r;
	for(int i=0; i<n ;i++){
		cin >> A[i].original;
		if(A[i].original > max){
			max = A[i].original;
			max2 = A[i].original;
		}
	}
//	ans = inversion_pair(n);
	ans = mergeSort(n);
	cout << ans << endl;
	
	while(max>0){
		long long int a = max % r;
		max = max/r;
		count++;
	}
	
	for(int i=0; i<n; i++){
		long long int num = A[i].original;
		long long int p = 0;
		long long int change = 0;
		while(num > 0){
			long long int a = num % r;
			change += a * pow(10, p);
			num = num / r;
			p++;
		}
		A[i].change = change;
		cout << A[i].change << "!" << endl; 
	}
	radixsort(n, max2);
//	BucketSort(n, r, count);
	return 0;
} 
















// wrong
//int inversion_pair(int n)
//{
//	int i=0;
//	int count=0;
//	while(i<n-1){
//		for(int j=i+1; j<n ;j++){
//			if(A[j].original < A[i].original) count++;
//		}
//		i++;
//	}
//	return count;
//}
