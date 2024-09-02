#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

// Insertion Sort function
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    ofstream outFile("insertion_worst_case.txt");  // Create a text file to write execution times


    int initial_size = 100;  // Initial array size
    int max_iterations = 10;   // Number of iterations (adjust as needed)

    for (int iter = 0; iter < max_iterations; ++iter) {
        int n = initial_size * 100 * (iter+1);  // Increase input size by a factor of 1000


        // Generate a random array of size n
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

	sort(arr.rbegin(), arr.rend());
        // Record the start time
        auto start = high_resolution_clock::now();

        // Perform insertion sort
        insertionSort(arr);

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
