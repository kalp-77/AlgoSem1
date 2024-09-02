#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

long long count_bubble;
// Function to perform Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
            else count_bubble++;
        }
    }
}

int main() {
    ofstream outFile("bubble_avg_case.txt");  // Create and open a text file to write execution times
    ofstream bubble("bubble.txt"); 


    int initial_size = 10;
    int max_iterations = 30;  // You can change this to control the number of iterations

    for (int i = 0; i < max_iterations; ++i) {
        int n = initial_size * 100 * (i+1);

        // Generate a random array of size n
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10000;
        }

        auto start = high_resolution_clock::now();
        bubbleSort(arr);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        // Write the input size and execution time to the file
        outFile << n << " " << duration.count() << endl;
        bubble << n << " " << count_bubble << endl;

        cout << "Sorted array of size " << n << " in " << duration.count() << " ms" << endl;
    }

    outFile.close();
    return 0;
}
