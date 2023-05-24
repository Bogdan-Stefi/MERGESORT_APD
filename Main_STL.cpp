#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <chrono>
#include <random>
#include <fstream>

template <typename T>
void merge(std::vector<T>& arr, std::vector<T>& left, std::vector<T>& right)
{
    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }
    while (i < left.size())
    {
        arr[k++] = left[i++];
    }
    while (j < right.size())
    {
        arr[k++] = right[j++];
    }
}

template <typename T>
void mergeSort(std::vector<T>& arr)
{
    if (arr.size() < 2)
        return; // Base case: array has 0 or 1 element

    size_t mid = arr.size() / 2;
    std::vector<T> left(arr.begin(), arr.begin() + mid);
    std::vector<T> right(arr.begin() + mid, arr.end());

    mergeSort(left); // Recursively sort left half
    mergeSort(right); // Recursively sort right half

    merge(arr, left, right); // Merge sorted halves
}

int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 1000);

    const int numElements = 1000000; // Numărul de elemente dorit

    std::vector<int> arr(numElements);
    for (int i = 0; i < numElements; ++i)
    {
        arr[i] = dis(gen); // Generare valori aleatoare
    }

    //std::cout << "Array before sorting: ";
    //for (const auto& num : arr)
    //{
    //    std::cout << num << " ";
    //}
    std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    std::sort(std::execution::par, arr.begin(), arr.end());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    //std::cout << "Array after sorting: ";
    //for (const auto& num : arr)
    //{
    //    std::cout << num << " ";
    //}
    //std::cout << std::endl;

    std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

    std::ofstream outputFile("sorted_array.txt");
    if (outputFile.is_open())
    {
        for (const auto& num : arr)
        {
            outputFile << num << " ";
        }
        outputFile.close();
        std::cout << "Sorted array saved to file: sorted_array.txt" << std::endl;
    }
    else
    {
        std::cerr << "Failed to open file for writing." << std::endl;
    }

    return 0;
}
