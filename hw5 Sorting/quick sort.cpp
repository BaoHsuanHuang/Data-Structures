#include <iostream>
using namespace std;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
int Partition(int *arr, int front, int end){
    int pivot = arr[end];
    int i = front -1;  // int i為所有小於pivot的數 所形成的數列的「最後位置」
    for (int j = front; j < end; j++) {  // 從front檢查到end-1(因為end是pivot自己)
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);  // 放到比pivot大的數的「前面」
        }
    }
    i++;
    swap(&arr[i], &arr[end]);  // 比pivot小  pivot  比pivot大 
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
