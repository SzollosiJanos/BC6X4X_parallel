#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <omp.h>
#include <math.h>

#define N 16
#define THREADNUMBER 2


void listarray(int* array,int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
}

void szekv(int* array,int* rarray,int a, int b){
	int sum=0;
	int i;
	
	for(i=a;i<b;i++){
		if(i==N){
			return;
		}
		sum+=array[i];
		rarray[i]=sum;
	}
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
	#pragma omp for
	for(i=1;i<N;i++){
		erewarray[i]=array[i-1]+array[i];
	}
	k=2;
	while(k<N){
		#pragma omp for
		for(i=N-1;i>=k;i--){
			erewarray[i]=erewarray[i-k]+erewarray[i];
		}
		k*=2;
	}
}

void optimal_prefix(int* array,int* Y){
	int p;
	p=N/(log(N)/log(2));
	int i,Z[p],W[p];
	
	for(i=0;i<N;i+=p){
		szekv(array,Y,i,i+p);
	}
	//printf("\nszekv utan: ");listarray(Y,N);
	for(i=1;i<=p;i++){
		Z[i-1]=Y[i*p-1];
	}
	//printf("Z tomb: ");listarray(Z,N/p);
	crew_prefix(Z,W,0,p);
	//printf("w tomb: ");listarray(W,N/p);
	for(i=0;i<N-p;i++){
		Y[i+p]+=W[i/p];
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
	int array[N],rarray[N],crewarray[N],erewarray[N],optimalarray[N];
	int i;
	
	//copyarray(array,crewarray);
	srand(time(NULL));
	
	load(array);
	printf("default array:\t\t");
	listarray(array,N);
	szekv(array,rarray,0,N);
	printf("szekv:\t\t\t");
	listarray(rarray,N);
	crew_prefix(array,crewarray,0,N-1);
	printf("crew array:\t\t");
	listarray(crewarray,N);
	printf("erew array:\t\t");
	erew_prefix(array,erewarray);
	listarray(erewarray,N);
	printf("optimal array:\t\t");
	optimal_prefix(array,optimalarray);
	listarray(optimalarray,N);
	printf("\n\n%d | %d | %d | %d",rarray[N-1],crewarray[N-1],erewarray[N-1],optimalarray[N-1]);
	return 0;
}
