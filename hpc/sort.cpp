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
    for (int i = 0; i < n; i++) {
        #pragma omp parallel for
        for (int j = i % 2; j < n - 1; j += 2) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

// Merge two halves
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;
    while (i <= mid && j <= right)
        temp.push_back(arr[i] <= arr[j] ? arr[i++] : arr[j++]);
    while (i <= mid) temp.push_back(arr[i++]);
    while (j <= right) temp.push_back(arr[j++]);
    copy(temp.begin(), temp.end(), arr.begin() + left);
}


// Sequential Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// Parallel Merge Sort using OpenMP
void parallelMergeSort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left >= right) return;
    int mid = (left + right) / 2;

    if (depth < 4) {
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, left, mid, depth + 1);
            #pragma omp section
            parallelMergeSort(arr, mid + 1, right, depth + 1);
        }
    } else {
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
    }

    merge(arr, left, mid, right);
}


int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    
    vector<int> data(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
        cin >> data[i];
    
    // Copies for testing
    vector<int> bubbleSeq = data;
    vector<int> bubblePar = data;
    vector<int> mergeSeq = data;
    vector<int> mergePar = data;

    double start, end;

    // Sequential Bubble Sort
    start = omp_get_wtime();
    bubbleSort(bubbleSeq);
    end = omp_get_wtime();
    cout << "\nSequential Bubble Sort Time: " << end - start << " seconds\n";
   
    // Parallel Bubble Sort
    start = omp_get_wtime();
    parallelBubbleSort(bubblePar);
    end = omp_get_wtime();
    cout << "Parallel Bubble Sort Time: " << end - start << " seconds\n";
   

    // Sequential Merge Sort
    start = omp_get_wtime();
    mergeSort(mergeSeq, 0, n - 1);
    end = omp_get_wtime();
    cout << "\nSequential Merge Sort Time: " << end - start << " seconds\n";
   

    // Parallel Merge Sort
    start = omp_get_wtime(); 
    parallelMergeSort(mergePar, 0, n - 1);
    end = omp_get_wtime();
    cout << "Parallel Merge Sort Time: " << end - start << " seconds\n";
    

    return 0;
}


/* vector<int> data(n);
    cout << "Choose input method:\n1. Enter manually\n2. Generate random numbers\nEnter choice (1/2): ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter " << n << " elements:\n";
        for (int i = 0; i < n; i++)
            cin >> data[i];
    } else {
        srand(time(0));
        for (int i = 0; i < n; i++)
            data[i] = rand() % 10000;
        cout << "Random data generated.\n"; //
    } */