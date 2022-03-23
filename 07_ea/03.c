#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <string.h>


typedef struct topic{
	char text[1000];
}Topic;


void subscribe(Topic* topic1){
	//ennek mit is kellene csinálnia?!
}

void publish(Topic* topic1,char text[]){
	strcpy(topic1->text,text);
}


int main(int argc, char* argv[])
{
	Topic topic1;
	subscribe(&topic1);
	publish(&topic1,"ez egy teszt");
	printf("%s",topic1.text);
	return 0;
}
