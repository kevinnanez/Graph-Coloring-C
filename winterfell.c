#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>

//Creamos la estructura vertice, que representa cada vertice del grafo.
//grade es la cantidad de conexiones, n es el nombre.
struct _vertex_t{
  uint32_t grade;
  uint32_t color;
  uint32_t n;
}

//creamos la estructura WinterSt que contiene toda la informacion del grafo.
struct _WinterSt_t {
  uint32_t v;
  uint32_t l;
  vertex_t g[];
}

//creamos un puntero  una estructura de datos WinterSt.
struct _WinterIsHere_t{
  WinterSt_t *WinterSt;
}

//alocamos memoria, inicializamos la estructura WinterSt, leemos un grafo DIMACS
//cargamos la informacion y devolvemos un puntero a esta.
WinterIsHere_t WinterIsComing(void){
  WinterSt_t graph = NULL;
  
}
