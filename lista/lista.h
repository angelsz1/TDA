#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "..\..\libs\common\common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct sNodo{
    void* dato;
    struct sNodo* sig;
    unsigned tamDato;
}tNodo;

typedef tNodo* list;

typedef struct
{
    tNodo* first;
    tNodo* cur;
}Iterador;
typedef int (Cmp)(void* n1, void* n2);

//tda lista
void crearlista(list* pl);
void vaciarLista(list *pl);
void ordenarLista(list* pl, int (*cmp)( void *,  void *));
bool listaVacia(list* pl);
bool enlistarAlFinal(list* pl, const void* pd, unsigned tamDato);
bool enlistarAlPrincipio(list* pl, const void* pd, unsigned tamDato);
bool desenlistarDelFinal(list* pl, void* pd, unsigned tamDato);
bool desenlistarDelPrincipio(list* pl, void* pd, unsigned tamDato);
bool ingresarEnListaOrdenado(list* pl, void* pd, unsigned tamDato, Cmp cmp, bool repetido);
bool ingresarEnListaPorPosicion(list* pl, void* pd, unsigned tamDato, unsigned posicion);
bool eliminarEnPosicion(list* pl, unsigned posicion);
bool desenlistarDePos(list* pl, void* pd, unsigned tamDato, unsigned posicion);
void ordenarLista2(list* pl, int (*cmp)( void *,  void *));
bool desenlistarPorContenido(list* pl, void* pd, int (*cmp)(void*, void*));
//xtra func
tNodo* anteriorAlMayor(tNodo** actual, int(*cmp)( void*,  void*));
tNodo* crearNodo(const void *pd, unsigned tamDato);
void destruirNodo(tNodo* pn);
int cantNodosLista(list* pl);
//void recorrerLista(list* pl, Accion accion, void* datosAccion);
//iterador
void crearIterador(Iterador* it, list* pl);
bool primeroDeLista(Iterador* it, void* pd, unsigned tamDato);
bool ultimoDeLista(Iterador* it, void* pd, unsigned tamDato);
bool siguiente(Iterador* it, void* pd, unsigned tamDato);
bool anterior(Iterador* it, void* pd, unsigned tamDato);


#endif // LISTA_H_INCLUDED
