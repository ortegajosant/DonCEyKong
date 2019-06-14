#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <unistd.h>
#include "allegro5/allegro_image.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

/// Denificion de variables del jugador
const int MARIO_SIZE = 39;
float mario_x;
float mario_y;
int a = 1;
int *pt_mario = &a;
int vida_mario = 6;

///salto
bool salto_flag = false;
int salto_vertical = 0;
int y_salto = 0;

///Flag para activar el proceso de caida de muerte
bool flag_muerte;
int y_muerte = 0;

/// Flag para activar el proceso de colicion
bool flagColision = false;

/// Variables para para la animacion de la imagen de mario.
const int maxFrame = 3;
int curFrame = 0;
int frameCount = 0;
int frameDelay = 7;
int frameWidth = 32;
int frameHeight = 37;
ALLEGRO_BITMAP *image;
///

///Activa el flag para activar el proceso de muerte
void perder_vida(){
    flag_muerte = true;
}
/// Produce el efecto visual de mario cuadno muere.
void animacionMuerte(){
    image = al_load_bitmap("../img/muerte.png");
    if (!image)printf("Aqui1");
    if (++frameCount >= frameDelay) {
        if (++curFrame >= 4)
            curFrame = 0;
        frameCount = 0;
    }
}
/// Resetea las variables para evaluar cuando mario muere.
void muerte_mario(){
    flag_muerte = false;
    y_muerte = 0;
    mario_x = 9;
    mario_y = 650;
    *pt_mario = 1;
    vida_mario--;
}
/// Resetea las variables para evaluar cuando mario muere.
void gano_mario(){
    mario_x = 9;
    mario_y = 650;
    *pt_mario = 1;
    vida_mario++;
}
/// Reliza la caida de mario cuando muere, y ejecuta el proceso posterior a la muerte
void caida_muerte(){
    if(y_muerte > 60){
        image = al_load_bitmap("../img/muerte.png");
        ALLEGRO_BITMAP *fondo = al_load_bitmap("../img/fondo.png");
        al_clear_to_color(al_map_rgb(100,200,255));
        al_draw_bitmap(fondo,0,0,0);
        al_draw_bitmap_region(image, 4 * frameWidth, 0, frameWidth, frameHeight, mario_x, mario_y-40 - y_salto + y_muerte, 0);
        al_flip_display();
        sleep(1);
        muerte_mario();
        curFrame = 0;
        image = al_load_bitmap("../img/marioDer.png");
    }
    if(flag_muerte){
        y_muerte++;
    }
}
/// Permite cambiar el valor de y
void set_y(float y)
{
    mario_y = y;
}
/// Permite el movimiento en x
void movement_x(float x){
    mario_x += x;
}
/// Permite el movimiento en y
void movement_y(float y) {
    mario_y += y;
}
/// Inicializa las variables del jugador
bool init_player(int alto_pantalla){
    if(!image) {
        image = al_load_bitmap("../img/marioDer.png");
        mario_x = 9;
        mario_y = 650;
        return true;
    }
    printf("Error al cargar a Mario!\n");
    return false;
}
/// Modifica la posicion de mario para efectuar el salto.
int salto(){
    if(!salto_flag){
        salto_flag = true;
        salto_vertical = 2;
        y_salto = 1;
    }
    if(y_salto >= 43){
        salto_vertical = -1;
    }
    if(y_salto == 0){
        salto_flag = false;
        salto_vertical = 0;
    }
    y_salto += salto_vertical;
}
/// Produce el efecto visual para subir en el borde de la escalera.
DWORD WINAPI animacionFinal(){
    image = al_load_bitmap("../img/subefinal.png");
    if (!image)printf("Aqui1");
    curFrame = 0;
    frameCount = 0;
    for (int i = 0; i < 3; i++) {
        curFrame = i;
        usleep(70000);
    }
    mario_y -= 16;
}
/// Realiza la animacion cuando mario sube por las escaleras y cuando llega al borde de la escalera
/// para subir al siguiente nivel.
void subeEscalera(int val){
    if (val == 1){
        movement_y(-val);
        image = al_load_bitmap("../img/escaleras.png");
        if (!image)printf("Aqui1");
        if (++frameCount >= frameDelay) {
            if (++curFrame >= maxFrame)
                curFrame = 0;
            frameCount = 0;
        }
    }else if(val == -1) {
        CreateThread(NULL,0,animacionFinal,NULL,0,NULL);
    }
}
/// Funcion que se encarga de realizar la animacion cuando
/// mario baja por las escaleras
void bajaEscalera(int val){
    if(val != 0) {
        if(val!=-1) {
            movement_y(val);
        }
        image = al_load_bitmap("../img/escaleras.png");
        if (++frameCount >= frameDelay) {
            if (++curFrame >= maxFrame)
                curFrame = 0;
            frameCount = 0;
        }
    }
}
/// Funcion que se encarga de realizar la animacion cuando
/// mario se desplaza hacia la izquierda
void caminaIzq(){
    image = al_load_bitmap("../img/marioIzq.png");
    if(!image)printf("Aqui1");
    if (++frameCount >= frameDelay) {
        if (++curFrame >= maxFrame) {
            curFrame = 0;
        }
        frameCount = 0;
    }
}
/// Funcion que se encarga de realizar la animacion cuando
/// mario se desplaza hacia la derecha
void caminaDerecha(){
    image = al_load_bitmap("../img/marioDer.png");
    if(!image)printf("Aqui");
    if (++frameCount >= frameDelay) {
        if (++curFrame >= maxFrame) {
            curFrame = 0;
        }
        frameCount = 0;
    }
}

#pragma clang diagnostic pop