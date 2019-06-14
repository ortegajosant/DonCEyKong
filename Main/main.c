#include <stdio.h>
#include <allegro5/allegro.h>
#include <unistd.h>
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "screen.h"
#include "Player/player.h"
#include "controlDeMovimiento.h"
#include "Sprites/sprites.h"
#include "windows.h"
#include "Barriles/barril.c"
#include "Socket_Cliente/Cliente.h"
#include <allegro5/allegro_native_dialog.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

//Inicio de variables del juego
enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

bool key[4];
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
bool redraw;
bool done;
float velBarril = 0.2;

///////////// Manejo de barriles ////////////
int largo = 0;
struct barril barriles[50];

/// Agrega un barril nuevo a la lista de barriles
/// \param barril1 Barril a agregar
void agregar_barril (struct barril barril1) {
    barriles[largo] = barril1;
    largo++;
    usleep(1000000000);
    flagBarril =false;
}
/// Elimina el barril en la posicion num de la lista de barriles
/// \param num Posicion del barril de que se quiere eliminar
void elimianar_barril(int num){
    if(num < largo) {
        for (int i = 0; i < largo-1; ++i) {
            if (i >= num) {
                barriles[i] = barriles[i + 1];
                perder_vida();
            }
        }
        largo--;
    }
}
/// Se encarga del movimiento de los barriles que se encuetren en la lista de
/// barriles
void barril_simple(){
    while(true) {
        if (largo > 0 && !flagColision) {
            for (int i = 0; i < largo; ++i) {
                if (barriles[i].pt_barril > 0) {
                    int aux = control_posciciones(barriles[i].pt_barril, barriles[i].x);
                    if (aux != -1) {
                        barriles[i].dy = 0;
                        barriles[i].x += barriles[i].dirreccion_de_movimiento + (velBarril*barriles[i].dirreccion_de_movimiento);
                        barriles[i].y = aux;
                    }
                    else {
                        if(barriles[i].dy >= 60){
                            barriles[i].pt_barril--;
                            barriles[i].dirreccion_de_movimiento *= -1;
                        } else{
                            barriles[i].dy++;
                        }
                    }
                } else if (barriles[i].pt_barril <= 0) {
                    elimianar_barril(i);
                }
            }
            usleep(10000);
        }
    }
}
/// Funcion que se encarga de dibujar todos los barriles que hayan en la lista.
void dibujar_barriles(){
    for (int i = 0; i < largo; ++i) {
        struct barril aux = barriles[i];
        al_draw_bitmap_region(barril, curFrameBarril*20, 0, 20, 20, aux.x, aux.y-20+aux.dy, 0);
    }

}
/// Pinta en pantalla todos los elementos que se encuentren en ella en sus nuevas
/// posiciones en cada actualizazcion
void dibujar_pantalla(){
    al_clear_to_color(al_map_rgb(100,200,255));
    al_draw_bitmap(fondo,0,0,0);
    al_draw_bitmap_region(pauline, curFramePauline * frameWidth, 0, frameWidth, frameHeight, 270, 35, 0);
    al_draw_bitmap_region(ayuda, curFrameAyuda * frameWidthAyuda, 0, frameWidthAyuda, frameHeightAyuda, 300, 35, 0);
    al_draw_bitmap_region(image, curFrame * frameWidth, 0, frameWidth, frameHeight, mario_x, mario_y-40 - y_salto + y_muerte, 0);
    if(largo >0 ){
        dibujar_barriles();
    }
    al_draw_bitmap_region(donkey, curFrameDonkey * frameWidthDonkey, 0, frameWidthDonkey, frameHeightDonkey, 75, 75, 0);
    al_draw_bitmap_region(barriles_image, 0, 0, 98, 145, 10, 75, 0);
}
/// Revisa la posicion de mario con la posicion de cada barril para conocer cuando se dio una
/// colision
void colicion(){
    for (int i = 0; i < largo; ++i) {
        if(mario_x >=  barriles[i].x -5 && mario_x < barriles[i].x+20){
            if(mario_y - y_salto + 15 >= barriles[i].y && mario_y - y_salto <= barriles[i].y){
                flagColision = true;
                for (int k = 0; k < 150; ++k) {
                    image = al_load_bitmap("../img/muerte.png");
                    if (++frameCount >= frameDelay) {
                        if (++curFrame >= maxFrame)
                            curFrame = 0;
                        frameCount = 0;
                    }
                    dibujar_pantalla();
                    al_flip_display();
                    usleep(2000);
                }
                image = al_load_bitmap("../img/marioDer.png");
                largo = 0;
                al_clear_to_color(al_map_rgb(0,0,0));
                al_flip_display();
                usleep(300000);
                flagColision = false;
                muerte_mario();
            }

        }
    }
}
/// Se encarga de inicializar todas las dependencias para que el juego funicone, iniciar el jugar
/// y installar funcionalidades como el teclado.
/// \return
int init_game() {
    key[1] = false; key[2] = false; key[3] = false; key[4] = false;
    redraw = true;
    done = false;
    escalera = false;

    al_init();
    al_init_primitives_addon();
    al_init_image_addon();
    al_install_keyboard();

    // Inicializacion de jugador -------
    init_player(ALTO_PANTALLA);

    // Inicializacion de pantalla
    init_screen();
    al_draw_bitmap(fondo, 0, 0, 0);
    al_clear_to_color(al_map_rgb(255, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(pantalla));
    pauline = al_load_bitmap("../img/pauline.png");
    ayuda = al_load_bitmap("../img/help.png");
    donkey = al_load_bitmap("../img/donkeyKong.png");
    barriles_image = al_load_bitmap("../img/barriles.png");
    barril = al_load_bitmap("../img/barrilesRodando.png");
    // Actualizacion de pantalla
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();

    // Registro de eventos  en event_queue  e inicializacion dek timer
    timer = al_create_timer(1.0 / FPS);
    al_start_timer(timer);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(pantalla));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    return 0;
}
/// Revisa si hay mas de dos teclas presicionadas para bloquear los movimientos del jugador
/// \return numero de teclas presicionadas
int teclas_presiconadas(){
    int contador_keys = 0;
    for (int i = 0; i < 4; ++i) {
        if(key[i] == true){
            contador_keys++;
        }
    }
    return contador_keys;
}
void gano(){
    if(*pt_mario == 7 && mario_x < 330 && mario_x > 243){
        ayuda = al_load_bitmap("../img/love.png");
        curFrameAyuda = 0;
        dibujar_pantalla();
        al_flip_display();
        sleep(1);
        ayuda = al_load_bitmap("../img/help.png");
        al_show_native_message_box(al_get_current_display(),
                                   "Felicidades!",
                                   "Ha completado el nivel, ahora irá más rápido",
                                   "",
                                   NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL);
        velBarril += 0.4;
        largo = 0;
        gano_mario();
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
        key[1] = false; key[2] = false; key[3] = false; key[4] = false;
        usleep(300000);
        fondo = al_load_bitmap("../img/fondo.png");
    }
}
///Variable que modifica la velocidad a la que se mueve mario
float mov = 2.0;
/// Funcion que se encarga de correr el hilo principal del juego
/// \return 0.
int run(){
    int val = 0;
    CreateThread(NULL, 0, colocarPauline, NULL, 0, NULL); /// Se crean hilos para trabajas secundarios con los otros elementos
    CreateThread(NULL, 0, colocarAyuda, NULL, 0, NULL); ///  del juego.
    CreateThread(NULL, 0, colocarDonkey, NULL, 0, NULL);
    CreateThread(NULL,0,barril_simple,NULL,0,NULL);
    CreateThread(NULL, 0, colocarBarril, NULL, 0, NULL);
    while(!done)
    {
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type == ALLEGRO_EVENT_TIMER ) {
            if(teclas_presiconadas() < 2 && !y_muerte){
                if(key[KEY_UP] && mario_y >= mov + 53) {
                    val = control_escaleras(pt_mario,(int)mario_x, (int)mario_y, false);
                    subeEscalera(val);
                }
                if(key[KEY_DOWN] && mario_y <= ALTO_PANTALLA - MARIO_SIZE) {
                    val = control_escaleras(pt_mario,(int)mario_x, (int)mario_y, true);
                    bajaEscalera(val);
                }
                if(key[KEY_LEFT] && mario_x >= mov && !escalera) {
                    caminaIzq();
                    float movimiento_y = control_posciciones(*pt_mario,(int)mario_x - mov);
                    if(movimiento_y != -1){
                        movement_x(-mov);
                        set_y(movimiento_y);
                    }else{
                        perder_vida();
                    }
                }
                if(key[KEY_RIGHT] && mario_x <= ANCHO_PANTALLA - MARIO_SIZE - mov && !escalera) {
                    caminaDerecha();
                    float movimiento_y = (control_posciciones(*pt_mario,(int)mario_x + mov));
                    if(movimiento_y != -1) {
                        movement_x(mov);
                        set_y(movimiento_y);

                    }else{
                        perder_vida();
                    }
                }
                sprintf(dato,"{%d,%d}",(int)mario_x ,(int)mario_y);
            }
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN ) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
        }
        else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
            switch(ev.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
            }
        }
        if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE && !escalera && !salto_flag){
            salto();
        }
        if(salto_flag){
            salto();
        }
        if(flag_muerte){
            animacionMuerte();
            caida_muerte();
        }
        ///
        colicion();
        gano();
        if(flagBarril){
            struct barril barril_temp;
            barril_temp.x = 150; barril_temp.y = 198; barril_temp.pt_barril = 6;
            barril_temp.dirreccion_de_movimiento = 1; barril_temp.dy = 0;
            agregar_barril(barril_temp);
        }
        ///
        if(redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            dibujar_pantalla();
            al_flip_display();
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_D && ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            printf("%d, %d\n",(int)mario_x, (int)mario_y);
            printf("%d\n",*pt_mario);
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_Z && ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            struct barril barril_temp;
            barril_temp.x = 150; barril_temp.y = 198; barril_temp.pt_barril = 6;
            barril_temp.dirreccion_de_movimiento = 1; barril_temp.dy = 0;
            agregar_barril(barril_temp);
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_A && ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            *pt_mario += 1 ;
        }
        if(ev.keyboard.keycode == ALLEGRO_KEY_S && ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            *pt_mario -= 1 ;
        }
    }
    return 0;
}

/// Main del juego
/// \return
int main() {
    CreateThread(NULL, 0, conectarServer, NULL, 0, NULL);
    init_game();
    run();
    // Destruccion de punteros
    al_destroy_bitmap(fondo);
    al_destroy_timer(timer);
    al_destroy_display(pantalla);
    al_destroy_event_queue(event_queue);
    return 0;
}

#pragma clang diagnostic pop