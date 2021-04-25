// 5093257

#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>


bool pertenece(nat elem, TCadena cad) {
    if (esVaciaCadena(cad)) return false;
    TLocalizador aux = inicioCadena(cad);
    while (aux != NULL && natInfo(infoCadena(aux, cad)) != elem) {
      aux = siguiente(aux, cad);
    }
    if (aux == NULL) return false;
    return natInfo(infoCadena(aux, cad)) == elem;
}


nat longitud(TCadena cad) {
    nat contador = 0;
    TLocalizador aux = inicioCadena(cad);
    while (aux != NULL) {
        contador++;
        aux = siguiente(aux, cad);
    }
    return contador;
}


bool estaOrdenadaPorNaturales(TCadena cad) {
  bool ordenada = true;
  TLocalizador aux = inicioCadena(cad);
  if (esVaciaCadena(cad) || esFinalCadena(aux, cad)) return true;
  while (!esFinalCadena(aux, cad) && ordenada) {
    ordenada = natInfo(infoCadena(aux, cad)) <= natInfo(infoCadena(siguiente(aux, cad), cad));
    aux = siguiente(aux, cad);
  }
  return ordenada;
}

bool hayNatsRepetidos(TCadena cad) {
  bool repetidos = false;
  TLocalizador aux = inicioCadena(cad);
  while (aux != NULL && !repetidos) {
    TLocalizador target = siguiente(aux, cad);
    while (target != NULL && !repetidos) {
      repetidos = natInfo(infoCadena(aux, cad)) == natInfo(infoCadena(target, cad));
      target = siguiente(target, cad);
    }
    aux = siguiente(aux, cad);
  }
  return repetidos;
}


bool sonIgualesCadena(TCadena c1, TCadena c2) {
  TLocalizador aux1 = inicioCadena(c1);
  TLocalizador aux2 = inicioCadena(c2);
  bool iguales = true;
  while ( aux1 != NULL && aux2 != NULL && iguales ) {
    iguales = sonIgualesInfo(infoCadena(aux1, c1), infoCadena(aux2, c2));
    aux1 = siguiente(aux1, c1);
    aux2 = siguiente(aux2, c2);
  }
  return iguales && aux1 == NULL && aux2 == NULL;
}

TCadena concatenar(TCadena c1, TCadena c2) {
  TCadena c1copia = copiarSegmento(inicioCadena(c1), finalCadena(c1), c1);
  TCadena c2copia = copiarSegmento(inicioCadena(c2), finalCadena(c2), c2);
  return insertarSegmentoDespues(c2copia, finalCadena(c1copia), c1copia);
}

TCadena ordenar(TCadena cad) {
  TLocalizador aux = inicioCadena(cad);
  while (aux) {
    TLocalizador menor = menorEnCadena(aux, cad);
    intercambiar(aux, menor, cad); // ver si es necesario igualar a CAD
    aux = siguiente(aux, cad);
  }

  return cad;
}

TCadena cambiarTodos(nat original, nat nuevo, TCadena cad) {
  TLocalizador aux = siguienteClave(original, inicioCadena(cad), cad);
  while(aux) {
    TInfo info = crearInfo(nuevo, realInfo(infoCadena(aux, cad)));
    liberarInfo(infoCadena(aux, cad));
    cambiarEnCadena(info, aux, cad); // same above
    if(siguiente(aux, cad)) {
      aux = siguienteClave(original, siguiente(aux, cad), cad);
    } else {
      aux = NULL;
    }
  }

  return cad;
}


TCadena subCadena(nat menor, nat mayor, TCadena cad) {
  assert(estaOrdenadaPorNaturales(cad) || pertenece(menor, cad) || pertenece(mayor, cad));
  TLocalizador aux = inicioCadena(cad);
  TCadena nuevaCad = crearCadena();

  while(aux && (menor <= natInfo(infoCadena(aux, cad))) && natInfo(infoCadena(aux, cad)) <= mayor) {
    TInfo info = copiaInfo(infoCadena(aux, cad));
    nuevaCad = insertarAlFinal(info, nuevaCad);
    aux = siguiente(aux, cad);
  }

  return nuevaCad;
}



