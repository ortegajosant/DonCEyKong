#include <stdio.h>


bool tirarBarril = true;

/// Variables para la animacion de pauline
int curFramePauline = 0;
int frameCountPauline = 0;

/// Variables para la animacion de ayuda
const int maxFrameAyuda = 2;
int curFrameAyuda = 0;
int frameCountAyuda = 0;
int frameWidthAyuda = 60;
int frameHeightAyuda  = 21;

/// Variables para la animacion de DonKey Kong
int curFrameDonkey = 0;
int frameCountDonkey = 0;
int frameWidthDonkey = 116;
int frameHeightDonkey  = 84;

/// Variables para la animacion del barril
int curFrameBarril = 0;
int frameCountBarril = 0;
int maxFrameBarril = 4;

//// Imagenes de los personajes secundarios
ALLEGRO_BITMAP *pauline = NULL;
ALLEGRO_BITMAP *ayuda = NULL;
ALLEGRO_BITMAP *donkey = NULL;
ALLEGRO_BITMAP *barriles_image =NULL;
ALLEGRO_BITMAP *barril = NULL;

///  Funcion  para la rotacion del barril
/// \return Paara la creacion de un hilo
DWORD WINAPI colocarBarril(){
    while (true) {
        if (++frameCountBarril >= frameDelay && !flagColision) {
            if (++curFrameBarril >= maxFrameBarril)
                curFrameBarril = 0;
            frameCountBarril = 0;
        }
        usleep(20000);
    }
}
/// Funcion para el movimiento de pauline
/// \return  Creacion de un hilo
DWORD WINAPI colocarPauline(){
    while (true) {
        if (++frameCountPauline >= frameDelay && !flagColision) {
            if (++curFramePauline >= maxFrame)
                curFramePauline = 0;
            frameCountPauline = 0;
        }
        usleep(70000);
    }
}

/// Animacion para el rotulo de ayuda de pauline
DWORD WINAPI colocarAyuda(){
    while (true){
        if (++frameCountAyuda >= frameDelay && !flagColision) {
            if (++curFrameAyuda >= maxFrameAyuda)
                curFrameAyuda = 0;
            frameCountAyuda = 0;
        }
        usleep(100000);
    }
}
/// Animacion para que DonKey Kong tire un barril
DWORD WINAPI colocarDonkey(){
    while (tirarBarril){
        if (++frameCountDonkey >= frameDelay && !flagColision) {
            if (++curFrameDonkey >= maxFrame) {
                if (curFrameDonkey == 3) {
                    donkey = al_load_bitmap("../img/donkeyKong.png");
                }
                curFrameDonkey = 0;
            }
            frameCountDonkey = 0;
        }

        usleep(100000);
    }
}
/// Activacion del proceso para que DonKey Kong tire un barril.
DWORD WINAPI lanzarBarril(){
    tirarBarril = false;
    donkey = al_load_bitmap("../img/donkeyTira.png");
    curFrameDonkey = 0;
    tirarBarril = true;
}

