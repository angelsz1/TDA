#include "arbol.h"

void crearArbol(Arbol* pa)
{
    *pa = NULL;
}
int alturaArbol(const Arbol* pa)
{
    if(!*pa)
        return 0;
    return MAYOR(alturaArbol(&(*pa)->hIzq),alturaArbol(&(*pa)->hDer)) + 1;
}
int insertarEnArbol(Arbol* pa, void* pd, unsigned tamDato, int(*cmp)(const void* e1, const void* e2))
{
    while(*pa)
    {
        if((cmp)(pd, (*pa)->dato) > 0)
            pa = &(*pa)->hDer;
        else if((cmp)(pd, (*pa)->dato) < 0)
            pa = &(*pa)->hIzq;
        else
            return DUP;
    }
    aNodo* nue = (aNodo*)malloc(sizeof(aNodo));
    void* aux = malloc(tamDato);
    if(!nue || !aux)
    {
        free(nue);
        free(aux);
        return SIN_MEM;
    }
    memcpy(aux, pd, tamDato);
    nue->dato = aux;
    nue->tamDato = tamDato;
    nue->hDer = NULL;
    nue->hIzq = NULL;
    *pa = nue;
    return TODO_OK;
}
int cantidadDeNodosArbol(const Arbol* pa)
{
    if(!*pa)
        return 0;
    return cantidadDeNodosArbol(&(*pa)->hIzq) +
           cantidadDeNodosArbol(&(*pa)->hDer) + 1;
}
int cantidadDeNodosHastaNivel(const Arbol* pa, int nivel)
{
    if(!*pa || !nivel )
        return 0;
    return cantidadDeNodosHastaNivel(&(*pa)->hIzq, nivel -1 ) +
           cantidadDeNodosHastaNivel(&(*pa)->hDer, nivel -1 ) + 1;
}
boolean esArbolCompleto(const Arbol* pa)
{
    if(!*pa)
        return t;
    int cnc =(1<<alturaArbol(pa)) - 1;
    return cnc == cantidadDeNodosArbol(pa);
}
boolean esArbolBalanceado(const Arbol* pa)
{
    if(alturaArbol(pa) <= 2)
        return t;
    int cnc = (1 << ((alturaArbol(pa)) -1)) -1;
    int cnr = cantidadDeNodosHastaNivel(pa, alturaArbol(pa) -2); // la altura me da nivel + 1, y yo necesito calcular los nodos hasta nivel - 1
    return cnc == cnr;
}
boolean recorrerEnPreorden(Arbol* pa, void(*mostrar)(void*))
{
    if(!*pa)
        return f;
    mostrar((*pa)->dato);
    recorrerEnPreorden(&(*pa)->hIzq, mostrar);
    recorrerEnPreorden(&(*pa)->hDer, mostrar);
    return t;
}

int ingresarEnArbolDSOrdenado(Arbol* pa, void* ds,
                              unsigned (*leer)(void** , void*, unsigned, void* params),
                              int li, int ls, void* params  )
{
    int m = (li + ls)/2,
        r;
    if(li>ls)
        return TODO_OK;

    (*pa) = (aNodo*) malloc(sizeof(aNodo));
    if(!*pa || !((*pa)->tamDato = leer(&(*pa)->dato, ds, m, params)))
    {
        free(*pa);
        return SIN_MEM;
    }
    (*pa)->hIzq = (*pa)->hDer = NULL;

    if((r=ingresarEnArbolDSOrdenado(&(*pa)->hIzq, ds, leer, li, m-1, params)) != TODO_OK)
        return r;
    return ingresarEnArbolDSOrdenado(&(*pa)->hDer, ds, leer, m+1, ls, params);

}

void eliminarDeArbol(Arbol* pa, void* pd, size_t tamDato, int(*cmp)(const void*, const void*))
{
    if(!*pa)
        return;
    aNodo** nodoAElim = buscarNodoArbol(pa, pd, cmp);
    if(!nodoAElim)
        return;
    if(esHoja(*nodoAElim))
    {
        free((*nodoAElim)->dato);
        free(*nodoAElim);
        *nodoAElim = NULL;
        return;
    }
    aNodo** reemplazo;
    int altHijIzq = alturaArbol(&(*nodoAElim)->hIzq);
    int altHijDer = alturaArbol(&(*nodoAElim)->hDer);
    if(altHijDer >= altHijIzq)
    {
        reemplazo = &(*nodoAElim)->hDer;
        while((*reemplazo)->hIzq)
            reemplazo = &(*reemplazo)->hIzq;
    }
    else
    {
        reemplazo = &(*nodoAElim)->hIzq;
        while((*reemplazo)->hDer)
            reemplazo = &(*reemplazo)->hDer;
    }
    memcpy((*nodoAElim)->dato, (*reemplazo)->dato, (*reemplazo)->tamDato);
    (*nodoAElim)->tamDato = (*reemplazo)->tamDato;
    eliminarDeArbol(reemplazo, (*reemplazo)->dato, (*reemplazo)->tamDato, cmp);
}
boolean esHoja(aNodo* nod)
{
    return !nod->hDer && !nod->hIzq;
}
const Arbol* buscarNodoArbol(const Arbol* pa, const void* pd, int(*cmp)(const void*, const void*))
{
    if(!*pa)
        return NULL;
    int r;
    if((r = (cmp)((*pa)->dato, pd)) > 0)
        return buscarNodoArbol(&(*pa)->hIzq, pd, cmp);
    else if(r < 0)
        return buscarNodoArbol(&(*pa)->hDer, pd, cmp);
    return pa;
}

