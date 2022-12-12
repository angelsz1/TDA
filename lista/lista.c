#include "lista.h"

//tda lista
void crearlista(list* pl){
    *pl = NULL;
}
bool listaVacia(list* pl){
    return *pl == NULL;
}
void vaciarLista(list *pl){
    tNodo* aux = *pl;
    while(*pl){
        *pl = aux->sig;
        destruirNodo(aux);
        aux = *pl;
    }
}
bool enlistarAlFinal(list* pl, const void* pd, unsigned tamDato){
    tNodo* newNode = (tNodo*)malloc(sizeof(tNodo));
    if(!newNode || !(newNode->dato = malloc(tamDato))){
        free(newNode);
        return false;
    }
    while((*pl))
        pl = &(*pl)->sig;
    memcpy(newNode->dato, pd, tamDato);
    newNode->tamDato = tamDato;
    newNode->sig = NULL;
    *pl = newNode;
    return true;
}
bool enlistarAlPrincipio(list* pl, const void* pd, unsigned tamDato){
    tNodo* aux =(tNodo*)malloc(sizeof(tNodo));
    if(!aux || !(aux->dato=malloc(tamDato))){
        free(aux);
        return false;
    }
    memcpy(aux->dato, pd, tamDato);
    aux->tamDato = tamDato;
    aux->sig = *pl;
    *pl = aux;
    return true;
}
bool desenlistarDelFinal(list* pl, void* pd, unsigned tamDato){
    if(!(*pl)){
        printf("Lista vacia!\n");
        return false;
    }
    while((*pl)->sig)
        pl = &(*pl)->sig;
    memcpy(pd, (*pl)->dato, MENOR(tamDato,(*pl)->tamDato));
    free((*pl)->dato);
    free(*pl);
    *pl = NULL;
    return true;
}
bool desenlistarDelPrincipio(list* pl, void* pd, unsigned tamDato){
    tNodo* nodAElim = *pl;
    if(!(*pl)){
        printf("Lista vacia!\n");
        return false;
    }
    memcpy(pd,(*pl)->dato, MENOR(tamDato, (*pl)->tamDato));
    *pl = (*pl)->sig;
    free(nodAElim->dato);
    free(nodAElim);
    return true;
}
bool ingresarEnListaOrdenado(list* pl, void* pd, unsigned tamDato, Cmp cmp, bool repetido)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue || !((nue->dato) = malloc(tamDato))){
        free(nue);
        return false;
    }
    memcpy(nue->dato, pd, tamDato);
    nue->tamDato = tamDato;
    if(!(*pl))
    {
        nue->sig = NULL;
        *pl = nue;
        return true;
    }
    if(cmp((*pl)->dato, nue->dato) >= 0)
    {
        if(!repetido && cmp((*pl)->dato, nue->dato) == 0)
            return false;
        nue->sig = *pl;
        *pl = nue;
        return true;
    }
    else if (repetido){
        while((*pl)->sig && cmp((*pl)->sig->dato, nue->dato) < 0)
            pl = &(*pl)->sig;
        nue->sig = (*pl)->sig;
        (*pl)->sig = nue;
    }
    else{
        while((*pl)->sig && cmp((*pl)->sig->dato, nue->dato) <= 0){
            if(cmp((*pl)->sig->dato, nue->dato) == 0)
            {
                free(nue->dato);
                free(nue);
                return false;
            }
            pl = &(*pl)->sig;
        }
        nue->sig = (*pl)->sig;
        (*pl)->sig = nue;
    }
    return true;
}
void ordenarLista(list* pl, int (*cmp)( void *, void *)){
    if(!(*pl))
        return;
    list ListaOrdenada = NULL;
    tNodo** actual = pl;
    tNodo* nodoAntMayor;
    tNodo* nai;
    while(*pl)
    {
        nodoAntMayor = anteriorAlMayor(actual, cmp);
        if(nodoAntMayor == NULL)
        {
            nai = *pl;
            *pl = (*pl)->sig;
        }
        else
        {
            nai = nodoAntMayor->sig;
            nodoAntMayor->sig = nodoAntMayor->sig->sig;
        }
        actual = pl;
        nai->sig = ListaOrdenada;
        ListaOrdenada = nai;
    }
    *pl = ListaOrdenada;
}
tNodo* anteriorAlMayor(tNodo** actual, int(*cmp)( void*,  void*)){
    tNodo* anteriorMayor = NULL;
    tNodo* mayor = *actual;
    while((*actual)->sig)
    {
        if((cmp)(mayor->dato, (*actual)->sig->dato) < 0){
            anteriorMayor = *actual;
            mayor = (*actual)->sig;
        }
        actual = &(*actual)->sig;
    }
    return anteriorMayor;
}

