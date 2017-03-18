cmake_minimum_required(VERSION 3.5.1)

project(BMP24)

LINK_LIBRARIES("m")

set (SRC_LIST main.c bitmap.c gaussian.c mat.c)

add_executable(bmp24 ${SRC_LIST})

