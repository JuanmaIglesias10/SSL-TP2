#include "reconocedor.h"

int main() {
    char expresion[100];
    int linea = 1;

    while (1) {
        printf("Ingrese una expresion (o presione Enter para salir): ");
        if (fgets(expresion, sizeof(expresion), stdin) == NULL || expresion[0] == '\n') {
            break;
        }
        reconocerTokens(expresion, linea++);
        reconocerExpresion(expresion);
    }

    return 0;
}