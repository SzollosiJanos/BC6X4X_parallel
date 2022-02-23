#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define N 50000

int ellenorzes(int *tomb, int meret, int szam);
int ellenorzesTeljes(int *tomb, int meret);
void generate(int *tomb,int meret);

int main(int argc, char* argv[])
{
	int tomb[N];
	
	for(int i=100;i<=N;i+=100){
		generate(tomb,i);
	}
	printf("Egyediseg: %s",ellenorzesTeljes(tomb,N)?"hamis":"igaz");
	return 0;
}


int ellenorzes(int *tomb,int meret, int szam){
	for(int i=0;i<meret;i++){
		if(tomb[i]==szam){
			return 1;
		}
	}
	return 0;
}

int ellenorzesTeljes(int *tomb, int meret){
	for(int i=0;i<meret;i++){
		if(ellenorzes(tomb,i,tomb[i])==1){
			return 1;
		}
	}
	return 0;
}


void generate(int *tomb,int meret){
	int dup;
	struct timeval stop, start;
	
	srand(time(NULL));
	gettimeofday(&start, NULL);
	for(int i=0;i<meret;i++){
		tomb[i]=rand()%meret*2+1;
		if(ellenorzes(tomb,i,tomb[i])==1){
			i--;
			continue;
		}
		dup=rand()%200;
		if(dup==1){
			tomb[i]=tomb[rand()%i];
		}
		//printf("%d ",tomb[i]);
	}
	gettimeofday(&stop, NULL);
	printf("Meret: %d",meret);
	printf("\ntook %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 
}