#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <exception>

using namespace std;
using namespace std::chrono;

// Function to get the maximum value in the array
int getMax(const vector<int>& arr) {
    int max_val = arr[0];
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] > max_val)
            max_val = arr[i];
    return max_val;
}

// Counting sort used by Radix Sort
void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n); // Create an output array of the same size as arr
    int count[10] = {0}; // Create a count array to store the count of occurrences

    // Store the count of occurrences
    for (int i = 0; i < n; i++) {
        int index = (arr[i] / exp) % 10;
        count[index]++;
    }

    // Change count[i] so that it now contains the actual position of the digit in output[]
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    // Build the output array
    for (int i = n - 1; i >= 0; i--) {
        int index = (arr[i] / exp) % 10;
        output[count[index] - 1] = arr[i];
        count[index]--;
    }

    // Copy the output array to arr, so that arr now contains sorted numbers according to the current digit
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

// Radix Sort function
void radixSort(vector<int>& arr) {
    int max_val = getMax(arr);

    // Perform counting sort for every digit
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

int main() {
    ofstream outFile("radix_worst_case.txt");  // Create a text file to write execution times

    int initial_size = 100;  // Initial array size
    int max_iterations = 10;   // Reduce iterations to avoid running out of memory (adjust as needed)

    for (int iter = 0; iter < max_iterations; ++iter) {
        int n = initial_size * 100 * (iter+1);  // Increase input size by a factor of 10

        // Catch any bad allocation errors (e.g., when memory is exhausted)
            // Generate a random array of size n
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                arr[i] = rand() % 10000000;
            }

            // Record the start time
            auto start = high_resolution_clock::now();

            // Perform radix sort
            radixSort(arr);

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
