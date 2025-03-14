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
    printf(" Prueba de funciones\n")

    // Insertar valores de prueba
    printf("\nInsertando claves...\n");

    struct Coord coord1 = {2, 3};
    double vec1[3] = {5.2, 3.5, 7.4};
    
    if (set_value(5, "Ejemplo2", 3, vec1, coord1) == 0) {
        printf("Clave 5 insertada correctamente.\n");
    } else {
        printf(" Error al insertar la clave 5.\n");
    }

    // Comprobar si existe una clave que creó otro cliente
    printf("\nVerificando si la clave 42 existe...\n");
    if (exist(42) == 1) {
        printf("La clave 42 existe en la base de datos.\n");
    } else {
        printf("La clave 42 no fue encontrada.\n");
    }


    // Obtener valores almacenados de una clave creada por otro usuario
    printf("\nObteniendo valores de la clave 41...\n");
    char value1[256];
    int N_value2;
    double V_value2[32];
    struct Coord value3;
    ResponseMessage resultado;

    if ((resultado = get_value(41, value1, &N_value2, V_value2, &value3)) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("    value1: %s\n", resultado.value1);
        printf("    N_value2: %d\n", resultado.N_value2);
        printf("    V_value2: ");
        print_vector(resultado.V_value2, resultado.N_value2);
        printf("    value3: (%d, %d)\n", resultado.value3.x, resultado.value3.y);
    } else {
        printf("Error al obtener la clave 41.\n");
    }
    
    // Modificar valores de la clave de otro usuario
    printf("\nModificando la clave 41...\n");
    struct Coord coord2 = {3, 4};
    double vec2[2] = {99.9, 88.8};

    if (modify_value(41, "ModificaciónExterna", 2, vec2, coord2) == 0) {
        printf(" Clave 41 modificada correctamente.\n");
    } else {
        printf("Error al modificar la clave 41.\n");
    }

    // Obtener los valores modificados
    printf("\n Obteniendo valores modificados de la clave 41...\n");
    if (resultado=get_value(41, value1, &N_value2, V_value2, &value3) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("   🔹 value1: %s\n", resultado.value1);
        printf("   🔹 N_value2: %d\n", resultado.N_value2);
        printf("   🔹 V_value2: ");
        print_vector(resultado.V_value2, resultado.N_value2);
        printf("   🔹 value3: (%d, %d)\n", resultado.value3.x, resultado.value3.y);
    } else {
        printf(" Error al obtener la clave 41.\n");
    }

    // Eliminar la clave creada por otro cliente
    printf("\nEliminando la clave 41...\n");
    if (delete_key(42) == 0) {
        printf("Clave 42 eliminada correctamente.\n");
    } else {
        printf("Error al eliminar la clave 41.\n");
    }

    // Verificar si la clave sigue existiendo
    printf("\n🔍 Verificando si la clave 41 aún existe...\n");
    if (exist(42) == 1) {
        printf("La clave 41 aún existe (error).\n");
    } else {
        printf("La clave 41 ha sido eliminada correctamente.\n");
    }

    printf("\n Pruebas finalizadas.\n");
    return 0;
}