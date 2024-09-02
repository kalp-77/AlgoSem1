#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cmath>

using namespace std;
using namespace std::chrono;

// Function to heapify a subtree rooted at index i
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap Sort function
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(arr[0], arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

int main() {
    ofstream outFile("heap_avg_case.txt");  // Create a text file to write execution times

    int initial_size = 100;  // Initial array size
    int max_iterations = 10;   // Number of iterations (adjust as needed)

    for (int iter = 0; iter < max_iterations; ++iter) {
        int n = initial_size * 100 * (iter+1);  // Increase input size by a factor of 1000

        // Limit the size to prevent excessive memory usage (adjust as needed)
        if (n > 10000000) {
            break;
        }

        // Generate a random array of size n
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

        // Record the start time
        auto start = high_resolution_clock::now();

        // Perform heap sort
        heapSort(arr);

        // Record the end time
        auto stop = high_resolution_clock::now();

        // Calculate the duration
        auto duration = duration_cast<milliseconds>(stop - start);

        // Write the input size and execution time to the file
        outFile << n << " " << duration.count() << endl;

        // Print the result to console (optional)
        cout << "Sorted array of size " << n << " in " << duration.count() << " ms" << endl;
    }

    outFile.close();  // Close the output file
    return 0;
}
