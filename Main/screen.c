#include "screen.h"

void init_screen(){
pantalla = al_create_display(ANCHO_PANTALLA, ALTO_PANTALLA);
fondo = al_load_bitmap("../img/fondo.png");
}
