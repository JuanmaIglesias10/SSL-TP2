#include <stdio.h>
#include <ctype.h>

// Definimos los tipos de tokens
typedef enum {
    NUMERO,
    OPERADOR,
    PARENTESIS_IZQUIERDO,
    PARENTESIS_DERECHO,
    DESCONOCIDO,
    FIN_DE_LINEA
} TipoToken;

// Estructura para representar un token
typedef struct {
    TipoToken tipo;
    char valor[50];
    int linea;
    int columna;
} Token;

// Función para imprimir un token
void imprimirToken(Token t) {
    switch (t.tipo) {
        case NUMERO:
            printf("Token: NUMERO, Valor: %s, Linea: %d, Columna: %d\n", t.valor, t.linea, t.columna);
            break;
        case OPERADOR:
            printf("Token: OPERADOR, Valor: %s, Linea: %d, Columna: %d\n", t.valor, t.linea, t.columna);
            break;
        case PARENTESIS_IZQUIERDO:
            printf("Token: PARENTESIS_IZQUIERDO, Valor: %s, Linea: %d, Columna: %d\n", t.valor, t.linea, t.columna);
            break;
        case PARENTESIS_DERECHO:
            printf("Token: PARENTESIS_DERECHO, Valor: %s, Linea: %d, Columna: %d\n", t.valor, t.linea, t.columna);
            break;
        case DESCONOCIDO:
            printf("Token: DESCONOCIDO, Valor: %s, Linea: %d, Columna: %d\n", t.valor, t.linea, t.columna);
            break;
        case FIN_DE_LINEA:
            printf("Fin de Linea\n");
            break;
    }
}

// Función para procesar la expresión y generar los tokens
void procesarExpresion(char* expresion, int linea) {
    int columna = 1;
    int i = 0;
    while (expresion[i] != '\0') {
        Token token;
        token.linea = linea;
        token.columna = columna;

        if (isdigit(expresion[i])) {
            token.tipo = NUMERO;
            int j = 0;
            while (isdigit(expresion[i])) {
                token.valor[j++] = expresion[i++];
            }
            token.valor[j] = '\0';
            imprimirToken(token);
        } else if (expresion[i] == '+' || expresion[i] == '-' || expresion[i] == '*' || expresion[i] == '/') {
            token.tipo = OPERADOR;
            token.valor[0] = expresion[i++];
            token.valor[1] = '\0';
            imprimirToken(token);
        } else if (expresion[i] == '(') {
            token.tipo = PARENTESIS_IZQUIERDO;
            token.valor[0] = expresion[i++];
            token.valor[1] = '\0';
            imprimirToken(token);
        } else if (expresion[i] == ')') {
            token.tipo = PARENTESIS_DERECHO;
            token.valor[0] = expresion[i++];
            token.valor[1] = '\0';
            imprimirToken(token);
        } else if (expresion[i] == ' ' || expresion[i] == '\t') {
            i++;
            columna++;
        } else {
            token.tipo = DESCONOCIDO;
            token.valor[0] = expresion[i++];
            token.valor[1] = '\0';
            imprimirToken(token);
        }
    }
}

int main() {
    char expresion[100];
    int linea = 1;

    while (1) {
        printf("Ingrese una expresion (o presione Enter para salir): ");
        if (fgets(expresion, sizeof(expresion), stdin) == NULL || expresion[0] == '\n') {
            break;
        }
        procesarExpresion(expresion, linea++);
    }

    return 0;
}
