#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
	srand(time(0));
	int a=rand()%1000;
	int b=rand()%1000;
	int szam=a+b;
	printf("Mennyi a ketto szam osszege?\n\n%d + %d\n",a,b);
	clock_t begin = clock();
	int c;
	scanf("%d",&c);
	clock_t end = clock();
	int time_spent = (int)(end - begin) / CLOCKS_PER_SEC;
	if(c==szam){
		printf("Helyes a megoldasod!!!!\nMegoldas:%d\nEltelt ido:%d",szam,time_spent);
	}else{
		printf("Helytelen a megoldasod!!!!\nMegoldas:%d\nTe megoldasod:%d\nEltelt ido:%d",szam,c,time_spent);
	}
	
	return 0;
}
