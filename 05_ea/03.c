#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

#define N 10
#define THREADNUMBER 10


void listarray(int* array){
	int i;
	for(i=0;i<N;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}

int szekv(int* array){
	int sum=0;
	int i;
	
	for(i=0;i<N;i++){
		sum+=array[i];
	}
	return sum;
}

void crew_prefix(int* array,int* crewarray,int a, int b){
	int i,k;
	
	if(a==b){
		crewarray[a]=array[a];
		return ;
	}else{
		k=(a+b)/2;
		crew_prefix(array,crewarray,a,k);
		crew_prefix(array,crewarray,k+1,b);
		for(i=k+1;i<=b;i++){
			crewarray[i]+=crewarray[k];
		}
	}
}

void erew_prefix(int* array,int* erewarray){
	int i,k;
	
	erewarray[0]=array[0];
	for(i=1;i<N;i++){
		erewarray[i]=array[i-1]+array[i];
	}
	listarray(erewarray);
	k=2;
	while(k<N){
		for(i=k;i<N;i++){
			erewarray[i]=erewarray[i-k]+erewarray[i];
		}
		printf("k: %d \n",k);
		listarray(erewarray);
		k*=2;
	}
}

void load(int* array){
	int i;
	
	for(i=0;i<N;i++){
		array[i]=rand()%20;
	}
}

void copyarray(int* array,int* carray){
	int i;
	
	for(i=0;i<N;i++){
		carray[i]=carray[i];
	}
}


int main(int argc, char* argv[])
{
	int array[N],crewarray[N],erewarray[N];
	int i;
	
	//copyarray(array,crewarray);
	srand(time(NULL));
	
	load(array);
	printf("szekv: %d\n",szekv(array));
	listarray(array);
	crew_prefix(array,crewarray,0,N-1);
	listarray(crewarray);
	erew_prefix(array,erewarray);
	listarray(erewarray);
	return 0;
}
