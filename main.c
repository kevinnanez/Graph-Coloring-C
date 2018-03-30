#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "TheOutsider.h"
#include <stdint.h>
#include <inttypes.h>

int main(){
        printf("\n");
        Grafo_t graph = ConstruccionDelGrafo();
        printf("Tabla ingresada:\n" );
        printable(graph);
        uint32_t c = 1;
        uint32_t i = 10;
        GrafoSt_t pointer = *graph->GrafoSt;
        int greedy = (int)NotSoGreedy(graph, 512);
        printf("NotSogreedy:\n" );
        printable(graph);
        int bipartito = Bipartito(graph);
        int vertices = (int)NumeroDeVertices(graph);
        int lados = (int)NumeroDeLados(graph);
        int verticescolor = (int)NumeroVerticesDeColor(graph, c);
        int colores = (int)NumeroDeColores(graph);
        int ivertice = (int)IesimoVerticeEnElOrden(graph, i);
        int nombre = (int)NombreDelVertice(graph, c);
        int color = (int)ColorDelVertice(graph, c);
        int grado = (int)GradoDelVertice(graph, c);
        int ivecino = (int)IesimoVecino(graph, c, c);

        printf("Greedy = %d\n",greedy);
        printf("Bipartito = %s\n", bipartito == 1 ? "Si" : "No");

        printf("Numero de vertices = %d\n", vertices);
        printf("Numero de lados = %d\n", lados);
        printf("Numero de vertices de color 1 = %d\n", verticescolor);
        printf("Numero de colores = %d\n", colores);
        printf("Indice del vertice = %d\n", ivertice);
        printf("Nombre del vertice = %d\n", nombre);
        printf("Color del vertice = %d\n", color);
        printf("Grado del vertice = %d\n", grado);
        printf("Indice del vecino = %d\n", ivecino);

        printf("\n");
        CambiarDatos(&pointer->graph[0], &pointer->graph[1]);
        printf("swap:\n");
        printable(graph);
        printf("\n");
        QuickSort(graph,vertices);
        printf("QuickSort\n");
        printable(graph);
        OrdenWelshPowell(graph);
        printf("WelshPowell\n");
        printable(graph);
        AleatorizarVertices(graph, 23);
        printf("Aleatorizar vertices\n");
        printable(graph);
        ReordenManteniendoBloqueColores(graph, 0);
        printf("r 1 2 ... r-1\n");
        printable(graph);
        ReordenManteniendoBloqueColores(graph, 1);
        printf("r r-1 ... 2 1\n");
        printable(graph);
        ReordenManteniendoBloqueColores(graph, 2);
        printf("|c1|<|c2|<...<|cr|\n");
        printable(graph);
        ReordenManteniendoBloqueColores(graph, 3);
        printf("|c1|>|c2|>...>|cr|\n");
        printable(graph);
        printf("\n");
        ReordenManteniendoBloqueColores(graph, 4);
        printf("colores aleatorios 4\n");
        printable(graph);
        printf("\n");
        ReordenManteniendoBloqueColores(graph, 5);
        printf("colores aleatorios 5\n");
        printable(graph);
        printf("\n");
        ReordenManteniendoBloqueColores(graph, 6);
        printf("colores aleatorios 6\n");
        printable(graph);
        printf("\n");
        return 0;
}
