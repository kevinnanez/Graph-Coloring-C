#ifndef _JON_H_
#define _JON_H_
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct _WinterIsHere_t *WinterIsHere_t;
typedef struct _WinterSt_t *WinterSt_t;
typedef uint32_t *u32;
//Winterfell
WinterIsHere_t WinterIsComing(void);
int Primavera(WinterIsHere_t w);
int32_t NumeroDeVertices(WinterIsHere_t w);
int32_t NumeroDeLados(WinterIsHere_t w);
int32_t NumeroVerticesDeColor(WinterIsHere_t w, int32_t i);
int32_t NumeroDeColores(WinterIsHere_t w);
int32_t IesimoVerticeEnElOrden(WinterIsHere_t w, int32_t i);
int32_t NombreDelVertice(WinterIsHere_t w, int32_t x);
int32_t ColorDelVertice(WinterIsHere_t w, int32_t x);
int32_t GradoDelVertice(WinterIsHere_t w, int32_t x);
int32_t IesimoVecino(WinterIsHere_t w, int32_t x, int32_t i);

#endif
