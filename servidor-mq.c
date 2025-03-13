#include "claves.h"

void * SendResponse(void* arg){
    RequestMessage* request = (RequestMessage*)arg;
    ResponseMessage response;
    mqd_t client_queue;
    char client_queue_name[64];

    // Limpiar la respuesta, evita valores inesperados en el lugar de memoria de la respuesta
    memset(&response, 0, sizeof(ResponseMessage));  

    // Procesar la solicitud
    switch (request->action) {
        case DESTROY:
            response.result = destroy();
            break;
        case SET_VALUE:
            response.result = set_value(request->key, request->value1, request->N_value2, request->V_value2, request->value3);
            break;
        case GET_VALUE:
            response.result = get_value(request->key, response.value1, &response.N_value2, response.V_value2, &response.value3);
            break;
        case MODIFY_VALUE:
            response.result = modify_value(request->key, request->value1, request->N_value2, request->V_value2, request->value3);
            break;
        case DELETE_KEY:
            response.result = delete_key(request->key);
            break;
        case EXIST:
            response.result = exist(request->key);
            break;
        default:
            response.result = -1;
            break;
    }

    // Enviar la respuesta al cliente
    // Introduce el request.client_pid dentro del template de cliente definido en las constantes
    snprintf(client_queue_name, sizeof(client_queue_name), CLIENT_QUEUE_TEMPLATE, request->client_pid);
    if ((client_queue = mq_open(client_queue_name, O_WRONLY))  == -1){
        perror("Error al abrir la cola de mensajes del cliente");
        free(request);
        pthread_exit(NULL);
    }
    else if ((mq_send(client_queue, (char*)&response, sizeof(ResponseMessage), 0)) == -1) {
        perror("Error al enviar la respuesta");
    }

    mq_close(client_queue);
    free(request);
    pthread_exit(NULL);
}


int main() {
    mqd_t server_queue;
    struct mq_attr attr;
    // Configurar atributos de la cola de mensajes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(RequestMessage);
    RequestMessage* request;

    // Crear la cola de mensajes del servidor
    if ((server_queue = mq_open(SERVER_QUEUE, O_CREAT | O_RDONLY, QUEUE_PERMISSIONS_SERVER, &attr)) == -1){
        perror("Error al abrir la cola de mensajes del servidor");
        exit(1);
    }

    printf("Servidor activo. Esperando mensajes...\n");

    pthread_attr_t thread_attr;
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);   

    // Bucle infinito para manejar las solicitudes
    while (1) {
        // Reservar memoria para la solicitud
        request = (RequestMessage*)malloc(sizeof(RequestMessage));
        if (!request) {
            perror("Error al reservar memoria para la solicitud");
            continue;
        }

        // Recibir el mensaje de un cliente
        if ((mq_receive(server_queue, (char*)request, sizeof(RequestMessage), NULL)) == -1) {
            perror("Error al recibir mensaje");
            free(request);
            continue;
        }

        printf("Solicitud recibida: Acción %d en Clave %d\n", request->action, request->key);
        
        pthread_t thread_id;
        if (pthread_create(&thread_id, &thread_attr, SendResponse, (void*)request) != 0) {
            perror("Error al crear el hilo");
            free(request);
        }
    }
    
    pthread_attr_destroy(&thread_attr);
    pthread_mutex_destroy(&mutex);

    // Cerrar la cola del servidor
    mq_close(server_queue);
    mq_unlink(SERVER_QUEUE);

    return 0;
}

