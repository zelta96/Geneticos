#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<math.h>
#include<unistd.h>

/*********************************************
* Definicion de variables                    *
*********************************************/

#define INDIVIDUOS 16
#define ALELO 4
#define NUM_COMANDOS 4
#define PMUTA 0.2
#define PI 3.141592654
#define PFLIP 0.7

/*********************************************
* Funciones del programa                     *
*********************************************/

void inicia_algo();
void write_arch(double h[], int opc,int GENERACION);
void graphics(void);
int transform(int a[]);
double calc_apt(int x);
double calc_pro(double x, int total);
void met_mutar(int h[]);
void mutaciones();
void met_ruleta(int indiv[][ALELO+1], int hijo[][ALELO+1], int generacionanterior[], int max);
int function_flip();
void met_barajear(int a[]);
void genesis(int a[][ALELO+1]);
int met_torneo(int ganadores[], int indiv1[], int indiv2[], int i1, int i2);

/*********************************************
* Variables globales para otras funciones    *
*********************************************/

double maxApt = 0.0, sumApt = 0.0, minApt = 1.0;
int m,n,gen,GENERACION;
int cad[INDIVIDUOS][ALELO+1], baraja1[INDIVIDUOS], baraja2[INDIVIDUOS], hijos[INDIVIDUOS][ALELO+1], ganador[INDIVIDUOS][ALELO+1];
int generacionanterior[ALELO];
int x, ptCruza, nMuta, contador = 0;
double sumProb = 0.0, maxProb = 0.0, ptr = 0.0, sumAcum = 0.0;



/*********************************************
* Main del programa                          *
*********************************************/

int main(int argc, char *argv[])
{    
    
    srand(getpid());

    int GENERACION;
    GENERACION = atoi(argv[1]);
    double betgen[GENERACION], lessgen[GENERACION];

    for(m = 0; m < INDIVIDUOS; m++)
        betgen[m] = 0.0;

    for(m = 0; m < INDIVIDUOS; m++)
        lessgen[m] = 1.0;

    genesis(cad);

    for(gen = 0; gen < GENERACION; gen++)
    {
        
        printf("\nGeneracion %d\n",gen+1);
        
        for(int y = 0; y < INDIVIDUOS; y++)
        {
            x = transform(cad[y]);
            sumApt += calc_apt(x);
            if(maxApt < calc_apt(x))
                maxApt = calc_apt(x);
        }

        inicia_algo();
        if(gen == 0)
        {
            betgen[0] = maxApt;
            lessgen[0] = minApt;
        }

        printf("\n\nTorneo probabilistico s. \n");
        printf("\n\nPrimer barajeo. \n");
		printf("\n NUMERO |  APT  |barajear |Ganador\n");

        met_barajear(baraja1);
        met_barajear(baraja2);

        
        for( m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d   |  ",m+1);                //orden
            x = transform(cad[m]);
            printf("%4f | ",calc_apt(x));     //Aptitud
            printf("%4d    |",baraja1[m]);          //Baraja1
            if((m % 2) == 0)
				printf("%6d  |",met_torneo(ganador[m],cad[baraja1[m]],cad[baraja1[m+1]],baraja1[m],baraja1[m+1]));    //Ganador1
			else
				printf("    --  |");
            printf("\n");
        }

         printf("\n\nSegundo barajeo \n");
        printf("\n NUMERO |  APT  |barajear |Ganador\n");

        for( m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d   |  ",m+1);                //orden
            x = transform(cad[m]);
            printf("%4f | ",calc_apt(x));     //Aptitud
            printf("%4d     |",baraja2[m]);
            if((m % 2) == 0)
				printf("%4d  ",met_torneo(ganador[m+1],cad[baraja2[m]],cad[baraja2[m+1]],baraja2[m],baraja2[m+1]));    //Ganador1
			else
				printf("  --  ");
            printf("\n");
        }
        
        for(n = 0; n < INDIVIDUOS; n++)
        {
			for(m = 0; m < ALELO; m++)
				cad[n][m]=ganador[n][m];
		}

        printf("\n\nCruza y evaluación de la descendencia. \n\n");
        printf("No.\t|cruza       \t|P Cruza \t|Descendencia\t|Val X       |Aptitud\n");

        for(m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            
            if((m % 2) == 0)            
                ptCruza = (rand() % 3)+1;
            
            for(n = 0; n < ALELO; n++)
            {
                if(n == ptCruza)
                    printf("|%d",cad[m][n]);
                else
                    printf("%d",cad[m][n]);
            }
            printf("\t|%4d\t\t|    ",ptCruza);
            if((m % 2) == 0)
            {
                for(int i = 0; i < ALELO; i++)
                {
                    if(i < ptCruza)
                        hijos[m][i] = cad[m][i];
                    else
                        hijos[m][i] = cad[m+1][i];
        
                    printf("%d",hijos[m][i]);
                }
            }
            else{
                    for(int i = 0; i < ALELO; i++)
                    {
                        if(i < ptCruza)
                            hijos[m][i] = cad[m][i];
                        else
                            hijos[m][i] = cad[m+1][i];

                        printf("%d",hijos[m][i]);
                    }
                }
                
            x = transform(hijos[m]);
            printf("\t|%6d\t     |%f\n",x,calc_apt(x));
        }

        sumApt = maxApt = 0.0;
        for(m = 0; m < INDIVIDUOS; m++)
        {
            x = transform(hijos[m]);
            sumApt += calc_apt(x);
            if(maxApt < calc_apt(x))
                maxApt = calc_apt(x);
        }
        printf("\nSuma Aptitud: %f\n",sumApt);
        printf("Promedio Aptitud: %f\n",sumApt/INDIVIDUOS);
        printf("Maximo Aptitud: %f\n",maxApt);

        mutaciones();

        if(gen > 0)
        {
            betgen[gen] = maxApt;
            lessgen[gen] = minApt;
        }

        met_ruleta(cad,hijos,generacionanterior,sumApt);

        sumApt = maxApt = 0.0;
        minApt = 1.0;
        sumProb = maxProb = ptr = sumAcum = 0.0;
        contador = 0;
    }

    //imprimircaday(betgen);
    //imprimircaday(lessgen);
    write_arch(betgen,1,GENERACION);
    write_arch(lessgen,0,GENERACION);
    graphics();
    
    return 0;
}

