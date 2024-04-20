#include <stdio.h>
#include <stdlib.h>
#include "sort_collection.h"
#include <math.h>
unsigned long compare_count = 0;

void cmp_cnt_reset(void) {
  compare_count = 0;
}

int compare(int ldata, int rdata) {
  compare_count++;
  if      (ldata  < rdata) {
  	//printf("Left value %d is smaller than Right value %d!", ldata, rdata);
	//printf("\n");
  	return -1;
  } else if (ldata == rdata) {
  	//printf("Left value %d is equal to Right value %d!", ldata, rdata);
	//printf("\n");
  	return  0;
  } else {
  	//printf("Left value %d is larger than Right value %d!", ldata, rdata);
	//printf("\n");  
      return  1;
   }
}

void swap(int a[], int lidx, int ridx) {
  int temp = a[lidx];
  a[lidx] = a[ridx];
  a[ridx] = temp;
  //printf("Swapped the number at %d position (%d) with the number at %d position (%d)!", lidx, a[ridx], ridx, a[lidx]);
  //printf("\n"); 
}

void display(int a[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

void selection_sort(int a[], int n) {
  int i, j;
  for (i = 0; i < n - 1; i++) {
    int min = i;
    for (j = i + 1; j < n; j++) {
      if (compare(a[j], a[min]) == -1) {
        min = j;
      }
    }
    swap(a, i, min);
  }
}

// Insertion sort
/**************************************/
void insertion_sort(int a[], int n) {
  int i, key, j;
  for (i = 1; i < n; i++) {
    key = a[i];
    j = i - 1;

    while (j >= 0 && compare(a[j], key) == 1) {
      a[j + 1] = a[j];
      j = j - 1;
    }
    a[j + 1] = key;
  }
}


// Functions for Heap sort
/**************************************/
void sift_down(int a[], int i, int n) { //this fuction rearrange the position of a parent and its 2 children, the largest number is parent
  int maxChild, tmp;
  while ((2 * i) + 1 < n) { //while the node at i position and its children exist in the tree. After sorting, we will either break the while loop (complete sorting) or moved to the leaf of the tree (when 2*i+1 = n) 
    maxChild = (2 * i) + 1;
    if (((2 * i) + 2 < n) && (compare(a[(2 * i) + 2], a[maxChild]) == 1)) { //a[(2 * i) + 2 > a[(2 * i) + 1
      maxChild = (2 * i) + 2;
    }
    if (compare(a[i], a[maxChild]) == -1) {
      tmp = a[i];
      a[i] = a[maxChild];
      a[maxChild] = tmp;
      i = maxChild; //put the index i to the position of that child that we just moved it to the parent position
    } else {
      break;
    }
  }
}

//make a max heap tree
void build_heap(int a[], int n) { //n is max node
  int i;                          // i is index of current node  
  for (i = (n / 2) - 1; i >= 0; i--) { //initially i indicates the last parent node and we keep using sift_down until i = 0 (i went to the root) 
    sift_down(a, i, n);
  }
} 


void heap_sort(int a[], int n) {
  build_heap(a, n); //after this build_heap funtion, we have a complete reverse heap tree (like [6, 5, 4, 3, 2]) 
  int i;
  for (i = n - 1; i > 0; i--) { 
  	//2 function below work as we delete the root from a heap tree
    swap(a, 0, i); //keep swapping the last element to the first element (like [2, 5, 4, 3, 6]), now we "deleted" the last element (6) and use sift_down to reaggange the reverse heap tree
    sift_down(a, 0, i); //this sift_down rearranges the reverse heap tree as it keeps the largest number at root
  }
}


// Functions for Quick sort
/**************************************/
int partition(int a[], int pivot, int left, int right) {
  int pivotValue = a[pivot];
  swap(a, pivot, right);
  int storeIndex = left;

  for (int i = left; i < right; i++) {
    if (compare(a[i], pivotValue) == -1) {
      swap(a, i, storeIndex); //meet a smaller value than pivot => swap it to the leftmost of the list, then forget it and move the leftmost position to the next position
      storeIndex++; //store index = leftmost larger value than pivot => move all larger value next to left of pivot, then swap pivot with the leftmost one
    }
  }

  swap(a, storeIndex, right); //swap pivot with the leftmost number of those which are all bigger than pivot
  return storeIndex;
}

void quick_sort(int a[], int left, int right) {
  if (left < right) { //there are still element(s)in list
   int pivot = left + (right - left) / 2; //create pivot in norrmal case
   //int pivot = right; //create pivot in worst case
    int newPivot = partition(a, pivot, left, right); //newPivot still has the value of pivot, however the list a[] now is sorted as smaller than pivot went to left, larger than pivot went to right
    quick_sort(a, left, newPivot - 1);
    quick_sort(a, newPivot + 1, right);
  }
}

void q_sort(int a[], int n) {
  quick_sort(a, 0, n - 1);
}

// Functions for Radix sort
/**************************************/
void bucket_sort (int a[], int n, int digit) {
	int i = 0;
	int total_bucket = 10;
	int bucket_index = 0;		
	int bucket[total_bucket][n];

    int bucket_sizes[total_bucket];
    for (i = 0; i < total_bucket; i++) {
        bucket_sizes[i] = 0; //bucket_sizes = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, each number shows how many element in each bucket, starts from bucket 0 and ends with bucket 10
    }
	
    //move from array a to sub-array bucket
	for (i = 0; i < n; i++) {
		bucket_index = (a[i] % (int)pow(10, digit + 1) / (int)pow(10, digit)) %  total_bucket; //maybe we dont need this "%  total_bucket" part
		bucket[bucket_index][bucket_sizes[bucket_index]] = a[i];
		bucket_sizes[bucket_index]++;

		//bucket_sizes[bucket_index] is the number in bucket_sizes array, each number is corresponding to that bucket number (thanks to bucket_index)
		//after add an element to a bucket, plus 1 to the corresponding element in the bucket_sezes array
	}
   	
   	//Loop to print all buckets
   	printf("Before sorting:");
	printf("\n");
   	for (i = 0; i < total_bucket; i++){
	for (int j = 0; j < n; j++){
	printf("%d ", bucket[i][j]);
	}
	printf("\n");
	}	
	//sort values inside pocket	
	for (bucket_index = 0; bucket_index < total_bucket; bucket_index++) {
		//printf("bucket[bucket_index] before sorting is %d, bucket_sizes[bucket_index] before sorting is %d\n", bucket_index, bucket_sizes[bucket_index]);
		q_sort(bucket[bucket_index], bucket_sizes[bucket_index]);
	}
	
	//Loop to print all buckets
   	printf("After sorting:");
	printf("\n");
   	for (i = 0; i < total_bucket; i++){
	for (int j = 0; j < n; j++){
	printf("%d ", bucket[i][j]);
	}
	printf("\n");
	}
	
	
	//move back values from bucket to array a
	for (i = 0, bucket_index = 0; bucket_index < total_bucket; bucket_index++) {
	int value_inside_bucket = 0;
	//bucket_sizes[bucket_index] != 0 mean that bucket has elements in it
	//value_inside_bucket < bucket_sizes[bucket_index] and value_inside_bucket++ means only take the number that we put into bucket
	while (bucket_sizes[bucket_index] != 0 && value_inside_bucket < bucket_sizes[bucket_index] && i < n) {
		a[i] = bucket[bucket_index][value_inside_bucket];
		i++;
		value_inside_bucket++;
	}
	}
} 

void radix_sort(int a[], int n, int k) {
	//k is the maximum digits
	int digit = 0;	
	for (digit; digit < k; digit++) {
		bucket_sort (a, n, digit);
		printf("at digit %d, array a is ", digit);
		for (int i = 0; i < n; i++) {
			printf("%d ", a[i]);	
	        }	
	      printf("\n");	 
	}
}
