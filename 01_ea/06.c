#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int prime(int n);

int main(int argc, char* argv[])
{
	clock_t begin = clock();
	prime(10000);
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\n%lf",time_spent);
	return 0;
}


int prime(int n){
	int counter=0;
	for(int k=2;k<n;k++){
		int m=k/2;    
		int flag=0;
		for(int i=2;i<=m;i++)    
		{    
			if(k%i==0)    
			{    
				flag=1;    
				break;    
			}    
		}    
		if(flag==0){
			printf("%d ",k);
			counter++;
		}    
	}
	printf("\ndarabszam:%d",counter);
}