#include "../include/iterador.h"
#include "../include/utils.h"
#include "../include/binario.h"
#include <stdio.h> // sprintf
#include <stdlib.h>
#include <string.h> // strcpy, strcat
#include <assert.h>

typedef struct _rep_binario *TBinario;
struct _rep_binario {
    TInfo dato;
    TBinario der;
    TBinario izq;
};

TBinario crearBinario() {
    TBinario res = new _rep_binario;
    return res;
}

TBinario insertarEnBinario(TInfo i, TBinario b) {
    if (b) {
        if (natInfo(i) > natInfo(b->dato)) {
            b->der = insertarEnBinario(i, b->der);
        
        } else if (natInfo(i) < natInfo(b->dato)) {
            b->izq = insertarEnBinario(i, b->izq);
        }
    } else {
        TBinario nuevoArbol = new _rep_binario;
        nuevoArbol->der = nuevoArbol->izq = NULL;
        nuevoArbol->dato = i;
        b = nuevoArbol;
    }
    return b;
}

