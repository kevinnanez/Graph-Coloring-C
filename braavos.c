#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>
#include <inttypes.h>
//Funciones para extraer informacion de los datos del grafo

//devuelve el numero de vertices de w
int32_t NumeroDeVertices(WinterIsHere_t w){
  return w->WinterSt->v;
}

//Devuelve el numero de lados de w
int32_t NumeroDeLados(WinterIsHere_t w){
  return w->WinterSt->l;
}

//Devuelve el numero de vertices de color i
int32_t NumeroVerticesDeColor(WinterIsHere_t w, int32_t i){
  int32_t j = 0;
  int32_t k = 0;
  while(k < w->WinterSt->v){
    if(w->WinterSt->graph[k][2] == i){
      j++;
    }
    k++;
  }
  return j;
}

//devuelve la cantidad de colores usados en el coloreo de W
int32_t NumeroDeColores(WinterIsHere_t w){
  int32_t j = 0;
  int32_t i = 0;
  while(i < w->WinterSt->v){
    if(w->WinterSt->graph[k][2] > j){
      j = WinterSt->graph[k][2]
    }
  }
  return j;
}

//devuelve la etiqueta del vertice numero i
int32_t IesimoVerticeEnElOrden(WinterIsHere_t w, int32_t i){
  int32_t j = 0;
  int32_t k = 0;
  while(k < w->WinterSt->v) {
          if(i == (*w).graph[j][0]){
            j = k;
            break;
          }
    k++;
  }
  return j;
}
