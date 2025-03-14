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

    // Insertar valores de prueba, se insertan dos para probar si se logra iterar a través de las tuplas
    printf("\nInsertando claves...\n");

    struct Coord coord1 = {2, 3};
    double vec1[3] = {5.2, 3.5, 7.4};
    
    if (set_value(43, "Ejemplo1", 3, vec1, coord1) == 0) {
        printf("Clave 43 insertada correctamente.\n");
    } else {
        printf(" Error al insertar la clave 43.\n");
    }

    coord1.x = 1;
    coord1.y = 2;
    vec1[0] = 10.5; 
    vec1[1] = 20.5;
    vec1[2] = 30.5;

    if (set_value(42, "Ejemplo2", 3, vec1, coord1) == 0) {
        printf("Clave 42 insertada correctamente.\n");
    } else {
        printf(" Error al insertar la clave 42.\n");
    }

    coord1.x = 9;
    coord1.y = 2;
    vec1[0] = 4.3; 
    vec1[1] = 5.7;
    vec1[2] = 2.5;

    if (set_value(41, "Ejemplo3", 3, vec1, coord1) == 0) {
        printf("Clave 41 insertada correctamente.\n");
    } else {
        printf(" Error al insertar la clave 41.\n");
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
    ResponseMessage resultado;

    if ((resultado = get_value(42, value1, &N_value2, V_value2, &value3)) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("    value1: %s\n", resultado.value1);
        printf("    N_value2: %d\n", resultado.N_value2);
        printf("    V_value2: ");
        print_vector(resultado.V_value2, resultado.N_value2);
        printf("    value3: (%d, %d)\n", resultado.value3.x, resultado.value3.y);
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
    if (resultado=get_value(42, value1, &N_value2, V_value2, &value3) == 0) {
        printf("Valores obtenidos correctamente:\n");
        printf("   🔹 value1: %s\n", resultado.value1);
        printf("   🔹 N_value2: %d\n", resultado.N_value2);
        printf("   🔹 V_value2: ");
        print_vector(resultado.V_value2, resultado.N_value2);
        printf("   🔹 value3: (%d, %d)\n", resultado.value3.x, resultado.value3.y);
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

