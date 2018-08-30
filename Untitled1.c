#include <stdio.h>
#include <stdlib.h>

void main(){
	int  c[10],x,j;
	time_t t;
	srand((unsigned)time(&t));
	for(x=0;x<10;x++){
		c[x]=rand()%50;
	}
	for(x=0;x<10;x++){
		printf("posicion del arreglo %d , valor %d \n",x,c[x]);
	}
	printf("HISTROGRAMA\n");
	for(x=0;x<10;x++){
		printf("%d",x+1);
		for(j=0;j<c[x];j++)
		printf(".");
		printf("%d\n",c[x]);
	}
	return;
}

