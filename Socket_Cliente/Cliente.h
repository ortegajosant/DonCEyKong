//
// Created by Christian on 6/14/2019.
//

#ifndef DONCEYKONG_CLIENTE_H
#define DONCEYKONG_CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

WSADATA wsaData;
SOCKET conn_socket;
struct sockaddr_in server;
struct hostent *hp;
int resp;
char dato[20];
char RecvBuff[20];

int conectarServer();
void obtenerRespuesta(char*);
bool  flagBarril;
#endif //DONCEYKONG_CLIENTE_H
