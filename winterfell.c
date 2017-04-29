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
        int32_t **graph;
};

//Create a pointer to a Winterst structure.
struct _WinterIsHere_t {
        WinterSt_t *WinterSt;
};


//alloc memory, start the WinterSt structure, read a graph in DIMACS format.
//load the information from it and return a pointer to it.
WinterIsHere_t WinterIsComing(){
        WinterIsHere_t winter = calloc(1, sizeof(struct _WinterIsHere_t));
        WinterSt_t w = calloc(1, sizeof(struct _WinterSt_t));
        FILE *archivo;
        int comment = 1;
        int flag = 1;
        int32_t x,y,numver,numlad, i,j, columns, row, notfound,verticei;
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
                                                //en el tercer espacio castear el string en int32_t
                                                numver = (int32_t)strtol(aux, &aux, 10);
                                        }
                                        if(flag == 4) {
                                                //en el cuarto espacio castear
                                                numlad = (int32_t)strtol(aux, &aux, 10);
                                        }
                                        aux = strtok(NULL, " ");
                                        flag++;
                                }
                                (*w).v = numver;
                                (*w).l = numlad;
                                w->graph = (int32_t **)malloc(numver * sizeof(int32_t *));
                                for(i = 0; i < numver; i++)
                                        (*w).graph[i] = (int32_t *)malloc(numver+2 * sizeof(int));
                                //carga las primeras 3 celdas con el nombre, el color y el grado
                                //respectivamente
                                for (i = 0; i < numver; i++) {
                                        (*w).graph[i][0] = 0;
                                        (*w).graph[i][1] = 0;
                                        (*w).graph[i][2] = 0;
                                }

                        } else if(*p == 'e') {
                                aux = strtok(line, " ");
                                flag = 1;
                                notfound = 0;
                                verticei = 0;
                                i = 0;
                                j = 0;
                                while(aux != NULL) {
                                        if(flag == 2) {
                                                x = (int32_t)strtol(aux,&aux,10);
                                        }
                                        if(flag == 3) {
                                                y = (int32_t)strtol(aux,&aux,10);
                                        }
                                        aux = strtok(NULL, " ");
                                        flag++;
                                }
                                printf("x=%u y=%u\n", x, y);
                                //busca el indice si el vertice ya está guardado
                                while(i < numver && x != (*w).graph[i][0]) {
                                        i++;
                                        if(i == numver) {
                                                notfound = 1;
                                        }
                                }
                                //si llega al numero de vertices entonces no lo encontro

                                if(notfound) {
                                        //agrego el vertice nuevo
                                        while((*w).graph[j][0] != 0) {
                                                j++;
                                        }
                                        verticei = j;

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
                                notfound = 0;
                                while(i < numver && y != (*w).graph[i][0]) {
                                        i++;
                                        if(i == numver)
                                                notfound = 1;
                                }
                                if(notfound) {
                                        while((*w).graph[j][0] != 0) {
                                                j++;
                                        }
                                        verticei = j;
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
                }


        }
        fclose(archivo);
        //para ver si se agregaron bien los valores
        for(row = 0; row < numver; row++) {
                for(columns = 0; columns < numver + 2; columns++) {
                        printf("%d ", (*w).graph[row][columns]);
                }
                printf("\n");
        }
        winter->WinterSt = &w;
        return winter;
}

int Primavera(WinterIsHere_t w){
        WinterSt_t grafo = *w->WinterSt;
        int32_t **tabla = grafo->graph;
        free(tabla);
        free(grafo);
        free(w);
        return 1;
}

//devuelve el numero de vertices de w
int32_t NumeroDeVertices(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        return walker->v;
}
//Devuelve el numero de lados de w
int32_t NumeroDeLados(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        return walker->l;
}
//Devuelve el numero de vertices de color i

int32_t NumeroVerticesDeColor(WinterIsHere_t w, int32_t i){
        WinterSt_t walker = *w->WinterSt;
        int32_t j = 0;
        int32_t k = 0;
        while(k < walker->v) {
                if(walker->graph[k][2] == i) {
                        j++;
                }
                k++;
        }
        return j;
}

//devuelve la cantidad de colores usados en el coloreo de W
int32_t NumeroDeColores(WinterIsHere_t w){
        WinterSt_t walker = *w->WinterSt;
        int32_t j = 0;
        int32_t i = 0;
        while(i < walker->v) {
                if(walker->graph[i][2] > j) {
                        j = walker->graph[i][2];
                }
                i++;
        }
        return j;
}

//devuelve la etiqueta del vertice numero i
int32_t IesimoVerticeEnElOrden(WinterIsHere_t w, int32_t i){
        WinterSt_t walker = *w->WinterSt;
        int32_t k = 0;
        while(k < walker->v) {
                if(i == walker->graph[k][0]) {
                        break;
                }
                k++;
        }
        return k;
}

//devuelve el nombre real del vertice cuya etiqueta es x
int32_t NombreDelVertice(WinterIsHere_t w, int32_t x){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][0];
}

