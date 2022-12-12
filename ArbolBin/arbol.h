#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../libs/common/common.h"
#define DUP 3
#define SIN_MEM 2
#define TODO_OK 1
#define TODO_MAL 0

#define MAYOR(x,y) (x>y? x: y)


typedef struct BNodo{
    void* dato;
    unsigned tamDato;
    struct BNodo* hIzq;
    struct BNodo* hDer;

} aNodo;

typedef aNodo* Arbol;
typedef enum{f, t} boolean;

//typedef int (Accion)(const void elemento, const void* datos);
//typedef int (Actualizar)(void actual, void* nuevo);
typedef void (*Imprimir)(const void *elemento, const void* datos, int nivel);


/*
void crearArbol(Arbol* arbol);
int insertarEnArbol(Arbol* arbol, void* elemento, size_t tamElemento, FuncComparar comparar, FuncActualizar actualizar);
int recorrerArbolPreOrden(const Arbol* arbol, FuncAccion accion, void* datosAccion);
int recorrerArbolEnOrden(const Arbol* arbol, FuncAccion accion, void* datosAccion);
int recorrerArbolPosOrden(const Arbol* arbol, FuncAccion accion, void* datosAccion);
void imprimirArbol(const Arbol* arbol, FuncImprimir imprimir, void* datosImprimir);
void eliminarDeArbol(Arbol* arbol, void* elemento, size_t tamElemento, FuncComparar comparar);
const Arbol* buscarNodoArbol(const Arbol* arbol, const void* elemento, FuncComparar comparar);
const Arbol* menorDeArbol(const Arbol* arbol);
const Arbol* mayorDeArbol(const Arbol* arbol);
int alturaArbol(const Arbol* arbol);
int esArbolCompleto(const Arbol* arbol);
int esArbolBalanceado(const Arbol* arbol);
int esArbolAVL1 (const Arbol* arbol);
int esArbolAVL2 (const Arbol* arbol);
*/
void crearArbol(Arbol *pa);
boolean arbolVacio(Arbol* pa);
int alturaArbol(const Arbol* pa);
int insertarEnArbol(Arbol* pa, void* pd, unsigned tamDato, int(*cmp)(const void*, const void*));
int cantidadDeNodosArbol(const Arbol* pa);
boolean esArbolCompleto(const Arbol* pa);
boolean esArbolBalanceado(const Arbol* pa);
boolean recorrerEnPreorden(Arbol* pa, void(*mostrar)(void*));
void mostrarInt(void* n1);
unsigned leerDesdeVectorEnteros(void **d, void* vec, unsigned pos, void* params);
unsigned leerDesdeArchivoEntero(void **d, void* vec, unsigned pos, void* params);
int ingresarEnArbolDSOrdenado(Arbol* pa, void* ds,
                              unsigned (*leer)(void** , void*, unsigned, void* params),
                              int li, int ls, void* params  );
int ingresarEnArbolDSOrdenadoGuti(Arbol* pa, void* ds,
                                  unsigned (*leer)(void** , void*, unsigned, void* params),
                                  int li, int ls, void* params  );
void eliminarDeArbol(Arbol* pa, void* pd, size_t tamDato, int(*cmp)(const void*, const void*));
const Arbol* buscarNodoArbol(const Arbol* pa, const void* pd, int(*cmp)(const void*, const void*));
boolean esHoja(aNodo* nod);
aNodo** mayorDeArbol(Arbol* pa);
aNodo** menorDeArbol(Arbol* pa);
void vaciarArbol(Arbol* pa);
int insertarEnArbol2(Arbol* pa, void* pd, unsigned tamDato, int (*cmp)(const void*, const void* ));
void imprimirConForma(void* info, unsigned tam, unsigned n, void* params);
aNodo** buscarNodoArbolYo(Arbol* pa, void* pd, int(*cmp)(const void*, const void*));
bool eliminarDeArbolYo(Arbol* pa, void* pd, int(*cmp)(const void*, const void*));
bool eliminarRaizDeArbol(Arbol* pa);
void imprimirArbol_ALU(Arbol* pa, Imprimir im , void* datos);
void imprimirRec(Arbol*, Imprimir im, void* datos, int nivel);
void imprimirEntero_ALU(const void* dato, const void* datosImp, int nivel);

size_t leerDesdeArchivoBIN(void** d, void* ds, int pos, void* params);
int cargarArbolRec(Arbol* pa, void* ds, size_t(*leer)(void** d, void* ds, int pos, void* params ), int li, int ls, void* params);
int cargarArbolDeArchivoOrdenado(Arbol* pa, unsigned tamDato, const char* nomArch);

void imprimirEntero(const void* elemento, const void* datosImprimir, int nivel);
void imprimirArbolRecursivo(const Arbol* arbol, void (*imprimir)(const void*, const void*, int), void* datosImprimir, int nivel);
void imprimirArbol(const Arbol* arbol, void (*imprimir)(const void*, const void*, int), void* datosImprimir);
#endif // ARBOL_H_INCLUDED
