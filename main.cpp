#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <fstream>

using namespace std;

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]

void merge(int array[], int const left, int const mid, int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	// Create temp arrays
	auto* leftArray = new int[subArrayOne];
	auto* rightArray = new int[subArrayTwo];

	// Copy data to temp arrays leftArray[] and rightArray[]
	for (auto i = 0; i < subArrayOne; i++) {
		leftArray[i] = array[left + i];
	}
	for (auto j = 0; j < subArrayTwo; j++) {
		rightArray[j] = array[mid + 1 + j];
	}
	auto indexOfSubArrayOne = 0; // Initial index of first sub-array
	auto indexOfSubArrayTwo = 0; // Initial index of second sub-array
	int indexOfMergedArray = left; // Initial index of merged array

	// Merge the temp arrays back into array[left..right]
	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	// Copy the remaining elements of
	// left[], if there are any
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	// Copy the remaining elements of
	// right[], if there are any
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end) return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

// Function to print an array
void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

// Function to print an array
void printArrayWithSingleOccurrenceOfTheElement(int A[], int size)
{
	int prev = A[0];
	cout << prev << " ";
	for (auto i = 1; i < size; i++) {
		if (A[i] != prev) {
			cout << A[i] << " ";
			prev = A[i];
		}
	}
	cout << endl;
}


// Driver code
int main()
{
	srand(time(NULL));
	int arr_size;
	cout << "Enter the size of array:";
	cin >> arr_size;

	int* arr = new int[arr_size];
	int* arr_old = new int[arr_size];

	for (int i = 0; i < arr_size; i++) {
		arr[i] = rand() % 100000000;  //Generate number between 0 to 99999999
		arr_old[i] = arr[i];
	}

	cout << "\nElements of the array:" << endl;

	printArray(arr, arr_size);

	// Record starting time
	auto start_time = chrono::high_resolution_clock::now();

	mergeSort(arr, 0, arr_size - 1);

	// Record ending time
	auto end_time = chrono::high_resolution_clock::now();

	cout << "\nSorted array is: \n";
	printArray(arr, arr_size);

	cout << "\nSorted array with a single occurrence of the element is: \n";
	printArrayWithSingleOccurrenceOfTheElement(arr, arr_size);

	// Calculate execution time in milliseconds
	auto duration_ms = chrono::duration_cast<chrono::microseconds>(end_time - start_time);

	// Print execution time
	cout << "\nExecution time: " << duration_ms.count() << " microseconds" <<endl;

	//Save the tests in .txt
	ofstream myfile("Test.txt");
	if (myfile.is_open())
	{
		myfile << "The size of array: " << arr_size;
		myfile << "\nExecution time: " << duration_ms.count() << " microseconds" << endl;

		myfile << "\nUnordered array: ";
		myfile << endl;
		for (int i = 0; i < arr_size; i++) {
			myfile << arr_old[i] << " ";
		}

		myfile << endl;
		myfile << "\nOrdered array: ";
		myfile << endl;
		for (int i = 0; i < arr_size; i++) {
			myfile << arr[i] << " ";
		}

		int prev = arr[0];
		myfile << endl;
		myfile << "\nOrdered array with single occurrence of the element: ";
		myfile << endl;
		for (int i = 0; i < arr_size; i++) {
			if (arr[i] != prev) {
				myfile << arr[i] << " ";
				prev = arr[i];
			}
		}
		myfile.close();
	}
	else {
		cout << "Unable to open file";
	}
	return 0;
}