#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<math.h>
#include<unistd.h>

void cruzar(int p1[], int p2[], int h[], int n, int numale, int conta);
void doble_cruza(int p1[],int p2[], int h[], int pt1, int pt2, int numale);
void cruzaxul2(int numale, int pt1,int pt2,int m,int cad[]);
void uni_cruza(int p1[], int p2[],int h[], int patron[],int numale);

void ace_cruza(int p1[], int p2[],int h[], int mP1[], int mP2[],int numale);
int menu();

char resp;

int main()
{   
    int gene,n,j;
    int cru, cru2, contador,indice;
    srand(getpid());
    int numind, numale;
    printf("Numero de numind");
    scanf("%d", &numind);
    
    if((numind % 2) != 0){
        numind=numind+1;
            
    }
     int cad[numind][numale+1];

    printf("numero de alelo:");
    scanf("%d", &numale);
    
    printf("forzando a un individuo mas %d\n",numind);

   int nexgen[numind][numale+1], auxre[numale], marcas[numind][numale+1];
    int tam = numale/2;
    
    int xx,yy,i;
    int alelo;
    
    for(xx = 0;xx < numind; xx++)
    {
        for(yy = 0; yy < numale; yy++)
        {
            alelo = rand() % 2;
            cad[xx][yy] = alelo;
        }
    }

    
    while ((getchar()) != '\n');
    do{
        menu();
        switch(resp){
            case '1':
                printf("\tAGENTE.\t|a cruzar       \t|Cruzado \t|Descendencia\n");
                    for(gene = 0; gene < numind; gene++)
                    {   
                        if((gene % 2) == 0){
                        printf(" %d\t|  ",gene+1);           
                        cru = (rand() % (numale-1))+1;
                        //printf("pto cruza %d\n",cru);
                        for(n = 0; n < numale; n++)
                        {
                            if(cru == n){
                                printf("|%d",cad[gene][n]);
                            }
                            else
                            {
                                printf("%d",cad[gene][n]);
                            }
                        }
                        printf("\t|%4d\t\t|  ",cru);
                        if((gene% 2) == 0)
                            cruzar(cad[gene],cad[gene+1],nexgen[gene],cru,numale,gene+2);
                        printf("\n");
                        }
                    }

                
                printf("\n\nCOntinue...");
                while ((getchar()) != '\n');
                resp = 0;
                break;
                
            case '2':
                printf("\tAGENTE.\t|a cruzar       \t|Cruzado \t|Descendencia\n");
                
                    for(gene = 0; gene < numind; gene++)
                    {
                        printf("%3d\t|  ",gene+1);
                        
                        if((gene % 2) == 0)
                        {            
                            cru = (rand() % (numale-1))+1;
                            cru2 = (rand() % (numale-1))+1;
                        }
                        
                        cruzaxul2(numale,cru,cru2,gene,cad[gene]);
                        if((gene % 2) == 0)
                            doble_cruza(cad[gene],cad[gene+1],nexgen[gene],cru,cru2,numale);
                        else
                            doble_cruza(cad[gene],cad[gene-1],nexgen[gene],cru,cru2,numale);
                        
                        printf("\n");
                    }
                    printf("\n");
                
                printf("\n\nCOntinue...");
                while ((getchar()) != '\n');
                resp = 0;
                break;
                
            case '3':
                printf("\tAGENTE.\t|a cruzar       \t|Cruzado \t|Descendencia\n");
                    for(gene = 0; gene < numind; gene++)
                    {
                        printf("%3d\t|  ",gene+1);
                        
                        if(gene % 2 == 0){
                                for(i = 0; i < numale; i++){
                                    auxre[i] = 0;
                                }
                                contador=0;
                                while(contador < tam)
                                {
                                    indice = rand() % numale;
                                    j = 0;
        
                                    while(j < indice)
                                        j++;
        
                                    if(!auxre[j]){
                                        auxre[j] = 1;
                                        contador++;
                                    }   
                                }
                        }
                        
                        for(n = 0; n < numale; n++)
                        {    
                            printf("%d",cad[gene][n]);
                            
                        }

                        printf("\t| ");

                        for(n = 0; n < numale; n++)
                        {    
                            printf("   %d",auxre[n]);
                            
                        }
                        
                        printf("\t|  ");
                        
                        if((gene % 2) == 0)
                            uni_cruza(cad[gene],cad[gene+1],nexgen[gene],auxre,numale);
                        else
                            uni_cruza(cad[gene],cad[gene-1],nexgen[gene],auxre,numale);
                        
                        printf("\n");
                    }
                printf("\n\nCOntinue...");
                while ((getchar()) != '\n');
                resp = 0;
                break;
            
            case '4':
            	printf("\nNo.\t|P.Ini       \t|Marcas  \t|Descendencia\n");
            	
            		for(i = 0; i < numind; i++){
		                for(j = 0; j < numale; j++){
			                n = rand() % 2;
			                marcas[i][j] = n;
		                }
	                }
            	
            	
            		for(gene = 0; gene < numind; gene++){
            			printf("%3d\t|  ",gene+1);
            			for(n = 0; n < numale; n++){
                            printf("%d",cad[gene][n]);
                        }
                        printf("\t|");
                        for(n = 0; n < numale; n++){
                            printf("%d  ",marcas[gene][n]);
                        }
                           

                        
                        if((gene % 2) == 0)
                        	ace_cruza(cad[gene],cad[gene+1],nexgen[gene],marcas[gene],marcas[gene+1],numale);
                        else
                        	ace_cruza(cad[gene],cad[gene-1],nexgen[gene],marcas[gene],marcas[gene-1],numale);
                        
                        printf("\n");
            		}
            	printf("\n\nCOntinue...");
                while ((getchar()) != '\n');
                resp = 0;
                break;

        }
    
    }while(resp != '5' );
    
    return 0;
}

