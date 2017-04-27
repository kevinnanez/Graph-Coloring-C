#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include "JonSnow.h"
#include <stdint.h>
#include <inttypes.h>

int main(){
  WinterIsHere_t dragon = WinterIsComing();
  Primavera(dragon);
  return 0;
}
