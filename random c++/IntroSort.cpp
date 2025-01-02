#include <bits/stdc++.h>
#include <chrono>
#include <random>

const int INSERTION_SORT_THRESHOLD = 16;

void insertionSort(std::vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void introsortUtil(std::vector<int>& arr, int low, int high, int depthLimit) {
    while (high - low > INSERTION_SORT_THRESHOLD) {
        if (depthLimit == 0) {
            heapSort(arr, high - low + 1);
            return;
        }
        --depthLimit;
        int pivot = partition(arr, low, high);
        introsortUtil(arr, pivot + 1, high, depthLimit);
        high = pivot - 1;
    }
    insertionSort(arr, low, high);
}

void introSort(std::vector<int>& arr) {
    int n = arr.size();
    int depthLimit = 2 * log(n);
    introsortUtil(arr, 0, n - 1, depthLimit);
}

std::vector<int> generateRandomArray(int n, int m) {
    std::vector<int> arr(n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, m);
    for (int& x : arr) {
        x = dis(gen);
    }
    return arr;
}

int main() {
    int n, m;
    std::cout << "Enter the size of the array (n): ";
    std::cin >> n;
    std::cout << "Enter the maximum element size (m): ";
    std::cin >> m;

    std::vector<int> arr = generateRandomArray(n, m);

    auto start = std::chrono::high_resolution_clock::now();
    introSort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    //std::cout << "Sorted array is: \n";
    // for (const int& x : arr)
    //     std::cout << x << " ";
    std::cout << "\nTime taken to sort: " << duration.count() << " seconds" << std::endl;

    return 0;
}