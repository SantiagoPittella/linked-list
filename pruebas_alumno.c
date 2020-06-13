#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "testing.h"

#define ELEMENTOS_PRUEBA_VOLUMEN 1000

void pruebas_vacia() {
    printf("\n~~~~~ PRUEBAS LISTA VACIA ~~~~~\n\n");
    lista_t* lista = lista_crear();

    print_test("Lista creada", lista != NULL);
    print_test("Esta vacia", lista_esta_vacia(lista));
    print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Largo es 0", lista_largo(lista) == 0);

    lista_destruir(lista, free);
}

void pruebas_un_elemento() {
    printf("\n~~~~~ PRUEBAS UN ELEMENTO ~~~~~\n\n");
    lista_t* lista = lista_crear();

    int* elemento = malloc(sizeof(int));
    printf("\n Insertando primero\n\n");
    print_test("Insertar primero", lista_insertar_primero(lista, elemento));
    print_test("Largo es 1", lista_largo(lista) == 1);
    print_test("Ver primero es elemento", lista_ver_primero(lista) == elemento);
    print_test("Ver ultimo es elemento", lista_ver_ultimo(lista) == elemento);
    print_test("Esta vacia es false", !lista_esta_vacia(lista));
    print_test("Borrar primero devuelve correctamente", lista_borrar_primero(lista) == elemento);
    print_test("Largo es 0", lista_largo(lista) == 0);
    print_test("Esta vacia", lista_esta_vacia(lista));
    print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Borrar primero es NULL", lista_borrar_primero(lista) == NULL);

    printf("\n Insertando ultimo\n\n");
    print_test("Insertar ultimo", lista_insertar_ultimo(lista, elemento));
    print_test("Largo es 1", lista_largo(lista) == 1);
    print_test("Ver primero es elemento", lista_ver_primero(lista) == elemento);
    print_test("Ver ultimo es elemento", lista_ver_ultimo(lista) == elemento);
    print_test("Esta vacia es false", !lista_esta_vacia(lista));
    print_test("Borrar primero devuelve correctamente", lista_borrar_primero(lista) == elemento);
    print_test("Largo es 0", lista_largo(lista) == 0);
    print_test("Esta vacia", lista_esta_vacia(lista));
    print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Borrar primero es NULL", lista_borrar_primero(lista) == NULL);

    free(elemento);
    lista_destruir(lista, free);
}