//devuelve el color con el que esta coloreado el vertice x

int32_t ColorDelVertice(WinterIsHere_t w, int32_t x){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][2];
}

//devuelve el grado del vertice x

int32_t GradoDelVertice(WinterIsHere_t w, int32_t x){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][1];
}

//devuelve la etiqueta del vecino numero i del vertice x

int32_t IesimoVecino(WinterIsHere_t w, int32_t x, int32_t i){
        WinterSt_t walker = *w->WinterSt;
        return walker->graph[x][i+2];
}

bool arraysearch(int32_t array[],int32_t size, int32_t t){
        bool flag = false;
        for(int i = 0; i < (int)size; i++) {
                if(array[i] == t) {
                        flag = true;
                        break;
                }
        }
        return flag;
}

int32_t Greedy(WinterIsHere_t w){
        int32_t chromatic = 1;
        int k, m;
        WinterSt_t walker = *w->WinterSt;
        int32_t array[walker->v];
        memset(array, 0, (walker->v)*(walker->v)*sizeof(int32_t));
        walker->graph[0][2] = 1;
        //por cada vertice
        for(int i = 1; i < (int)walker->v; i++) {
                m = 0;
                //nos fijamos en sus vecinos, y por cada vecino
                for(int j = 3; j < ((int)walker->graph[i][1]+2); j++) {
                        //los colores de los vecinos menores al vertice se agregan a un arreglo
                        if(walker->graph[i][j] < walker->graph[i][0]) {
                                for(int l = 0; l < walker->v; l++) {
                                    if(walker->graph[l][0] == walker->graph[i][j]){
                                        array[m] = walker->graph[l][2];
                                        m++;
                                        break;
                                      }
                                }
                        }
                }
                //aca buscamos el menor entero que no esta en el arreglo
                //desde 2 porque ya hay 1 color.
                for(k = 2; k < walker->v; k++) {
                        if(!arraysearch(array, walker->v, k)) {
                                //si no esta el color k, el nuevo color es k
                                walker->graph[i][2] = k;
                                break;
                        }
                }
                if(chromatic < k) {
                        chromatic = k;
                }
        }

        return chromatic;
}

int Bipartito(WinterIsHere_t w){

        int32_t chromatic = 1;
        int k, m;
        WinterSt_t walker = *w->WinterSt;
        int32_t array[walker->v];
        memset(array, 0, (walker->v)*(walker->v)*sizeof(int32_t));
        walker->graph[0][2] = 1;
        //por cada vertice
        for(int i = 1; i < (int)walker->v; i++) {
                m = 0;
                //nos fijamos en sus vecinos, y por cada vecino
                for(int j = 3; j < ((int)walker->graph[i][1]+2); j++) {
                        //los colores de los vecinos menores al vertice se agregan a un arreglo
                        if(walker->graph[i][j] < walker->graph[i][0]) {
                                for(int l = 0; l < walker->v; l++) {
                                    if(walker->graph[l][0] == walker->graph[i][j]){
                                        array[m] = walker->graph[l][2];
                                        m++;
                                        break;
                                      }
                                }
                        }
                }
                //aca buscamos el menor entero que no esta en el arreglo
                //desde 2 porque ya hay 1 color.
                for(k = 2; k < walker->v; k++) {
                        if(!arraysearch(array, walker->v, k)) {
                                //si no esta el color k, el nuevo color es k
                                walker->graph[i][2] = k;
                                break;
                        }
                }
                if(chromatic < k) {
                        chromatic = k;
                }
                if(chromatic > 2) {
                  return 0;
                }
        }
        if(chromatic != 2){
          return 0;
        } else {
          return 1;
        }
}

void CambiarDatos(WinterIsHere_t w, int32_t a, int32_t b){
    WinterSt_t walker = *w->WinterSt;
    //variables auxiliares y temporales
    WinterSt_t temp = *w->WinterSt;
    int32_t auxnom, auxcol, auxgrad;
              
    auxnom = walker->graph[a][0];
    auxcol = walker->graph[a][1];
    auxgrad = walker->graph[a][2];

    /*while ( <=auxgrad){
    //copiar los vecinos de izq
    }*/

    walker->graph[a][0] = temp->graph[b][0];
    walker->graph[a][1] = temp->graph[b][1];
    walker->graph[a][2] = temp->graph[b][2];

    /*for(){
    //copiar vecinos de der a izq y borrar? vecinos de a si tiene mas que der
    }*/

    walker->graph[b][0] = auxnom;
    walker->graph[b][1] = auxcol;
    walker->graph[b][2] = auxgrad;

    /*while ( <=auxgrad){
    //copiar los vecinos aux a der y borrar? vecinos de der si tenia mas que aux
    }*/
}

