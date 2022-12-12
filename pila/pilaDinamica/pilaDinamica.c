#include "pilaDinamica.h"

void crearPila(tPila *pp){
   *pp = NULL;
}
bool pila_vacia(const tPila *pp){
    return *pp == NULL;
}
bool poner_en_pila(tPila *pp, const void *pd, size_t tamDato){
    Nodo *nue;
    nue = (Nodo*) malloc(sizeof(Nodo));
    nue->info = malloc(tamDato);
    if(nue == NULL || nue->info == NULL){
        free(nue->info);
        free(nue);
        return false;
    }
    memcpy(nue->info, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sigNodo = *pp;
    *pp = nue;
    return true;
}
bool sacar_de_pila(tPila *pp, void *pd, size_t tamDato){
    Nodo *n = *pp;
    if(*pp == NULL)
        return false;
    memcpy(pd, (*pp)->info, MENOR(tamDato, (*pp)->tamInfo));
    *pp = n->sigNodo;
    free(n->info);
    free(n);
    return true;
}
bool ver_tope(const tPila *pp, void* pd, size_t tamDato){
    if(*pp == NULL)
        return false;
    memcpy(pd, (*pp)->info, MENOR(tamDato, (*pp)->tamInfo));
    return true;
}
bool pila_llena(const tPila *pp, size_t tamDato){
    Nodo* nue = (Nodo*)malloc(sizeof(Nodo));
    nue->info = malloc(tamDato);
    free(nue->info);
    free(nue);
    return !nue || !nue->info;
}
void vaciar_pila(tPila *pp){
    Nodo* n;
    while(*pp){
        n = *pp;
        *pp = n->sigNodo;
        free(n->info);
        free(n);
    }
}
