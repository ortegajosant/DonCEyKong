#include <unistd.h>
#include "Cliente.h"

int conectarServer(){
    resp = WSAStartup(MAKEWORD(1, 0), &wsaData);
    if (resp) {
        printf("Error al inicializar socket\n");
        getchar();
        return -1;
    }
    //Obtenemos la IP del servidor... en este caso
    // localhost indica nuestra propia máquina...
    hp = (struct hostent *) gethostbyname("172.18.20.7");

    if (!hp) {
        printf("No se ha encontrado servidor...\n");
        getchar();
        WSACleanup();
        return WSAGetLastError();
    }

    // Creamos el socket...
    conn_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (conn_socket == INVALID_SOCKET) {
        printf("Error al crear socket\n");
        getchar();
        WSACleanup();
        return WSAGetLastError();
    }

    memset(&server, 0, sizeof(server));
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(6000);

    // Nos conectamos con el servidor...
    if (connect(conn_socket, (struct sockaddr *) &server, sizeof(server)) == SOCKET_ERROR) {
        printf("Fallo al conectarse con el servidor\n");
        closesocket(conn_socket);
        WSACleanup();
        getchar();
        return WSAGetLastError();
    }
    memset(RecvBuff, 0, 512);
    printf("Conexion establecida con: %s\n", inet_ntoa(server.sin_addr));
    recv(conn_socket, RecvBuff, sizeof(RecvBuff), 0);
    memset(RecvBuff, 0, 512);
    int verificacion;
    send(conn_socket, "Conectado", sizeof("Conectado"), 0);
    while(1) {
        printf("Enviando Mensaje... \n");
        if (strcmp(dato,":exit") == 0) {
            send(conn_socket, dato, sizeof(dato), 0);
            break;
        }
        printf("Datos enviados: %s \n", "45");
        printf("Recibiendo Mensaje... \n");
        verificacion = recv(conn_socket, RecvBuff, sizeof(RecvBuff), 0);
        if (verificacion >= 0) {
            if (strlen(RecvBuff)) {
                obtenerRespuesta(RecvBuff);
            }
            printf("Datos recibidos: %s \n", RecvBuff);
            memset(RecvBuff, 0, 512);
        }
        send(conn_socket, "Conectado", sizeof("Conectado"), 0);
//        usleep(600000);
    }
    // Cerramos el socket y liberamos la DLL de sockets
    closesocket(conn_socket);
    WSACleanup();
    return EXIT_SUCCESS;
}

void obtenerRespuesta(char * respuesta) {
    int proceso = atoi(respuesta);
    printf("%d", proceso);
    switch (proceso) {
        case 1:
            printf("Barril 1\n");
            flagBarril = true;
            break;
        case 2:
            printf("Barril 2\n");
            break;
        default:
            printf("DEFAULT\n");
            break;
    }
}