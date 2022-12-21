// C program for Merge Sort
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h> 
# include <time.h>

#define SIZE 100
// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]

int arr[SIZE];
struct index {
	int left;
	int right;
};

struct mergeInfor {
	int left;
	int right;
	int mid;
	sem_t my_semaphore;
};

void* threadMerge(void * args){
	struct mergeInfor data = *((struct mergeInfor*) args);
	int l = data.left;
	int r = data.right;
	int m = data.mid;
	sem_t my_semaphore = data.my_semaphore;

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

	// creamo sun semaforo 
	// sem_t mutex1;
	// sem_t mutex2;

	// inicializamos el semaforo con valor 1
	// int rc1 = sem_init(&mutex1, 0, 0);
	// int rc2 = sem_init(&mutex1, 0, 0);

	if(l < r) {
		int mid = l + (r - l)/2;

		pthread_t t1, t2;
		//pthread merge;

		struct index i1;
		i1.left = l;
		i1.right = mid;

		struct index i2;
		i2.left = mid + 1;
		i2.right = r;


		pthread_create(&t1, NULL, threadSort, &i1);
		// signal(&mutex1);
		//sem_post(&mutex1);

		pthread_create(&t2, NULL, threadSort, &i2);
		// sem_post(&mutex2);

		
		// // llamamos para que se haga merge
		// struct mergeInfor m1;
		// m1.left = l;
		// m1.right = r;
		// m1.mid = mid;
		// m1.my_semaphore = mutex1;
		
		// // 
		// // llamamos para que se haga merge
		// pthread_create(&merge, NULL, threadMerge, &m1);


		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
		//pthread_join(merge, NULL);

		merge(l, mid, r);
	}
	//printf("l = %d, r = %d, llego al mas pequeno \n", l, r);
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
		//printf("l = %d, m =  %d, r = %d \n", l,mid, r);

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

	// merge con hilos

	// strct for time
	struct timeval t0, t1;
	// struct timespec start, finish;

	// double elapsed;

	unsigned int ut1, ut0;

	printf("Pthread - Given array is \n");
	printArray(arr, arr_size);

	gettimeofday(&t0 , NULL);
	// clock_gettime(CLOCK_MONOTONIC, &start);

	pthread_create(&t, NULL, threadSort, &data);
	// clock_gettime(CLOCK_MONOTONIC, &finish);

	gettimeofday(&t1 , NULL);
	pthread_join(t, NULL);
	
	// elapsed = (finish.tv_sec - start.tv_sec);
	//elapsed += (finish.tv_nsec - start.tv_nsec) ;
	
	ut1 = t1. tv_sec *1000000+ t1. tv_usec ;
	ut0 = t0. tv_sec *1000000+ t0. tv_usec ;

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	printf ("%d microsegundos - hilos \n", (ut1 - ut0)) ;


	// merge recursivo
	// strct for time
	// struct timespec startR, finishR;

	// double elapsedR;

	struct timeval t0R, t1R;
	unsigned int ut1R, ut0R;

	printf("\nrecursive - Given array is \n");
	printArray(arr, arr_size);
	
	gettimeofday(&t0R , NULL);
	// clock_gettime(CLOCK_MONOTONIC, &startR);

	recursiveMergeSort(0, SIZE - 1);
	// clock_gettime(CLOCK_MONOTONIC, &finishR);

	gettimeofday(&t1R , NULL);
	pthread_join(t, NULL);

	// elapsedR = (finishR.tv_sec - startR.tv_sec);
	//elapsedR += (finishR.tv_nsec - startR.tv_nsec) ;

	ut1R = t1R. tv_sec *1000000+ t1R. tv_usec ;
	ut0R = t0R. tv_sec *1000000+ t0R. tv_usec ;

	printf("\nSorted array is \n");
	printArray(arr, arr_size);
	printf (" %d microsegundos - recursivo \n", (ut1R - ut0R)) ;

	return 0;
}
