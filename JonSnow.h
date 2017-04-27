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

WinterIsHere_t WinterIsComing(void);
int Primavera(WinterIsHere_t w);
#endif
