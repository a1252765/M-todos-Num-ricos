#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <Windows.h>

float Trapecio(float *a,float *b, int funcion);
float TrapecioMultiple(float *a, float *b, float *n, int funcion);
float Funcion(float x, int funcion);
float Error(float a, float b, int tipo, int funcion);


void Submenu1();
void Submenu2();
void Submenu3();


int main()
{ int metodo, opcion = 1;

    system("cls");
    printf("INTEGRACION NUMERICA\n");

    do{

        printf("Metodo: \n\n");
        printf("  [1] Trapecio\n");
        printf("  [2] Simpson 1/3\n");
        printf("  [3] Simpson 3/8\n");
        printf("  [4] Salir\n");
        scanf("%d", &metodo);



        switch(metodo)
        {
            case 1: Submenu1();
                    break;
            case 2: Submenu2();
                    break;
            case 3: Submenu3();
                    break;
            case 4: opcion = 0;
                    break;
        }

    } while(opcion);


}

void Submenu1()
{ int metodo, funcion, opcion = 1 ; float a,b,n;

    system("cls");
    do{

        printf("  [1] Trapecio Simple\n");
        printf("  [2] Trapecio Multiple\n");
        printf("  [3] Salir\n");

        scanf("%d", &metodo);

        if (metodo != 3)
        {
            printf("Funcion:\n\n");
            printf("[1] 0.2 + 25x -200x^2 + 675x^3 - 900x^4 + 400x^5\n");
            printf("[2] 1 - e^-2x\n");
            printf("[3] 6 + Cos(x)\n\n");
            scanf("%d", &funcion);

        } 
        else metodo = 4;

        if (funcion != 4)
        {
            switch(metodo)
            {
                case 1: printf("Resultado: %f\n\n", Trapecio(&a,&b,funcion));
                        printf("Error: %f \n", Error(a,b,1,funcion));
                        break;
                case 2: printf("Resultado: %f\n\n", TrapecioMultiple(&a,&b, &n, funcion));
                        break;
                case 4: opcion = 0;
                        break;
            }
        }

        else opcion = 0;

    } while (opcion);

    system("cls");

}


void Submenu2()
{
    system("cls");
}

void Submenu3()
{
    system("cls");
}

float Error(float a, float b, int tipo, int funcion)
{   float resultado;

    switch (tipo)
    {
        case 1: resultado = -pow((b-a),2)*((Funcion(a,funcion + 10) + Funcion(b, funcion + 10))*(b-a)/2)/12 ;
                break;
    }

    return resultado;
}

float Trapecio(float *a, float *b, int funcion)
{ float resultado; 

    system("cls");

    printf("Intervalo [a,b]\n\n");    
    printf("a: ");
    scanf("%f", a);
    printf("\nb: ");
    scanf("%f", b);
    printf("\n");

    resultado = (Funcion(*a,funcion) + Funcion(*b,funcion))*(*b-*a)/2;

    return resultado;
}

float TrapecioMultiple(float *a, float *b, float *n, int funcion)
{ float resultado, acumulador = 0, h; int i;

    system("cls");

    printf("Intervalo [a,b]\n\n");    
    printf("a: ");
    scanf("%f", a);
    printf("\nb: ");
    scanf("%f", b);
    printf("\nn: ");
    scanf("%f", n);
    printf("\n");

    // de donde a donde va?

    h = (*b-*a)/ *n;
    for(i = 1; i < *n; i++)
        acumulador = acumulador + Funcion(*a+i*h, funcion);

    resultado = (Funcion(*a,funcion) + 2*acumulador + Funcion(*b,funcion))*h/2;

    return resultado;
}


float Funcion(float x, int funcion)
{   float resultado;

    switch (funcion)
    {
        case 1: resultado = 0.2 + 25*x -200*pow(x,2) + 675*pow(x,3) - 900*pow(x,4) + 400*pow(x,5);
                break;
        case 2: resultado = 1 - pow(M_E,-2*x);
                break;
        case 3: resultado = 6 + cos(x);

        // segunda derivada de funciones
        case 11: resultado = -400*x + 675*3*pow(x,2) -900*4*pow(x,3) + 400*5*pow(x,4);
                 break;
        case 12: resultado = -4*pow(M_E,-2*x);
                 break;
        case 13: resultado = -cos(x);
                 break;
    }

    return resultado;
}
