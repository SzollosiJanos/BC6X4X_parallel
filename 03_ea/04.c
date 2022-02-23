#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 30000

void generate(FILE *fp);
void generateR(FILE *fp,int size);

int main(int argc, char* argv[])
{
	FILE *fp;
	struct timeval stop, start;
	
	fp=fopen("generate.txt","w");
	srand(time(NULL));
	gettimeofday(&start, NULL);
	generate(fp);
	fclose(fp);
	gettimeofday(&stop, NULL);
	printf("\ntook %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
	gettimeofday(&start, NULL);
	fp=fopen("generateR.txt","w");
	generateR(fp,N);
	fclose(fp);
	gettimeofday(&stop, NULL);
	printf("\ntook %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
	return 0;
}


void generate(FILE *fp){
	char ch;
	int r,db=0;
	
	
	for(int i=0;i<N;i++){
		r=rand()%5;
		switch(r){
		case 0:
			ch=rand()%25+97;
			break;
		case 1:
			ch=rand()%10+48;
			break;
		case 2:
			ch=rand()%25+65;
			break;
		case 3:
			ch=' ';
			break;
		case 4:
			ch='\n';
			db++;
			break;
		}
		
		fprintf(fp,"%c",ch);
	}
	printf("Sorok szama:%d",db);
}

void generateR(FILE *fp, int size){
	int r;
	char ch;
	
	if(size==-1){
		return;
	}
	
	r=rand()%5;
	switch(r){
	case 0:
		ch=rand()%25+97;
		break;
	case 1:
		ch=rand()%10+48;
		break;
	case 2:
		ch=rand()%25+65;
		break;
	case 3:
		ch=' ';
		break;
	case 4:
		ch='\n';
		break;
	}
	fprintf(fp,"%c",ch);
	size--;
	generateR(fp,size);
	
}