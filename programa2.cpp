#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RANDOM(A, B) (rand() % ((B) - (A) + 1) + (A))

int main(){
	
	time_t t;
	
	int binario[10][5];
	int gray[10][5];
	double reales[10][5];
	int enteros[10][5];
	
	srand((unsigned) time(&t));
	/////BINARIO/////////
	for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){
			binario[j][i]=rand() % 2;			
		}
	}
	/////////IMPRESION DE INDIVIDUOS BINARIOS Y AGREGAR INDIDUOS GRAY/////////
	printf("\t\t\t BINARIO \n");
	for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){
			if(i != 4){
				gray[j][i]=binario[j][i] ^binario[j][i+1];
			}
			else{
				gray[j][i]=binario[j][i] ^ binario[j][0];
			}
			
			
			printf("%d",binario[j][i]);		
		}
		printf("\n");
	}
	//////////////// IMPRESION DE  GRAY////////////////////
	printf("\t\t\t GRAY \n");
	for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){

			
			printf("%d",gray[j][i]);		
		}
		printf("\n");
	}
	
	//////////  NUMEROS REALES //////////////
	printf("\t\t\t REALES \n");
	
	
	for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){
			reales[j][i] = (double)rand()/RAND_MAX*3.0-0.0;
					
		}
	}
		for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){
			
				printf("%f ",reales[j][i]);		
		}
		printf("\n");
	}
	 ///////////// NUMEROS ENTEROS/////////////
 
 printf("\t\t\t NUMEROS ENTEROS \n");
 for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){
			enteros[j][i]=rand() % 50;			
		}
	}
	for(int j=0;j<10;j++)
	{
		for(int i=0;i<5;i++){
			printf("%d ",enteros[j][i]);		
		}
		printf("\n");
	}
}



