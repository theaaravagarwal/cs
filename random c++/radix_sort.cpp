#include <vector>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

int getMax(const vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

void sort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);
    int count[10] = {0};
    for (int i=0; i<n; i++) count[(arr[i]/exp)%10]++;
    for (int i=1; i<10; i++) count[i] += count[i - 1];
    for (int i=n-1; i>=0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for (int i=0; i<n; i++) arr[i] = output[i];
}

void radixSort(vector<int>& arr) {
    int max = getMax(arr);
    for (int exp=1; max/exp>0; exp*=10) sort(arr, exp);
}

vector<int> generateRandomArray(int size, int maxValue) {
    vector<int> arr(size);
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> distr(0, maxValue);
    for (int i=0; i<size; ++i) {
        arr[i] = distr(eng);
    }
    return arr;
}

int main() {
    int size, maxValue;
    cout << "Enter the size of the array: ";
    cin >> size;
    cout << "Enter the maximum integer value in the array: ";
    cin >> maxValue;
    std::vector<int> arr = generateRandomArray(size, maxValue);
    auto start = std::chrono::high_resolution_clock::now();
    radixSort(arr);
    auto end = std::chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}