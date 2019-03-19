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
Matriz multiplicaMatriz(Matriz *, Matriz *);
Matriz Inversa(Matriz *);

int main()
{
    Matriz matriz  = { {0,0} , NULL};
    Matriz identidad = { {0,0} , NULL};
	Matriz resultante;

    do{

        printf("Ingrese dimension para Matriz Cuadrada: \n");
        scanf("%d", &matriz.dimension.renglones);
        matriz.dimension.columnas = matriz.dimension.renglones;
        identidad.dimension.renglones = matriz.dimension.renglones;
        identidad.dimension.columnas = 2*matriz.dimension.renglones;

        if(matriz.dimension.renglones > 1){
        	setMemoria(&matriz);
        	setMemoria(&identidad);
        }

        else printf("Ingrese dimension mayor a 1\n");

    } while (matriz.dimension.renglones <= 1);

	Matriz b = {{matriz.dimension.renglones,1},NULL};
	setMemoria(&b);

    captura(&matriz);
    imprimeMatriz(&matriz);
	captura(&b);

    inicializaIdentidad(&matriz,&identidad);

    calculaInversa(&matriz,&identidad);
    imprimeMatriz(&matriz);
	imprimeMatriz(&identidad);

	Matriz inversa = Inversa(&identidad);

	resultante = multiplicaMatriz(&inversa,&b);

	imprimeMatriz(&resultante);
	printf("Hola");

    free(matriz.matriz);
    free(identidad.matriz);
    printf("ola");

    return 0;
}

Matriz Inversa(Matriz *M){
	int i,j;
	Matriz resultante={{M->dimension.renglones,M->dimension.renglones},NULL};
	setMemoria(&resultante);

	for(i = 0; i< M->dimension.renglones; i++)
		for (j = 0; j < M->dimension.columnas;j++)
				resultante.matriz[i][j] = M->matriz[i][j+M->dimension.renglones];
	return resultante;
}

void setMemoria(Matriz *M)
{	int i;
	M->matriz = (float**) calloc(M->dimension.renglones, sizeof(float *)) ;
	if (M->matriz == NULL) printf("No se pudo asignar memoria a Matriz\n");
	for (i=0; i < M->dimension.renglones; i++)
	{
		M->matriz[i] = (float*) calloc(M->dimension.columnas, sizeof(float));
		if(M->matriz[i] == NULL) printf("No se pudo asignar memoria a Matriz[%d]\n", i );
	}

}

void captura(Matriz *M){

    int i, j;

    for(i = 0; i < M->dimension.renglones; i++){
        for(j = 0; j < M->dimension.columnas; j++){
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
	printf("\n");
}

Matriz multiplicaMatriz(Matriz *m1, Matriz *m2)
{	Matriz MatrizResultante = {{m1->dimension.renglones, m2->dimension.columnas}, NULL};
	setMemoria(&MatrizResultante);

	int i,j,k;
		for(i=0; i < m1->dimension.renglones; i++)
			for(j=0; j< m2->dimension.columnas; j++)
				for(k=0; k< m1->dimension.columnas; k++)
					MatrizResultante.matriz[i][j] += m1->matriz[i][k] * m2->matriz[k][j];
	return MatrizResultante;

}
