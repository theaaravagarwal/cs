#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back 
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], 
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], 
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Function to print a vector
void printVector(vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Driver code
int main() {
    int n, maxInt;
    cout << "Enter the size of the vector: ";
    cin >> n;
    cout << "Enter the maximum integer value: ";
    cin >> maxInt;

    vector<int> arr(n);
    
    // Seed for random number generation
    srand(static_cast<unsigned int>(time(0)));

    // Generate random integers for the vector
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (maxInt + 1); // Random number between 0 and maxInt
    }

    cout << "Given vector is \n";
    //printVector(arr);

    // Start timing
    auto start = chrono::high_resolution_clock::now();
    
    mergeSort(arr, 0, n - 1);
    
    // End timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\nSorted vector is \n";
    //printVector(arr);
    
    // Output the time taken
    cout << "Runtime: " << duration.count() << " seconds" << endl;

    return 0;
}