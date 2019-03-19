#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int renglones;
	int columnas;
}Dimension;


typedef struct{
    Dimension dimension;
    float **matriz;
}Matriz;

void captura(Matriz *);
void inicializaIdentidad(Matriz *, Matriz *);
void calculaInversa(Matriz *, Matriz *);
void imprimeMatriz(Matriz *);
void setMemoria(Matriz *);

int main()
{
    Matriz matriz  = { {0,0} , NULL};
    Matriz inversa = { {0,0} , NULL};

    do{

        //Asignacion de memoria a las matrices.
        printf("Ingrese dimension para Matriz Cuadrada: \n");
        scanf("%d", &matriz.dimension.renglones);
        matriz.dimension.columnas = matriz.dimension.renglones;
        inversa.dimension.renglones = matriz.dimension.renglones;
        inversa.dimension.columnas = 2*matriz.dimension.renglones;

        if(matriz.dimension.renglones > 1){
        	setMemoria(&matriz);
        	setMemoria(&inversa);    
        }

        else printf("Ingrese dimension mayor a 1\n");
        
    } while (matriz.dimension.renglones <= 1);
    //Fin de asignacion.

    captura(&matriz);
    inicializaIdentidad(&matriz,&inversa);
    calculaInversa(&matriz,&inversa);
    imprimeMatriz(&inversa);

    //Liberacion de memoria cuando termina el programa.
    free(matriz.matriz);
    free(inversa.matriz);
    return 0;
}

void setMemoria(Matriz *M)
{
	M->matriz = (float**) calloc(M->dimension.renglones, sizeof(float *)) ;
	if (M->matriz == NULL) printf("No se pudo asignar memoria a Matriz\n");
	for (int i=0; i < M->dimension.renglones; i++)
	{
		M->matriz[i] = (float*) calloc(M->dimension.columnas, sizeof(float));
		if(M->matriz[i] == NULL) printf("No se pudo asignar memoria a Matriz[%d]\n", i );
	}

}

void captura(Matriz *M){

    int i, j;

    for(i = 0; i < M->dimension.renglones; i++){
        for(j = 0; j < M->dimension.renglones; j++){
            if(i==0 && j==0){
                printf("M[%d][%d] debe ser diferente 0.\n",i,j);
            }
            printf("Ingrese dato para M[%d][%d]:  ",i,j);
            scanf("%f", &M->matriz[i][j]);
            printf("\n");
        }
    }
}

void inicializaIdentidad(Matriz *matriz, Matriz *inversa){
// x matriz, y inversa
    int i,j;
    //Matriz con la que haremos los calculos.
    for(i = 0; i < matriz->dimension.renglones; i++)

        for(j = 0; j < inversa->dimension.columnas; j++)
        {
            
            if(j == (matriz->dimension.renglones + i))
                inversa->matriz[i][j] = 1;
            
            else if(j >= matriz->dimension.renglones)
                inversa->matriz[i][j] = 0;
            
            else
                inversa->matriz[i][j] = matriz->matriz[i][j];
        }
}

void calculaInversa(Matriz *matriz, Matriz *inversa){

    int i,j,k;
    float temp;

    for(i = 0; i < matriz->dimension.renglones; i++)

        for(j = 0; j < matriz->dimension.renglones; j++){
            if(i==j){
                temp = inversa->matriz[i][j];
                
                for(k = 0; k < inversa->dimension.columnas; k++)
                    inversa->matriz[i][k]/=temp;   
            }

            if(i!=j){
                temp = inversa->matriz[j][i]/inversa->matriz[i][i];
                
                for(k = 0; k < inversa->dimension.columnas; k++)
                    inversa->matriz[j][k] = inversa->matriz[j][k] - temp*inversa->matriz[i][k];
            }
        }
}

void imprimeMatriz(Matriz *M){
    //funcion para imprimir x matriz
    int i,j;
    for(i = 0; i < M->dimension.renglones; i++){
        for(j = 0; j < M->dimension.columnas; j++)
            printf("%.2f\t\t",M->matriz[i][j]);
        
        printf("\n");
    }
}
