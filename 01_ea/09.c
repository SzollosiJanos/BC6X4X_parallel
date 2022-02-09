#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int prime(int n);

int main(int argc, char* argv[])
{
	char c[50];
	scanf("%s",&c);
	int szam;
	scanf("%d",&szam);
	FILE *fp;
	fp=fopen(c,"w");
	srand(time(0));
	clock_t begin = clock();
	for(int i=0;i<szam;i++){
		fprintf(fp,"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
	}
	
	
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\n%lf",time_spent);
	fclose(fp);
	return 0;
}
