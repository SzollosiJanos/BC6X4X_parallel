#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>
#include "omp.h"
#include <pthread.h>
#include <string.h>

#define FORK_LIMIT 1000

struct Compare { int val; int index; };

typedef struct Task
{
  int* array;
  int start;
  int end;
} Task;

#pragma omp declare reduction(minimum : struct Compare : omp_out = omp_in.val < omp_out.val ? omp_in : omp_out) initializer(omp_priv=omp_orig)

clock_t t;
double cpu_time_used;

void mergesort_wrapper(Task* task);

void listarray(int* array,int n){
	for(int i=0;i<n;i++){
		printf("%d\n",array[i]);
	}
}

int getlines(FILE* fp){
	fp=fopen("asd.txt","r");
	char ch;
	int count=1;
	do{
		ch=getc(fp);
		if(ch=='\n' || ch=='\r'){
			count++;
		}
	}while(ch != EOF);
	fclose(fp);
	return count;
}

void readfile(FILE* fp,int* array,int n){
	fp=fopen("asd.txt","r");
	for(int i=0;i<n;i++){
		fscanf(fp,"%d",&array[i]);
	}
	fclose(fp);
	//listarray(array,n);
}


void checkarray(int* array, int n){
	for(int i=0;i<n-1;i++){
		if(array[i+1]<array[i]){
			printf("Error!!!\n");
			return;
		}
	}
	printf("Success!!!\n");
}

void copyarray(int* array, int* newarray, int n){
	for(int i=0;i<n;i++){
		newarray[i]=array[i];
	}
}

void sortarray_beszurasos(int* array,int n){
	int temp,j;
	for(int i=1;i<n;i++){
		j=i;
		while(j>0 && array[j]<array[j-1]){
			temp=array[j];
			array[j]=array[j-1];
			array[j-1]=temp;
			j--;
		}
	}
	//listarray(array,n);
}

void sortarray_minimum(int* Array, int size){
	int k,i,temp;
	
	for(k = 0; k < size; k++){
		struct Compare min;
		
        min.val = Array[k];
        min.index = k;
		
        #pragma omp parallel for reduction(minimum:min)
		for(i=k+1; i< size; ++i){
			if(Array[i] < min.val){
				min.val = Array[i];
				min.index = i;
			}
		}
		temp=Array[k];
		Array[k]=Array[min.index];
		Array[min.index]=temp;
	}
	//listarray(Array,size);
}


void sortarray_minimum_noparallel(int* Array, int size){
	int k,i,temp;
	
	for(k = 0; k < size; k++){
		struct Compare min;
		
        min.val = Array[k];
        min.index = k;
		for(i=k+1; i< size; ++i){
			if(Array[i] < min.val){
				min.val = Array[i];
				min.index = i;
			}
		}
		temp=Array[k];
		Array[k]=Array[min.index];
		Array[min.index]=temp;
	}
	//listarray(Array,size);
}

void merge(int* array, int left, int right)
{
  int* temp;
  int left_index, right_index, result_index;
  int length;
  int array_size;

  length = left + right;
  array_size = length * sizeof(int);
  temp = (int*)malloc(array_size);
  memcpy(temp, array, array_size);

  left_index = 0;
  right_index = left;
  result_index = 0;
  while (left_index < left && right_index < length) {
    if (temp[left_index] < temp[right_index]) {
      array[result_index] = temp[left_index];
      ++left_index;
    } else {
      array[result_index] = temp[right_index];
      ++right_index;
    }
    ++result_index;
  }
  while (left_index < left) {
    array[result_index] = temp[left_index];
    ++left_index;
    ++result_index;
  }
  while (right_index < length) {
    array[result_index] = temp[right_index];
    ++right_index;
    ++result_index;
  }

  free(temp);
}


void sortarray_mergesort(int* array, int start, int end)
{
  int q;
  pthread_t thread;
  Task task;

  if (start < end) {
    q = (start + end) / 2;
    if (end - start > FORK_LIMIT) {
      task.array = array;
      task.start = start;
      task.end = q;
      pthread_create(&thread, NULL, mergesort_wrapper, &task);
      sortarray_mergesort(array, q + 1, end);
      pthread_join(thread, NULL);
    } else {
      sortarray_mergesort(array, start, q);
      sortarray_mergesort(array, q + 1, end);
    }
    merge(array + start, q - start + 1, end - q);
  }
}

void mergesort_wrapper(Task* task)
{
  sortarray_mergesort(task->array, task->start, task->end);
}

void merge_noparallel(int* array, int left, int right)
{
  int* temp;
  int left_index, right_index, result_index;
  int length;
  int array_size;
  
  length = left + right;
  array_size = length * sizeof(int);
  temp = (int*)malloc(array_size);
  memcpy(temp, array, array_size);

  left_index = 0;
  right_index = left;
  result_index = 0;
  while (left_index < left && right_index < length) {
    if (temp[left_index] < temp[right_index]) {
      array[result_index] = temp[left_index];
      ++left_index;
    } else {
      array[result_index] = temp[right_index];
      ++right_index;
    }
    ++result_index;
  }
  while (left_index < left) {
    array[result_index] = temp[left_index];
    ++left_index;
    ++result_index;
  }
  while (right_index < length) {
    array[result_index] = temp[right_index];
    ++right_index;
    ++result_index;
  }

  free(temp);
}


