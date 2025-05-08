#include <iostream>
#include <cuda_runtime.h>

__global__ void add(int *a, int *b, int *c, int n) {
    int i = threadIdx.x + blockIdx.x * blockDim.x;
    if (i < n) c[i] = a[i] + b[i];
}

int main() {
    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    size_t size = n * sizeof(int);
    int *a = (int*)malloc(size);
    int *b = (int*)malloc(size);
    int *c = (int*)malloc(size);

    std::cout << "Enter " << n << " elements for array A:\n";
    for (int i = 0; i < n; i++) std::cin >> a[i];

    std::cout << "Enter " << n << " elements for array B:\n";
    for (int i = 0; i < n; i++) std::cin >> b[i];

    int *d_a, *d_b, *d_c;
    cudaMalloc(&d_a, size);
    cudaMalloc(&d_b, size);
    cudaMalloc(&d_c, size);

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    add<<<(n + 255) / 256, 256>>>(d_a, d_b, d_c, n);
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    std::cout << "Result (A + B):\n";
    for (int i = 0; i < n; i++) std::cout << c[i] << " ";
    std::cout << std::endl;

    cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);
    free(a); free(b); free(c);
    return 0;
}
