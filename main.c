#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>
#include <inttypes.h>

int main(){
        printf("\n");
        WinterIsHere_t dragon = WinterIsComing();
        printf("Tabla ingresada:\n" );
        printable(dragon);
        uint32_t c = 1;
        uint32_t i = 10;
        WinterSt_t walker = *dragon->WinterSt;
        int greedy = (int)Greedy(dragon);
        printf("greedy:\n" );
        printable(dragon);
        int bipartito = Bipartito(dragon);
        int vertices = (int)NumeroDeVertices(dragon);
        int lados = (int)NumeroDeLados(dragon);
        int verticescolor = (int)NumeroVerticesDeColor(dragon, c);
        int colores = (int)NumeroDeColores(dragon);
        int ivertice = (int)IesimoVerticeEnElOrden(dragon, i);
        int nombre = (int)NombreDelVertice(dragon, c);
        int color = (int)ColorDelVertice(dragon, c);
        int grado = (int)GradoDelVertice(dragon, c);
        int ivecino = (int)IesimoVecino(dragon, c, c);

        printf("Greedy = %d\n",greedy);
        printf("Bipartito = %s\n", bipartito == 1 ? "Si" : "No");

        printf("Numero de vertices = %d\n", vertices);
        printf("Numero de lados = %d\n", lados);
        printf("Numero de vertices de color = %d\n", verticescolor);
        printf("Numero de colores = %d\n", colores);
        printf("Indice del vertice = %d\n", ivertice);
        printf("Nombre del vertice = %d\n", nombre);
        printf("Color del vertice = %d\n", color);
        printf("Grado del vertice = %d\n", grado);
        printf("Indice del vecino = %d\n", ivecino);

        printf("\n");
        CambiarDatos(&walker->graph[0], &walker->graph[1]);
        printf("swap:\n");
        printable(dragon);
        printf("\n");
        QuickSort(dragon,vertices);
        printf("QuickSort\n");
        printable(dragon);
        OrdenWelshPowell(dragon);
        printf("WelshPowell\n");
        printable(dragon);
        AleatorizarVertices(dragon, 2);
        printf("Aleatorizar vertices\n");
        printable(dragon);
        ReordenManteniendoBloqueColores(dragon, 0);
        printf("r 1 2 ... r-1\n");
        printable(dragon);
        ReordenManteniendoBloqueColores(dragon, 1);
        printf("r r-1 ... 2 1\n");
        printable(dragon);
        printf("\n");
        Primavera(dragon);
        return 0;
}
