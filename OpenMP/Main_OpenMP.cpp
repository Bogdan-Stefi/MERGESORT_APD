#include <iostream>
#include <cstring>
#include <cstdlib>
#include <omp.h>

#define MAX_SIZE 100000

//Function for creating an input array||Update according to your needs
void generate_list(int* x, int n) {
    for (int i = 0; i < n; i++)
        x[i] = i;
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        int t = x[i];
        x[i] = x[j];
        x[j] = t;
    }
}

void print_list(int* x, int n) {
    for (int i = 0; i < n; i++) {
        std::cout << x[i] << " ";
    }
}

//Merging 2 sorted subarrays into one tmp array
void merge(int* X, int n, int* tmp) {
    int i = 0;
    int j = n / 2;
    int ti = 0;
    //i will iterate till first half and j will iterate for the second half of the array
    while (i < n / 2 && j < n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        }
        else {
            tmp[ti] = X[j];
            ti++;
            j++;
        }
    }
    while (i < n / 2) {
        tmp[ti] = X[i];
        ti++;
        i++;
    }
    while (j < n) {
        tmp[ti] = X[j];
        ti++;
        j++;
    }
    //Copy the sorted array tmp back to X (Original array)
    std::memcpy(X, tmp, n * sizeof(int));
} // end of merge()

void mergesort(int* X, int n, int* tmp)
{
    if (n < 2) return;

#pragma omp task firstprivate (X, n, tmp)
    mergesort(X, n / 2, tmp);

#pragma omp task firstprivate (X, n, tmp)
    mergesort(X + (n / 2), n - (n / 2), tmp);

    //Wait for both parallel tasks to complete execution
#pragma omp taskwait

/* merge sorted halves into sorted list */
    merge(X, n, tmp);
}

int main()
{
    int n = 500000;
    double start, stop;
    int data[MAX_SIZE], tmp[MAX_SIZE];

    generate_list(data, n);
    std::cout << "List Before Sorting..." << std::endl;
    print_list(data, n);
    start = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
#pragma omp task firstprivate (data, n, tmp)
            mergesort(data, n, tmp);
        }
    }

    stop = omp_get_wtime();
    std::cout << "\nList After Sorting..." << std::endl;
    print_list(data, n);
    std::cout << "\nTime: " << (stop - start) * 1000000 << " microseconds" << std::endl;
}