cmake_minimum_required(VERSION 3.10)
project(DonCEyKongVersionFinal C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
link_libraries(ws2_32 wsock32)
add_executable(DonCEyKongVersionFinal
        Main/controlDeMovimiento.h
        Main/main.c
        Main/screen.h
        Player/player.h
        Sprites/sprites.h
        Socket_Cliente/Cliente.c
        Socket_Cliente/Cliente.h
        Barriles/barril.c Main/screen.c Main/controlDeMovimiento.c Player/player.c)

target_link_libraries(DonCEyKongVersionFinal -lmingw32 -lallegro-5.0.10-monolith-md-debug)