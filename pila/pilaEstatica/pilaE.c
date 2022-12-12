#include "..\pila.h"

void crearPila(tPila *pp){
    pp->tope = 0;
}

bool pila_llena (const tPila *pp, size_t tamDato){
    return (pp->tope + tamDato + sizeof(size_t))>PILA_MAX;
}

bool pila_vacia(const tPila *pp){
    return pp->tope == 0;
}

void vaciar_pila(tPila *pp){
    pp->tope = 0;
}

bool poner_en_pila(tPila * pp, const void * pd, size_t tamDato){
    if((pp->tope + tamDato + sizeof(size_t))>PILA_MAX)
        return false;
    memcpy((pp->pila + pp->tope), pd, tamDato);
    pp->tope += tamDato;
    memcpy((pp->pila + pp->tope), &tamDato, sizeof(size_t));
    pp->tope += sizeof(size_t);
    return true;
}

bool sacar_de_pila(tPila * pp, void * pd, size_t tamDato){
    if(pp->tope == 0)
        return false;
    size_t tamDatoAnterior;
    memcpy(&tamDatoAnterior, pp->pila + pp->tope - sizeof(size_t), sizeof(size_t));
    pp->tope -= (MENOR(tamDato, tamDatoAnterior) + sizeof(size_t));
    memcpy(pd,(pp->pila + pp->tope), MENOR(tamDato, tamDatoAnterior));
    return true;
}
bool ver_tope(const tPila *pp, void * pd, size_t tamDato){
    if(pp->tope == 0)
        return false;
    size_t tamDatoAnterior,
             minTamDatos;
    memcpy(&tamDatoAnterior, pp->pila + pp->tope -sizeof(size_t), sizeof(size_t));
    minTamDatos = MENOR(tamDatoAnterior, tamDato);
    //pp->tope -= minTamDatos + sizeof(size_t);
    memcpy(pd, pp->pila + pp->tope -(minTamDatos + sizeof(size_t)), minTamDatos);
    //pp->tope += minTamDatos + sizeof(size_t);
    return true;
}
