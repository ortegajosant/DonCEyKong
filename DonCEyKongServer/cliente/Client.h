//
// Created by jorte on 12/6/2019.
//

#ifndef DONCEYKONGSERVER_CLIENT_H
#define DONCEYKONGSERVER_CLIENT_H
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

WSADATA wsaData;
SOCKET conn_socket;
struct sockaddr_in server;
struct hostent *hp;
int resp;

int conectarServer();

#endif //DONCEYKONGSERVER_CLIENT_H
