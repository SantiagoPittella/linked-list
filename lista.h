#include <stdbool.h>
#include <stddef.h>

typedef struct lista lista_t;

/*
*************************************************************
*                   PRIMITIVAS DE LA LISTA                  *
*************************************************************
*/

/*
Crea una lista.
Post: La lista fue creada.
*/
lista_t *lista_crear(void);
/*
Indica si la lista esta vacia.
Pre: la lista fue creada.
Post: devuelve true si la lista no tiene ningun elemento, false en caso contrario.
*/
bool lista_esta_vacia(const lista_t *lista);
/*
Inserta un elemento al comienzo de la lista.
Pre: La lista fue creada.
Post: se inserto un elemento en a primer posicion de la lista y devuelve true. 
En caso de algun error al realizar la operacion devuelve false y no inserta
nada.
*/
bool lista_insertar_primero(lista_t *lista, void *dato);
/*
Inserta un elemento al final de la lista.
Pre: la lista fue creada.
Post: se inserto un elemento en la ultima posicion de la lista y devuelve true.
En caso de algun error al realizar la operacion devuelve false y no inserta nada.
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);
/*
Borra el primer elemento de la lista
Pre: la lista fue creada.
Post: Elimina el primer elemento de la lista y lo devuelve. En caso de que
la lista esta vacia devuelve NULL.
*/
void *lista_borrar_primero(lista_t *lista);
/*
Da el primer elemento de la lista, dejandola sin cambios.
Pre: la lista fue creada.
Post: Devuelve el primer elemento. Si la lista esta vacia devuelve NULL.
*/
void *lista_ver_primero(const lista_t *lista);
/*
Da el ultimo elemento de la lista, dejandola sin cambios
Pre: la lista fue creada.
Post: Devuelve el ultimo elemento de la lista. Si la lista esta vacia
devuelve NULL.
*/
void *lista_ver_ultimo(const lista_t *lista);
/*
Indica el largo de la lista.
Pre: la lista fue creada.
Post: Devuelve el largo de la lista.
*/
size_t lista_largo(const lista_t *lista);
/*
Destruye la lista, aceptando una funcion para destruir los datos.
Pre: la lista fue creada. Si como parametro para destruir los datos se pasa
NULL estos quedaran como estaban.
Post: La lista fue destruida.
*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/*
*******************************************************************
*                    PRIMITIVA ITERADOR INTERNO                   *
*******************************************************************
*/

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/*
******************************************************************
*                    PRIMITIVAS ITERADOR EXTERNO                 *
******************************************************************
*/
typedef struct lista_iter lista_iter_t;

/*
Pre: La lista fue creada.
Post: Devuelve un iterador de la lista en el primer elemento de la misma. 
En caso de algun error al crearla, devuelve NULL.
*/
lista_iter_t *lista_iter_crear(lista_t *lista);

/*
Pre: El iterador fue creado.
Post: Avanza el iterador al siguiente elemento y devuelve true.
En caso de no poder avanzar devuelve false.
*/
bool lista_iter_avanzar(lista_iter_t *iter);
/*
Pre: el iterador fue creado.
Post: Devuelve el elemento en el que esta situado el iterador.
Si este se encuentra al final, devuelve NULL.
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);
/*
Pre: El iterador fue creado.
Post: Devuelve true si el iterador se encuentra al final de la listam
false en caso contrario.
*/
bool lista_iter_al_final(const lista_iter_t *iter);
/*
Pre: el iterador fue creado.
Post: destruye el iterador.
*/
void lista_iter_destruir(lista_iter_t *iter);
/*
Pre: el iterador fue creado.
Post: Inserta un elemento en la posicion en la que se encontraba el iterador.
Devuelve true si la operacion se efectuo correctamente, false en caso de error.
*/
bool lista_iter_insertar(lista_iter_t *iter, void *dato);
/*
Pre: El iterador fue creado.
Post: Destruye el elemento en el que se encuentra el iterador y lo devuelve.
Devuelve NULL en caso de que la lista este vacia o el iterador se encuentre al final.
*/
void *lista_iter_borrar(lista_iter_t *iter);