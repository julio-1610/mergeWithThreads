// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h> 
# include <time.h>

#define SIZE 1000
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

void recursiveMergeSort(int l, int r) {
	if(l < r) {
		int mid = l + (r - l)/2;

		recursiveMergeSort(l, mid);
		recursiveMergeSort(mid + 1, r);

		merge(l, mid, r);
	}
}

// Driver code
int main() {
	pthread_t t;
	generateRandomArray();
	int arr_size = sizeof(arr) / sizeof(arr[0]);
	struct index data;
	data.left = 0;
	data.right = SIZE - 1;

    printf("Size of array: %d \n", SIZE);

    // --------------------------------------------------------
    struct timeval start, finish;
    unsigned int ut0, ut1;
	


	gettimeofday(&start, NULL);
    pthread_create(&t, NULL, threadSort, &data);
    gettimeofday(&finish, NULL);
    
	pthread_join(t, NULL);
	

    ut0 = start.tv_sec * 1000000 + start.tv_usec;
    ut1 = finish.tv_sec * 1000000 + finish.tv_usec;

    printf("Time: %d microseconds - hilos\n", (ut1 - ut0));


    // --------------------------------------------------------
    
    generateRandomArray();

    // ---------------------------------------------------------
    
    struct timeval start2, finish2;
    unsigned int ut0R, ut1R;

	
	gettimeofday(&start2, NULL);
    recursiveMergeSort(0, SIZE - 1);
    gettimeofday(&finish2, NULL);


    ut0R = start2.tv_sec * 1000000 + start2.tv_usec;
    ut1R = finish2.tv_sec * 1000000 + finish2.tv_usec;


    printf("Time: %d microseconds - recursivo\n", (ut1R - ut0R));
	return 0;
}
