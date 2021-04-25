// 5093257

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad) {
  while (cad->inicio) {
    TLocalizador borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(borrar -> dato);
    delete borrar;
  }
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
  return !cad || cad->inicio == NULL;
}

TLocalizador inicioCadena(TCadena cad) {
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else {
    res = cad->inicio;
  }
  return res;
}

TLocalizador finalCadena(TCadena cad) {
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else {
    res = cad->final;
  }
  return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  return loc->siguiente;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  return loc->anterior;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  return (!esVaciaCadena(cad)) && (loc == finalCadena(cad));
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
  return (!esVaciaCadena(cad)) && (loc == inicioCadena(cad));
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  TLocalizador nuevoNodo = new nodoCadena;
  nuevoNodo->dato = i;
  nuevoNodo->anterior = cad->final;
  nuevoNodo->siguiente = NULL;
  if (cad->final) {
    cad->final->siguiente = nuevoNodo;
  }
  if (esVaciaCadena(cad)) {
    cad->inicio = nuevoNodo;
  }
  cad->final = nuevoNodo;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  TLocalizador nuevoNodo = new nodoCadena;
  nuevoNodo->dato = i;
  nuevoNodo->siguiente = loc;
  nuevoNodo->anterior = loc->anterior;
  
  if (loc != inicioCadena(cad)) {
    loc->anterior->siguiente = nuevoNodo;
  } else {
    cad->inicio = nuevoNodo;
  }
  loc->anterior = nuevoNodo;
  return cad;
}


TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  if (esInicioCadena(loc, cad)) {
    if (esFinalCadena(loc, cad)) {
      liberarInfo(loc->dato);
      cad->inicio = NULL;
      cad->final = NULL; 
      delete loc;
    }
    else {
      liberarInfo(loc->dato);
      cad->inicio = loc->siguiente;
      delete loc;
    }
  }
  else if (esFinalCadena(loc, cad)) {
    loc->anterior->siguiente = NULL;
    liberarInfo(loc->dato);
    cad->final = loc->anterior;
    delete loc;
  }
  else {
    TLocalizador aux = loc->anterior;
    aux->siguiente = loc->siguiente;
    loc->siguiente->anterior = aux;
    liberarInfo(loc->dato);
    delete loc;
  } 
  return cad;
}


void imprimirCadena(TCadena cad) {
  TLocalizador actual = inicioCadena(cad);
  while (actual) {
    ArregloChars auxArray = infoATexto(infoCadena(actual, cad));
    printf ("%s", auxArray);
    delete [] auxArray;
    actual = actual->siguiente;
  }
  printf("\n");
}

TLocalizador kesimo(nat k, TCadena cad) {
  if (k<=0) return NULL;
  TLocalizador head = cad->inicio;
  nat contador = 1;
  while (head != NULL && contador != k) {
    head = head->siguiente;
    contador++;
  }
  return head;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));

  if (esVaciaCadena(cad)) {
    cad->inicio = sgm->inicio;
    cad->final = sgm->final;
  } else if (!esVaciaCadena(sgm)) {
    TLocalizador aux = loc->siguiente;
    loc->siguiente = sgm->inicio;
    sgm->inicio->anterior = loc;
    if (!esFinalCadena(loc, cad)) {
      loc->siguiente->anterior = sgm->final;
      sgm->final->siguiente = aux;
    } else {
      sgm->final->siguiente = NULL;
      cad->final = sgm->final;
    }
  }
  delete(sgm);
  return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  assert(esVaciaCadena(cad) || precedeEnCadena(desde, hasta, cad));
  TCadena resultado = crearCadena();
  if (esVaciaCadena(cad)) {
    resultado->inicio = NULL;
    resultado->final = NULL;
    return resultado;
  }
  TLocalizador aux = desde;
  while (aux != hasta) {
    insertarAlFinal(copiaInfo(aux->dato), resultado);
    aux = aux->siguiente;
  }
  insertarAlFinal(copiaInfo(hasta->dato), resultado);
  return resultado;
} 

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TCadena cadAux = crearCadena();
  cadAux->inicio = desde;
  cadAux->final = hasta;
  cadAux->final->siguiente = NULL;
  cadAux->inicio->anterior = NULL;
  liberarCadena(cadAux);
  if (esFinalCadena(hasta, cad)) { 
    cad->final = desde->anterior;
  } else {
    hasta->siguiente->anterior = desde->anterior;
  }
  if (esInicioCadena(desde, cad)) {
    cad->inicio = hasta->siguiente;
    if (esFinalCadena(hasta, cad)) {
      cad->inicio = cad->final = NULL;
    } else {
      hasta->siguiente->anterior = NULL;
      cad->inicio = hasta->siguiente;
    }
  } else {
    desde->anterior->siguiente = hasta->siguiente;
  }
  delete(hasta);
  delete(desde);
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  loc->dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  TInfo aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad) || loc == NULL) return false;
  TLocalizador aux = inicioCadena(cad);
  while (aux != loc && aux != NULL) {
    aux = aux->siguiente;
  }
  return aux == loc;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  if (esVaciaCadena(cad) || loc2 == NULL) return false;
  TLocalizador aux = loc1;
  while (aux != loc2 && aux != NULL) {
    aux = aux->siguiente;
  }
  return aux == loc2;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  if (esVaciaCadena(cad)) return loc = NULL;
  TLocalizador aux = loc;
  while (aux != NULL && natInfo(aux->dato) != clave) {
    aux = aux->siguiente;
  }
  return aux;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  assert(esVaciaCadena(cad) || localizadorEnCadena(loc, cad));
  if (esVaciaCadena(cad)) return loc = NULL;
  TLocalizador aux = loc;
  while (aux != NULL && natInfo(aux->dato) != clave) {
    aux = aux->anterior;
  }
  return aux;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador menor = loc;
  TLocalizador aux = loc;
  while (aux != NULL) {
    if (natInfo(aux->dato) < natInfo(menor->dato)) {
      menor = aux;
    }
    aux = aux->siguiente;
  }
  return menor;
}
