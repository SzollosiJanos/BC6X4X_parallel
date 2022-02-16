#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000

int main(int argc, char* argv[])
{
	FILE *fp;
	fp=fopen("asd.txt","w");
	char ch;
	srand(time(NULL));
	int r,db=0,counter=0;
	for(int i=0;i<N;i++){
		r=rand()%5;
		switch(r){
			case 0:ch=rand()%25+97;counter=0;break;
			case 1:ch=rand()%10+48;counter=0;break;
			case 2:ch=rand()%25+65;counter=0;break;
			case 3:ch=' ';counter=0;break;
			case 4:ch='\n';db++;if(counter==1){}counter=0;break;
		}
		
		fprintf(fp,"%c",ch);
	}
	fclose(fp);
	printf("Sorok szama:%d",db);
	return 0;
}
