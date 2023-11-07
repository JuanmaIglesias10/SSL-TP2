#include <stdio.h>
#include <ctype.h>

typedef enum {
    NUMERO,
    OPERADOR,
    PARENTESIS_IZQUIERDO,
    PARENTESIS_DERECHO,
    DESCONOCIDO,
    FIN_DE_LINEA
} TipoToken;

typedef struct {
    TipoToken tipo;
    char valor[50];
    int linea;
    int columna;
} Token;

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

void reconocerTokens(char* expresion, int linea) {
    int i = 0;
    int columna = 1;
    char ultimoCaracter = '\0';

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
            if (isdigit(ultimoCaracter) || ultimoCaracter == ')' || ultimoCaracter == ' ') {
                token.tipo = OPERADOR;
                token.valor[0] = expresion[i++];
                token.valor[1] = '\0';
                imprimirToken(token);
            } else {
                printf("Error: Operadores consecutivos en la posicion %d\n", i);
                return;
            }
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
        } else if (expresion[i] == '\n') {
            token.tipo = FIN_DE_LINEA;
            imprimirToken(token);
            i++;
            linea++;
            columna = 1; // Reiniciar la columna al inicio de una nueva línea
        } else {
            token.tipo = DESCONOCIDO;
            token.valor[0] = expresion[i++];
            token.valor[1] = '\0';
            imprimirToken(token);
        }

        // Actualizar el último carácter procesado
        ultimoCaracter = expresion[i];
    }
}

int reconocerExpresion(char* expresion) {
    int i = 0;
    int parentesisAbiertos = 0;
    int parentesisCerrados = 0;

    char ultimoCaracter = '\0';

    while (expresion[i] != '\0') {
        if (expresion[i] == '(') {
            parentesisAbiertos++;
            if (ultimoCaracter == ')' || ultimoCaracter == '(' || ultimoCaracter == '*' || ultimoCaracter == '/' || ultimoCaracter == '+' || ultimoCaracter == '-') {
                printf("Error: Expresion invalida en la posicion %d\n", i);
                return 0;
            }
        } else if (expresion[i] == ')') {
            parentesisCerrados++;
            if (ultimoCaracter == '(' || ultimoCaracter == '*' || ultimoCaracter == '/' || ultimoCaracter == '+' || ultimoCaracter == '-') {
                printf("Error: Expresion invalida en la posicion %d\n", i);
                return 0;
            }
        } else if (expresion[i] == '*' || expresion[i] == '/' || expresion[i] == '+' || expresion[i] == '-') {
            if (ultimoCaracter == '(' || ultimoCaracter == '*' || ultimoCaracter == '/' || ultimoCaracter == '+' || ultimoCaracter == '-') {
                printf("Error: Expresion invalida en la posicion %d\n", i);
                return 0;
            }
        } else if (isdigit(expresion[i])) {
            if (ultimoCaracter == ')') {
                printf("Error: Expresion invalida en la posicion %d\n", i);
                return 0;
            }
        }

        ultimoCaracter = expresion[i];
        i++;
    }

    if (parentesisAbiertos == parentesisCerrados) {
        printf("La expresion es valida.\n");
        return 1;
    } else {
        printf("Error: La cantidad de parentesis abiertos y cerrados no coincide.\n");
        return 0;
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
        reconocerTokens(expresion, linea++);
        reconocerExpresion(expresion);
    }

    return 0;
}
