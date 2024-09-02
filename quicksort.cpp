#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

// Quick Sort Partition function
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    ofstream outFile("quick_worst_case.txt");
    int initial_size = 100;  // Initial array size
    int max_iterations = 10;  // Number of iterations

    for (int i = 0; i < max_iterations; ++i) {
        int n = initial_size * 100 * (i+1);  // Increase input size by a factor of 1000

        // Generate a random array of size n
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

	sort(arr.begin(), arr.end());
        auto start = high_resolution_clock::now();
        quickSort(arr, 0, n - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        outFile << n << " " << duration.count() << endl;

        // Print the result to console (optional)
        cout << "Sorted array of size " << n << " in " << duration.count() << " ms" << endl;
    }

    outFile.close();  // Close the output file
    return 0;
}
