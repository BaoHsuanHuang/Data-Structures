#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(int *arr, int front, int end){
    int pivot = arr[end];
    int i = front -1;  // int i┮Τpivot计 ┮Θ计程竚
    for (int j = front; j < end; j++) {  // 眖front浪琩end-1(end琌pivot)
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);  // ゑpivot计玡
        }
    }
    i++;
    swap(&arr[i], &arr[end]);  // ゑpivot  pivot  ゑpivot 
    return i;
}
void QuickSort(int *arr, int front, int end){
    if (front < end) {
        int pivot = Partition(arr, front, end);
        QuickSort(arr, front, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
}
void PrintArray(int *arr, int size){
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {

    int n = 9;
    int arr[] = {9, 4, 1, 6, 7, 3, 8, 2, 5};
    cout << "original:\n";
    PrintArray(arr, n);

    QuickSort(arr, 0, n-1);

    cout << "sorted:\n";
    PrintArray(arr, n);
    return 0;
}
