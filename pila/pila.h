#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#define PILA_MAX 500
#include "..\..\libs\common\common.h"
#include <string.h>
typedef struct
{
    char pila [PILA_MAX];
    size_t tope;
}tPila;

void crearPila(tPila *pp);
bool pila_llena (const tPila *pp, size_t tamDato);
bool poner_en_pila(tPila * pp, const void * pd, size_t tamDato);
bool ver_tope(const tPila *pp, void * pd, size_t tamDato);
bool pila_vacia(const tPila *pp);
bool sacar_de_pila(tPila * pp, void * pd, size_t tamDato);
void vaciar_pila(tPila *pp);

#endif //PILA_H_INCLUDED
