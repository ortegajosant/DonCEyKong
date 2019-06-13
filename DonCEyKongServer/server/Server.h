//
// Created by jorte on 12/6/2019.
//

#ifndef CLIENTESERVIDOR_SERVER_H
#define CLIENTESERVIDOR_SERVER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/time.h>

#define MAX_OBSERVERS 5
#define PORT 6000
#define TRUE 1

char SendBuff[512];
char RecvBuff[512];
WSADATA wsaData;
SOCKET conn_socket;
struct sockaddr_in server;
struct hostent *hp;
int resp;
int player, newSocket;
int observers[MAX_OBSERVERS];


int iniciar();
int iniciarServidor();
void manejar();

#endif //CLIENTESERVIDOR_SERVER_H