void QuickSort(WinterIsHere_t w, int32_t a, int32_t b){
    WinterSt_t walker = *w->WinterSt;
    int32_t izq, der, pivote;
    int32_t i = a;
    int32_t j = b;

    izq = walker->graph[i][0];
    der = walker->graph[j][0];
    //elejimos el pivote al medio
    pivote = walker->graph[(i+j)/2][0];
    //ordena de menor a mayor
    while (i<=j){
            while(izq<pivote && i<b){
                i++;
                izq= walker->graph[i][0];              
            }
                
            while(pivote<der && j>izq){
                j--;
                der = walker->graph[j][0];
            }

            if(izq<=der){
               CambiarDatos(w, izq, der);
                izq++;
                der--;
            }
        }

        if(a<der){
            QuickSort(w,a,der);
        }

        if(b>izq){
            QuickSort(w,izq,b);
        }
}

void OrdenNatural(WinterIsHere_t w){
    WinterSt_t walker = *w->WinterSt;
    QuickSort(w,0,walker->v);
}

void WelshPowell(WinterIsHere_t w, int32_t a, int32_t b){
    WinterSt_t walker = *w->WinterSt;
    int32_t izq, der, pivote;
    int32_t i = a;
    int32_t j = b;

    izq = walker->graph[i][2];
    der = walker->graph[j][2];
    //elejimos el pivote al medio
    pivote = walker->graph[(i+j)/2][2];
    //como el QuickSort pero de mayor a menor
    while (i<=j){
            while(izq>pivote && i<b){
                i++;
                izq= walker->graph[i][2];              
            }
                
            while(pivote>der && j>izq){
                j--;
                der = walker->graph[j][2];
            }

            if(izq>der){
               CambiarDatos(w, izq, der);
                izq++;
                der--;
            }
        }

        if(a<der){
            WelshPowell(w,a,der);
        }

        if(b>izq){
            WelshPowell(w,izq,b);
        }
}

void OrdenWelshPowell(WinterIsHere_t w){
    WinterSt_t walker = *w->WinterSt;
    WelshPowell(w, 0, walker->v);
}

void AleatorizarVertices(WinterIsHere_t w, int32_t x){
    OrdenWelshPowell(w);
    //inserte codigo xD

}

int32_t max ( int32_t *list, int32_t r){
    int32_t i ;
    int32_t j = 0;
    int32_t max = 0;
    for(i = 0; i <= r+1;i++){
        if(list[i] > max){
            max = list[i];
            j = i;
        } 
    }
    return j;
}
void RordenManteniendoBloqueColores(WinterIsHere_t w, int32_t x){
    WinterSt_t walker = *w->WinterSt;
    int32_t r = NumeroDeColores(w);
    int32_t i = 0;
    int32_t current = 0;
    int32_t j = 1;
    int32_t v = NumeroDeVertices(w);

    if(x == 0){
        //agrupamos los de color r 
        while(i <= v){
            if(walker->graph[i][1] != r){
                i++;
            } else{
                current++;
                CambiarDatos(w, i, current);
            }
        }
        //armamos bloques con colores = 1, 2 .. r-1
        i = current + 1;
        while(j < r && i <= v){
            for( ; i <= v;i++){
                if(walker->graph[i][1] != j){
                    i++;
                } else{
                    current++;
                    CambiarDatos(w, i, current);
                }
            }
            j++;
            i = current +1;
        } 
    } else if(x == 1){
        //agrupamos primero los de color r
        while(i <= v){
            if(walker->graph[i][1] != r){
                i++;
            } else{
                current++;
                CambiarDatos(w, i, current);
            }
        }
        //armamos bloques r-1, r-2...1
        i = current + 1;
        j = r - 1;
        while(j > 1 && i <= v){
            for( ; i <= v;i++){
                if(walker->graph[i][1] != j){
                    i++;
                } else{
                    current++;
                    CambiarDatos(w, i, current);
                }
            }
            j--;
            i = current +1;
        } 

    } else if(x == 2){
        //calculamos cuantos vertices hay para cada color
        int32_t cantvert[r+1];
        for(i = 1; i <= r; i++){
            cantvert[i] = NumeroVerticesDeColor(w, i);
        }
        //buscamos el color con mas vertices
        j = max(cantvert, r);
        while(j!= 0 && i <= v){
            for(; i <= v; i++){
                if(walker->graph[j][1] != j){
                    i++;
                } else{
                    current++;
                    CambiarDatos(w, i, current);
                }
            }
            cantvert[j] = 0;
            j = max(cantvert, r);
        }

    } else if(x == 3){
        //calculamos cuantos vertices hay para cada color
        int32_t cantvert[r+1];
        for(i = 1;i <= r;  i++){
            cantvert[i] = NumeroVerticesDeColor(w, i);
        }
        //buscamos el color con mas vertices
        j = max(cantvert, r);
        i = v;
        current = v;
        while(j != 0 && i > 0){
            for(; i = 0; i--){
                if(walker->graph[j][1] != j){
                    i--;
                } else{
                    current--;
                    CambiarDatos(w, i, current);
                }
            }
        }
    } else{
        //AleatorizarVertices(w,x);
        OrdenWelshPowell(w);
    }
}