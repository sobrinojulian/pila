#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>


static void prueba_pila_vacia(void) {
    pila_t* pila = pila_crear();

    print_test("La pila esta vacia", pila_esta_vacia(pila) == true);

    pila_destruir(pila);
}

static void prueba_pila_apilar_vacia(void) {
    pila_t* pila = pila_crear();
    int elem = 5;
    pila_apilar(pila, &elem);

    print_test("Se apilo un elemento en una pila vacia", pila_esta_vacia(pila) == false);

    pila_destruir(pila);
}

static void prueba_pila_desapilar_vacia(void) {
    pila_t* pila = pila_crear();

    print_test("No se puede desapilar una pila vacia", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
}

static void prueba_destruir_pila(void) {
    pila_t* pila = pila_crear();
    char elem = 'a';
    pila_apilar(pila, &elem);
    void* tope_anterior = pila_ver_tope(pila);
    pila_destruir(pila);
    print_test("Se destruyo la pila", &elem == tope_anterior);
    // Se libero la memoria utilizada en la prueba
}

static void prueba_apilo_y_desapilo_elemento(void) {
    pila_t* pila = pila_crear();
    int elem = 3;
    pila_apilar(pila, &elem);
    void* desapilado = pila_desapilar(pila);
    print_test("Se apilo un elemento, y se desapilo correctamente", (desapilado == &elem) && pila_ver_tope(pila) == NULL);
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
}

static void prueba_apilar_muchos_elementos(void) {
    pila_t* pila = pila_crear();
    int* int_arr = malloc(sizeof(int) * 1000);
    int tope_correcto = 1;
    for (int i = 0; i < 1000; i++) {
        int_arr[i] = i;
        pila_apilar(pila, &(int_arr[i]));
        if (pila_ver_tope(pila) != &(int_arr[i])) {
            tope_correcto = 0;
        }
    }
    int elem_2 = 1000;
    pila_apilar(pila, &elem_2);
    print_test("Se apilaron mas de 1000 elementos", tope_correcto && (pila_ver_tope(pila) == &elem_2) && (pila_desapilar(pila) == &elem_2) && (pila_desapilar(pila) == &int_arr[999]));
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
    free(int_arr);
}

static void prueba_apilar_null(void) {
    pila_t* pila = pila_crear();
    pila_apilar(pila, NULL);
    print_test("Se apilo NULL correctamente", pila_ver_tope(pila) == NULL);
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
}

static void prueba_desapilar_hasta_vaciar(void) {
    pila_t* pila = pila_crear();
    int* int_arr = malloc(sizeof(int) * 10);
    int tope_correcto = 1;
    for (int i = 0; i < 10; i++) {
        int_arr[i] = i;
        pila_apilar(pila, &(int_arr[i]));
        if (pila_ver_tope(pila) != &(int_arr[i])) {
            tope_correcto = 0;
        }
    }
    while(!pila_esta_vacia(pila)) {
        void* anterior_tope = pila_ver_tope(pila);
        void* desapilado = pila_desapilar(pila);
        if (anterior_tope != desapilado) {
            tope_correcto = 0;
        }
    }

    print_test("Se apilaron varios elementos y se desapilaron correctamente", tope_correcto && (pila_ver_tope(pila) == NULL));
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
    free(int_arr);
}

static void prueba_ver_tope_pila_vacia(void) {
    pila_t* pila = pila_crear();
    print_test("Ver tope de una pila vacia", pila_ver_tope(pila) == NULL);
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);

}

static void prueba_esta_vacia_pila(void) {
    pila_t* pila = pila_crear();
    print_test("La pila vacia esta vacia", pila_esta_vacia(pila));
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
}

static void prueba_ver_tope_pila_desapilada(void) {
    pila_t* pila = pila_crear();
    int tope_correcto = 1;
    int elem_1 = 1;
    char elem_2 = 'a';
    void *elem_3;

    pila_apilar(pila, &elem_1);
    pila_apilar(pila, &elem_2);
    pila_apilar(pila, &elem_3);
    while(!pila_esta_vacia(pila)) {
        void* anterior_tope = pila_ver_tope(pila);
        void* desapilado = pila_desapilar(pila);
        if (anterior_tope != desapilado) {
            tope_correcto = 0;
        }
    }

    print_test("El tope de una pila desapilada es nulo", tope_correcto && (pila_ver_tope(pila) == NULL));
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
}

static void prueba_desapilar_pila_desapilada(void) {
    pila_t* pila = pila_crear();
    int elem_1 = 1;
    char elem_2 = 'a';
    void *elem_3;

    pila_apilar(pila, &elem_1);
    pila_apilar(pila, &elem_2);
    pila_apilar(pila, &elem_3);

    void *desapilado_3 = pila_desapilar(pila);
    void *desapilado_2 = pila_desapilar(pila);
    void *desapilado_1 = pila_desapilar(pila);

    print_test("Desapilar una pila desapilada es nulo", ((desapilado_1 == &elem_1) && (desapilado_2 == &elem_2) && (desapilado_3 == &elem_3) && (pila_desapilar(pila) == NULL)));
    // Libero la memoria utilizada en la prueba
    pila_destruir(pila);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_pila_apilar_vacia();
    prueba_pila_desapilar_vacia();
    prueba_destruir_pila();
    prueba_apilo_y_desapilo_elemento();
    prueba_apilar_muchos_elementos();
    prueba_apilar_null();
    prueba_desapilar_hasta_vaciar();
    prueba_ver_tope_pila_vacia();
    prueba_esta_vacia_pila();
    prueba_ver_tope_pila_desapilada();
    prueba_desapilar_pila_desapilada();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
