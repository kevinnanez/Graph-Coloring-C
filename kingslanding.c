#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>
#include <inttypes.h>
//Funciones de los vertices

//devuelve el nombre real del vertice cuya etiqueta es x
int32_t NombreDelVertice(WinterIsHere_t w, int32_t x){
  return w->WinterSt->graph[x][0];
}

//devuelve el color con el que esta coloreado el vertice x

int32_t ColorDelVertice(WinterIsHere_t w, int32_t x){
  return w->WinterSt->graph[x][2];
}

//devuelve el grado del vertice x

int32_t GradoDelVertice(WinterIsHere_t w, int32_t x){
  return w->WinterSt->graph[x][1];
}

//devuelve la etiqueta del vecino numero i del vertice x

int32_t IesimoVecino(WinterIsHere_t w, int32_t x, int32_t i){
  return w->WinterSt->graph[x][i+2];
}
