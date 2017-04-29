#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "JonSnow.h"
#include <stdint.h>


void CambiarDatos(WinterIsHere_t w, int32_t a, int32_t b){
    //variables auxiliares y temporales
    WinterIsHere_t temp;
    int32_t auxnom, auxcol, auxgrad;
              
    auxnom = w->graph[a][0];
    auxcol = w->WinterSt->graph[a][1];
    auxgrad = w->WinterSt->graph[a][2];

    /*while ( <=auxgrad){
    //copiar los vecinos de izq
    }*/

    w->WinterSt->graph[a][0] = temp->WinterSt->graph[b][0];
    w->WinterSt->graph[a][1] = temp->WinterSt->graph[b][1];
    w->WinterSt->graph[a][2] = temp->WinterSt->graph[b][2];

    /*for(){
    //copiar vecinos de der a izq y borrar? vecinos de a si tiene mas que der
    }*/

    w->WinterSt->graph[b][0] = auxnom;
    w->WinterSt->graph[b][1] = auxcol;
    w->WinterSt->graph[b][2] = auxgrad;

    /*while ( <=auxgrad){
    //copiar los vecinos aux a der y borrar? vecinos de der si tenia mas que aux
    }*/
}

void QuickSort(WinterIsHere_t w, int32_t a, int32_t b){
    int32_t izq, der, pivote;
    int32_t i = a;
    int32_t j = b;

    izq = w->WinterSt->graph[i][0];
    der = w->WinterSt->graph[j][0];
    //elejimos el pivote al medio
    pivote = w->WinterSt->graph[(i+j)/2][0];
    //ordena de menor a mayor
    while (i<=j){
            while(izq<pivote && i<b){
                i++;
                izq= w->WinterSt->graph[i][0];              
            }
                
            while(pivote<der && j>izq){
                j--;
                der = w->WinterSt->graph[j][0];
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
    QuickSort(w,0,w->WinterSt->v);
}

void WelshPowell(WinterIsHere_t w, int32_t a, int32_t b){
    int32_t izq, der, pivote;
    int32_t i = a;
    int32_t j = b;

    izq = w->WinterSt->graph[i][2];
    der = w->WinterSt->graph[j][2];
    //elejimos el pivote al medio
    pivote = w->WinterSt->graph[(i+j)/2][2];
    //como el QuickSort pero de mayor a menor
    while (i<=j){
            while(izq>pivote && i<b){
                i++;
                izq= w->WinterSt->graph[i][2];              
            }
                
            while(pivote>der && j>izq){
                j--;
                der = w->WinterSt->graph[j][2];
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
    WelshPowell(w, 0, w->WinterSt->v);
}

void AleatorizarVertices(WinterIsHere_t w, int32_t x){
    OrdenWelshPowell(w);
    //inserte codigo xD

}

int32_t max ( int32_t *list, int32_t r){
    int32_t i ;
    int32_t j = 0;
    int32_t max = 0;
    for(i = 0; i++; i <= r+1){
        if(list[i] > max){
            max = list[i];
            j = i;
        } 
    }
    return j;
}
void RordenManteniendoBloqueColores(WinterIsHere_t w, int32_t x){
    int32_t r = NumeroDeColores(w);
    int32_t i = 0;
    int32_t current = 0;
    int32_t j = 1;
    int32_t v = NumeroDeVertices(w);

    if(x == 0){
        //agrupamos los de color r 
        while(i <= v){
            if(w->WinterSt->graph[i][1] != r){
                i++;
            } else{
                current++;
                CambiarDatos(w, i, current);
            }
        }
        //armamos bloques con colores = 1, 2 .. r-1
        i = current + 1;
        while(j < r && i <= v){
            for(i ; i++; i <= v){
                if(w->WinterSt->graph[i][1] != j){
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
            if(w->WinterSt->graph[i][1] != r){
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
            for(i ; i++; i <= v){
                if(w->WinterSt->graph[i][1] != j){
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
        for(i = 1; i++; i <= r){
            cantvert[i] = NumeroVerticesDeColor(w, i);
        }
        //buscamos el color con mas vertices
        j = max(cantvert, r);
        while(j!= 0 && i <= v){
            for(i; i++; i <= v){
                if(w->WinterSt->graph[j][1] != j){
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
        for(i = 1; i++; i <= r){
            cantvert[i] = NumeroVerticesDeColor(w, i);
        }
        //buscamos el color con mas vertices
        j = max(cantvert, r);
        i = v;
        current = v;
        while(j != 0 && i > 0){
            for(i; i--; i = 0){
                if(w->WinterSt->graph[j][1] != j){
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