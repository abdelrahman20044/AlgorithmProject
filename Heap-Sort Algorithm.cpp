#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void maxHeapify(vector<int>& arr, int heapSize, int rootIndex) {
    int largest = rootIndex;
    int leftChild = 2 * rootIndex + 1;
    int rightChild = 2 * rootIndex + 2;

    if (leftChild < heapSize && arr[leftChild] > arr[largest])
        largest = leftChild;

    if (rightChild < heapSize && arr[rightChild] > arr[largest])
        largest = rightChild;

    if (largest != rootIndex) {
        swap(arr[rootIndex], arr[largest]);
        maxHeapify(arr, heapSize, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        maxHeapify(arr, i, 0);
    }
}

int main() {
    vector<int> arr = { 12, 11, 13, 5, 6, 7 };
    heapSort(arr);

    cout << "Sorted array: ";
    for (int num : arr)
        cout << num << " ";
    cout << endl;

    return 0;
}
