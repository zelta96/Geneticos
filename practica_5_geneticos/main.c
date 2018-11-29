#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<math.h>

#include"algoritmo.h"
#define GEN 1
#define DEFS_H
#define numind 16
#define NUM_COMANDOS 4
#define numale 5
#define MAX 1.1
#define PMUTA 0.1

double probatotal=0.0, maxProb=0.0, ptr , sumAcum;;
int c[numind][numale+1];
int lastgen[numale];
double maximo = 0, apttotal = 0,minimo;
int cad[numind][numale+1];
int nextgen[numind][numale+1];
int muto,cnt;


void inicialgo(int cad[][numale+1]);
void cruzazul();
void mutaciones();
void reinicia();
void ord(int indiv[][numale+1]);
double rankea(int i);
void funcion_rlt(int indiv[][numale+1], int hijo[][numale+1], int lastgen[], int max);

void imprimir_poblacionB(int b[][numale+1])
{
    int i,j;
    for(j = 0; j < numind; j++)
    {
        for(i = 0; i < numale; i++)
           printf("%d ",b[j][i]);

		printf("\n");
    }
}

int main(int argc, char *argv[])
{   //enteeros para recorrer ciclos 
    int m,k,numGen,x,rul;

    srand(getpid());

    numGen=atoi(argv[1]);

    double bestgen[numGen], lessgen[numGen];

    for(m = 0; m < numGen; m++)
        bestgen[m] = 0.0;

    for(m = 0; m < numGen; m++)
        lessgen[m] = 1.0;

    genesis(cad);
    
    for( k = 0; k < numGen; k++){
        //sumProb = maxProb = sumAcum = 0.0;
        reinicia();
        cnt=maximo = apttotal = 0;


		printf("\n\tGENERACION %d \n\n", k+1);
		
		printf("\n\n1. Inicialización, evaluación, y selección de padres \n");
		printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)\t|Probabilidad\n");
        

        for(m = 0; m < numind; m++){
            x = indecimal(cad[m]);
            if(m == 0)
                minimo = calc_apt(x);
            apttotal += calc_apt(x);
            if(maximo < calc_apt(x))
                maximo = calc_apt(x);
            if(minimo > calc_apt(x))
                maximo = calc_apt(x);
        }

        inicialgo(cad);

        //Guardamos los valores de la Generación 0
        if(k == 0){
            bestgen[0] = maximo;
            lessgen[0] = minimo;
        }

        //Ordenamos por Aptitud, donde 1 representa al menos apto.
        ord(cad);

        printf("\n\n2. Cruza y evaluación de la descendencia. \n\n");
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       |Aptitud\n");
        printf("--------+---------------+---------------+---------------+------------+---------\n");

        cruzazul();

        printf("\n\n Mutacion y evaluacion de descendencia. \n\n");
        printf("No.\t|Descendencia  \t|Mutacion \t|Val X\t\t|Aptitud\n");
        printf("--------+---------------+---------------+---------------+-----------\n");

        muto = numind * PMUTA;

        mutaciones();
        if(k > 0){
            bestgen[k] = maximo;
            lessgen[k] = minimo;
        }

        funcion_rlt(cad,nextgen,lastgen,apttotal);
        rul=0;  

        apttotal = maximo = 0.0;
        minimo = 1.0;
    }
    arc_esc(bestgen,1);
    arc_esc(lessgen,0);
    graficar();
    
    return 0;
}
void reinicia(){
    probatotal = maxProb = ptr = sumAcum = 0.0;
}


void inicialgo(int cad[][numale+1]){
    int x,m=0;
    
    printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)\t|Probabilidad\t|ValEsp\n");
    int n;
        
        for(m = 0; m < numind; m++)
        {
            printf("%3d\t|  ",m+1);
            for(n = 0; n < numale; n++)
            {
                printf("%d",cad[m][n]);
            }
            x = indecimal(cad[m]);
            probatotal += obtenerprobar(calc_apt(x),apttotal);
            if(maxProb < obtenerprobar(calc_apt(x),apttotal)){
                maxProb = obtenerprobar(calc_apt(x),apttotal);
                 for( n = 0; n < numale; n++)
                    lastgen[n] = cad[m][n];
                }
            printf("\t\t|%8d\t|%f\t|%f\n",x,calc_apt(x),obtenerprobar(calc_apt(x),apttotal));
        }
        
        printf("\nSuma:      \t\t\t %f\t\t\n",apttotal);
        printf("Promedio:  \t\t\t\t%f\t\t\n",apttotal/numind);
        printf("Maximo:    \t\t\t\t%f\t\t\n",maximo);

}

