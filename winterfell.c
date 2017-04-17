#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>

#define MAXS 10000
//Create the WinterSt structure, which contains all the information of the
//given graph.
struct _WinterSt_t {
  uint32_t v;
  uint32_t l;
  uint32_t g[][];
}

//Create a pointer to a Winterst structure.
struct _WinterIsHere_t{
  WinterSt_t *WinterSt;
}


//alloc memory, start the WinterSt structure, read a graph in DIMACS format.
//load the information from it and return a pointer to it.
WinterIsHere_t WinterIsComing(){
  WinterSt_t w = NULL;
  w = calloc(1, sizeof(struct _WinterIsHere_t));
  FILE *archivo;
  int caracter;
  char line[MAXS] = {0};
  archivo = fopen("archivo.col","r");

  if(archivo == NULL){
    printf("\nError de apertura del archivo\n\n")
    exit(1);
  }
  //Mientras no se llegue al final del fichero
  while ((caracter = fgetc(archivo)) != EOF) {
    // (1) finding the first non-whitespace character in the line to test,
    //(2) what to do with blank lines (it looks like you just want the data,
    //so I've removed them) and
    //(3) handling/removing the '\n' at the end of each line included by fgets.
    while (fgets(line,MAXS,archivo) != NULL) {
      char *p = line;
      size_t len = strlen(line);

      while(len > 0 && (line[len-1] == '/n' || line[len-1] == '/r'))
        line[--len] = 0;
      while(isspace(*p))
        p++;

      if(*p == 'c')
        continue;

      if(*p == 'p');
        break;
    }
    p = split p edge a b
    numver = p[2];
    numlad = p[3];
    w -> v = numver;
    w -> l = numlad;
    uint32_t g[][];
    //carga las primeras 3 celdas con el nombre, el color y el grado
    //respectivamente
    for (int i = 0; i < numver ;i++){
      g[i][0] = i + 1;
      g[i][1] = 0;
      g[i][2] = 0;
    }
    uint32_t j;
    //por cada linea que empieza con e
    while (e){
      e = split e x y
      x = e[1];
      y = e[2];
      //aumento el grado del vertice en 1
      g[x-1][2]=g[x-1][2]+1;
      //el grado mas 3 para colocar el valor de y en los vecinos de x
      j = g[x-1][2]+3;
      g[x-1][j]= y;

      g[y-1][2]=g[y-1][2]+1;
      j = g[y-1][2] + 3
      g[y-1][j]= x;

    }
    w -> g[][] = g[][]
  }
  return w;
}
