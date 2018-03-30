#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "TheOutsider.h"
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

//funcion para elevar 2 a la i
int binarypow(int i){
        int p = 1;
        while (i > 0) {
                p = p * 2;
                i--;
        }
        return p;
}

//verifica si el numero dado es potencia de dos
bool espotenciadedos(uint32_t i){
        return ((i != 0) && ((i & (i - 1)) == 0));
}

//funcion que randomiza dado una semilla x y un rango de numeros s,...,t
int rueda(uint32_t x, uint32_t s, uint32_t t){
        float size = (float)t-(float)s; //tamaño del rango
        uint32_t seed = x; //guardo la semilla
        float f = (float)x; //auxiliar
        int r; //output
        float cut; //en cuanto voy a dividir el tamaño
        int i = 0;
        float j; //cuenta en que fraccion del rango pararse
        if(espotenciadedos(x) && x!=1) { //si es potencia de dos entonces toma el ultimo numero
                r = t;
        } else {
                if(x == 0 || x==1) { //si la semilla es 0 va a dar el primer numero;
                        cut = 2;
                } else {
                        while (f > 1) { //busco la cantidad de cifras que tiene el numero binario de x
                                i++;
                                f = f/2;
                        }
                        cut = size/(binarypow(i));
                }
                j = (seed-(binarypow(i-1))+1)*2;
                r = (cut * j)+s; //Mas s para correr el resultado al rango
        }
        return r;

}
//Greedy coloring
uint32_t NotSoGreedy(Grafo_t w, uint32_t x){

        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t chromatic = 1; //cantidad de colores del grafo
        int m,vecinos;
        pointer->graph[0][2] = 1; //el primer vertice obviamente tendra color 1
         //areglo que guarda los colores de los vecinos

        //For each vertex
        //por cada vertice
        for(uint32_t i = 1; i < pointer->v; i++) {
                m = 0;
                int flanders[chromatic+1];
                //we look at his neighbours; and for each neighbour
                //miramos sus vecinos y por cada vecino
                for(uint32_t init = 0; init < chromatic+1; init++){
                  flanders[init] = 0;
                }
                vecinos = (int)pointer->graph[i][1]+3;
                for(int j = 3; j < vecinos; j++) {
                        //The colors of the neighbours which are smaller than the vertex
                        //are added to an array; we look for the neighbour's color
                        //los colores de los vecinos menores al vertice se agregan a un arreglo
                        //busco el color del vecino

                        if(pointer->graph[i][j] < pointer->graph[i][0]) {
                          for(uint32_t l = 0; l < pointer->v; l++) {

                                  if(pointer->graph[l][0] == pointer->graph[i][j]) {
                                          flanders[pointer->graph[l][2]] = 1;
                                          break; //no va haber vertices repetidos
                                  }
                          }
                        }
                }
                int chrome[chromatic];//colores disponibles
                for(uint32_t init = 0; init < chromatic; init++){
                  chrome[init] = 0;
                }
                for(uint32_t color = 1; color < chromatic+1; color++){
                  if (flanders[color]!=1){
                    chrome[m] = color;
                    m++;
                  }
                }

                if( m != 0){
                  int range = rueda(x, 0, m-1);
                  pointer->graph[i][2] = chrome[range];
                } else {
                  chromatic++;
                  pointer->graph[i][2] = chromatic; //si no hay colores disponibles
                }
        }

        return chromatic;
}
//Bipartite coloring
//coloreo bipartito
int Bipartito(Grafo_t w){

        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t chromatic = 1;
        int m,vecinos;
        uint32_t k;
        pointer->graph[0][2] = 1;
        uint32_t array[pointer->v];
        //memset(array, 0, (pointer->v)*(pointer->v)*sizeof(uint32_t));
        //for each vertex
        //por cada vertice
        for(int i = 1; i < (int)pointer->v; i++) {
                m = 0;
                //we look at his neighbours; and for each neighbour
                //nos fijamos en sus vecinos, y por cada vecino
                vecinos = (int)pointer->graph[i][1]+3;
                for(int j = 3; j < vecinos; j++) {
                        //The colors of the neighbours which are smaller than the vertex
                        //are added to an array; we look for the neighbour's color
                        //los colores de los vecinos menores al vertice se agregan a un arreglo
                        if(pointer->graph[i][j] < pointer->graph[i][0]) {
                                //We look for the neighbour's color
                                //busco el color del vecino
                                for(uint32_t l = 0; l < pointer->v; l++) {
                                        if(pointer->graph[l][0] == pointer->graph[i][j]) {
                                                array[m] = pointer->graph[l][2];
                                                m++;
                                                break;
                                        }
                                }
                        }
                }
                //Here we look for the smallest integer which is not in the array
                //aca buscamos el menor entero que no esta en el arreglo
                for(k = 1; k < pointer->v; k++) {
                        if(!arraysearch(array, pointer->v - 1, k)) {
                                //if color k it's not there, the new color is k
                                //si no esta el color k, el nuevo color es k
                                pointer->graph[i][2] = k;
                                break;
                        }
                        if(k == pointer->v-1) {
                                pointer->graph[i][2] = k + 1;
                        }
                }
                if(chromatic < k) {
                        chromatic = k;
                }
                if(chromatic > 2) {
                        return 0;
                }
        }
        if(chromatic != 2) {
                return 0;
        } else {
                return 1;
        }
}
//swap de arreglos
void CambiarDatos(uint32_t **a, uint32_t **b){
        uint32_t *tmp = *a;
        *a = *b;
        *b = tmp;
}
//Quick sort
uint32_t pivot_up(Grafo_t w,  uint32_t left,  uint32_t right, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t piv = left;

        uint32_t i = left+1;
        uint32_t j = right;

        while(i<=j)
        {
                if(pointer->graph[i][x] <= pointer->graph[piv][x])
                {
                        i++;
                }
                else
                {
                        if(pointer->graph[j][x] > pointer->graph[piv][x])
                        {
                                j--;
                        }
                        else
                        {
                                CambiarDatos(&pointer->graph[i],&pointer->graph[j]);
                                i++;
                                j--;
                        }
                }
        }
        if(piv!=j)
        {
                CambiarDatos(&pointer->graph[piv],&pointer->graph[j]);
                piv = j;
        }
        return piv;
}
void recursive_quick_sort_up(Grafo_t w, int left, int right, uint32_t x){
        uint32_t piv;
        if(right>left)
        {
                piv = pivot_up(w,left,right, x);
                recursive_quick_sort_up(w,left,((int)piv)-1,x);
                recursive_quick_sort_up(w,((int)piv)+1,right,x);
        }
}
void QuickSort(Grafo_t w, uint32_t length){
        if(length>2)
        {
                recursive_quick_sort_up(w,0,(length)-1,0);
        }
}
void OrdenNatural(Grafo_t w){
        GrafoSt_t pointer = *w->GrafoSt;
        QuickSort(w,pointer->v);
}
//WelshPowell
uint32_t pivotdown(Grafo_t w,  uint32_t left,  uint32_t right, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t piv = left;

        uint32_t i = left+1;
        uint32_t j = right;

        while(i<=j)
        {
                if(pointer->graph[i][x] > pointer->graph[piv][x])
                {
                        i++;
                }
                else
                {
                        if(pointer->graph[j][x] <= pointer->graph[piv][x])
                        {
                                j--;
                        }
                        else
                        {
                                CambiarDatos(&pointer->graph[i],&pointer->graph[j]);
                                i++;
                                j--;
                        }
                }
        }
        if(piv!=j)
        {
                CambiarDatos(&pointer->graph[piv],&pointer->graph[j]);
                piv = j;
        }
        return piv;
}
void recursive_quick_sort_down(Grafo_t w, int left, int right, uint32_t x){
        uint32_t piv;
        if(right>left)
        {
                piv = pivotdown(w,left,right,x);
                recursive_quick_sort_down(w,left,((int)piv)-1, x);
                recursive_quick_sort_down(w,((int)piv)+1,right, x);
        }
}
void WelshPowell(Grafo_t w, uint32_t length){
        if(length>2)
        {
                recursive_quick_sort_down(w,0,(length)-1,1);
        }
}
void OrdenWelshPowell(Grafo_t w){
        GrafoSt_t pointer = *w->GrafoSt;
        WelshPowell(w, pointer->v);
}
//Aleatorizar vertices con semilla x
void AleatorizarVertices(Grafo_t w, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        for(int i = pointer->v-1; i > 0; i--) {
                int j = rueda(x,0,i);
                CambiarDatos(&pointer->graph[i], &pointer->graph[j]);
        }
}
//Aleatorizar arreglo con semilla x
void AleatorizarArreglo(uint32_t array[],uint32_t r, uint32_t x){
        uint32_t temp;
        for(uint32_t i = r; i > 0; i--) {
                int j = rueda(x,0,i);
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
        }
}
//Orden segun color
// si x = 0 entonces primero van los de color r, seguido del 1 al r-1
// si x = 1 entonces primero van los de color r, seguidos del r-1 al 1
// si x = 2 entonces se ordenan la cantidad de cada color de mayor a menor
// si x = 3 entonces se ordenan la cantidad de cada color de menor a mayor
// si x > 3 entonces se ordenan pseudoaleatoriamente pero manteniendo juntos los
// vertices de cada color.
void ReordenManteniendoBloqueColores(Grafo_t w, uint32_t x){
        GrafoSt_t pointer = *w->GrafoSt;
        uint32_t r = NumeroDeColores(w);
        uint32_t i = 0;
        uint32_t current = 0;
        uint32_t c;
        uint32_t j = 1;
        uint32_t v = NumeroDeVertices(w);
        if(r != 1) {
                if(x == 0) {
                        //Ordena r, 1, 2,...,r-1
                        for(; i < v; i++) {
                                if(pointer->graph[i][2] == r) {
                                        CambiarDatos(&pointer->graph[i], &pointer->graph[current]);
                                        current++;
                                }
                        }
                        //armamos bloques con colores = 1, 2 .. r-1
                        if((v-current)>2) {
                                recursive_quick_sort_up(w, current, v-1, 2);
                        }
                } else if(x == 1) {
                        if(r > 2) {
                                recursive_quick_sort_down(w, 0, v-1, 2);
                        }
                } else if(x == 2) {
                        uint32_t module[r];
                        //primero ordeno segun el color
                        recursive_quick_sort_up(w, 0, v-1, 2);
                        current = pointer->graph[0][2];
                        //Guardo en un arreglo la cantidad de vertices por color
                        //El indice 0 corresponde al vertice 1
                        c = 1;
                        uint32_t i = 0;
                        for(j = 1; j < v; j++) {
                                if(current != pointer->graph[j][2]) {
                                        module[i] = c;
                                        i++;
                                        current = pointer->graph[j][2];
                                        c = 1;
                                        if(j == v-1)
                                                module[i] = c;
                                } else {
                                        c++;
                                        current = pointer->graph[j][2];
                                        if(j == v-1)
                                                module[i] = c;
                                }
                        }
                        //busco el indice del minimo del arreglo
                        i = min(module, r)+1;
                        c = 0;
                        for(uint32_t k = 0; k < r; k++) {
                                for(j = 0; j < v; j++) {
                                        if(pointer->graph[j][2]==i) {
                                                if(j != c) {
                                                        CambiarDatos(&pointer->graph[c],&pointer->graph[j]);
                                                }
                                                c++;
                                        }
                                }
                                module[i-1] = 0;
                                i = min(module,r) + 1;
                        }
                } else if(x == 3) {
                        uint32_t module[r];
                        //primero ordeno segun el color
                        recursive_quick_sort_up(w, 0, v-1, 2);
                        current = pointer->graph[0][2];
                        //Guardo en un arreglo la cantidad de vertices por color
                        //El indice 0 corresponde al vertice 1
                        c = 1;
                        uint32_t i = 0;
                        for(j = 1; j < v; j++) {
                                if(current != pointer->graph[j][2]) {
                                        module[i] = c;
                                        i++;
                                        current = pointer->graph[j][2];
                                        c = 1;
                                        if(j == v-1)
                                                module[i] = c;
                                } else {
                                        c++;
                                        current = pointer->graph[j][2];
                                        if(j == v-1)
                                                module[i] = c;
                                }
                        }
                        //busco el indice del maximo del arreglo
                        i = max(module, r)+1;
                        c = 0;
                        for(uint32_t k = 0; k < r; k++) {
                                for(j = 0; j < v; j++) {
                                        if(pointer->graph[j][2]==i) {
                                                if(j != c) {
                                                        CambiarDatos(&pointer->graph[c],&pointer->graph[j]);
                                                }
                                                c++;
                                        }
                                }
                                module[i-1] = 0;
                                i = max(module,r) + 1;
                        }
                } else {
                        c = 0;
                        uint32_t module[r];
                        for(uint32_t i = 0; i < r; i++) {
                                module[i] = i+1;
                        }
                        AleatorizarArreglo(module, r, x);
                        for(uint32_t k = 0; k < r; k++) {
                                i = module[k];
                                for(uint32_t j = 0; j < v; j++) {
                                        if(pointer->graph[j][2] == i) {
                                                CambiarDatos(&pointer->graph[j], &pointer->graph[c]);
                                                c++;
                                        }
                                }
                        }
                }
        }
}
