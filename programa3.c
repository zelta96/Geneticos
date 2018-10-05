#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<math.h>
#include<unistd.h>
#include"defs.h"
#include"binario.h"
#include"algoritmo.h"
#ifndef DEFS_H
#define DEFS_H
#define INDIVIDUOS 6
#define ALELO 5
#define NUM_COMANDOS 4
#define PMUTA 0.2
#define GENERACIONES 10
#endif
void cruzar(int p1[], int p2[], int h[], int n)
{
    register int i;
    
    for(i = 0; i < ALELO; i++)
    {
        if(i < n)
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf("%d",h[i]);
    }
}

void mutar(int h[])
{
    register int k;
    int alelo = rand() % ALELO;

    for(k = 0; k < ALELO; k++)
    {
        if(k == alelo)
            h[k] = (h[k]== 0) ? 1 : 0;
    }
}

double calcularProba(int x, int total)
{
    return 1.00*x/total;
}

double calcularEsperanza(int fi, double f)
{
    return 1.00*fi/f;
}

int To_decimal(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (ALELO - 1); i < ALELO; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}
int obtenerAptitud(int a)
{
   return a*a;
}

void crear_poblacion(int a[][ALELO+1])
{
    int i,j;
    int alelo;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELO; j++)
        {
            alelo = rand() % 2;
            a[i][j] = alelo;
        }
    }
    //imprimir_poblacionB(a);
}
int maxApt = 0, sumApt = 0;
int main()
{	
	    int indi,j,random,gene,m,n;
	    int x, i, ptCruza, nMuta, contador = 0;
	    int arr[INDIVIDUOS][ALELO+1], r[INDIVIDUOS], c[INDIVIDUOS][ALELO+1], hijos[INDIVIDUOS][ALELO+1];
	    double arr2[INDIVIDUOS], aptMax[GENERACIONES], aptMin[GENERACIONES],sumProb = 0.0, maxProb = 0.0, ptr = 0.0, sumAcum = 0.0;
	    srand(getpid());
		crear_poblacion(arr);
		printf("\n1.Inicialización, evaluacion y seleccion de padres\n\n");
		printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)=x^2\t|Probabilidad\t\n");
        printf("--------+---------------+---------------+---------------+---------------\n");
        for(gene=0;gene<3;gene++){
		
         for(m = 0; m < 6; m++)
        {
            x = To_decimal(arr[m]);
            sumApt =sumApt+ obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }
        
        for(m = 0; m < 6; m++)
        {
            printf("%3d\t|  ",m+1);
            for( n = 0; n < 5; n++)
            {
                printf("%d",arr[m][n]);
            }
            x = To_decimal(arr[m]);
            arr2[m] = calcularEsperanza(obtenerAptitud(x),((double)sumApt/INDIVIDUOS));
            sumProb += calcularProba(obtenerAptitud(x),sumApt);
            if(maxProb < calcularProba(obtenerAptitud(x),sumApt))
                maxProb = calcularProba(obtenerAptitud(x),sumApt);
            printf("\t|%6d\t\t|%5d\t\t|%f\t|\n",x,obtenerAptitud(x),calcularProba(obtenerAptitud(x),sumApt));
        }
        printf("\nSuma:      \tAptitud: %5d\t\tProbabilidad: %f\n",sumApt,sumProb);
        printf("Promedio:  \tAptitud: %5d\t\tProbabilidad: %f\n",sumApt/INDIVIDUOS,(1.00*sumProb)/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %5d\t\tProbabilidad: %f\n",maxApt,maxProb);
        ptr = (double) (rand() % 11)/10;
        
        for(m = 0; m < 6; m++)
        {
            //printf("m = %d ---------sum = %.1f ------- ptr = %.1f\n",m,sumAcum,ptr);
            for(sumAcum += arr2[m]; sumAcum > ptr; ptr++)
            {
                //printf("m = %d ---------sum = %.1f ------- ptr = %.1f\n",m,sumAcum,ptr);
                if(sumAcum > ptr)
                    r[m] += 1;
            }   
        }
        //printf("\n");
        //imprimirArray(r);
        //printf("\n");
        
        for(m = 0,i = 0; m < 6; m++)
        {
            if(r[m] > 0)
            {
                for(n = 0; n < r[m]; n++)
                {
                    for(j=0;j<ALELO;j++)
                        c[i][j] = arr[m][j];
                    i++;
                }
            }
        }
                //imprimir_poblacionB(arr);
	printf("\n2.Cruza y evaluacion de la descendencia\n\n");
        
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       \t|Aptitud\n");
        printf("--------+---------------+---------------+---------------+---------------+---------\n");
        
        for(m = 0; m < 6; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                ptCruza = (rand() % 4)+1;
            
            for(n = 0; n < ALELO; n++)
            {
                if(n == ptCruza)
                    printf("|%d",c[m][n]);
                else
                    printf("%d",c[m][n]);
            }
            printf("\t|%6d\t\t|    ",ptCruza);
            if((m % 2) == 0)
                cruzar(c[m],c[m+1],hijos[m],ptCruza);
            else
                cruzar(c[m],c[m-1],hijos[m],ptCruza);
                
            x = To_decimal(hijos[m]);
            printf("\t|%6d\t\t|%5d\n",x,obtenerAptitud(x));
        }

        sumApt = 0;
        maxApt = 0;
        
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = To_decimal(hijos[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }
        
        printf("\nSuma:      \tAptitud: %5d\n",sumApt);
        printf("Promedio:  \tAptitud: %5d\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %5d\n",maxApt);

        printf("\n3.Mutacion y evaluacion de la descendencia\n\n");
        nMuta = INDIVIDUOS * PMUTA;
        printf("No.\t|Descendencia  \t|Mutacion \t|Val X\t\t|Aptitud\n");
        printf("--------+---------------+---------------+---------------+-----------\n");

        for (m = 0; m < 6; m++)
        {
            printf("%3d\t|   ", m+1);
            for (n = 0; n < 5; n++)
                printf("%d", hijos[m][n]);

            printf("\t|    ");
            if ((rand() % 2) && (contador < nMuta))
            {
                mutar(hijos[m]);
                contador++;
                printf("#");
            }
            for (n = 0; n < ALELO; n++)
                printf("%d", hijos[m][n]);

            x = To_decimal(hijos[m]);
            printf("\t|%6d\t\t|%7d\n",x,obtenerAptitud(x));
        }

        sumApt = 0;
        maxApt = 0;
        
        for(m = 0; m < 6; m++)
        {
            x = To_decimal(hijos[m]);
            sumApt += obtenerAptitud(x);
            if(maxApt < obtenerAptitud(x))
                maxApt = obtenerAptitud(x);
        }

        printf("\nSuma:      \tAptitud: %5d\n",sumApt);
        printf("Promedio:  \tAptitud: %5d\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %5d\n",maxApt);
}
}
