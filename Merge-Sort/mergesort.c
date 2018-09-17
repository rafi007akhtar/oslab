/** Perform MERGESORT operation on an array recursively, using 3 threads in each recursion:
 * thread1 -- to perform sorting on the first half of the array
 * thread2 -- to perform sorting on the second half of the array
 * thread3 -- to merge the above two sorted arrays
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *arr; // global array

void *mergeSort(void*);
void *merge(void*);

int main(void)
{
	int n, i;
	printf("Enter n: "); // number of elements
	scanf("%d", &n);
	arr = (int *) malloc(n*sizeof(int));

	printf("Enter %d unsorted elements:\n", n);
	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	
	int params[2]; // parameters (begin, end) to pass along to the sorting function
	params[0] = 0; // begin 
	params[1] = n-1; // end

	pthread_t thread;
	pthread_create(&thread, NULL, mergeSort, params); // sort the elements
	pthread_join(thread, NULL);

	printf("Sorted array:\n"); // print the sorted array
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

void *mergeSort(void *parameters)
{
	/** Divide the array into halves, each one gets sorted with its own thread, and then both merge using another thread, recursively */

	int *params = (int *) parameters;
	int begin = params[0];
	int end = params[1];
	int sortParams[2]; // parameters to pass to the mergeSort function in recursion
	int mergeParams[3]; // parameters to pass to the merge function in recursion

	if (begin < end)
	{
		pthread_t thread1, thread2, thread3;
		int mid = (begin + end) / 2;

		// work on first-half of the array
		sortParams[0] = begin;
		sortParams[1] = mid;
		pthread_create(&thread1, NULL, mergeSort, sortParams);
		pthread_join(thread1, NULL);

		// work on second-half of the array
		sortParams[0] = mid+1;
		sortParams[1] = end;
		pthread_create(&thread2, NULL, mergeSort, sortParams);
		pthread_join(thread2, NULL);

		// merge these two arrays
		mergeParams[0] = begin;
		mergeParams[1] = mid;
		mergeParams[2] = end;
		pthread_create(&thread3, NULL, merge, mergeParams);
		pthread_join(thread3, NULL);
	}
}

void *merge(void *params)
{
	/** The global array arr is an array such that subarray arr[0:mid] and arr[mid+1:end] are sorted
	 * Merge them in a way that arr becomes sorted
	 */

	// retrieve the paramaters required for merging
	int *mergeParams = (int *)params;
	int begin = mergeParams[0];
	int mid = mergeParams[1];
	int end = mergeParams[2];

	// create left and right subarrays
	int sizeL = mid-begin+1;
	int sizeR = end-mid;
	int left[sizeL];
	int right[sizeR];

	// add elements to left and right
	for (int i = 0; i < sizeL; i++)
		left[i] = arr[begin + i];
	for (int i = 0; i < sizeR; i++)
		right[i] = arr[mid+i+1];

	int l = 0; // base index of left subarray
	int r = 0; // base index of right subarray
	int k = begin; // base index of merged array

	// the merge process
	while (l < sizeL && r < sizeR)
	{
		if (left[l] < right[r])
			arr[k++] = left[l++];
		else
			arr[k++] = right[r++];
	}

	// append remaining elements
	while (l < sizeL)	arr[k++] = left[l++];
	while (r < sizeR)	arr[k++] = right[r++];
}
