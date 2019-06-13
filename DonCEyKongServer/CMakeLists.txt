cmake_minimum_required(VERSION 3.13)
project(DonCEyKongServer C)

set(CMAKE_C_STANDARD 99)
link_libraries(ws2_32 wsock32)

add_executable(DonCEyKongServer main.c server/Server.h server/Server.c cliente/Client.h cliente/Client.c)