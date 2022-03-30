#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>

#define THREADNUMBER 2

pthread_mutex_t value_mutex = PTHREAD_MUTEX_INITIALIZER;

struct promise{
	int result;
	bool hasresult;
}promise_default ={0,0};
typedef struct promise Promise;


void await_promise(){
	pthread_mutex_lock(&value_mutex);
	pthread_mutex_unlock(&value_mutex);
}

bool has_value(Promise* promise1){
	if(promise1->hasresult==0){
		return false;
	}
	return true;
}

int get_value(Promise* promise1){
	if(promise1->hasresult==false){
		return 0;
	}
	return promise1->result;
}

void set_value(Promise* promise1, int result){
	promise1->result=result;
	promise1->hasresult=true;
	pthread_mutex_unlock(&value_mutex);
}


void* test1(Promise* promise1)
{
	await_promise();
	printf("Value: %d",get_value(promise1));
}


void* test2(Promise* promise1)
{
	printf("Sleep for 5 sec\n");
	sleep(5);
	set_value(promise1, 10);
	printf("Set value to 10\n");
}

int main(int argc, char* argv[])
{
	Promise promise1 = promise_default;
	pthread_mutex_lock(&value_mutex);
	pthread_t threads[THREADNUMBER];
	int i;
	
	pthread_create(&threads[0], NULL, (void*)test1, &promise1);
	pthread_create(&threads[1], NULL, (void*)test2, &promise1);
	
	
	for(i=0;i<THREADNUMBER;i++){
		pthread_join(threads[i], NULL);
	}
	return 0;
}
