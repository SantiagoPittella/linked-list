#include "lista.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
    struct nodo* proximo;
    void* dato;
} nodo_t;

struct lista {
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

/*
Crea un nodo con el dato que se le pasa por parametro.
devuelve true si el nodo se creo correctamente,
false en caso de error
*/
nodo_t* nodo_crear(void* dato) {
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (!nodo) return false;

    nodo->dato = dato;
    nodo->proximo = NULL;
    return nodo;
}

lista_t* lista_crear() {
    lista_t* lista = malloc(sizeof(lista_t));
    if (!lista) return NULL;

    lista->largo = 0;
    lista->primero = NULL;
    lista->ultimo = NULL;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista) {
    return lista->largo == 0;
}

bool lista_insertar_primero(lista_t* lista, void* dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (!nodo) return false;

    nodo->proximo = lista->primero;
    lista->largo++;
    lista->primero = nodo;

    if (!lista->ultimo) lista->ultimo = nodo;

    return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato) {
    nodo_t* nodo = nodo_crear(dato);
    if (!nodo) return false;

    if (lista_esta_vacia(lista)) {
        lista->primero = nodo;
    } else {
        lista->ultimo->proximo = nodo;
    }

    lista->ultimo = nodo;
    lista->largo++;
    return true;
}

void* lista_borrar_primero(lista_t* lista) {
    if (lista_esta_vacia(lista)) return NULL;

    nodo_t* primero = lista->primero;
    void* dato = lista->primero->dato;
    lista->primero = lista->primero->proximo;

    if (lista->largo == 1) {
        lista->ultimo = lista->ultimo->proximo;
    }

    free(primero);
    lista->largo--;
    return dato;
}

void* lista_ver_primero(const lista_t* lista) {
    return (lista_esta_vacia(lista) ? NULL : lista->primero->dato);
}

void* lista_ver_ultimo(const lista_t* lista) {
    return (lista_esta_vacia(lista) ? NULL : lista->ultimo->dato);
}

size_t lista_largo(const lista_t* lista) {
    return lista->largo;
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)) {
    while (!lista_esta_vacia(lista)) {
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato != NULL) {
            destruir_dato(dato);
        }
    }
    free(lista);
}

/*
iterador interno
*/
void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra) {
    nodo_t* actual = lista->primero;
    while (actual) {
        if (!visitar(actual->dato, extra)) return;
        actual = actual->proximo;
    }
}

/*
iterador externo
*/

struct lista_iter {
    nodo_t* actual;
    nodo_t* anterior;
    lista_t* lista;
};

lista_iter_t* lista_iter_crear(lista_t* lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;

    iter->lista = lista;
    iter->actual = lista->primero;
    iter->anterior = lista->primero;
    return iter;
}

void* lista_iter_ver_actual(const lista_iter_t* iter) {
    return (lista_iter_al_final(iter) ? NULL : iter->actual->dato);
}

bool lista_iter_al_final(const lista_iter_t* iter) {
    return (iter->actual ? false : true);
}

void lista_iter_destruir(lista_iter_t* iter) {
    free(iter);
}

void* lista_iter_borrar(lista_iter_t* iter) {
    if (lista_iter_al_final(iter)) return NULL;

    nodo_t* auxiliar = iter->actual;
    void* dato = auxiliar->dato;

    iter->actual = iter->actual->proximo;
    iter->lista->largo--;
    if (auxiliar == iter->anterior) {
        iter->anterior = iter->actual;
        iter->lista->primero = iter->actual;
    } else {
        iter->anterior->proximo = iter->actual;
    }
    if (iter->actual == NULL) {
        iter->lista->ultimo = iter->anterior;
    }
    free(auxiliar);
    return dato;
}

bool lista_iter_avanzar(lista_iter_t* iter) {
    if (lista_iter_al_final(iter)) return false;

    if (iter->anterior != iter->actual) {
        iter->anterior = iter->anterior->proximo;
    }
    iter->actual = iter->actual->proximo;

    return true;
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato) {
    if (iter->actual == iter->anterior) {
        if (!lista_insertar_primero(iter->lista, dato)) return false;
        iter->actual = iter->lista->primero;
        iter->anterior = iter->lista->primero;
        return true;
    }

    nodo_t* auxiliar = nodo_crear(dato);
    if (!auxiliar) return false;

    auxiliar->proximo = iter->actual;
    iter->anterior->proximo = auxiliar;
    iter->actual = auxiliar;
    iter->lista->largo++;

    if (iter->anterior == auxiliar->proximo) {
        iter->anterior = auxiliar;
        iter->lista->primero = auxiliar;
    }

    if (!auxiliar->proximo) {
        iter->lista->ultimo = auxiliar;
    }
    return true;
}