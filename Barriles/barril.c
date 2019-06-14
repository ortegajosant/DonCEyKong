
#ifndef DONCEYKONG_BARRIL_H
#define DONCEYKONG_BARRIL_H

#include <stdbool.h>

/// Estructura para la creacion de barriles
///
struct barril{
    float x; /// posiciones
    float y;
    int dy; /// pasar de nivel
    int pt_barril; /// nivel en el que se mueve el barril
    int dirreccion_de_movimiento; /// Hacia la izquierda o derecha
};

#endif //DONCEYKONG_BARRIL_H

