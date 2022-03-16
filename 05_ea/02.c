#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>

#define N 500
#define THREADNUMBER 10

struct arg_struct {
    int arg1;
    int* arg2;
	int odd;
	int even;
	int zero;
	int negativ;
}args;


void sumofarray(void* param1)
{
	int i;
	int *array;
	struct arg_struct *args = param1;
	
	i=args->arg1;
	array=args->arg2;
	for(;i<N;i+=THREADNUMBER){
		if(array[i]==0){
			printf("%d number is zero\n",array[i]);
			args->zero++;
		}else if(array[i]%2==0){
			printf("%d number is even %s\n",array[i],(array[i]<0)?"and negativ":"");
			args->even++;
		}else{
			printf("%d number is odd %s\n",array[i],(array[i]<0)?"and negativ":"");
			args->odd++;
		}
		if(array[i]<0){
			args->negativ++;
		}
	}
}


int main(int argc, char* argv[])
{
	int array[N],i;
	int sodd,seven,snegativ,szero;
	sodd=seven=snegativ=szero=0;
	pthread_t threads[THREADNUMBER];
	struct arg_struct args[THREADNUMBER];
	srand(time(NULL));
	printf("generate array\n");
	for(i=0;i<N;i++){
		array[i]=rand()%100-50;
	}
	clock_t begin = clock();
	printf("create threads\n");
	for(i=0;i<THREADNUMBER;i++){
		args[i].arg1 = i;
		args[i].arg2 = array;
		args[i].odd = 0;
		args[i].even = 0;
		args[i].zero = 0;
		args[i].negativ = 0;
		pthread_create(&threads[i], NULL, sumofarray, (void *)&args[i]);
	}
	printf("wait for threads\n");
	for(i=0;i<THREADNUMBER;i++){
		pthread_join(threads[i], NULL);
	}
	for(i=0;i<THREADNUMBER;i++){
		sodd+=args[i].odd;
		seven+=args[i].even;
		snegativ+=args[i].negativ;
		szero+=args[i].zero;
	}
	printf("\nodd:%d\neven:%d\nzero:%d\nnegativ:%d\n",sodd,seven,szero,snegativ);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time: %.12lf",time_spent);
	return 0;
}
