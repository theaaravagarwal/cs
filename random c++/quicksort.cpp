#include <bits/stdc++.h>
#include <vector>
#include <iostream>
using namespace std;

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);
        if (arr[low] > arr[high]) swap(arr[low], arr[high]);
        if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);
        int pivot = arr[mid];
        swap(arr[mid], arr[high]);
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(vector<int>& arr) {
    for (int i : arr) {
        cout << i << " ";
    }
    cout << endl;
}

void generateRandomArray(vector<int>& arr, int size, int max) {
    for (int i = 0; i < size; i++) {
        arr.push_back(rand() % max + 1);
    }
}

int main() {
    vector<int> arr;
    int n;
    cout << "Enter size: " << endl;
    cin >> n;
    int x;
    cout << "Enter max value: " << endl;
    cin >> x;
    generateRandomArray(arr, n, x);
    cout << "Unsorted array: ";
    printArray(arr);
    cout << endl;
    quickSort(arr, 0, n - 1);
    cout << "Sorted array: ";
    printArray(arr);
    return 0;
}