int ingresarEnArbolDSOrdenadoGuti(Arbol* pa, void* ds,
                              unsigned (*leer)(void** , void*, unsigned, void* params),
                              int li, int ls, void* params  )
{
    if(li > ls)
        return TODO_OK;
    int medio = (li + ls) / 2,
        retorno;
    aNodo* nai = malloc(sizeof(aNodo));
    if(!nai)
    {
        free(nai);
        return SIN_MEM;
    }

    if(!(nai->tamDato = leer(&nai->dato, ds, medio, params)))
    {
        free(nai->dato);
        free(nai);
        return SIN_MEM;
    }

    *pa = nai;
    (*pa)->hDer = (*pa)->hIzq = NULL;
    if((retorno = ingresarEnArbolDSOrdenadoGuti(&(*pa)->hDer, ds, leer, medio + 1, ls, params)) != TODO_OK)
        return retorno;
    else
        return ingresarEnArbolDSOrdenadoGuti(&(*pa)->hIzq, ds, leer, li, medio - 1, params);

}
aNodo** mayorDeArbol(Arbol* pa)
{
    if(!*pa)
        return NULL;
    if(!(*pa)->hDer)
        return pa;
    return mayorDeArbol(&(*pa)->hDer);
}
aNodo** menorDeArbol(Arbol* pa)
{
    if(!*pa)
        return NULL;
    if(!(*pa)->hIzq)
        return pa;
    return menorDeArbol(&(*pa)->hIzq);
}

unsigned leerDesdeVectorEnteros(void **d, void* vec, unsigned pos, void* params)
{
    *d=malloc(sizeof(int));
    if(!*d)
        return 0;
    memcpy(*d, vec+(sizeof(int)*pos), sizeof(int));
    return sizeof(int);
}

unsigned leerDesdeArchivoEntero(void **d, void* vec, unsigned pos, void* params)
{
    *d = (int*)malloc(sizeof(int));
    if(!*d)
        return 0;
    FILE* pArch = (FILE*) vec;

    fseek(pArch, sizeof(int)*pos, SEEK_SET);
    fread(*d, sizeof(int), 1, pArch);

    return sizeof(int);
}

void mostrarInt(void* n1)
{
    printf("%d ",*(int*)n1);
}

void imprimirConForma(void* info, unsigned tam, unsigned n, void* params)
{
    int * i = (int *) info;
    printf("%*s-%3d-\n",n*3, "", *i);
}

void imprimirArbol(const Arbol* arbol, void (*imprimir)(const void*, const void*, int), void* datosImprimir){
    return imprimirArbolRecursivo(arbol, imprimir, datosImprimir, 0);
}

void imprimirArbolRecursivo(const Arbol* arbol, void (*imprimir)(const void*, const void*, int), void* datosImprimir, int nivel) {
    if(!*arbol) {
        return;
    }

    imprimirArbolRecursivo(&(*arbol)->hDer, imprimir, datosImprimir, nivel+1);

    imprimir((*arbol)->dato, datosImprimir, nivel);

    imprimirArbolRecursivo(&(*arbol)->hIzq, imprimir, datosImprimir, nivel+1);
}
void imprimirEntero(const void* elemento, const void* datosImprimir, int nivel) {
    for(int i=0; i<nivel; i++) {
        putchar('\t');
    }
    int numero = *(int*)elemento;
    printf("%d\n", numero);
}


void vaciarArbol(Arbol* pa)
{
    if(!*pa)
        return;
    vaciarArbol(&(*pa)->hIzq);
    vaciarArbol(&(*pa)->hDer);
    free((*pa)->dato);
    free(*pa);
    *pa = NULL;
}



boolean arbolVacio(Arbol* pa)
{
    return *pa == NULL;
}

