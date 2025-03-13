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

    // Eliminar todos los valores previos
    printf("\nEliminando datos previos...\n");
    if (destroy() == 0) {
        printf("Todos los valores fueron eliminados.\n");
    } else {
        printf("Error al eliminar.\n");
    }

    // Insertar valores de prueba
    printf("\nInsertando claves...\n");
    struct Coord coord1 = {1, 2};
    double vec1[3] = {10.5, 20.5, 30.5};

    if (set_value(42, "Ejemplo1", 3, vec1, coord1) == 0) {
        printf("Clave 42 insertada correctamente.\n");
    } else {
        printf(" Error al insertar la clave 42.\n");
    }

    // Comprobar si existe la clave
    printf("\nVerificando si la clave 42 existe...\n");
    if (exist(42) == 1) {
        printf("La clave 42 existe en la base de datos.\n");
    } else {
        printf("La clave 42 no fue encontrada.\n");
    }

    // Obtener valores almacenados
    printf("\nObteniendo valores de la clave 42...\n");
    char value1[256];
    int N_value2;
    double V_value2[32];
    struct Coord value3;
    int resultado;

    if ((resultado = get_value(42, value1, &N_value2, V_value2, &value3)) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("    value1: %s\n", value1);
        printf("    N_value2: %d\n", N_value2);
        printf("    V_value2: ");
        print_vector(V_value2, N_value2);
        printf("    value3: (%d, %d)\n", value3.x, value3.y);
    } else {
        printf("Error al obtener la clave 42.\n");
    }
    
    // Modificar valores de la clave
    printf("\nModificando la clave 42...\n");
    struct Coord coord2 = {3, 4};
    double vec2[2] = {99.9, 88.8};

    if (modify_value(42, "EjemploModificado", 2, vec2, coord2) == 0) {
        printf(" Clave 42 modificada correctamente.\n");
    } else {
        printf("Error al modificar la clave 42.\n");
    }

    // Obtener los valores modificados
    printf("\n Obteniendo valores modificados de la clave 42...\n");
    if (get_value(42, value1, &N_value2, V_value2, &value3) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("   🔹 value1: %s\n", value1);
        printf("   🔹 N_value2: %d\n", N_value2);
        printf("   🔹 V_value2: ");
        print_vector(V_value2, N_value2);
        printf("   🔹 value3: (%d, %d)\n", value3.x, value3.y);
    } else {
        printf(" Error al obtener la clave 42.\n");
    }

    // Eliminar la clave
    printf("\nEliminando la clave 42...\n");
    if (delete_key(42) == 0) {
        printf("Clave 42 eliminada correctamente.\n");
    } else {
        printf("Error al eliminar la clave 42.\n");
    }

    // Verificar si la clave sigue existiendo
    printf("\n🔍 Verificando si la clave 42 aún existe...\n");
    if (exist(42) == 1) {
        printf("La clave 42 aún existe (error).\n");
    } else {
        printf("La clave 42 ha sido eliminada correctamente.\n");
    }

    printf("\n Pruebas finalizadas.\n");
    return 0;
}