bool ingresarEnListaPorPosicion(list* pl, void* pd, unsigned tamDato, unsigned posicion)
{
    int posActual = 1;
    while(*pl && posActual < posicion)
    {
        pl = &(*pl)->sig;
        posActual++;
    }
    if(posActual != posicion)
        return false;
    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));
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
    nue->sig = *pl;
    *pl = nue;
    return true;

}
bool eliminarEnPosicion(list* pl, unsigned posicion)
{
    if(!(*pl))
        return false;
    int posAct = 1;
    while(*pl && posAct < posicion)
    {
        pl = &(*pl)->sig;
        posAct++;
    }
    if(posAct != posicion)
        return false;
    tNodo* nodAElim = *pl;
    *pl = (*pl)->sig;
    free(nodAElim->dato);
    free(nodAElim);
    return true;
}
bool desenlistarDePos(list* pl, void* pd, unsigned tamDato, unsigned posicion)
{
    if(!(*pl))
        return false;
    int posAct = 1;
    while(*pl && posAct < posicion)
    {
        pl = &(*pl)->sig;
        posAct++;
    }
    if(posAct != posicion)
        return false;
    tNodo* nodAElim = *pl;
    *pl = (*pl)->sig;
    memcpy(pd,nodAElim->dato,MENOR(nodAElim->tamDato,tamDato));
    free(nodAElim->dato);
    free(nodAElim);
    return true;
}
bool desenlistarPorContenido(list* pl, void* pd, int (*cmp)(void*, void*))
{
    while(*pl && (cmp)(pd,(*pl)->dato) != 0)
        pl = &(*pl)->sig;
    if(!(*pl))
        return false;
    tNodo* nai = *pl;
    *pl = (*pl)->sig;
    free(nai->dato);
    free(nai);
    return true;
}
int cantNodosLista(list* pl)
{
    int cont = 0;
    while(*pl)
    {
        cont++;
        pl = &(*pl)->sig;
    }
    return cont;
}
void ordenarLista2(list* pl, int (*cmp)( void *,  void *))
{
    if(!(*pl))
        return;
    tNodo** aux = pl;
    tNodo** mayor = pl;
    tNodo* nodoMayor;
    list listaOrd = NULL;
    while(*pl)
    {
        while(*aux)
        {
            if((cmp)((*aux)->dato, (*mayor)->dato) > 0)
                mayor = aux;
            aux = &(*aux)->sig;
        }
        aux = mayor;
        nodoMayor = *mayor;
        *aux = (*aux)->sig;
        nodoMayor->sig = listaOrd;
        listaOrd = nodoMayor;
        aux = mayor = pl;
    }
    *pl = listaOrd;

}


//nodos
/* tNodo *crearNodo(const void *pd, unsigned tamDato)
{
    tNodo *nue = (tNodo *)malloc(sizeof(tNodo));
    if (!nue || !(nue->dato = malloc(tamDato)))
    {
        free(nue);
        return NULL;
    }
    memcpy(nue->dato, pd, tamDato);
    nue->tamDato = tamDato;
    nue->sig = NULL;
    return nue;
}

void destruirNodo(tNodo *pn)
{
    free(pn->dato);
    free(pn);
}
 */
//iterador
void crearIterador(Iterador* it, list* pl){
    it->first = *pl;
    it->cur = NULL;
}
bool primeroDeLista(Iterador* it, void* pd, unsigned tamDato){
    if(!it->first){
        printf("Lista vacia!\n");
        return false;
    }
    it->cur = it->first;
    memcpy(pd, it->cur->dato, MENOR(tamDato, it->cur->tamDato));
    return true;
}
bool ultimoDeLista(Iterador* it, void* pd, unsigned tamDato){
    if(!it->first){
        printf("Lista vacia!\n");
        return false;
    }
    while(it->cur->sig)
        it->cur = it->cur->sig;
    memcpy(pd, it->cur->dato, MENOR(tamDato, it->cur->tamDato));
    return true;
}
bool siguiente(Iterador* it, void* pd, unsigned tamDato){
    if(!it->cur){
        printf("Iterador invalido!\n");
        return false;
    }
    it->cur = it->cur->sig;
    if(!it->cur){
        printf("No hay siguiente!\n");
        return false;
    }
    memcpy(pd, it->cur->dato, MENOR(tamDato, it->cur->tamDato));
    return true;
}
bool anterior(Iterador* it, void* pd, unsigned tamDato){
    if(!it->cur){
        printf("Iterador invalido!\n");
        return false;
    }
    tNodo* curr = it->cur;
    it->cur = it->first;
    while(it->cur->sig != curr)
        it->cur = it->cur->sig;
    memcpy(pd, it->cur->dato, MENOR(tamDato, it->cur->tamDato));
    return true;
}