/***************************************************
* IMPRESION DE ARCHIVOS                            *
***************************************************/

void write_arch(double h[], int opc,int GENERACION)
{
    FILE* arch = NULL;
    register int k;

    if(opc)
        arch = fopen("betgen.txt","w+");
    else
        arch = fopen("lessgen.txt","w+");

    if (arch == NULL)
    {
        perror("Error al crear el archivo de texto\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (k = 0; k < GENERACION; k++)
        {
            fprintf(arch, "%d %f\n", k+1, h[k]);
        }
    }

    fclose(arch);
}

void graphics(void)
{
    register int t;

    char* configGnuplot[] = {"set title \" Resultados. \"",
                                "set ylabel \"%Fitness\"",
                                "set xlabel \"Generacion\"",
                                "plot \"betgen.txt\" using 1:2 with lines, \"lessgen.txt\" using 1:2 with lines"
                            };

    FILE* ventanaGnuplot = popen("gnuplot -persist", "w");

    for (t = 0; t < NUM_COMANDOS; t++)
    {
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[t]);
    }
}


/***************************************************
* PARTE QUE LE DA VIDA AL ALGORITMO                *
***************************************************/

void inicia_algo(){
            printf("No.\t|Pobla Ini\t|valor X\t|Apt F(X)\t|Probabilidad\n");
        for(int m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|  ",m+1);
            for(int n = 0; n < ALELO; n++)
            {
                printf("%d",cad[m][n]);
            }
            x = transform(cad[m]);
            sumProb += calc_pro(calc_apt(x),sumApt);
            if(maxProb < calc_pro(calc_apt(x),sumApt))
            {
                maxProb = calc_pro(calc_apt(x),sumApt);
                
                for( n = 0; n < ALELO; n++)
                    generacionanterior[n] = cad[m][n];
            }
            printf("\t\t|%8d\t|%f\t|%f\n",x,calc_apt(x),calc_pro(calc_apt(x),sumApt));
        }
        printf("\nSuma Aptitud: %f\\n",sumApt);
        printf("Promedio Aptitud: %f\n",sumApt/INDIVIDUOS);
        printf("Maximo Aptitud: %f\n",maxApt);

}

