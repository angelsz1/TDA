#include "ListaDoble.h"

void crearListaD(ListaD* pl)
{
    *pl = NULL;
}
bool listaVaciaD(ListaD* pl)
{
    return *pl == NULL;
}
bool insertarEnListaInicioD(ListaD* pl, void* pd, unsigned tamDato)
{
    tNodoD* act = *pl;
    if(act)
        while(act->ant)
            act = act->ant;
    tNodoD* nue = crearNodo(pd, tamDato);
    if(!nue)
        return false;
    nue->sig = act;
    nue->ant = NULL;
    if(act)
        act->ant = nue;
    *pl = nue;
    return true;
}
bool insertarEnListaAlFinalD(ListaD* pl, void* pd, unsigned tamDato)
{
    tNodoD* act = *pl;
    if(act)
        while(act->sig)
            act = act->sig;
    tNodoD* nue = crearNodo(pd, tamDato);
    if(!nue)
        return false;
    nue->sig = NULL;
    nue->ant = act;
    if(act)
        act->sig = nue;
    *pl = nue;
    return true;
}
bool insertarEnListaPosD(ListaD* pl, void* pd, unsigned tamDato, unsigned pos)
{
    unsigned posAct = 1;
    tNodoD* act = *pl;
    tNodoD  *sig,
            *ant;
    if(act)
        while(act->ant)
            act = act->ant;
    while(act && posAct < pos)
    {
        ant = act;
        act = act->sig;
        posAct++;
    }
    if(posAct != pos)
        return false;

    tNodoD* nue = crearNodo(pd, tamDato);
    if(!nue)
        return false;


}
bool insertarEnListaOrd(ListaD* pl, void* pd, unsigned tamDato, Cmp cmp)
{
    tNodoD  *act = *pl,
            *sig,
            *ant;
    int com;
    while(act->sig && cmp(act->dato, pd) < 0 )
        act = act->sig;
    while(act->ant && cmp(act->dato, pd) > 0 )
        act = act->ant;
    com = cmp(act->dato, pd);
    if(!com)
        return false;
    tNodoD* nue = (tNodoD*)malloc(sizeof(tNodoD));
    void* aux = malloc(tamDato);
    if(!nue || !aux)
    {
        free(nue);
        free(aux);
        return false;
    }
    memcpy(aux, pd, tamDato);
    nue->dato = aux;
    nue->tamDato = tamDato;
    if(com > 0)
    {
        nue->sig = act;
        act->ant = nue;
        nue->ant = NULL;
    }
    else
    {
        ant = act;
        if(act->sig)
        {
            sig = act->sig;
            sig->ant = nue;
        }
        else
            sig = NULL;
        nue->sig = sig;
        nue->ant = ant;
        ant->sig = nue;
    }
    *pl = nue;
    return true;
}

tNodoD* crearNodo(void* pd, unsigned tamDato)
{
    tNodoD* nue = (tNodoD*)malloc(sizeof(tNodoD));
    void* aux = malloc(tamDato);
    if(!nue || !aux)
    {
        free(nue);
        free(aux);
        return NULL;
    }
    memcpy(aux, pd, tamDato);
    nue->dato = aux;
    nue->tamDato = tamDato;
    return nue;
}
