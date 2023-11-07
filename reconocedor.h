#ifndef RECONOCEDOR_H
#define RECONOCEDOR_H


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

int reconocerExpresion(char* expresion);
void reconocerTokens(char* expresion, int linea);
void imprimirToken(Token t);

#endif