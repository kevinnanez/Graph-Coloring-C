#ifndef _JON_H_
#define _JON_H_
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>
//Create the WinterSt structure, which contains all the information of the
//given graph.

typedef struct _WinterIsHere_t *WinterIsHere_t;
typedef struct _WinterSt_t *WinterSt_t;
typedef uint32_t *u32;

struct _WinterSt_t {
        uint32_t v;
        uint32_t l;
        uint32_t **graph;
};

//Create a pointer to a Winterst structure.
struct _WinterIsHere_t {
        WinterSt_t *WinterSt;
};

//Winterfell
WinterIsHere_t WinterIsComing(void);
int Primavera(WinterIsHere_t w);
uint32_t NumeroDeVertices(WinterIsHere_t w);
uint32_t NumeroDeLados(WinterIsHere_t w);
uint32_t NumeroVerticesDeColor(WinterIsHere_t w, uint32_t i);
uint32_t NumeroDeColores(WinterIsHere_t w);
uint32_t IesimoVerticeEnElOrden(WinterIsHere_t w, uint32_t i);
uint32_t NombreDelVertice(WinterIsHere_t w, uint32_t x);
uint32_t ColorDelVertice(WinterIsHere_t w, uint32_t x);
uint32_t GradoDelVertice(WinterIsHere_t w, uint32_t x);
uint32_t IesimoVecino(WinterIsHere_t w, uint32_t x, uint32_t i);
uint32_t Greedy(WinterIsHere_t w);
int Bipartito(WinterIsHere_t w);
void CambiarDatos(uint32_t **a, uint32_t **b);
void QuickSort(WinterIsHere_t w, uint32_t b);
void OrdenNatural(WinterIsHere_t w);
void WelshPowell(WinterIsHere_t w, uint32_t b);
void OrdenWelshPowell(WinterIsHere_t w);
void AleatorizarVertices(WinterIsHere_t w, uint32_t x);
uint32_t max ( uint32_t *list, uint32_t r);
void ReordenManteniendoBloqueColores(WinterIsHere_t w, uint32_t x);
void printable(WinterIsHere_t w);
void QuickSort(WinterIsHere_t w, uint32_t length);
void recursive_quick_sort(WinterIsHere_t w, int left, int right);
uint32_t pivot(WinterIsHere_t w,  uint32_t left,  uint32_t right);
uint32_t pivotwelsh(WinterIsHere_t w,  uint32_t left,  uint32_t right);
void recursive_quick_sort_welsh(WinterIsHere_t w, int left, int right);
uint32_t pivotcolores(WinterIsHere_t w,  uint32_t left,  uint32_t right);
void recursive_quick_sort_colores(WinterIsHere_t w, int left, int right);
#endif