void pruebas_elemento_NULL() {
    printf("\n~~~~~ PRUEBAS ELEMENTO NULL ~~~~~\n\n");
    lista_t* lista = lista_crear();

    char* elemento_null = NULL;
    print_test("Insertar NULL", lista_insertar_primero(lista, elemento_null));
    print_test("Largo es 1", lista_largo(lista) == 1);
    print_test("Ver primero es NULL", lista_ver_primero(lista) == elemento_null);
    print_test("Ver ultimo es NULL", lista_ver_ultimo(lista) == elemento_null);
    print_test("Esta vacia es false", !lista_esta_vacia(lista));
    print_test("Borrar primero devuelve correctamente", lista_borrar_primero(lista) == elemento_null);
    print_test("Largo es 0", lista_largo(lista) == 0);
    print_test("Esta vacia", lista_esta_vacia(lista));
    print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Ver ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("Borrar primero es NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, free);
}

void crear_n_elementos(int** elementos, int n) {
    for (int i = 0; i < n; i++) {
        elementos[i] = malloc(sizeof(int));
        *elementos[i] = i;
    }
}

bool agregar_n_primeros(lista_t* lista, int** elementos, int tam) {
    for (int i = 0; i < tam; i++) {
        if (!lista_insertar_primero(lista, elementos[i])) return false;
    }
    return true;
}

bool borrar_n_primeros(lista_t* lista, int** elementos, int tam) {
    for (int i = 0; i < tam; i++) {
        if (lista_borrar_primero(lista) != elementos[tam - 1 - i]) return false;
    }
    return true;
}

bool agregar_n_ultimos(lista_t* lista, int** elementos, int tam) {
    for (int i = 0; i < tam; i++) {
        if (!lista_insertar_ultimo(lista, elementos[i])) return false;
    }
    return true;
}

bool borrar_n_ultimos(lista_t* lista, int** elementos, int tam, int inicio) {
    for (int i = inicio; i < tam; i++) {
        if (lista_borrar_primero(lista) != elementos[i]) return false;
    }
    return true;
}
void pruebas_tres_elementos() {
    printf("\n~~~~~ PRUEBAS TRES ELEMENTO ~~~~~\n\n");
    lista_t* lista = lista_crear();

    int** elementos = malloc(3 * sizeof(int*));
    crear_n_elementos(elementos, 3);

    printf("\nInsertando primero\n\n");
    print_test("Agregar todos los elementos usando agregar primero", agregar_n_primeros(lista, elementos, 3));
    print_test("Largo es 3", lista_largo(lista) == 3);
    print_test("No esta vacia", !lista_esta_vacia(lista));
    print_test("Ver primero es el tercer elemento", lista_ver_primero(lista) == elementos[2]);
    print_test("Ver ultimo es primer elemento", lista_ver_ultimo(lista) == elementos[0]);
    print_test("Borra primer elemento", lista_borrar_primero(lista) == elementos[2]);
    print_test("Ver primero ahora es el segundo elemento", lista_ver_primero(lista) == elementos[1]);
    print_test("Largo es 2", lista_largo(lista) == 2);
    print_test("Borro demas elementos", borrar_n_primeros(lista, elementos, 2));
    print_test("Largo es 0", lista_largo(lista) == 0);
    print_test("Esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);

    lista_t* lista2 = lista_crear();
    printf("\nInsertando ultimo\n\n");
    print_test("Agregar todos los elementos insertando ultimo", agregar_n_ultimos(lista2, elementos, 3));
    print_test("Largo es 3", lista_largo(lista2) == 3);
    print_test("No esta vacia", !lista_esta_vacia(lista2));
    print_test("Ver primero es el primer elemento", lista_ver_primero(lista2) == elementos[0]);
    print_test("Ver ultimo es tercer elemento", lista_ver_ultimo(lista2) == elementos[2]);
    print_test("Borra primer elemento", lista_borrar_primero(lista2) == elementos[0]);
    print_test("Ver primero ahora es el segundo elemento", lista_ver_primero(lista2) == elementos[1]);
    print_test("Largo es 2", lista_largo(lista2) == 2);
    print_test("Borro demas elementos", borrar_n_ultimos(lista2, elementos, 3, 1));
    print_test("Largo es 0", lista_largo(lista2) == 0);
    print_test("Esta vacia", lista_esta_vacia(lista2));

    lista_destruir(lista2, free);
    for (int i = 0; i < 3; i++) {
        free(elementos[i]);
    }

    free(elementos);
}
void pruebas_volumen() {
    printf("\n~~~~~ PRUEBAS VOLUMEN ~~~~~\n\n");

    lista_t* lista = lista_crear();
    int** elementos = malloc(ELEMENTOS_PRUEBA_VOLUMEN * sizeof(int*));
    crear_n_elementos(elementos, ELEMENTOS_PRUEBA_VOLUMEN);

    printf("\nInsertando primero\n\n");
    print_test("Insertar muchos elementos", agregar_n_primeros(lista, elementos, ELEMENTOS_PRUEBA_VOLUMEN));
    print_test("El largo es correcto", lista_largo(lista) == ELEMENTOS_PRUEBA_VOLUMEN);
    print_test("No esta vacia", !lista_esta_vacia(lista));
    print_test("Ver primero es correcto", lista_ver_primero(lista) == elementos[ELEMENTOS_PRUEBA_VOLUMEN - 1]);
    print_test("Ver ultimo es correcto", lista_ver_ultimo(lista) == elementos[0]);
    print_test("Borrar todos los elementos", borrar_n_primeros(lista, elementos, ELEMENTOS_PRUEBA_VOLUMEN));
    print_test("Esta vacia", lista_esta_vacia(lista));
    print_test("Largo es 0", lista_largo(lista) == 0);

    lista_destruir(lista, free);

    lista_t* lista2 = lista_crear();

    printf("\nInsertando ultimo\n\n");
    print_test("Insertar muchos elementos", agregar_n_ultimos(lista2, elementos, ELEMENTOS_PRUEBA_VOLUMEN));
    print_test("El largo es correcto", lista_largo(lista2) == ELEMENTOS_PRUEBA_VOLUMEN);
    print_test("No esta vacia", !lista_esta_vacia(lista2));
    print_test("Ver primero es correcto", lista_ver_primero(lista2) == elementos[0]);
    print_test("Ver ultimo es correcto", lista_ver_ultimo(lista2) == elementos[ELEMENTOS_PRUEBA_VOLUMEN - 1]);
    print_test("Borrar todos los elementos", borrar_n_ultimos(lista2, elementos, ELEMENTOS_PRUEBA_VOLUMEN, 0));
    print_test("Esta vacia", lista_esta_vacia(lista2));
    print_test("Largo es 0", lista_largo(lista2) == 0);

    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) {
        free(elementos[i]);
    }

    lista_destruir(lista2, free);
    free(elementos);
}

bool agregar_n_listas(lista_t* lista, size_t cantidad) {
    for (size_t i = 0; i < cantidad; i++) {
        lista_t* auxiliar = lista_crear();
        if (!auxiliar) return false;
        if (!lista_insertar_ultimo(lista, auxiliar)) return false;
    }
    return true;
}

void _destruccion(void* lista) {
    lista_destruir(lista, free);
}
void pruebas_destruccion() {
    lista_t* lista = lista_crear();

    print_test("La lista fue creada y le agregamos elementos", agregar_n_listas(lista, ELEMENTOS_PRUEBA_VOLUMEN));
    printf("Destruir pasandole funcion que agrega a otra lista");
    lista_destruir(lista, _destruccion);
}

void pruebas_iter_vacia() {
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);

    printf("\nIterador de lista vacia:\n");
    print_test("El iterador fue creado", iter != NULL);
    print_test("Avanzar es false", !lista_iter_avanzar(iter));
    print_test("Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("El iterador esta al final", lista_iter_al_final(iter));
    print_test("Borrar es NULL", lista_iter_borrar(iter) == NULL);
    lista_iter_destruir(iter);
    lista_destruir(lista, free);
}

void pruebas_iter_un_elemento() {
    lista_t* lista = lista_crear();
    char* elemento = malloc(sizeof(char));
    *elemento = 'a';
    lista_iter_t* iter = lista_iter_crear(lista);

    printf("\nIterador un elemento:\n");
    print_test("Insertar con iterador", lista_iter_insertar(iter, elemento));
    print_test("Al final es false", !lista_iter_al_final(iter));
    print_test("Ver actual es el elemento que inserte", lista_iter_ver_actual(iter) == elemento);
    print_test("Largo de la lista es 1", lista_largo(lista) == 1);
    print_test("Borrar el elemento", lista_iter_borrar(iter) == elemento);
    print_test("Al final es true", lista_iter_al_final(iter));
    print_test("Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Largo ahora es 0", lista_largo(lista) == 0);

    lista_iter_destruir(iter);
    free(elemento);
    lista_destruir(lista, free);
}

void pruebas_iter_tres_elementos() {
    lista_t* lista = lista_crear();
    lista_iter_t* iter = lista_iter_crear(lista);

    char* elemento1 = malloc(sizeof(char));
    int* elemento2 = malloc(sizeof(int));
    double* elemento3 = malloc(sizeof(double));
    *elemento1 = 'A';

    printf("\nIterador con 3 elementos, sin avanzar [elem3, elem2, elem1]\n");
    print_test("Insertar primer elemento", lista_iter_insertar(iter, elemento1));
    print_test("Insertar segundo elemento", lista_iter_insertar(iter, elemento2));
    print_test("Insertar tercer elemento", lista_iter_insertar(iter, elemento3));
    print_test("Ver actual es tercer elemento", lista_iter_ver_actual(iter) == elemento3);
    print_test("lista_ver_primero es igual a ver actual", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
    print_test("Borrar saca tercer elemento", lista_iter_borrar(iter) == elemento3);
    print_test("Ver actual es segundo elemento", lista_iter_ver_actual(iter) == elemento2);

    print_test("lista_ver_primero es igual a ver actual", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
    print_test("Borrar saca segundo elemento", lista_iter_borrar(iter) == elemento2);
    print_test("Ver actual es primer elemento", lista_iter_ver_actual(iter) == elemento1);

    print_test("lista_ver_primero es igual a ver actual", lista_ver_primero(lista) == lista_iter_ver_actual(iter));
    print_test("Borrar saca primer elemento", lista_iter_borrar(iter) == elemento1);
    print_test("Iter al final", lista_iter_al_final(iter));
    lista_iter_destruir(iter);
    lista_destruir(lista, free);

    printf("\nIterador con 3 elementos, avanzando [elem1, elem2, elem3]\n");
    lista_t* lista2 = lista_crear();
    lista_iter_t* iter2 = lista_iter_crear(lista2);

    print_test("Insertar primer elemento", lista_iter_insertar(iter2, elemento1));
    print_test("Avanzar", lista_iter_avanzar(iter2));
    print_test("Insertar segundo elemento", lista_iter_insertar(iter2, elemento2));
    print_test("Avanzar", lista_iter_avanzar(iter2));
    print_test("Insertar tercer elemento", lista_iter_insertar(iter2, elemento3));
    print_test("Ver actual es tercer elemento", lista_iter_ver_actual(iter2) == elemento3);
    print_test("Avanzar", lista_iter_avanzar(iter2));
    print_test("Iter al final", lista_iter_al_final(iter2));
    print_test("Borrar es null", lista_iter_borrar(iter2) == NULL);
    print_test("largo = 3", lista_largo(lista2) == 3);

    lista_iter_destruir(iter2);
    lista_destruir(lista2, free);
}

bool inserta_compara_volumen(lista_iter_t* iter, int** elementos) {
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) {
        if (!lista_iter_insertar(iter, elementos[i])) return false;
        if (lista_iter_ver_actual(iter) != elementos[i]) return false;
    }
    return true;
}

bool borrar_volumen_con_iter(lista_iter_t* iter, int** elementos) {
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) {
        if (lista_iter_borrar(iter) != elementos[ELEMENTOS_PRUEBA_VOLUMEN - i - 1]) return false;
    }
    return true;
}

bool insertar_avanzar_volumen(lista_iter_t* iter, int** elementos) {
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) {
        if (!lista_iter_insertar(iter, elementos[i])) return false;
        if (!lista_iter_avanzar(iter)) return false;
        if (lista_iter_ver_actual(iter) != NULL) return false;
    }
    return true;
}
bool borrar_volumen_con_iter_avanzando(lista_iter_t* iter, int** elementos) {
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) {
        if (lista_iter_borrar(iter) != elementos[i]) return false;
    }
    return true;
}
void pruebas_iter_volumen() {
    printf("\nPruebas de volumen con iterador:\n\n");

    lista_t* lista = lista_crear();
    int** elementos = malloc(ELEMENTOS_PRUEBA_VOLUMEN * sizeof(int*));
    crear_n_elementos(elementos, ELEMENTOS_PRUEBA_VOLUMEN);
    lista_iter_t* iter = lista_iter_crear(lista);

    printf("Insertando sin avanzar:\n");
    print_test("Insertar elementos, mientras se comparan con ver actual", inserta_compara_volumen(iter, elementos));
    print_test("Borrar todos los elementos", borrar_volumen_con_iter(iter, elementos));
    print_test("Iter al final", lista_iter_al_final(iter));

    lista_iter_destruir(iter);
    lista_destruir(lista, NULL);

    printf("\nInsertando y avanzando:\n");
    lista_t* lista2 = lista_crear();
    lista_iter_t* iter2 = lista_iter_crear(lista2);

    print_test("Inserta, avanza y compara (siempre NULL)", insertar_avanzar_volumen(iter2, elementos));
    lista_iter_destruir(iter2);
    lista_iter_t* iter3 = lista_iter_crear(lista2);
    print_test("Borro iterador, creo nuevo y borro todos los elementos con el nuevo", borrar_volumen_con_iter_avanzando(iter3, elementos));

    lista_iter_destruir(iter3);
    lista_destruir(lista2, free);
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) free(elementos[i]);
    free(elementos);
}

