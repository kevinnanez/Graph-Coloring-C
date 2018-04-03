#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "TheOutsider.h"
#include <stdint.h>
#include <string.h>
#include <inttypes.h>


//devuelve el numero de vertices de w
uint32_t NumeroDeVertices(Grafo_t w){
        GrafoSt_t pointer = *w->GrafoSt;
        return pointer->v;
}
//Devuelve el numero de lados de w
uint32_t NumeroDeLados(Grafo_t w){
        GrafoSt_t pointer = *w->GrafoSt;
        return pointer->l;
}
uint32_t ColorJotaesimoVecino(Grafo_t w, uint32_t x, uint32_t j){

        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t vecino = pointer->graph[x][j+3];
        uint32_t color = 0;
        for(uint32_t i = 0; i < pointer->v; i++) {

                if(pointer->graph[i][0] == vecino) {
                        color = pointer->graph[i][2];
                        break;
                }
        }
        return color;
}
uint32_t NombreJotaesimoVecino(Grafo_t w, uint32_t x, uint32_t j){

        GrafoSt_t pointer = *w->GrafoSt;
        return pointer->graph[x][j+3];
}
//devuelve la cantidad de colores usados en el coloreo de W
uint32_t NumeroDeColores(Grafo_t w){
        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t j = 0;
        uint32_t i = 0;
        while(i < pointer->v) {
                if(pointer->graph[i][2] > j) {
                        j = pointer->graph[i][2];
                }
                i++;
        }
        return j;
}

//devuelve el nombre real del vertice cuya etiqueta es x
uint32_t NombreDelVertice(Grafo_t w, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        return pointer->graph[x][0];
}
//devuelve el color con el que esta coloreado el vertice x
uint32_t ColorDelVertice(Grafo_t w, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        return pointer->graph[x][2];
}
//devuelve el grado del vertice x
uint32_t GradoDelVertice(Grafo_t w, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        return pointer->graph[x][1];
}
//Maximo de un arreglo
uint32_t max ( uint32_t *list, uint32_t r){
        uint32_t i;
        uint32_t j = 0;
        uint32_t max = 0;
        for(i = 0; i < r; i++) {
                if(list[i] != 0) {
                        max = list[i];
                        break;
                }
        }
        for(i = 0; i < r; i++) {
                if(list[i] >= max && list[i] != 0 ) {
                        max = list[i];
                        j = i;
                }
        }
        return j;
}
//Minimo de un arreglo
uint32_t min ( uint32_t *list, uint32_t r){
        uint32_t i;
        uint32_t j = 0;
        uint32_t min = 0;
        for(i = 0; i < r; i++) {
                if(list[i] != 0) {
                        min = list[i];
                        break;
                }
        }
        for(i = 0; i < r; i++) {
                if(list[i] <= min && list[i]!= 0) {
                        min = list[i];
                        j = i;
                }
        }
        return j;
}
//devuelve true si t esta en el arreglo
bool arraysearch(uint32_t array[],uint32_t size, uint32_t t){
        bool flag = false;
        for(int i = 0; i < (int)size; i++) {
                if(array[i] == t) {
                        flag = true;
                        break;
                }
        }
        return flag;
}
