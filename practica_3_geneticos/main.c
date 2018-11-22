#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

#include"algoritmo.h"
#define GEN 10
#define DEFS_H
#define numind 32
#define NUM_COMANDOS 4
#define numale 5
#define PMUTA 0.2
void inicialgo(int cad[][numale+1],double cad2[]);
int maxApt = 0, apttotal = 0;
double probatotal=0.0, maxProb=0.0 ;
int main()
{   //enteeros para recorrer ciclos 
    int m,n,k;
    //enteros para llenar  los cadeglos
    int cad[numind][numale+1], r[numind];
    double ptr , sumAcum;
    double cad2[numind], bestgen[GEN], lessgen[GEN];
    int x, i, j, cruz, muto, contador = 0;
    srand(getpid());
    //rellenar la mejor generacion
    for(m = 0; m < numind; m++)
        bestgen[m] = 0.0;
    //rellenar la peor generacion
    for(m = 0; m < numind; m++)
        lessgen[m] = 1.0;
    //GENENACION
     int c[numind][numale+1];
     int nextgen[numind][numale+1];
    for(k = 0; k < GEN; k++)
    {
        probatotal = maxProb = ptr = sumAcum = 0.0;
        contador = maxApt = apttotal = 0;

        for(m = 0; m < numind; m++)
            r[m] = 0;
        
        printf("\n\n\t\t\t GENERACION %d\n\n\n",k+1);
        printf("\n1.Inicial, evalua y selecciona a padres\n\n");
        genesis(cad);
        inicialgo(cad,cad2);
        
        
        ptr = (double) (rand() % 11)/10;
        
        for(m = 0; m < numind; m++)
        {
            for(sumAcum += cad2[m]; sumAcum > ptr; ptr++)
            {
                if(sumAcum > ptr)
                    r[m] += 1;
            }   
        }
        
        for(m = 0,i = 0; m < numind; m++)
        {
            if(r[m] > 0)
            {
                for(n = 0; n < r[m]; n++)
                {
                    for(j=0;j<numale;j++)
                        c[i][j] = cad[m][j];
                    i++;
                }
            }
        }
        
        printf("\n\t\t\t 2.-CRUZA\n\n");
        
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       \t|Aptitud\n");
        
        for(m = 0; m < numind; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                cruz = (rand() % 4)+1;
            
            for(n = 0; n < numale; n++)
            {
                if(n == cruz)
                    printf("|%d",c[m][n]);
                else
                    printf("%d",c[m][n]);
            }
            printf("\t|%6d\t\t|    ",cruz);
            if((m % 2) == 0)
                cruzar(c[m],c[m+1],nextgen[m],cruz);
            else
                cruzar(c[m],c[m-1],nextgen[m],cruz);
                
            x = indecimal(nextgen[m]);
            printf("\t|%6d\t\t|%5d\n",x,calc_apt(x));
        }

        apttotal = 0;
        maxApt = 0;
        
        for(m = 0; m < numind; m++)
        {
            x = indecimal(nextgen[m]);
            apttotal += calc_apt(x);
            if(maxApt < calc_apt(x))
                maxApt = calc_apt(x);
        }
        
        printf("\nSuma:      \t\t\t %d\t\t\n",apttotal);
        printf("Promedio:  \t\t\t\t%d\t\t\n",apttotal/numind);
        printf("Maximo:    \t\t\t\t%d\t\t\n",maxApt);

        printf("\n\t\t\t3.MUTACION\n\n");
        muto = numind * PMUTA;
        printf("No.\t|Descendencia  \t|Mutacion \t|Val X\t\t|Aptitud\n");

        for (m = 0; m < numind; m++)
        {
            printf("%3d\t|   ", m+1);
            for (int n = 0; n < numale; n++)
                printf("%d", nextgen[m][n]);

            printf("\t|    ");
            if ((rand() % 2) && (contador < muto))
            {
                mutar(nextgen[m]);
                contador++;
                printf("#");
            }
            for (n = 0; n < numale; n++)
                printf("%d", nextgen[m][n]);

            x = indecimal(nextgen[m]);
            printf("\t|%6d\t\t|%7d\n",x,calc_apt(x));
        }

        apttotal = 0;
        maxApt = 0;
        
        for(m = 0; m < numind; m++)
        {
            x = indecimal(nextgen[m]);
            apttotal += calc_apt(x);
            if(maxApt < calc_apt(x))
                maxApt = calc_apt(x);
        }

        printf("\nSuma:      \t\t\t %d\t\t\n",apttotal);
        printf("Promedio:  \t\t\t\t%d\t\t\n",apttotal/numind);
        printf("Maximo:    \t\t\t\t%d\t\t\n",maxApt);

        for (m = 0; m < numind; m++)
        {
            x = indecimal(nextgen[m]);

            if (bestgen[k] < obtenerprobar(calc_apt(x),apttotal))
                bestgen[k] = obtenerprobar(calc_apt(x),apttotal);

            if (lessgen[k] > obtenerprobar(calc_apt(x),apttotal))
                lessgen[k] = obtenerprobar(calc_apt(x),apttotal);
        }
    }

    arc_esc(bestgen,1);
    arc_esc(lessgen,0);
    graficar();
    
    return 0;
}

void inicialgo(int cad[][numale+1],double cad2[]){
    int x,m=0;
       for(m = 0; m < numind; m++)
        {
            x = indecimal(cad[m]);
            apttotal += calc_apt(x);
            if(maxApt < calc_apt(x))
                maxApt = calc_apt(x);
        }
        printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)=x^2\t|Probabilidad\t|ValEsp\n");
    int n;
        
        for(m = 0; m < numind; m++)
        {
            printf("%3d\t|  ",m+1);
            for(n = 0; n < numale; n++)
            {
                printf("%d",cad[m][n]);
            }
            x = indecimal(cad[m]);
            cad2[m] = obteneresp(calc_apt(x),((double)apttotal/numind));
            probatotal += obtenerprobar(calc_apt(x),apttotal);
            if(maxProb < obtenerprobar(calc_apt(x),apttotal))
                maxProb = obtenerprobar(calc_apt(x),apttotal);
            printf("\t|%6d\t\t|%5d\t\t|%.4f\t\t|%.4f\n",x,calc_apt(x),obtenerprobar(calc_apt(x),apttotal),cad2[m]);
        }
        
        printf("\nSuma:      \t\t\t %d\t\t\n",apttotal);
        printf("Promedio:  \t\t\t\t%d\t\t\n",apttotal/numind);
        printf("Maximo:    \t\t\t\t%d\t\t\n",maxApt);
}