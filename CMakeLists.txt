cmake_minimum_required(VERSION 3.5.1)

project(BMP24)

LINK_LIBRARIES("m")

set (LIB_SRC bitmap.c gaussian.c)
set (APP_SRC main.c)

add_library(libbmp24 SHARED ${LIB_SRC})
set_target_properties(libbmp24 PROPERTIES OUTPUT_NAME "bmp24")

add_executable(bmp24 ${APP_SRC})
target_link_libraries(bmp24 libbmp24)

