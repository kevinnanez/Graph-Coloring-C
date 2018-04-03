#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "TheOutsider.h"
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#define MAXS 10000
//alloc memory, start the GrafoSt structure, read a graph in DIMACS format.
//load the information from it and return a pointer to it.
Grafo_t ConstruccionDelGrafo(){

        Grafo_t gg = calloc(1, sizeof(struct _Grafo_t));//pido memoria para un puntero a un grafo
        GrafoSt_t w = calloc(1, sizeof(struct _GrafoSt_t));//pido memoria para un grafo
        FILE *archivo;//puntero a una estructura FILE
        int comment = 1;//variable para comentarios (c de DIMACS)
        int flag = 1;
        bool primero = true;
        uint32_t magic = 4294967295; //magic number para el mayor entero de 32 bits
        uint32_t i,j,found,verticei;
        uint32_t numver = 0;
        uint32_t numlad = 0;
        uint32_t x = 0;
        uint32_t y = 0;
        uint32_t guardado = 1;
        char line[MAXS] = {0};//Creo un arreglo de 10000 caracteres del numero 0
        archivo = fopen("archivo.col","r");//abro el archivo dimacs
        if(archivo == NULL) {
                printf("\nError de apertura del archivo\n\n");
                exit(1);
        }
        //While the file doesn't end
        //Mientras no se llegue al final del fichero
        while (!feof(archivo)) {
                //(1) it finds the first non-whitespace character in the line to test
                //(2) Then removes the blank lines
                //(3) and removes the '\n' at the end of each line included by fgets.
                while (fgets(line,MAXS,archivo) != NULL) {
                        char *p = line; //creo un puntero al arreglo line
                        char * aux; //puntero auxiliar
                        size_t len = strlen(line);//len es el tamaño del arreglo

                        while(len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) //mientras encuentre \n y \r
                                line[--len] = 0;   //llena con 0

                        while(isspace(*p))  //avanza hasta el primer caracter que no es un espacio, '#' ó '@'
                                p++;
                        if(*p == 'c') {//si encuentra una c
                                printf("Comment %d\n", comment++); //aumenta comment
                                continue;
                        } else if(*p == 'p') {//si encuentra una p
                                printf("%s\n", p);
                                aux = strtok(line, " ");//parto el string de la linea con el espacio como delimitador
                                while(aux != NULL) {//mientras no se termine la linea
                                        if(flag == 3) {//en el tercer espacio (n) castear el string en uint32_t
                                                numver = (uint32_t)strtol(aux, &aux, 10);
                                        }
                                        if(flag == 4) {//en el cuarto espacio (m) castear el string en uint32_t
                                                numlad = (uint32_t)strtol(aux, &aux, 10);
                                        }
                                        aux = strtok(NULL, " ");//ignora p edge y los espacios
                                        flag++;
                                }
                                (*w).v = numver;
                                (*w).l = numlad;
                                w->graph = (uint32_t **)calloc(numver , sizeof(uint32_t *)); //reservo memoria para el arreglo VxV
                                for(i = 0; i < numver; i++) {//por cada arreglo reservo memoria para guardar los vecinos,
                                        (*w).graph[i] = (uint32_t *)calloc(numver+2 , sizeof(uint32_t));
                                }
                                //carga las primeras 3 celdas con el nombre, el color y el grado
                                //respectivamente
                                for (i = 0; i < numver; i++) {
                                        (*w).graph[i][0] = magic;//el entero de 32 bits unsigned mas grande
                                        //(*w).graph[i][1] = 0;
                                        //(*w).graph[i][2] = 0;
                                }
                                printf("\n");
                        } else if(*p == 'e') { //si encuentra una e
                                aux = strtok(line, " ");
                                flag = 1;
                                found = 0;
                                verticei = 0;
                                i = 0;
                                j = 0;
                                while(aux != NULL) {
                                        if(flag == 2) {
                                                x = (uint32_t)strtol(aux,&aux,10); //guarda un vertice en x
                                        }
                                        if(flag == 3) {
                                                y = (uint32_t)strtol(aux,&aux,10); //guarda el otro vertice en y
                                        }
                                        aux = strtok(NULL, " ");//ignora la e primera y los espacios
                                        flag++;
                                }
                                printf("x=%u y=%u\n", x, y);

                                //Busca el indice si el vertice ya está guardado

                                  while(i < guardado) {
                                          if((*w).graph[i][0] == x) {
                                                  found = 1;
                                                  break;
                                          }
                                          i++;
                                  }

                                //Si no lo encuentra agrego el vertice nuevo
                                if(!found) {
                                        while((*w).graph[j][0] != magic) {

                                                j++;
                                        }
                                        verticei = j;
                                        if(!primero){
                                          guardado++;
                                        }
                                        primero = false;
                                } else { //encontrado
                                        verticei = i;
                                }

                                w->graph[verticei][0] = x;//primera celda el nombre del vertice
                                w->graph[verticei][1] = w->graph[verticei][1] + 1;//segunda celda el numero de vecinos
                                w->graph[verticei][w->graph[verticei][1]+2] = y;//agregar vecino a un vertice, numero de vecinos +3 para ignorar las primeras 3 celdas
                                //lo mismo pero con y
                                i=0;
                                j=0;
                                found = 0;
                                while(i < guardado) {

                                        if((*w).graph[i][0] == y) {
                                                found = 1;
                                                break;
                                        }
                                        i++;
                                }
                                if(!found) {
                                        while((*w).graph[j][0] != magic) {
                                                j++;
                                        }
                                        verticei = j;
                                        guardado++;
                                } else {
                                        verticei = i;
                                }
                                w->graph[verticei][0] = y;
                                w->graph[verticei][1] = w->graph[verticei][1] + 1;
                                w->graph[verticei][w->graph[verticei][1]+2] = x;

                        } else {
                                printf("archivo invalido\n");
                                exit(1);
                        }

                } printf("\n");


        }
        fclose(archivo);
        //para ver si se agregaron bien los valores
        /*printf("Tabla de adyacencia:\n");
           for(row = 0; row < numver; row++) {
                for(columns = 0; columns < numver + 1; columns++) {
                        printf("%d ", (*w).graph[row][columns]);
                }
                printf("\n");
           }
           printf("\n");*/
        gg->GrafoSt = &w;
        return gg;
}
//imprime tabla
void printable(Grafo_t w){
        GrafoSt_t pointer = *w->GrafoSt;
        printf("Tabla de adyacencia:\n");
        for(uint32_t row = 0; row < pointer->v; row++) {
                for(uint32_t columns = 0; columns < pointer->graph[row][1] + 3; columns++) {
                        printf("%d ", pointer->graph[row][columns]);
                }
                printf("\n");
        }
        printf("\n");
}
//Destruye el grafo
int DestruccionDelGrafo(Grafo_t w){
        GrafoSt_t grafo = *w->GrafoSt;
        uint32_t **tabla = grafo->graph;
        for (uint32_t i = 0; i < grafo->v; i++) {
                free(grafo->graph[i]);
        }
        free(tabla);
        free(grafo);
        free(w);
        return 1;
}
