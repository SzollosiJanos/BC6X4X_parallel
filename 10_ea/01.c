#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdbool.h>
#include "omp.h"
#include <pthread.h>

struct Compare { int val; int index; };

#pragma omp declare reduction(minimum : struct Compare : omp_out = omp_in.val < omp_out.val ? omp_in : omp_out) initializer(omp_priv=omp_orig)

clock_t t;
double cpu_time_used;

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

void time_start(){
	t = clock();
}

void checktime(){
	t = clock()-t;
	cpu_time_used = ((double)t)/CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);
}

void start_sorting(int* array,int* beszuroarray, int* minimumarray,int* minimumarray_noparallel,int n){
	printf("File size: \t\t\t%d\n",n);
	copyarray(array,beszuroarray,n);
	copyarray(array,minimumarray,n);
	copyarray(array,minimumarray_noparallel,n);
	time_start();
	printf("Insertation sort:\t\t");
	sortarray_beszurasos(beszuroarray,n);
	checktime();
	checkarray(beszuroarray,n);
	time_start();
	printf("Selection sort:\t\t\t");
	sortarray_minimum(minimumarray,n);
	checktime();
	checkarray(minimumarray,n);
	time_start();
	printf("Selection sort noparallel:\t");
	sortarray_minimum_noparallel(minimumarray_noparallel,n);
	checktime();
	checkarray(minimumarray_noparallel,n);
	printf("\n");
}

int main(int argc, char* argv[])
{
	FILE* fp;
	int n=getlines(fp);
	int array[n],beszuroarray[n],minimumarray[n],minimumarray_noparallel[n];
	readfile(fp,array,n);
	for(int i=10000;i<=n;i+=10000){
		start_sorting(array,beszuroarray,minimumarray,minimumarray_noparallel,i);
	}
	return 0;
}
