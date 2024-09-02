#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

// Merge function to merge two halves
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Merge Sort function
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    ofstream outFile("merge_avg_case.txt");  // Create a text file to write execution times
    if (!outFile) {
        cerr << "Error creating file!" << endl;
        return 1;
    }
    int initial_size = 100;  // Initial array size
    int max_iterations = 10;  // Number of iterations

    for (int i = 0; i < max_iterations; ++i) {
        int n = initial_size * 100 * (i+1);  // Increase input size by factor of 1000

        // Generate a random array of size n
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        outFile << n << " " << duration.count() << endl;

        cout << "Sorted array of size " << n << " in " << duration.count() << " ms" << endl;
    }

    outFile.close();  // Close the output file
    return 0;
}