int menu(){
        //printf("funciona");
        printf("\nTipos de cruza......\n\n");
        printf("Cruza punto...........1\n");
        printf("Cruza dos punto.......2\n");
        printf("Cruza uniforme.........3\n");
        printf("Cruza acentuada.........4\n");
        printf("Exit...................5\n");
        printf("Ingrese la opcion deseada: ");
        resp = getchar();
        return resp;
}

void cruzar(int p1[], int p2[], int h[], int n, int numale, int conta)
{
    register int i;
    
    for(i = 0; i < numale; i++)
    {
        if(i < n)
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf(" %d",h[i]);
    }
    printf("\n");
    printf("  %d\t",conta);
    for(i = 0; i < numale; i++)
    {
        if(i == n)
            printf(" |%d",p2[i]);
        else
        printf(" %d",p2[i]);
    }
    printf("\t\t\t\t");
    for(i = 0; i < numale; i++)
    {
        if(i < n)
            h[i] = p2[i];
        else
            h[i] = p1[i];
        
        printf(" %d",h[i]);
    }
}

void doble_cruza(int p1[],int p2[], int h[], int pt1, int pt2, int numale)
{
    register int i;
    
    for(i = 0; i < numale; i++)
    {
        if(i < pt1)
            h[i] = p1[i];
        else{
            if(i <= pt2)
                h[i] = p2[i];
            else
                h[i] = p1[i];
        }
        
        printf("%d",h[i]);
    }
}

void uni_cruza(int p1[], int p2[],int h[], int patron[],int numale)
{
    register int i;
    
    for(i = 0; i < numale; i++){
        if(patron[i])
            h[i] = p1[i];
        else
            h[i] = p2[i];
        
        printf("%d",h[i]);
    }
}

void ace_cruza(int p1[], int p2[],int h[], int mP1[], int mP2[],int numale)
{
	register int i;
	int flagP1 = 1;
	
	for(i = 0; i < numale; i++){
		if(!mP1[i] && !mP2[i]){
			if(flagP1)
				h[i] = p1[i];
			else
				h[i] = p2[i];
		}else{
			if(flagP1)
				h[i] = p1[i];
			else
				h[i] = p2[i];
			if(flagP1)
				flagP1 = 0;
			else
				flagP1 = 1;
		}
		printf("%d",h[i]);
	}
}

void cruzaxul2(int numale, int pt1,int pt2,int m,int cad[]){
    int n;
    for(n = 0; n < numale; n++)
    {
        if(pt1 == n)
            printf("|%d",cad[n]);
        else if(pt2 == n)
            printf("%d|",cad[n]);
        else
        printf("%d",cad[n]);
    }
    printf("\t|%4d,%d\t\t|  ",pt1, pt2);

}