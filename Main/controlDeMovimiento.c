#include "controlDeMovimiento.h"


/// Cada funcion recibe el valor de "x" y segun sea la plataforma en la que se encuentra
/// retorne un valor de y
/// Posiciones  para la plataforma 1
pt_1(int x)
{
    if (x >= 345){
        return (int)(-0.061*x +669);
    }
    else {
        return 650;
    }
}
/// Posiciones  para la plataforma 2
int pt_2(int x)
{
    if(x < 630){
        return (int)(0.06119*x+ 528);
    }
    return -1;
}
/// Posiciones  para la plataforma 3
int pt_3(int x)
{
    if(x > 32  ){
        return (int)(-0.0645*x + 471.69);
    }
    return -1;
}
/// Posiciones  para la plataforma 4
int pt_4(int x)
{
    if(x < 624){
        return (int)(0.06410*x+329.423);
    }
    return -1;
}
/// Posiciones  para la plataforma 5
int pt_5(int x)
{
    if( x > 35){
        return (int)(-0.06321*x+ 273);
    }
    return -1;
}
/// Posiciones  para la plataforma 6
int pt_6(int x)
{
    if (x < 438){
        return 158;
    }
    else if(x < 619) {
        return (int)(0.05208*x+137.1889);
    }
    return -1;
}
/// Posiciones  para la plataforma 7
int pt_7(int x)
{
    if(228 < x && x < 390){
        return 74;
    }
    return  -1;
}
/// Decide en cual funcion se debe evaluar la x segun sea la plataforma.
int control_posciciones(int plataforma, int x){
    switch (plataforma){
        case 1:
            return pt_1(x);
        case 2:
            return pt_2(x);
        case 3:
            return pt_3(x);
        case 4:
            return pt_4(x);
        case 5:
            return pt_5(x);
        case 6:
            return pt_6(x);
        case 7:
            return pt_7(x);
    }
}


//// Conjunto de funciones que se encarga se verificar cuando se puede subir por una escalera
/// Y de moverser en cada una de ellas.
/// Cada una recibe la "x","y" y el numero de plataforma en la que se encuetra el objeto

/// Escaleras  para la plataforma 1
int es_pt1(int x , int y, bool flagD, int *plataforma){
    if (558 + correccion < x && x < 571 + correccion &&(y < 634 || !flagD)){
        escalera = true;
        if( 585 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    escalera = false;
    return 0;
}
/// Escaleras  para la plataforma 2
int es_pt2(int x, int y, bool flagD, int *plataforma){
    if (558 + correccion < x && x < 571 + correccion && flagD){
        escalera = true;
        if(585 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if (295 + correccion< x && x < 310 + correccion && (y < 546 || !flagD)){
        escalera = true;
        if( 473 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    if(103 + correccion< x && x < 116 + correccion&& (y < 535 || !flagD)){
        escalera = true;
        if(483 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    escalera = false;
    return 0;
}

/// Escaleras  para la plataforma 3
int es_pt3(int x, int y, bool flagD, int *plataforma)
{
    if (295 + correccion < x && x < 310 + correccion && flagD){
        escalera = true;
        if( 473 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if(103 + correccion< x && x < 116 + correccion && flagD){
        escalera = true;
        if(483 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if (343 + correccion< x && x < 356 + correccion && (y <450 || !flagD)) {
        escalera = true;
        if(371 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    if (558 + correccion< x && x < 571 + correccion && (y < 437 || !flagD)){
        escalera = true;
        if(385 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    escalera = false;
    return 0;
}
/// Escaleras  para la plataforma 4
int es_pt4(int x, int y , bool flagD, int *plataforma)
{
    if (343 + correccion < x && x < 356 + correccion && flagD) {
        escalera = true;
        if(371 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if (558 + correccion < x && x < 571 + correccion && flagD){
        escalera = true;
        if(385 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }

    if (223 + correccion< x && x < 236+ correccion && (y < 343 || !flagD)){
        escalera = true;
        if(277 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    if( 103 + correccion< x && x < 116 + correccion && (y < 340 || !flagD)){
        escalera = true;
        if(285 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    escalera = false;
    return 0;
}
/// Escaleras  para la plataforma 5
int es_pt5(int x, int y, bool flagD, int *plataforma)
{
    if (223 + correccion< x && x < 236 + correccion && flagD){
        escalera = true;
        if(277 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if( 103 + correccion< x && x < 116 + correccion && flagD){
        escalera = true;
        if(285 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if (558 + correccion< x && x < 571 + correccion && (y < 237 || !flagD)){
        escalera = true;
        if( 185 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    escalera = false;
    return 0;
}
/// Escaleras  para la plataforma 6
int es_pt6(int x,int y, bool flagD, int *plataforma)
{
    if (558 + correccion< x && x < 571 + correccion && flagD){
        escalera = true;
        if(185 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if ((381 + correccion< x && x < 401 + correccion) && (y < 158 || !flagD)){
        escalera = true;
        if( 92 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    if((246 + correccion< x && x < 256 + correccion) && (y < 158 || !flagD)){
        escalera = true;
        if( 92 > y){
            escalera = false;
            *plataforma += 1;
            return -1;
        }
        return 1;
    }
    if((199 + correccion< x && x < 208 + correccion) && (y < 154 || !flagD)){
        escalera = true;
        return 1;
    }
    escalera = false;
    return 0;
}
///  Escaleras para la plataforma 7
int es_pt7(int x, int y, bool flagD, int *plataforma){
    if ((381 + correccion < x && x < 401 + correccion && flagD)){
        escalera = true;
        if( 92 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    if(242 + correccion < x && x < 256 + correccion && flagD){
        escalera = true;
        if( 92 < y){
            escalera = false;
            *plataforma -= 1;
            return -1;
        }
        return 1;
    }
    escalera = false;
    return 0;
}
/// Decide con cual funcion evaluar las escaleras segun sea la plataforma en la que se encuentre
int control_escaleras(int *plataforma, int x, int y, bool flagD)
{
    switch (*plataforma){
        case 1:
            return es_pt1(x,y, flagD, plataforma);
        case 2:
            return es_pt2(x,y, flagD, plataforma);
        case 3:
            return es_pt3(x,y, flagD, plataforma);
        case 4:
            return es_pt4(x,y, flagD, plataforma);
        case 5:
            return es_pt5(x,y, flagD, plataforma);
        case 6:
            return es_pt6(x,y, flagD, plataforma);
        case 7:
            return es_pt7(x,y,flagD, plataforma);
        default:
            return y;
    }

}