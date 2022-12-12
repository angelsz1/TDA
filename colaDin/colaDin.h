#ifndef COLADIN_H_INCLUDED
#define COLADIN_H_INCLUDED
#include "..\..\libs\common\common.h"
#include <string.h>
#include <stdlib.h>
typedef struct sNodo{
    void* dato;
    struct sNodo* sig;
    unsigned tamInfo;
}tNodo;

typedef struct{
    tNodo* ult;
    tNodo* pri;
}tCola;
bool colaVacia(const tCola* pc);
void crearCola(tCola* pc);
void destruirCola(tCola* pc);
bool encolar(tCola* pc, void* pd, unsigned tamDato);
bool desencolar(tCola* pc, void* pd, unsigned tamDato);
bool colaLlena(const tCola* pc, unsigned tamDato);
bool verPrimero(const tCola* pc, void* pd, unsigned tamDato);
//xtra
bool crearNodo(tNodo* pn, void* pd, unsigned tamDato);
void destruirNodo(tNodo* pn);
#endif // COLADIN_H_INCLUDED
