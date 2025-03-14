#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "claves.h"


// Función para imprimir un vector de doubles
void print_vector(double *vector, int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%.2f ", vector[i]);
    }
    printf("]\n");
}

int main() {
    printf(" Prueba de funciones\n");

    //Esto debería dar un error, al estar ya subida por el otro cliente
    struct Coord coord1 = {4, 7};
    double vec1[3] = {25.2, 35.5, 37.4};

    if (set_value(43, "Ejemplo1", 3, vec1, coord1) == 0) {
        printf("Clave 42 insertada correctamente.\n");
    } else {
        printf(" Error al insertar la clave 42.\n");
    }

    // Esto debería devolver error ya que la clave 30 no existe
    printf("\nVerificando si la clave 30 existe...\n");
    if (exist(30) == 1) {
        printf("La clave 30 existe en la base de datos.\n");
    } else {
        printf("La clave 30 no fue encontrada.\n");
    }

    // Buscamos una clave que no existe
    printf("\nObteniendo valores de la clave 50...\n");
    char value1[256];
    int N_value2;
    double V_value2[32];
    struct Coord value3;
    ResponseMessage resultado;

    if ((resultado = get_value(50, value1, &N_value2, V_value2, &value3)) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("    value1: %s\n", resultado.value1);
        printf("    N_value2: %d\n", resultado.N_value2);
        printf("    V_value2: ");
        print_vector(resultado.V_value2, resultado.N_value2);
        printf("    value3: (%d, %d)\n", resultado.value3.x, resultado.value3.y);
    } else {
        printf("Error al obtener la clave 50.\n");
    }
    
    // Modificar una clave no existente
    printf("\nModificando la clave 50...\n");
    struct Coord coord2 = {3, 4};
    double vec2[2] = {99.9, 88.8};

    if (modify_value(41, "ModificaciónExterna", 2, vec2, coord2) == 0) {
        printf(" Clave 50 modificada correctamente.\n");
    } else {
        printf("Error al modificar la clave 50.\n");
    }

    // Eliminamos clave no existente
    printf("\nEliminando la clave 50...\n");
    if (delete_key(42) == 0) {
        printf("Clave 50 eliminada correctamente.\n");
    } else {
        printf("Error al eliminar la clave 50.\n");
    }

    printf("\n Pruebas finalizadas.\n");
    return 0;
}