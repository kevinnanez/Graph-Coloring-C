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
  uint32_t c = 1;
  uint32_t i = 10;
  int greedy = (int)Greedy(dragon);
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
  printf("Bipartito = %s\n", bipartito == 1 ? "Si":"No");
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
  Primavera(dragon);
  return 0;
}
