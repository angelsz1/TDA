#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED
#include "..\..\libs\common\common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sNodoD{
    void* dato;
    unsigned tamDato;
    struct sNodoD* sig;
    struct sNodoD* ant;
}tNodoD;

typedef tNodoD* ListaD;
typedef int (*Cmp)(const void*, const void*);

void crearListaD(ListaD* pl);
bool listaVaciaD(ListaD* pl);
bool insertarEnListaInicioD(ListaD* pl, void* pd, unsigned tamDato);
bool insertarEnListaAlFinalD(ListaD* pl, void* pd, unsigned tamDato);
bool insertarEnListaPosD(ListaD* pl, void* pd, unsigned tamDato, unsigned pos);


//NODO

tNodoD* crearNodo(void* pd, unsigned tamDato);
#endif // LISTADOBLE_H_INCLUDED
