

#ifndef DONCEYKONG_CONTROLDEMOVIMIENTO_H
#define DONCEYKONG_CONTROLDEMOVIMIENTO_H

#include <stdio.h>
#include <stdbool.h>

bool escalera;
/// Cada funcion recibe el valor de "x" y segun sea la plataforma en la que se encuentra
/// retorne un valor de y
/// Posiciones  para la plataforma 1
int pt_1(int x);

/// Posiciones  para la plataforma 2
int pt_2(int x);

/// Posiciones  para la plataforma 3
int pt_3(int x);

/// Posiciones  para la plataforma 4
int pt_4(int x);

/// Posiciones  para la plataforma 5
int pt_5(int x);

/// Posiciones  para la plataforma 6
int pt_6(int x);

/// Posiciones  para la plataforma 7
int pt_7(int x);
/// Decide en cual funcion se debe evaluar la x segun sea la plataforma.
int control_posciciones(int plataforma, int x);



//// Conjunto de funciones que se encarga se verificar cuando se puede subir por una escalera
/// Y de moverser en cada una de ellas.
/// Cada una recibe la "x","y" y el numero de plataforma en la que se encuetra el objeto
#define correccion -8
/// Escaleras  para la plataforma 1
int es_pt1(int x , int y, bool flagD, int *plataforma);

/// Escaleras  para la plataforma 2
int es_pt2(int x, int y, bool flagD, int *plataforma);


/// Escaleras  para la plataforma 3
int es_pt3(int x, int y, bool flagD, int *plataforma);

/// Escaleras  para la plataforma 4
int es_pt4(int x, int y , bool flagD, int *plataforma);

/// Escaleras  para la plataforma 5
int es_pt5(int x, int y, bool flagD, int *plataforma);

/// Escaleras  para la plataforma 6
int es_pt6(int x,int y, bool flagD, int *plataforma);

///  Escaleras para la plataforma 7
int es_pt7(int x, int y, bool flagD, int *plataforma);

/// Decide con cual funcion evaluar las escaleras segun sea la plataforma en la que se encuentre
int control_escaleras(int *plataforma, int x, int y, bool flagD);

#endif //DONCEYKONG_CONTROLDEMOVIMIENTO_H