#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>


#define THREADNUMBER 4

pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct data{
	int* array;
	int size;
	int current;
}Data;

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
}

void listarray(int* array,int n){
	for(int i=0;i<n;i++){
		printf("%d\n",array[i]);
	}
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
}

void* sortarray_minimum(Data* data){
	int temp,j;
	while(data->current<data->size-1){
		j=data->current;
		for(int i=data->current+1;i<data->size;i++){
			if(data->array[i]<data->array[j]){
				j=i;
			}
		}
		pthread_mutex_lock(&value_mutex);						//ez még bugos :(
		if(data->array[data->current]<data->array[j]){
			data->current++;
			pthread_mutex_unlock(&value_mutex);
			continue;
		}
		temp=data->array[j];
		data->array[j]=data->array[data->current];
		data->array[data->current]=temp;
		data->current++;
		pthread_mutex_unlock(&value_mutex);
	}
}

int main(int argc, char* argv[])
{
	FILE* fp;
	int n=getlines(fp);
	int array[n],beszuroarray[n],minimumarray[n];
	pthread_t threads[THREADNUMBER];
	Data data;
	data.array=minimumarray;
	data.size=n;
	data.current=0;
	
	readfile(fp,array,n);
	copyarray(array,beszuroarray,n);
	copyarray(array,minimumarray,n);
	listarray(beszuroarray,n);
	sortarray_beszurasos(beszuroarray,n);
	listarray(beszuroarray,n);
	for(int i=0;i<THREADNUMBER;i++){
		pthread_create(&threads[i], NULL, (void*)sortarray_minimum, &data);
	}
	for(int i=0;i<THREADNUMBER;i++){
		pthread_join(threads[i], NULL);
	}
	listarray(minimumarray,n);
	return 0;
}
