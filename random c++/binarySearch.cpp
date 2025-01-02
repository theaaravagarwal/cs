#include <bits/stdc++.h>

void search(vector<int>& arr, int target) {
    int left = 0, right = arr.size()-1;
    while (left<=right) {
        int mid = left+(right-left)/2;
        if (arr[mid] == target) {
            cout << "Element found at index: " << mid << "\n";
            return;
        } else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    cout << "Element not found\n";
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13, 15};
    int target = 7;
    search(arr, target);
    return 0;
}