bool iter_interno_insertar(void* dato, void* lista) {
    return lista_insertar_ultimo(lista, dato);
}
bool pasar_listas_iter_interno(lista_t* lista, lista_t* lista_aux, int** elementos) {
    lista_iterar(lista, iter_interno_insertar, lista_aux);
    return true;
}

bool comparar_listas(lista_t* lista, lista_t* lista_aux) {
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) {
        if (lista_borrar_primero(lista) != lista_borrar_primero(lista_aux)) return false;
    }
    return true;
}

bool _visitar(void* dato, void* extra) {
    if (*(int*)dato == ELEMENTOS_PRUEBA_VOLUMEN / 2) {
        printf("El iterador interno llego a lista_largo / 2, y devolvio false\n");
        return false;
    };
    return true;
}
void pruebas_iter_interno() {
    lista_t* lista = lista_crear();
    int** elementos = malloc(ELEMENTOS_PRUEBA_VOLUMEN * sizeof(int*));
    crear_n_elementos(elementos, ELEMENTOS_PRUEBA_VOLUMEN);
    print_test("Inserto elementos en una lista", agregar_n_ultimos(lista, elementos, ELEMENTOS_PRUEBA_VOLUMEN));
    lista_t* lista_aux = lista_crear();
    print_test("Uso el iterador interno para pasar todos los elementos a otra lista", pasar_listas_iter_interno(lista, lista_aux, elementos));
    print_test("Comparo ambas lista y borro", comparar_listas(lista, lista_aux));

    lista_destruir(lista, free);
    lista_destruir(lista_aux, free);
    for (int i = 0; i < ELEMENTOS_PRUEBA_VOLUMEN; i++) free(elementos[i]);
    free(elementos);

    //cuando la iter llegue a elementos/2 , devuelve false
    lista_t* lista2 = lista_crear();
    int** elementos2 = malloc(ELEMENTOS_PRUEBA_VOLUMEN * sizeof(int*));
    crear_n_elementos(elementos2, ELEMENTOS_PRUEBA_VOLUMEN);
    print_test("Inserto elementos en una lista", agregar_n_ultimos(lista2, elementos2, ELEMENTOS_PRUEBA_VOLUMEN));
    lista_iterar(lista2, _visitar, NULL);
    lista_destruir(lista2, free);
    free(elementos2);
}

void pruebas_lista_alumno() {
    pruebas_vacia();
    pruebas_un_elemento();
    pruebas_elemento_NULL();
    pruebas_tres_elementos();
    pruebas_volumen();
    pruebas_destruccion();
    printf("\n~~~~~ PRUEBAS ITERADOR EXTERNO ~~~~~\n\n");
    pruebas_iter_vacia();
    pruebas_iter_un_elemento();
    pruebas_iter_tres_elementos();
    pruebas_iter_volumen();

    printf("\n~~~~~ PRUEBAS ITERADOR INTERNO ~~~~~\n\n");
    pruebas_iter_interno();
}