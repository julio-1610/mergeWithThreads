// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define SIZE 100
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]

int arr[SIZE];
struct index {
	int left;
	int right;
};

void merge(int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays
	// L[] and R[]
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back
	// into arr[l..r]
	// Initial index of first subarray
	i = 0;

	// Initial index of second subarray
	j = 0;

	// Initial index of merged subarray
	k = l;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		} else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements
	// of L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

void* threadSort(void* arg) {
	struct index data = *((struct index*) arg);
	int l = data.left;
	int r = data.right;

	if(l < r) {
		int mid = l + (r - l)/2;

		pthread_t t1, t2;

		struct index i1;
		i1.left = l;
		i1.right = mid;

		struct index i2;
		i2.left = mid + 1;
		i2.right = r;

		pthread_create(&t1, NULL, threadSort, &i1);
		pthread_create(&t2, NULL, threadSort, &i2);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);

		merge(l, mid, r);
	}
}


void* threadTime(void* arg) {
	//CODE HERE
}

// UTILITY FUNCTIONS
// Function to print an array
void printArray(int A[], int size) {
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

void generateRandomArray() {
	for(int i = 0; i < SIZE; i++) 
		arr[i] = rand() % 100; //Números alaeatorios de 0 a 100
}

// Driver code
int main() {
	pthread_t t;
	generateRandomArray();
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	struct index data;
	data.left = 0;
	data.right = SIZE - 1;

	printf("Given array is \n");
	printArray(arr, arr_size);

	pthread_create(&t, NULL, threadSort, &data);
	pthread_join(t, NULL);

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	return 0;
}
