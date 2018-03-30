#ifndef _OUT_H_
#define _OUT_H_
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

//Create the GrafoSt structure, which contains all the information of the
//given graph.

typedef struct _Grafo_t *Grafo_t;
typedef struct _GrafoSt_t *GrafoSt_t;
typedef uint32_t *u32;

struct _GrafoSt_t {
        uint32_t v;
        uint32_t l;
        uint32_t **graph;
};

//Create a pointer to a GrafoSt structure.
struct _Grafo_t {
        GrafoSt_t *GrafoSt;
};

//Springfield
Grafo_t ConstruccionDelGrafo(void);
int DestruccionDelGrafo(Grafo_t g);
//Quahog
uint32_t NumeroDeVertices(Grafo_t g);
uint32_t NumeroDeLados(Grafo_t g);
uint32_t NumeroVerticesDeColor(Grafo_t g, uint32_t i);
uint32_t NumeroDeColores(Grafo_t g);
uint32_t IesimoVerticeEnElOrden(Grafo_t g, uint32_t i);
uint32_t NombreDelVertice(Grafo_t g, uint32_t x);
uint32_t ColorDelVertice(Grafo_t g, uint32_t x);
uint32_t GradoDelVertice(Grafo_t g, uint32_t x);
uint32_t IesimoVecino(Grafo_t g, uint32_t x, uint32_t i);
//Shelbyville
uint32_t NotSoGreedy(Grafo_t g,uint32_t x);
int Bipartito(Grafo_t g);
void CambiarDatos(uint32_t **a, uint32_t **b);
void QuickSort(Grafo_t g, uint32_t b);
void OrdenNatural(Grafo_t g);
void WelshPowell(Grafo_t g, uint32_t b);
void OrdenWelshPowell(Grafo_t g);
void AleatorizarVertices(Grafo_t g, uint32_t x);
bool arraysearch(uint32_t array[],uint32_t size, uint32_t t);
uint32_t max ( uint32_t *list, uint32_t r);
uint32_t min ( uint32_t *list, uint32_t r);
void ReordenManteniendoBloqueColores(Grafo_t g, uint32_t x);
void printable(Grafo_t g);
void QuickSort(Grafo_t g, uint32_t length);
void recursive_quick_sort_up(Grafo_t g, int left, int right, uint32_t x);
uint32_t pivot_up(Grafo_t g,  uint32_t left,  uint32_t right, uint32_t x);
uint32_t pivotdown(Grafo_t g,  uint32_t left,  uint32_t right, uint32_t x);
void recursive_quick_sort_down(Grafo_t g, int left, int right, uint32_t x);
#endif
