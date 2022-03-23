#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>


struct promise{
	int result;
	bool hasresult;
}promise_default ={0,0};
typedef struct promise Promise;

bool has_value(Promise* promise1){
	if(promise1->hasresult==0){
		return false;
	}
	return true;
}

int get_value(Promise* promise1){
	if(promise1->hasresult==false){
		return NULL;
	}
	return promise1->result;
}

void set_value(Promise* promise1, int result){
	promise1->result=result;
	promise1->hasresult=true;
}

int main(int argc, char* argv[])
{
	Promise promise1 = promise_default;
	printf("%d\n", has_value(&promise1));
	printf("%d\n", get_value(&promise1));
	set_value(&promise1, 10);
	printf("%d\n", has_value(&promise1));
	printf("%d\n", get_value(&promise1));
	return 0;
}
