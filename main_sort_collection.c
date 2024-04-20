#include <stdio.h>
#include <stdlib.h>
#include "sort_collection.h"
#include <math.h>
#include <sys/time.h>

int GetRandom(int min, int max) {
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main(int argc, char *argv[]) {
  if (argc != 1) {
    int numdata = atoi(argv[1]);  // set numdata with cmd. argument
    int *array = (int*)malloc(sizeof(int) * numdata);
    int i;
    printf("Enter %d integers\n", numdata);
    for (i = 0; i < numdata; i++) {
      scanf("%d", &array[i]);  // enter integers
    }
    radix_sort(array, numdata, 3);
    printf("sorting result\n");
    display(array, numdata);
    printf("# of comparisons: %lu\n", compare_count);
    free(array);
  } else {
    int numdata;
    
    struct timeval start, end; //counting time
    gettimeofday(&start, NULL); //counting time

    for (numdata = 10000; numdata <= 100000; numdata += 10000) {  // numdata is 10000, 20000, ..., 100000
      printf("numdata %d\n", numdata);
      int *array = (int*)malloc(sizeof(int) * (numdata));    
      int i;
      for (i = 0; i < numdata; i++) {
        array[i] = GetRandom(0, (numdata - 1));  // random number from 0 to numdata - 1
        //array[i] = i; //create increasing data (sorted data)
      	}
      printf("data created!");
      q_sort(array, numdata);
      //print array after sorting
      gettimeofday(&end, NULL); //counting time
	double elapsed_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6; //counting time
	printf("numdata = %d: time = %lf[sec]\n", numdata, elapsed_time); //print time
      //printf("%d %lu\n", numdata, compare_count);
      cmp_cnt_reset();
      free(array);
    }
  }

  return EXIT_SUCCESS;
}