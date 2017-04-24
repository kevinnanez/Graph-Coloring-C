#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>
#include <string.h>

#define MAXS 10000
//Create the WinterSt structure, which contains all the information of the
//given graph.
struct _WinterSt_t {
        uint32_t v;
        uint32_t l;
        uint32_t graph[MAXS][MAXS];
};

//Create a pointer to a Winterst structure.
struct _WinterIsHere_t {
        WinterSt_t *WinterSt;
};


//alloc memory, start the WinterSt structure, read a graph in DIMACS format.
//load the information from it and return a pointer to it.
WinterIsHere_t WinterIsComing(){
        WinterSt_t w = calloc(1, sizeof(struct _WinterIsHere_t));
        FILE *archivo;
        char ignore[1];
        uint32_t x,y,j,numver,numlad, i, columns, row;
        char line[MAXS] = {0};
        //carga las primeras 3 celdas con el nombre, el color y el grado
        //respectivamente
        for (i = 0; i < numver; i++) {
                (*w).graph[i][0] = i + 1;
                (*w).graph[i][1] = 0;
                (*w).graph[i][2] = 0;
        }
        archivo = fopen("archivo.col","r");
        if(archivo == NULL) {
                printf("\nError de apertura del archivo\n\n");
                exit(1);
        }
        //Mientras no se llegue al final del fichero
        //(caracter = fgetc(archivo)) != EOF
        while (!feof(archivo)) {
                //(1) finding the first non-whitespace character in the line to test,
                //(2) what to do with blank lines (it looks like you just want the data,
                //so I've removed them) and
                //(3) handling/removing the '\n' at the end of each line included by fgets.
                while (fgets(line,MAXS,archivo) != NULL) {
                        char *p = line;
                        size_t len = strlen(line);

                        while(len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
                                line[--len] = 0;   //strip newline or carriage rtn

                        while(isspace(*p))  //advance to first non-whitespace
                                p++;
                        //skip lines beginning with '#' or '@' or blank lines
                        if(*p == 'c' || !*p) {
                                continue;
                        } else if(*p == 'p') {
                                fscanf(archivo,"%s %u %u", ignore, &numver, &numlad);
                                (*w).v = numver;
                                (*w).l = numlad;
                        } else if(*p == 'e') {
                                fscanf(archivo, "%s %u %u", ignore, &x, &y);
                                //aumento el grado del vertice en 1
                                (*w).graph[x-1][2]=(*w).graph[x-1][2]+1;
                                //el grado mas 3 para colocar el valor de y en los vecinos de x
                                j = (*w).graph[x-1][2]+3;
                                (*w).graph[x-1][j]= y;

                                (*w).graph[y-1][2]=(*w).graph[y-1][2]+1;
                                j = (*w).graph[y-1][2] + 3;
                                (*w).graph[y-1][j]= x;

                        } else {
                                printf("archivo invalido\n");
                                exit(1);
                        }
                }

        }
        fclose(archivo);
        for(row = 0; row < numver; row++){
          for(columns = 0; columns < numver; columns++){
            printf("%d", (*w).graph[row][columns]);
          }
          printf("\n");
        }
        return 0;
}
