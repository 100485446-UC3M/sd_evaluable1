#include <stdio.h>
#include "claves.h"
#include <stdlib.h>
#include <pthread.h>

// Inicializar el mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Estructura para almacenar las tuplas
typedef struct Tupla {
    int key;
    char value1[256];
    int N_value2;
    double V_value2[32];
    struct Coord value3;
    struct Tupla *next;
} Tupla;

//Puntero a la lista de tuplas
static Tupla *head  = NULL;

//Implementación de las funciones

int destroy() {
    pthread_mutex_lock(&mutex);
    Tupla *current = head;
    while (current != NULL) {
        Tupla *temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    pthread_mutex_unlock(&mutex);

    return 0;
}

int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3){
    if (value1 == NULL || V_value2 == NULL || N_value2 > 32 || N_value2 < 1 || strnlen(value1, 256) > 255){
        return -1;
    }
    pthread_mutex_lock(&mutex);
    //Verificar si la llave ya existe
    Tupla *current = head;
    while (current != NULL){
        if (current->key == key){
            pthread_mutex_unlock(&mutex);
            return -1;
        }
        current = current -> next;
    }

    Tupla *new_tupla = malloc(sizeof(Tupla));
    if (new_tupla==NULL){
        return -1;
    }
    
    new_tupla->key = key;
    strncpy(new_tupla->value1, value1, 255); //Efectivo cuando hay límite de tamaño; 255 + código zero
    new_tupla->value1[255] = '\0'; //Nos aseguramos que existe el \0 incluso si el valor es exacto
    new_tupla->N_value2 = N_value2;
    memcpy(new_tupla->V_value2, V_value2, N_value2 * sizeof(double)); //Más efectivo que copiar con un loop
    new_tupla->value3 = value3;
    new_tupla->next = head;
    head = new_tupla;
    pthread_mutex_unlock(&mutex);
    return 0;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3){
    if (value1 == NULL || N_value2 == NULL || V_value2 == NULL || value3 == NULL) {
        return -1;
    }        
    pthread_mutex_lock(&mutex);
    Tupla *current = head;
    while (current != NULL) {
        if (current->key == key) {
            strncpy(value1, current->value1, 255);
            value1[255] = '\0';
            *N_value2 = current->N_value2;
            memcpy(V_value2, current->V_value2, (*N_value2) * sizeof(double));
            *value3 = current->value3;
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&mutex);
    return -1; 
}

int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3){
    if (value1 == NULL || V_value2 == NULL || N_value2 > 32 || N_value2 < 1 || strnlen(value1, 256) > 255){
        return -1;
    }
    
    pthread_mutex_lock(&mutex);
    Tupla *current = head;
    while (current != NULL) {
        if (current->key == key) {
            strncpy(current->value1, value1, 255);
            current->N_value2 = N_value2;
            memcpy(current->V_value2, V_value2, N_value2 * sizeof(double));
            current-> value3 = value3;
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&mutex);
    return -1; 
}

int delete_key(int key){
    pthread_mutex_lock(&mutex);
    Tupla *current = head;
    Tupla *prev = NULL;
    while(current!=NULL){
        if(current->key == key){
            if (prev){          //Si no es el primer elemento
                prev->next = current->next;
            }
            else{
                head = current -> next;
            }
            free(current);
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        prev = current;
        current = current -> next;
    }
    pthread_mutex_unlock(&mutex);
    return -1;
}

int exist(int key){
    pthread_mutex_lock(&mutex);
    Tupla *current = head;
    while(current!=NULL){
        if (current->key == key){
            pthread_mutex_unlock(&mutex);
            return 1;
        }
        current = current->next;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}