void funcion_rlt(int indiv[][numale+1], int hijo[][numale+1], int lastgen[], int max)
{
    int i,j,k;
    int rul, acum;
    for( i = 0; i < numale; i++)
    {
        indiv[0][i] = lastgen[i]; 
    }
    for( i = 1; i < numind; i++)
    {
        acum = 0;
        rul = rand()%(max+1);
        
        for( j = 0; j < numind; j++)
        {
            acum += rankea(j);
            if (acum >= rul)
            {
                for( k = 0; k < numale; k++)
                    indiv[i][k] = hijo[i][k];  
                break;
            }
        }
    }
}



void cruzazul(){
        printf("\n\t\t\t 2.-CRUZA\n\n");
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       \t|Aptitud\n");
int m=0,cruz=0,n,x;
         for(m = 0; m < numind; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                cruz = (rand() % 4)+1;
            
            for(n = 0; n < numale; n++)
            {
                if(n == cruz)
                    printf("|%d",cad[m][n]);
                else
                    printf("%d",cad[m][n]);
            }
            printf("\t|%6d\t\t|    ",cruz);
            if((m % 2) == 0)
                cruzar(cad[m],cad[m+1],nextgen[m],cruz);
            else
                cruzar(cad[m],cad[m-1],nextgen[m],cruz);
                
            x = indecimal(nextgen[m]);
            printf("\t|%6d\t\t|%5f\n",x,calc_apt(x));
        }
              

        apttotal = 0;
        maximo = 0;
        
        for(m = 0; m < numind; m++)
        {
            x = indecimal(nextgen[m]);
            apttotal += calc_apt(x);
            if(maximo < calc_apt(x))
                maximo = calc_apt(x);
        }
        
        printf("\nSuma:      \t\t\t %f\t\t\n",apttotal);
        printf("Promedio:  \t\t\t\t%f\t\t\n",apttotal/numind);
        printf("Maximo:    \t\t\t\t%f\t\t\n",maximo);
}

void mutaciones(){
    int m,x,n;
     for (m = 0; m < numind; m++)
        {
            printf("%3d\t|   ", m+1);
            for (int n = 0; n < numale; n++)
                printf("%d", nextgen[m][n]);

            printf("\t|    ");
            if ((rand() % 2) && (cnt < muto))
            {
                mutar(nextgen[m]);
                cnt++;
                printf("#");
            }
            for (n = 0; n < numale; n++)
                printf("%d", nextgen[m][n]);

            x = indecimal(nextgen[m]);
            printf("\t|%6d\t\t|%f\n",x,calc_apt(x));
        }

        apttotal = maximo = 0.0;

        for(m = 0; m < numind; m++)
        {
			x = indecimal(nextgen[m]);
			if(m == 0)
				minimo = calc_apt(x);
			apttotal += calc_apt(x);
			if(maximo < calc_apt(x))
				maximo = calc_apt(x);;
			if(minimo > calc_apt(x))
				minimo = calc_apt(x);
		}

        printf("\nSuma:      \tAptitud: %f\n",apttotal);
        printf("Promedio:  \tAptitud: %f\n",apttotal/numind);
        printf("Maximo:    \tAptitud: %f\n",maximo);
        printf("Minimo:    \tAptitud: %f\n",minimo);

}

void ord(int indiv[][numale+1]){
    int i,j,k;
    int x, tt1, tt2;
    int aux[numale+1];
    imprimir_poblacionB(indiv);
    for( i = 1; i < numind; i++)
    {
        for( j = 0; j < (numind-1); j++)
        {
            x = indecimal(indiv[j]);
            tt1 = calc_apt(x);
            x = indecimal(indiv[j]);
            tt2 = calc_apt(x);
            
            if (tt1 > tt2) {
                for( k = 0; k < numale+1; k++)
                    aux[k] = indiv[j][k];
                for( k = 0; k < numale; k++)
                    indiv[j][k] = indiv[j+1][k];
                for( k = 0; k < numale; k++)
                    indiv[j+1][k] = aux[k];
            }    
        }
    }
}

double rankea(int i){
    double P, base;
    int exp;
    double min = 2 - MAX;
    base = MAX - min;
    exp = (i-1)/(numind-1);
    i = i+1;
    P = min + (pow(base,exp));
    return P;
}
