#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define numind 16
#define ptralelo 5
#define NUM_COMANDOS 4
#define GEN 10
#define PI 3.141592654
#define MAX 1.1

void genesis (int a[][ptralelo+1])
{
    register int i,j;
    int alelo;
    
    for(i = 0; i < numind; i++)
    {
        for(j = 0; j < ptralelo; j++)
        {
            alelo = rand() % 2;
            a[i][j] = alelo;
        }
    }

}

int indecimal(int a[])
{
    int decimal = 0;
    register int i,j;
    
    for( i = 0, j = (ptralelo - 1); i < ptralelo; i++, j--)
    {
        decimal += pow(2,i)*a[j];
    }
    
    return decimal;
}

double calc_apt(int x)
{
   int a = x - 5;
    double b = 2.0 + sin(x/(180*PI));
   return ((float) a/b) < 0 ? (-1)*((float) a/b) : ((float) a/b);
}

double obtenerprobar(int x, int total)
{
    return 1.00*x/total;
}

double obteneresp(int fi, double f)
{
    return 1.00*fi/f;
}

void cruzar(int p1[], int p2[], int h[], int n)
{
    register int i;
    
    for(i = 0; i < ptralelo; i++)
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
    int alelo = rand() % ptralelo;

    for(k = 0; k < ptralelo; k++)
    {
        if(k == alelo)
            h[k] = (h[k]== 0) ? 1 : 0;
    }
}


void arc_esc(double h[], int opc)
{
    FILE* arch = NULL;
    register int k;

    if(opc)
        arch = fopen("bestgen.txt","w+");
    else
        arch = fopen("lessgen.txt","w+");

    if (arch == NULL)
    {
        perror("Error al crear el archivo de texto\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (k = 0; k < GEN; k++)
        {
            fprintf(arch, "%d %f\n", k, h[k]);
        }
    }

    fclose(arch);
}

void graficar(void)
{
    register int t;

    char* configGnuplot[] = {"set title \" Progrma 3. \"",
                                "set ylabel \"Aptitud\"",
                                "set xlabel \"GEN\"",
                                "plot \"bestgen.txt\" using 1:2 with lines, \"lessgen.txt\" using 1:2 with lines"
                            };

    FILE* ventanaGnuplot = popen("gnuplot -persist", "w");

    for (t = 0; t < NUM_COMANDOS; t++)
    {
        fprintf(ventanaGnuplot, "%s \n", configGnuplot[t]);
    }
}

