#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int minVal = arr[0], maxVal = arr[0], sum = 0;
    double avg = 0.0;

    #pragma omp parallel for reduction(min:minVal) reduction(max:maxVal) reduction(+:sum)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
        sum += arr[i];
    }

    avg = sum / (double)n;

    cout << "Min: " << minVal << "\n";
    cout << "Max: " << maxVal << "\n";
    cout << "Sum: " << sum << "\n";
    cout << "Average: " << avg << "\n";

    return 0;
}
