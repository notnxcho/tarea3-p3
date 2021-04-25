#include "../include/iterador.h"
#include "../include/utils.h"

#include <stdio.h> // sprintf
#include <stdlib.h>
#include <string.h> // strcpy, strcat
#include <assert.h>

typedef struct nodoIt *TNodoIt;
struct nodoIt {
    nat data;
    TNodoIt sig;
};

struct _rep_iterador {
  TNodoIt inicio, fin, actual;
  bool bloqueado;
};

/*
  Crea un 'TIterador' vacío (sin elementos) cuya posición actual no está
  definida.
  Se le puede agregar elementos.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador crearIterador() {
    TIterador res = new _rep_iterador;
    res->actual = res->inicio = res->fin = NULL;
    res->bloqueado = false;
    return res;
}

/*
  Agrega 'elem' al final de 'iter' si y solo si nunca se reinicio.
  Devuelve 'iter'.
  La posición actual sigue indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador agregarAIterador(nat elem, TIterador iter) {
    // chequear que nunca se reinicio el iter
    if (iter->bloqueado) return iter;

    // crear el nuevo nodo
    TNodoIt nuevoNodo = new nodoIt;
    nuevoNodo->data = elem;
    nuevoNodo->sig = NULL;


    // iterador vacio
    if (iter->inicio == NULL) {
        iter->inicio = iter->actual = iter->fin = nuevoNodo;
    } else {
    //iterador inicializado
    iter->fin->sig = nuevoNodo;
    iter->fin = nuevoNodo; 
    }
    return iter;
}

/*
  Mueve la posición actual de 'iter' al primero si y solo si 'iter' tiene
  elementos.
  Devuelve 'iter'.
  No se podrán agregar más elementos (aunque no hubiera ninguno).
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador reiniciarIterador(TIterador iter) {
    iter->actual = iter->inicio;
    iter->bloqueado = true;
    return iter;
}

/*
  Avanza la posición actual de 'iter' hacia el siguiente si y solo si'
  estaDefinidaActual(iter).
  Devuelve 'iter'.
  Si la posición actual es la última posición entonces la posición actual
  queda indefinida.
  El tiempo de ejecución en el peor caso es O(1).
 */
TIterador avanzarIterador(TIterador iter) {
    if (estaDefinidaActual(iter)) {
        iter->actual = iter->actual->sig;
    }
    return iter;
}
/*
  Devuelve el elemento de la posición actual de 'iter'.
  Precondición: estaDefinidaActual(iter).
  El tiempo de ejecución en el peor caso es O(1).
 */
nat actualEnIterador(TIterador iter) {
    assert(estaDefinidaActual(iter));
    if (estaDefinidaActual(iter)) {
        return iter->actual->data;
    }
}
/*
  Devuelve 'true' si y solo si la posición actual de 'iter' está definida.
  El tiempo de ejecución en el peor caso es O(1).
 */
bool estaDefinidaActual(TIterador iter) {
    return iter->actual != NULL;
}

/*
  Libera la memoria asignada a 'iter'.
  El tiempo de ejecución en el peor caso es O(n), siendo 'n' la cantidad
  de elementos de 'iter'.
 */
void liberarIterador(TIterador iter) {
    iter->actual = iter->inicio;
    while (iter->actual) {
        iter->actual = iter->actual->sig;
        delete(iter->inicio);
        iter->inicio = iter->actual;
    }
}