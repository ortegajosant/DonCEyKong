//
// Created by jorte on 12/6/2019.
//

#include "Client.h"
char SendBuff[512], RecvBuff[512];

int concectarServer(){
    resp = WSAStartup(MAKEWORD(1, 0), &wsaData);
    if (resp) {
        printf("Error al inicializar socket\n");
        getchar();
        return -1;
    }

    //Obtenemos la IP del servidor... en este caso
    // localhost indica nuestra propia máquina...
    hp = (struct hostent *) gethostbyname("localhost");

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


    printf("Conexión establecida con: %s\n", inet_ntoa(server.sin_addr));
    recv(conn_socket, RecvBuff, sizeof(RecvBuff), 0);
    memset(RecvBuff, 0, 512);
    char respuesta[256];
    while(1) {
        printf("Enviando Mensaje... \n");
        gets(SendBuff);
        if (strcmp(SendBuff,":exit") == 0) {
            send(conn_socket, SendBuff, sizeof(SendBuff), 0);
            break;
        }
        send(conn_socket, SendBuff, sizeof(SendBuff), 0);
        printf("Datos enviados: %s \n", SendBuff);
        printf("Recibiendo Mensaje... \n");
        recv(conn_socket, RecvBuff, sizeof(RecvBuff), 0);
        printf("Datos recibidos: %s \n", RecvBuff);
    }
    // Cerramos el socket y liberamos la DLL de sockets
    closesocket(conn_socket);
    WSACleanup();
    return EXIT_SUCCESS;
};