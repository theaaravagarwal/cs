#include <iostream>
using namespace std;

int main() {
    //getting inputs for size of arrs
    int a, b, f;
    cin >> a >> b >> f;
    long long arr1[a][b];
    long long arr2[a][b];
    memset(arr1, rand()%f, sizeof(arr1));
    memset(arr2, rand()%f, sizeof(arr2));

    //printing arr1
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        for (int j = 0; j < sizeof(arr1[i]) / sizeof(arr1[i][0]); j++) {
            std::cout << arr1[i][j] << " ";
        }
        cout << endl;
    }

    //printing arr2
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++) {
        for (int j = 0; j < sizeof(arr2[i]) / sizeof(arr2[i][0]); j++) {
            std::cout << arr2[i][j] << " ";
        }
        cout << endl;
    }
    //adding arr1 to arr2
    for (int i = 0; i < sizeof(arr1) / sizeof(arr1[0]); i++) {
        for (int j = 0; j < sizeof(arr1[i]) / sizeof(arr1[i][0]); j++) {
            arr2[i][j] *= arr1[i][j];
        }
    }

    //printing arr2
    for (int i = 0; i < sizeof(arr2) / sizeof(arr2[0]); i++) {
        for (int j = 0; j < sizeof(arr2[i]) / sizeof(arr2[i][0]); j++) {
            std::cout << arr2[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}