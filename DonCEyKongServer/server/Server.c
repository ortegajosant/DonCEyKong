//
// Created by jorte on 12/6/2019.
//
#include "Server.h"

int iniciar() {
    int opt = TRUE;

    resp = WSAStartup(MAKEWORD(1, 0), &wsaData);
    if (resp) {
        printf("Error al inicializar socket\n");
        getchar();
        return resp;
    }
    hp = gethostbyname("localhost");

    if (!hp) {
        printf("No se ha encontrado servidor...\n");
        getchar();
        WSACleanup();
        return WSAGetLastError();
    }

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
    server.sin_port = htons(PORT);

    resp = bind(conn_socket, (struct sockaddr *) &server, sizeof(server));
    if (resp == SOCKET_ERROR) {
        printf("Error al asociar puerto e ip al socket\n");
        closesocket(conn_socket);
        WSACleanup();
        getchar();
        return WSAGetLastError();
    }

    for (int i = 0; i < MAX_OBSERVERS; i++) {
        observers[i] = 0;
    }

    if (setsockopt(conn_socket, SOL_SOCKET, SO_REUSEADDR, (char *) &opt,
                   sizeof(opt)) < 0) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    return 0;
}

int iniciarServidor() {
    if (listen(conn_socket, MAX_OBSERVERS) == SOCKET_ERROR) {
        printf("Error al habilitar conexiones entrantes\n");
        closesocket(conn_socket);
        WSACleanup();
        getchar();
        return WSAGetLastError();
    }
    printf("Esperando conexiones entrantes... \n");
    int stsize = sizeof(struct sockaddr);

    fd_set readfds;
    int max_sd;
    int currentObserver;
    int verificacion;

    while (TRUE) {
        FD_ZERO(&readfds);

        FD_SET(conn_socket, &readfds);
        max_sd = conn_socket;

        for (int i = 0; i < MAX_OBSERVERS; i++) {
            if (observers[i] > 0) {
                FD_SET(observers[i], &readfds);
            }
            if (observers[i] > max_sd) {
                max_sd = observers[i];
            }
        }
        int activity = select(max_sd + 1, &readfds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            printf("select error");
        }
        if (FD_ISSET(conn_socket, &readfds)) {
            if ((newSocket = accept(conn_socket,
                                    (struct sockaddr *) &server, &stsize)) < 0) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("New connection , socket fd is %d , ip is : %s , port : %d\n", newSocket,
                   inet_ntoa(server.sin_addr), ntohs
                           (server.sin_port));

            if (send(newSocket, "Conectado con satisfaccion", strlen("Conectado con satisfaccion"), 0) !=
                strlen("Conectado con satisfaccion")) {
                perror("send");
            }

            puts("Welcome message sent successfully");


            for (int i = 0; i < MAX_OBSERVERS; i++) {
                if (observers[i] == 0) {
                    observers[i] = newSocket;
                    printf("Adding to list of sockets as %d\n", i);

                    break;
                }
            }
        }

        for (int i = 0; i < MAX_OBSERVERS; i++) {
            currentObserver = observers[i];
            if (FD_ISSET(currentObserver, &readfds)) {

                verificacion = recv(currentObserver, RecvBuff, sizeof(RecvBuff), 0);
                if (verificacion < 0) {

                    getpeername(currentObserver, (struct sockaddr *) &server, \
                        &stsize);
                    printf("Host disconnected , ip %s , port %d \n",
                           inet_ntoa(server.sin_addr), ntohs(server.sin_port));

                    close(observers[i]);
                    observers[i] = 0;
                }
                else {
                    strcpy(SendBuff, "Funco\0");
                    send(currentObserver, SendBuff, sizeof(SendBuff), 0);
                    printf("Cliente: %s\n", RecvBuff);
                    printf("Envio: %s\n", SendBuff);
                    memset(SendBuff, 0, 512);
                    memset(RecvBuff, 0, 512);

                }
            }
        }
    }
    return 0;
}