void sortarray_mergesort_noparallel(int* array, int start, int end)
{
  int q;

  if (start < end) {
    q = (start + end) / 2;
    sortarray_mergesort_noparallel(array, start, q);
    sortarray_mergesort_noparallel(array, q + 1, end);
    merge_noparallel(array + start, q - start + 1, end - q);
  }
}

int partition(int* array, int start, int end, int array_first)
{
  int i, j;
  int temp;

  i = start - 1;
  j = end + 1;
  while (i < j) {
    do {
      ++i;
    } while (array[i] < array_first);
    do {
      --j;
    } while (array[j] > array_first);
    if (i < j) {
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
    }
  }

  return j;
}

void sortarray_quicksort(int* array, int start, int end)
{
  int q;

  if (start < end) {
    q = partition(array, start, end, array[start]);
    sortarray_quicksort(array, start, q);
    sortarray_quicksort(array, q + 1, end);
  }
}

void sortarray_quicksort_omp(int* array, int start, int end)
{
  int q;

  if (start < end) {
    q = partition(array, start, end, array[start]);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			sortarray_quicksort(array, start, q);
		}
		#pragma omp section
		{
			sortarray_quicksort(array, q + 1, end);
		}
	}
  }
}

void time_start(){
	t = clock();
}

void checktime(FILE* fp){
	t = clock()-t;
	cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
	printf("%f\t\t\t", cpu_time_used);
	fprintf(fp,"%f\n",cpu_time_used);
}

void start_sorting(FILE* fp,int* array,int* beszuroarray, int* minimumarray,int* minimumarray_noparallel,int* mergesort,int* mergesort_noparallel,int* quicksort,int* quicksort_omp,int n){
	printf("File size: \t\t\t%d\n",n);
	fprintf(fp,"%d\n",n);
	copyarray(array,beszuroarray,n);
	copyarray(array,minimumarray,n);
	copyarray(array,minimumarray_noparallel,n);
	copyarray(array,mergesort,n);
	copyarray(array,mergesort_noparallel,n);
	copyarray(array,quicksort,n);
	copyarray(array,quicksort_omp,n);
	
	time_start();
	printf("Insertation sort:\t\t");
	sortarray_beszurasos(beszuroarray,n);
	checktime(fp);
	checkarray(beszuroarray,n);
	
	
	time_start();
	printf("Selection sort:\t\t\t");
	sortarray_minimum(minimumarray,n);
	checktime(fp);
	checkarray(minimumarray,n);
	
	
	time_start();
	printf("Selection sort noparallel:\t");
	sortarray_minimum_noparallel(minimumarray_noparallel,n);
	checktime(fp);
	checkarray(minimumarray_noparallel,n);
	
	time_start();
	printf("Merge sort:\t\t\t");
	sortarray_mergesort(mergesort,0,n-1);
	checktime(fp);
	checkarray(mergesort,n);
	
	time_start();
	printf("Merge sort noparallel:\t\t");
	sortarray_mergesort_noparallel(mergesort_noparallel,0,n-1);
	checktime(fp);
	checkarray(mergesort_noparallel,n);
	
	time_start();
	printf("quicksort:\t\t\t");
	sortarray_quicksort(quicksort,0,n-1);
	checktime(fp);
	checkarray(quicksort,n);
	
	time_start();
	printf("quicksort_omp:\t\t\t");
	sortarray_quicksort_omp(quicksort_omp,0,n-1);
	checktime(fp);
	checkarray(quicksort_omp,n);
	
	printf("\n");
}

int main(int argc, char* argv[])
{
	FILE* fp;
	int n=getlines(fp);
	int *array = calloc(n, sizeof(int));
	int *beszuroarray = calloc(n, sizeof(int));
	int *minimumarray = calloc(n, sizeof(int));
	int *minimumarray_noparallel = calloc(n, sizeof(int));
	int *mergesort = calloc(n, sizeof(int));
	int *mergesort_noparallel = calloc(n, sizeof(int));
	int *quicksort = calloc(n, sizeof(int));
	int *quicksort_omp = calloc(n, sizeof(int));
	
	readfile(fp,array,n);
	fp=fopen("kimenet.txt","w");
	for(int i=10000;i<=n;i+=10000){
		start_sorting(fp,array,beszuroarray,minimumarray,minimumarray_noparallel,mergesort,mergesort_noparallel,quicksort,quicksort_omp,i);
	}
	fclose(fp);
	
	
	free(array);
	free(beszuroarray);
	free(minimumarray);
	free(minimumarray_noparallel);
	free(mergesort);
	free(mergesort_noparallel);
	free(quicksort);
	free(quicksort_omp);
	return 0;
}
