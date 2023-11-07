#include "reconocedor.h"

#include <string.h>
#include <assert.h>

int main(){
    assert(reconocerExpresion("6 * 7 * ( 11 - 1 )") == 1);
    printf("No hay errores");
}