void mutaciones(){
    
        printf("\n\nMutacion y evaluacion de descendencia. \n\n");
        printf("No.\t|Descendencia  \t|Mutacion \t|Val X\t\t|Aptitud\n");

        nMuta = INDIVIDUOS * PMUTA;

        for (m = 0; m < INDIVIDUOS; m++)
        {
            printf("%3d\t|   ", m+1);
            for (int n = 0; n < ALELO; n++)
                printf("%d", hijos[m][n]);

            printf("\t|    ");
            if ((rand() % 2) && (contador < nMuta))
            {
                met_mutar(hijos[m]);
                contador++;
                printf("->");
            }
            for (n = 0; n < ALELO; n++)
                printf("%d", hijos[m][n]);

            x = transform(hijos[m]);
            printf("\t|%6d\t\t|%f\n",x,calc_apt(x));
        }

        sumApt = maxApt = 0.0;

        for(m = 0; m < INDIVIDUOS; m++)
        {
			x = transform(hijos[m]);
			if(m == 0)
				minApt = calc_apt(x);
			sumApt += calc_apt(x);
			if(maxApt < calc_apt(x))
				maxApt = calc_apt(x);;
			if(minApt > calc_apt(x))
				minApt = calc_apt(x);
		}

        printf("\nSuma:      \tAptitud: %f\n",sumApt);
        printf("Promedio:  \tAptitud: %f\n",sumApt/INDIVIDUOS);
        printf("Maximo:    \tAptitud: %f\n",maxApt);
        printf("Minimo:    \tAptitud: %f\n",minApt);

}

int transform(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (ALELO - 1); i < ALELO; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}

double calc_apt(int x)
{
    int h = x - 5;
    double b = 2.0 + sin(x/(180*PI));
   return ((float) h/b) < 0 ? (-1)*((float) h/b) : ((float) h/b);
}

double calc_pro(double x, int total)
{
    return 1.00*x/total;
}


void met_mutar(int h[])
{
    register int k;
    int alelo = rand() % ALELO;

    for(k = 0; k < ALELO; k++)
    {
        if(k == alelo)
            h[k] = (h[k]== 0) ? 1 : 0;
    }
}

int function_flip()
{
    double n = 0.0;
    n = (float) (rand() % 101) / 100;
    
    if (n >= PFLIP)
        return 1;
    else
        return 0;
    
}

void met_barajear(int a[])
{
    int elegidos[INDIVIDUOS]; 
    int posibles = INDIVIDUOS, contador, posicion, i, j;

    
    for( i = 0; i < INDIVIDUOS; i++)
        elegidos[i] = 0;    
    
    
    for( i = 0; i < INDIVIDUOS; i++)
    {
        posicion = rand() % posibles+1; 
        j = 0;
        contador = 0;             
        
        while(contador < posicion)
        {
            if(!elegidos[j++])
                contador++;         
        }
        j--;                        
        elegidos[j] = 1;        
        posibles--;                 
        a[i] = j+1;                
    }
}

void met_ruleta(int indiv[][ALELO+1], int hijo[][ALELO+1], int generacionanterior[], int max)
{
    int i,j,k;
    int rul, acum, dec;
    
    for( i = 0; i < ALELO; i++)
    {
        indiv[0][i] = generacionanterior[i]; 
    }
    
    for( i = 1; i < INDIVIDUOS; i++)
    {
        acum = 0;
        rul = rand()%(max+1);
        
        for( j = 0; j < INDIVIDUOS; j++)
        {
            dec = transform(hijo[j]);
            acum += calc_apt(dec);
            if (acum >= rul)
            {
                for( k = 0; k < ALELO; k++)
                    indiv[i][k] = hijo[i][k];  
                break;
            }
        }
    }
}

int met_torneo(int ganadores[], int indiv1[], int indiv2[], int i1, int i2)
{
    int iflip = function_flip();
    register int i;

    if(iflip == 1)       //si es verdadero entonces gana el de mejor aptitud
    {
        if ( calc_apt(transform(indiv1)) >= calc_apt(transform(indiv2)))
        {
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv1[i];
            
            return i1;
        }else{
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv2[i];

            return i2;
        }
    }else{                  //Si es falso entonces gana el de baja aptitud
        if ( calc_apt(transform(indiv1)) < calc_apt(transform(indiv2)))
        {
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv1[i];
            
            return i1;
        }else{
            for( i = 0; i < ALELO; i++)
                ganadores[i] = indiv2[i];

            return i2;
        }
    }
}

void genesis(int a[][ALELO+1])
{
    register int i,j;
    int alelo;
    
    for(i = 0; i < INDIVIDUOS; i++)
    {
        for(j = 0; j < ALELO; j++)
        {
            alelo = rand() % 2;
            a[i][j] = alelo;
        }
    }
}
