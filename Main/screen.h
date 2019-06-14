

#ifndef DONCEYKONG_SCREEN_H
#define DONCEYKONG_SCREEN_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
///Inicio de varibales de la pantalla

#define ANCHO_PANTALLA 684
#define FPS 60
#define ALTO_PANTALLA 673
ALLEGRO_DISPLAY *pantalla;
ALLEGRO_BITMAP *fondo;


/// Inicia los componestes de la pantalla
void init_screen();

#endif //DONCEYKONG_SCREEN_H
