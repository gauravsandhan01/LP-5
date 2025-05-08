#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sequential Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// Parallel Bubble Sort using OpenMP (Odd-Even Sort)
void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; i++) 
    {
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2) 
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void printArray(const vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < min(n, 10); i++)
        cout << arr[i] << " ";
    cout << (n > 10 ? "... (only first 10 shown)" : "") << endl;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> data(n);
    srand(time(0));
    for (int i = 0; i < n; i++)
        data[i] = rand() % 10000;

    // Copies for testing
    vector<int> bubbleSeq = data;
    vector<int> bubblePar = data;

    double start, end;

    // Sequential Bubble Sort
    start = omp_get_wtime();
    bubbleSort(bubbleSeq);
    end = omp_get_wtime();
    cout << "\nSequential Bubble Sort Time: " << end - start << " seconds\n";
    printArray(bubbleSeq);

    // Parallel Bubble Sort
    start = omp_get_wtime();
    parallelBubbleSort(bubblePar);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << " seconds\n";
    printArray(bubblePar);

    return 0;
}
