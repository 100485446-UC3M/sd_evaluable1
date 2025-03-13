#include "claves.h"

//La función es solo accesible dentro este archivo (solo para el cliente).
static int send_request_to_server(RequestMessage *request, ResponseMessage *response) {
    mqd_t server_queue, client_queue;
    struct mq_attr attr;
    // Configurar atributos de la cola de mensajes
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(ResponseMessage);
    char client_queue_name[64];

    // Crear cola del cliente para recibir respuesta

    snprintf(client_queue_name, sizeof(client_queue_name), CLIENT_QUEUE_TEMPLATE, request->client_pid);

    if ((client_queue = mq_open(client_queue_name, O_CREAT | O_RDONLY, QUEUE_PERMISSIONS_PROXY, &attr)) == -1){
        perror("Error al crear la cola del cliente");
        return -2;
    }

    //Abrir cola del servidor y enviar petición

    if ((server_queue = mq_open(SERVER_QUEUE, O_WRONLY)) == -1){
        perror("Error al abrir la cola del server");
        mq_close(client_queue);
        mq_unlink(client_queue_name);
        return -2;
    }

    if ((mq_send(server_queue, (char*)request, sizeof(RequestMessage), 0)) == -1) {
        perror("Error al enviar la solicitud al servidor");
        mq_close(server_queue);
        mq_close(client_queue);
        mq_unlink(client_queue_name);
        return -2;
    }

    // Esperar respuesta del servidor
    if ((mq_receive(client_queue, (char*)response, sizeof(ResponseMessage), NULL)) == -1) {
        perror("Error al recibir la respuesta del proxy");
        mq_close(server_queue);
        mq_close(client_queue);
        mq_unlink(client_queue_name);
        return -2;
    }
    
    // Cerrar y eliminar las colas
    mq_close(server_queue);
    mq_close(client_queue);
    mq_unlink(client_queue_name);

    return 0;

}

int destroy() {
    RequestMessage request = {.action = DESTROY, .client_pid = getpid()};
    ResponseMessage status;
    int ret = send_request_to_server(&request, &status);
    if (ret < 0) {
        return ret;
    }
    return status.result;
}


int set_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    RequestMessage request = {.action = SET_VALUE, .key = key, .client_pid = getpid()};
    strncpy(request.value1, value1, 255);
    request.N_value2 = N_value2;
    memcpy(request.V_value2, V_value2, N_value2 * sizeof(double));
    request.value3 = value3;

    ResponseMessage status;
    int ret = send_request_to_server(&request, &status);
    if (ret < 0) {
        return ret;
    }
    return status.result;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2, struct Coord *value3) {
    RequestMessage request = {.action = GET_VALUE, .key = key, .client_pid = getpid()};
    ResponseMessage values;

    int ret = send_request_to_server(&request, &values);
    if (ret < 0) {
        return ret;
    }
    if (values.result == 0) {
        strncpy(value1, values.value1, 255);
        value1[255] = '\0';
        *N_value2 = values.N_value2;
        memcpy(V_value2, values.V_value2, (*N_value2) * sizeof(double));
        *value3 = values.value3;
    }
    return values.result;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2, struct Coord value3) {
    RequestMessage request = {.action = MODIFY_VALUE, .key = key, .client_pid = getpid()};
    strncpy(request.value1, value1, 255);
    request.N_value2 = N_value2;
    memcpy(request.V_value2, V_value2, N_value2 * sizeof(double));
    request.value3 = value3;

    ResponseMessage status;
    int ret = send_request_to_server(&request, &status);
    if (ret < 0) {
        return ret;
    }
    return status.result;
}


int delete_key(int key) {
    RequestMessage request = {.action = DELETE_KEY, .key = key, .client_pid = getpid()};
    ResponseMessage status;
    int ret = send_request_to_server(&request, &status);
    if (ret < 0) {
        return ret;
    }
    return status.result;
}

int exist(int key) {
    RequestMessage request = {.action = EXIST, .key = key, .client_pid = getpid()};
    ResponseMessage status;
    int ret = send_request_to_server(&request, &status);
    if (ret < 0) {
        return ret;
    }
    return status.result;
}