int insertarEnArbol2(Arbol* pa, void* pd, unsigned tamDato, int (*cmp)(const void*, const void* ))
{
    int c;
    while(*pa)
    {
        if((c = (cmp)((*pa)->dato, pd) ) == 0 )
            return DUP;
        if(*pa && c < 0)
            pa = &(*pa)->hDer;
        else if(*pa && c > 0)
            pa = &(*pa)->hIzq;
    }
    aNodo* nue = (aNodo*)malloc(sizeof(aNodo));
    void* aux = malloc(tamDato);
    if(!nue || !aux)
    {
        free(nue);
        free(aux);
        return SIN_MEM;
    }
    memcpy(aux, pd, tamDato);
    nue->dato = aux;
    nue->tamDato = tamDato;
    *pa = nue;
    return TODO_OK;
}

bool eliminarDeArbolYo(Arbol* pa, void* pd, int(*cmp)(const void*, const void*))
{
    if(!*pa)
        return false;
    aNodo** nae = buscarNodoArbolYo(pa, pd, cmp);
    return eliminarRaizDeArbol(nae);
}
bool eliminarRaizDeArbol(Arbol* pa)
{
    if(!*pa)
        return false; // no lo encontro
    free((*pa)->dato);
    if(!(*pa)->hDer && !(*pa)->hIzq)
    {
        free(*pa);
        *pa = NULL;
        return true;
    }
    aNodo** remp,
            *elim;

    remp = (alturaArbol(&(*pa)->hIzq) > alturaArbol(&(*pa)->hDer) ) ? mayorDeArbol(&(*pa)->hIzq) : menorDeArbol(&(*pa)->hDer);

    elim = *remp;
    (*pa)->dato = elim ->dato;
    (*pa)->tamDato = elim->tamDato;
    *remp = elim->hIzq ? elim->hIzq : elim->hDer;
    free(elim);
    return 1;
}
aNodo** buscarNodoArbolYo(Arbol* pa, void* pd, int(*cmp)(const void*, const void*))
{
    int c;
    while(*pa && (c = cmp((*pa)->dato, pd) ))
    {
        if( c < 0)
            pa = &(*pa)->hDer;
        else
            pa = &(*pa)->hIzq;
    }
    if(!*pa)
        return NULL;
    return pa;

}

void imprimirArbol_ALU(Arbol* pa, Imprimir im , void* datos)
{
    if(!*pa)
        return;
    imprimirRec(pa, im, datos, 0);
}
void imprimirRec(Arbol* pa, Imprimir im, void* datos, int nivel)
{
    if(!*pa)
        return;
    imprimirRec(&(*pa)->hDer, im, datos, nivel + 1);
    im((*pa)->dato, datos, nivel);
    imprimirRec(&(*pa)->hIzq, im, datos, nivel + 1);

}
void imprimirEntero_ALU(const void* dato, const void* datosImp, int nivel)
{
    for(int i = 0; i < nivel; i++)
        putchar('\t');
    printf("%d\n",*(int*)dato );
}

int cargarArbolDeArchivoOrdenado(Arbol* pa, unsigned tamDato, const char* nomArch)
{
    FILE* pf = fopen(nomArch, "rb");
    if(!pf)
        return 3; //err_arch
    fseek(pf, 0, SEEK_END);
    int cantReg = ftell(pf) / tamDato,
        r;
    r = cargarArbolRec(pa, pf, leerDesdeArchivoBIN, 0, cantReg -1, &tamDato);
    fclose(pf);
    return r;
}
int cargarArbolRec(Arbol* pa, void* ds, size_t(*leer)(void** d, void* ds, int pos, void* params ), int li, int ls, void* params)
{
    if(li>ls)
        return 1; // todo_ok
    int medio = (li+ls)/2,
        r;
    *pa = (aNodo*)malloc(sizeof(aNodo));
    if(!*pa || !((*pa)->tamDato = leer(&(*pa)->dato, ds, medio, params )) )
    {
        free(*pa);
        return 2; //sin_mem
    }
    (*pa)->hDer = (*pa)->hIzq = NULL;
    if( (r = cargarArbolRec(&(*pa)->hIzq, ds, leer, li, medio -1, params)) != 1)
        return r;
    return cargarArbolRec(&(*pa)->hDer, ds, leer, medio + 1, ls, params);

}
size_t leerDesdeArchivoBIN(void** d, void* ds, int pos, void* params)
{
    int tam = *(int*)params;
    *d = malloc(tam);
    fseek((FILE*)ds, pos*tam, SEEK_SET);
    fread(*d, tam, 1, (FILE*)ds);
    return tam;
}
