#ifndef PILADINAMICA_H_INCLUDED
#define PILADINAMICA_H_INCLUDED

#include "..\..\..\libs\common\common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodo{
    void* info;
    size_t tamInfo;
    struct sNodo* sigNodo;
}Nodo;

typedef Nodo* tPila;

void crearPila(tPila *pp);
bool pila_llena (const tPila *pp, size_t tamDato);
bool poner_en_pila(tPila * pp, const void * pd, size_t tamDato);
bool ver_tope(const tPila *pp, void * pd, size_t tamDato);
bool pila_vacia(const tPila *pp);
bool sacar_de_pila(tPila * pp, void * pd, size_t tamDato);
void vaciar_pila(tPila *pp);

#endif // PILADINAMICA_H_INCLUDED
