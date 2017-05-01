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
//alloc memory, start the WinterSt structure, read a graph in DIMACS format.
//load the information from it and return a pointer to it.
WinterIsHere_t WinterIsComing(){
        WinterIsHere_t winter = calloc(1, sizeof(struct _WinterIsHere_t));
        WinterSt_t w = calloc(1, sizeof(struct _WinterSt_t));
        FILE *archivo;
        int comment = 1;
        int flag = 1;
        uint32_t x,y,numver,numlad, i,j, found,verticei;
        uint32_t guardado = 1;
        char line[MAXS] = {0};
        archivo = fopen("archivo.col","r");
        if(archivo == NULL) {
                printf("\nError de apertura del archivo\n\n");
                exit(1);
        }
        //Mientras no se llegue al final del fichero
        while (!feof(archivo)) {
                //(1) finding the first non-whitespace character in the line to test,
                //(2) what to do with blank lines (it looks like you just want the data,
                //so I've removed them) and
                //(3) handling/removing the '\n' at the end of each line included by fgets.
                while (fgets(line,MAXS,archivo) != NULL) {
                        char *p = line;
                        char * aux;
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
                                printf("%s\n", p);
                                //parto el string de la linea con el espacio como delimitador
                                aux = strtok(line, " ");
                                while(aux != NULL) {
                                        if(flag == 3) {
                                                //en el tercer espacio castear el string en uint32_t
                                                numver = (uint32_t)strtol(aux, &aux, 10);
                                        }
                                        if(flag == 4) {
                                                //en el cuarto espacio castear
                                                numlad = (uint32_t)strtol(aux, &aux, 10);
                                        }
                                        aux = strtok(NULL, " ");
                                        flag++;
                                }
                                (*w).v = numver;
                                (*w).l = numlad;
                                w->graph = (uint32_t **)malloc(numver * sizeof(uint32_t *));
                                for(i = 0; i < numver; i++) {
                                        (*w).graph[i] = (uint32_t *)malloc(numver+2 * sizeof(int));
                                }
                                //carga las primeras 3 celdas con el nombre, el color y el grado
                                //respectivamente
                                for (i = 0; i < numver; i++) {
                                        //el entero de 32 bits unsigned mas grande
                                        (*w).graph[i][0] = 4294967295;
                                        (*w).graph[i][1] = 0;
                                        (*w).graph[i][2] = 0;
                                }
                                printf("\n");
                        } else if(*p == 'e') {
                                aux = strtok(line, " ");
                                flag = 1;
                                found = 0;
                                verticei = 0;
                                i = 0;
                                j = 0;
                                while(aux != NULL) {
                                        if(flag == 2) {
                                                x = (uint32_t)strtol(aux,&aux,10);
                                        }
                                        if(flag == 3) {
                                                y = (uint32_t)strtol(aux,&aux,10);
                                        }
                                        aux = strtok(NULL, " ");
                                        flag++;
                                }
                                printf("x=%u y=%u\n", x, y);
                                //busca el indice si el vertice ya está guardado

                                while(i < guardado) {
                                        if((*w).graph[i][0] == x) {
                                                found = 1;
                                                break;
                                        }
                                        i++;
                                }

                                if(!found) {
                                        //agrego el vertice nuevo
                                        while((*w).graph[j][0] != 4294967295) {

                                                j++;
                                        }
                                        verticei = j;
                                        guardado++;
                                } else {
                                        //encontrado
                                        verticei = i;
                                }
                                //primera celda el nombre del vertice
                                (*w).graph[verticei][0] = x;
                                //segunda celda el numero de vecinos
                                (*w).graph[verticei][1] = (*w).graph[verticei][1] + 1;
                                //agregar vecino a un vertice, numero de vecinos +3 para ignorar las primeras 3 celdas
                                (*w).graph[verticei][(*w).graph[verticei][1]+2] = y;
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
                                        while((*w).graph[j][0] != 4294967295) {
                                                j++;
                                        }
                                        verticei = j;
                                        guardado++;
                                } else {
                                        verticei = i;
                                }
                                (*w).graph[verticei][0] = y;
                                (*w).graph[verticei][1] = (*w).graph[verticei][1] + 1;
                                (*w).graph[verticei][(*w).graph[verticei][1]+2] = x;

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
        winter->WinterSt = &w;
        return winter;
}
//imprime tabla
void printable(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        printf("Tabla de adyacencia:\n");
        for(uint32_t row = 0; row < walker->v; row++) {
                for(uint32_t columns = 0; columns < walker->graph[row][1] + 3; columns++) {
                        printf("%d ", walker->graph[row][columns]);
                }
                printf("\n");
        }
        printf("\n");
}
//Destruye el grafo
int Primavera(WinterIsHere_t w){
        WinterSt_t grafo = *w->WinterSt;
        uint32_t **tabla = grafo->graph;
        free(tabla);
        free(grafo);
        free(w);
        return 1;
}
//devuelve el numero de vertices de w
uint32_t NumeroDeVertices(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        return walker->v;
}
//Devuelve el numero de lados de w
uint32_t NumeroDeLados(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        return walker->l;
}
//Devuelve el numero de vertices de color i
uint32_t NumeroVerticesDeColor(WinterIsHere_t w, uint32_t i){
        WinterSt_t walker = *w->WinterSt;
        uint32_t j = 0;
        uint32_t k = 0;
        while(k < walker->v) {
                if(walker->graph[k][2] == i) {
                        j++;
                }
                k++;
        }
        return j;
}
//devuelve la cantidad de colores usados en el coloreo de W
uint32_t NumeroDeColores(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        uint32_t j = 0;
        uint32_t i = 0;
        while(i < walker->v) {
                if(walker->graph[i][2] > j) {
                        j = walker->graph[i][2];
                }
                i++;
        }
        return j;
}
//devuelve la etiqueta del vertice numero i
uint32_t IesimoVerticeEnElOrden(WinterIsHere_t w, uint32_t i){
        WinterSt_t walker = *w->WinterSt;
        uint32_t k = 0;
        while(k < walker->v) {
                if(i == walker->graph[k][0]) {
                        break;
                }
                k++;
        }
        return k;
}
//devuelve el nombre real del vertice cuya etiqueta es x
uint32_t NombreDelVertice(WinterIsHere_t w, uint32_t x){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][0];
}
//devuelve el color con el que esta coloreado el vertice x
uint32_t ColorDelVertice(WinterIsHere_t w, uint32_t x){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][2];
}
//devuelve el grado del vertice x
uint32_t GradoDelVertice(WinterIsHere_t w, uint32_t x){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][1];
}
//devuelve la etiqueta del vecino numero i del vertice x
uint32_t IesimoVecino(WinterIsHere_t w, uint32_t x, uint32_t i){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][i+2];
}
//busca t en el arreglo
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
//coloreo greedy
uint32_t Greedy(WinterIsHere_t w){

        WinterSt_t walker = *w->WinterSt;
        uint32_t chromatic = 1;
        int m,vecinos;
        uint32_t k;
        walker->graph[0][2] = 1;
        uint32_t array[walker->v];
        //memset(array, 0, (walker->v)*(walker->v)*sizeof(uint32_t));

        //por cada vertice
        for(int i = 1; i < (int)walker->v; i++) {
                m = 0;
                //nos fijamos en sus vecinos, y por cada vecino
                vecinos = (int)walker->graph[i][1]+3;
                for(int j = 3; j < vecinos; j++) {
                        //los colores de los vecinos menores al vertice se agregan a un arreglo
                        //if(walker->graph[i][j] < walker->graph[i][0]) {
                        //busco el color del vecino
                        for(uint32_t l = 0; l < walker->v; l++) {
                                if(walker->graph[l][0] == walker->graph[i][j]) {
                                        array[m] = walker->graph[l][2];
                                        m++;
                                        break;
                                }
                        }
                }
                //aca buscamos el menor entero que no esta en el arreglo
                for(k = 1; k < walker->v; k++) {
                        if(!arraysearch(array, walker->v - 1, k)) {
                                //si no esta el color k, el nuevo color es k
                                walker->graph[i][2] = k;
                                break;
                        }
                        if(k == walker->v-1) {
                                walker->graph[i][2] = k + 1;
                        }
                }
                if(chromatic < k) {
                        chromatic = k;
                }
        }

        return chromatic;
}
//coloreo bipartito
int Bipartito(WinterIsHere_t w){

        WinterSt_t walker = *w->WinterSt;
        uint32_t chromatic = 1;
        int m,vecinos;
        uint32_t k;
        walker->graph[0][2] = 1;
        uint32_t array[walker->v];
        //memset(array, 0, (walker->v)*(walker->v)*sizeof(uint32_t));

        //por cada vertice
        for(int i = 1; i < (int)walker->v; i++) {
                m = 0;
                //nos fijamos en sus vecinos, y por cada vecino
                vecinos = (int)walker->graph[i][1]+3;
                for(int j = 3; j < vecinos; j++) {
                        //los colores de los vecinos menores al vertice se agregan a un arreglo
                        if(walker->graph[i][j] < walker->graph[i][0]) {
                                //busco el color del vecino
                                for(uint32_t l = 0; l < walker->v; l++) {
                                        if(walker->graph[l][0] == walker->graph[i][j]) {
                                                array[m] = walker->graph[l][2];
                                                m++;
                                                break;
                                        }
                                }
                        }
                }
                //aca buscamos el menor entero que no esta en el arreglo
                for(k = 1; k < walker->v; k++) {
                        if(!arraysearch(array, walker->v - 1, k)) {
                                //si no esta el color k, el nuevo color es k
                                walker->graph[i][2] = k;
                                break;
                        }
                        if(k == walker->v-1) {
                                walker->graph[i][2] = k + 1;
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
//quick sort
uint32_t pivot(WinterIsHere_t w,  uint32_t left,  uint32_t right){
        WinterSt_t walker = *w->WinterSt;
        uint32_t piv = left;

        uint32_t i = left+1;
        uint32_t j = right;

        while(i<=j)
        {
                if(walker->graph[i][0] <= walker->graph[piv][0])
                {
                        i++;
                }
                else
                {
                        if(walker->graph[j][0] > walker->graph[piv][0])
                        {
                                j--;
                        }
                        else
                        {
                                CambiarDatos(&walker->graph[i],&walker->graph[j]);
                                i++;
                                j--;
                        }
                }
        }
        if(piv!=j)
        {
                CambiarDatos(&walker->graph[piv],&walker->graph[j]);
                piv = j;
        }
        return piv;
}
void recursive_quick_sort(WinterIsHere_t w, int left, int right){
        uint32_t piv;
        if(right>left)
        {
                piv = pivot(w,left,right);
                recursive_quick_sort(w,left,((int)piv)-1);
                recursive_quick_sort(w,((int)piv)+1,right);
        }
}
void QuickSort(WinterIsHere_t w, uint32_t length){
        if(length>2)
        {
                recursive_quick_sort(w,0,(length)-1);
        }
}
void OrdenNatural(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        QuickSort(w,walker->v);
}
//WelshPowell
uint32_t pivotwelsh(WinterIsHere_t w,  uint32_t left,  uint32_t right){
        WinterSt_t walker = *w->WinterSt;
        uint32_t piv = left;

        uint32_t i = left+1;
        uint32_t j = right;

        while(i<=j)
        {
                if(walker->graph[i][1] > walker->graph[piv][1])
                {
                        i++;
                }
                else
                {
                        if(walker->graph[j][1] <= walker->graph[piv][1])
                        {
                                j--;
                        }
                        else
                        {
                                CambiarDatos(&walker->graph[i],&walker->graph[j]);
                                i++;
                                j--;
                        }
                }
        }
        if(piv!=j)
        {
                CambiarDatos(&walker->graph[piv],&walker->graph[j]);
                piv = j;
        }
        return piv;
}
void recursive_quick_sort_welsh(WinterIsHere_t w, int left, int right){
        uint32_t piv;
        if(right>left)
        {
                piv = pivotwelsh(w,left,right);
                recursive_quick_sort_welsh(w,left,((int)piv)-1);
                recursive_quick_sort_welsh(w,((int)piv)+1,right);
        }
}
void WelshPowell(WinterIsHere_t w, uint32_t length){
        if(length>2)
        {
                recursive_quick_sort_welsh(w,0,(length)-1);
        }
}
void OrdenWelshPowell(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        WelshPowell(w, walker->v);
}
//orden decreciente de colores
uint32_t pivotcolores(WinterIsHere_t w,  uint32_t left,  uint32_t right){
        WinterSt_t walker = *w->WinterSt;
        uint32_t piv = left;

        uint32_t i = left+1;
        uint32_t j = right;

        while(i<=j)
        {
                if(walker->graph[i][2] > walker->graph[piv][2])
                {
                        i++;
                }
                else
                {
                        if(walker->graph[j][2] <= walker->graph[piv][2])
                        {
                                j--;
                        }
                        else
                        {
                                CambiarDatos(&walker->graph[i],&walker->graph[j]);
                                i++;
                                j--;
                        }
                }
        }
        if(piv!=j)
        {
                CambiarDatos(&walker->graph[piv],&walker->graph[j]);
                piv = j;
        }
        return piv;
}
void recursive_quick_sort_colores(WinterIsHere_t w, int left, int right){
        uint32_t piv;
        if(right>left)
        {
                piv = pivotcolores(w,left,right);
                recursive_quick_sort_colores(w,left,((int)piv)-1);
                recursive_quick_sort_colores(w,((int)piv)+1,right);
        }
}
//Aleatorizar con semilla x
void AleatorizarVertices(WinterIsHere_t w, uint32_t x){
        //x es la semilla
        srand(x);
        WinterSt_t walker = *w->WinterSt;
        for(int i = walker->v-1; i > 0; i--) {
                int j = rand() % (i+1);
                CambiarDatos(&walker->graph[i], &walker->graph[j]);
        }
}
//Maximo de un arreglo
uint32_t max ( uint32_t *list, uint32_t r){
        uint32_t i;
        uint32_t j = 0;
        uint32_t max = 0;
        for(i = 0; i <= r+1; i++) {
                if(list[i] > max) {
                        max = list[i];
                        j = i;
                }
        }
        return j;
}
void ReordenManteniendoBloqueColores(WinterIsHere_t w, uint32_t x){
        WinterSt_t walker = *w->WinterSt;
        uint32_t r = NumeroDeColores(w);
        uint32_t i = 0;
        uint32_t current = 0;
        uint32_t j = 1;
        uint32_t v = NumeroDeVertices(w);
        if(r != 1) {
                if(x == 0) {
                        //agrupamos los de color r
                        while(i < v) {
                                if(walker->graph[i][1] != r) {
                                        i++;
                                } else{
                                        CambiarDatos(&walker->graph[i], &walker->graph[current]);
                                        current++;
                                }
                        }
                        //armamos bloques con colores = 1, 2 .. r-1
                        if((r-current)>2) {
                                recursive_quick_sort(w, current, r);
                        }
                } else if(x == 1) {
                        if(r > 2){
                          recursive_quick_sort_colores(w, 0, r-1);
                        }
                } else if(x == 2) {
                        //calculamos cuantos vertices hay para cada color
                        uint32_t cantvert[r+1];
                        for(i = 1; i <= r; i++) {
                                cantvert[i] = NumeroVerticesDeColor(w, i);
                        }
                        //buscamos el color con mas vertices
                        j = max(cantvert, r);
                        while(j!= 0 && i <= v) {
                                for(; i <= v; i++) {
                                        if(walker->graph[j][1] != j) {
                                                i++;
                                        } else{
                                                current++;
                                                CambiarDatos(&walker->graph[i], &walker->graph[current]);
                                        }
                                }
                                cantvert[j] = 0;
                                j = max(cantvert, r);
                        }

                } else if(x == 3) {
                        //calculamos cuantos vertices hay para cada color
                        uint32_t cantvert[r+1];
                        for(i = 1; i <= r; i++) {
                                cantvert[i] = NumeroVerticesDeColor(w, i);
                        }
                        //buscamos el color con mas vertices
                        j = max(cantvert, r);
                        i = v;
                        current = v;
                        while(j != 0 && i > 0) {
                                for(; i == 0; i--) {
                                        if(walker->graph[j][1] != j) {
                                                i--;
                                        } else{
                                                current--;
                                                CambiarDatos(&walker->graph[i], &walker->graph[current]);
                                        }
                                }
                        }
                } else{
                        //AleatorizarVertices(w,x);
                        OrdenWelshPowell(w);

                }
        }
}
