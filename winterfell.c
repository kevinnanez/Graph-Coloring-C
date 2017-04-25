#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define MAXS 10000
//Create the WinterSt structure, which contains all the information of the
//given graph.
struct _WinterSt_t {
        int32_t v;
        int32_t l;
        int32_t graph[MAXS][MAXS];
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
        char ignore[1],ignore2[4];
        int comment = 1;
        int32_t x,y,j,numver,numlad, i, columns, row;
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
                        if(*p == 'c') {
                                printf("Comment %d\n", comment++);
                                continue;
                        } else if(*p == 'p') {
                                fscanf(archivo,"%s %s %"PRId32" %"PRId32"", ignore, ignore2, &numver, &numlad);
                                printf("numver= %"PRIu32" namlad = %"PRIu32"\n", numver, numlad);
                                (*w).v = numver;
                                (*w).l = numlad;
                        } else if(*p == 'e') {
                                fscanf(archivo, "%s %"PRId32" %"PRId32"", ignore, &x, &y);
                                //aumento el grado del vertice en 1
                                printf("x=%u y=%u\n", x, y);
                                (*w).graph[x][2]=(*w).graph[x][2]+1;
                                //el grado mas 3 para colocar el valor de y en los vecinos de x
                                j = (*w).graph[x][2]+3;
                                (*w).graph[x][j]= y;

                                (*w).graph[y][2]=(*w).graph[y][2]+1;
                                j = (*w).graph[y][2] + 3;
                                (*w).graph[y][j]= x;

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
