#include "colaDin.h"
//funciones extras
bool crearNodo(tNodo* pn, void* pd, unsigned tamDato){
    tNodo *nue =(tNodo*) malloc(sizeof(tNodo));
    nue->dato = malloc(tamDato);
    if(nue == NULL || nue->dato == NULL){
        free(nue->dato);
        free(nue);
        return false;
    }
    //copio los datos al nuevo nodo
    memcpy(nue->dato,pd,tamDato);
    nue->tamInfo = tamDato;
    nue->sig = NULL;
    //asigno el nuevo nodo al nodo parametro
    pn = nue;
    return true;
}
void destruirNodo(tNodo* pn){
    free(pn->dato);
    free(pn);
}
//primitivas tda cola dinamica
void crearCola(tCola* pc){
    pc->pri = pc->ult = NULL;
}
bool colaVacia(const tCola* pc){
    return pc->pri == NULL;
}
bool encolar(tCola* pc, void* pd, unsigned tamDato){
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue || !(nue->dato=malloc(tamDato))){
        free(nue);
        return false;
    }
    memcpy(nue->dato, pd, tamDato);
    nue->tamInfo = tamDato;
    nue->sig = NULL;
    if(!pc->pri)
        pc->ult = pc->pri = nue;
    else{
        pc->ult->sig = nue;
        pc->ult = pc->ult->sig;
    }
    return true;
}
bool desencolar(tCola* pc, void* pd, unsigned tamDato){
    if(!pc->pri)
        return false;
    tNodo* nodAElim = pc->pri;
    pc->pri = pc->pri->sig;
    if(!pc->pri)
        pc->ult = NULL;
    memcpy(pd, nodAElim->dato, MENOR(tamDato, nodAElim->tamInfo));
    destruirNodo(nodAElim);
    return true;
}
bool colaLlena(const tCola* pc, unsigned tamDato){
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    void* aux = malloc(tamDato);
    free(nue);
    free(aux);
    return (nue == NULL || aux == NULL)? true : false;
}
bool verPrimero(const tCola* pc, void* pd, unsigned tamDato){
    if(!pc->pri){
        printf("Cola vacia!\n");
        return false;
    }
    memcpy(pd, pc->pri->dato, MENOR(tamDato,pc->pri->tamInfo));
    return true;
}
void destruirCola(tCola* pc){
    if(pc->pri == NULL){
        printf("Cola vacia!");
        return;
    }
    tNodo* nodoAElim = pc->pri;
    pc->pri = pc->pri->sig;
    free(nodoAElim->dato);
    free(nodoAElim);
    while(pc->pri){
        nodoAElim = pc->pri;
        pc->pri = pc->pri->sig;
        free(nodoAElim->dato);
        free(nodoAElim);
    }
}
