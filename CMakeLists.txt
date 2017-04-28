cmake_minimum_required(VERSION 3.5.1)

project(BMP24)

if(UNIX)
    LINK_LIBRARIES("m")
endif()

set(BMP_LIB_SRC bitmap.c bitmap.h)
set(GAUS_LIB_SRC gaussian.c gaussian.h)
set(MED_LIB_SRC median.c median.h)
set(APP_SRC main.c)

add_library(libbmp24 SHARED ${BMP_LIB_SRC})
set_target_properties(libbmp24 PROPERTIES OUTPUT_NAME "bmp24")

add_library(libgaus SHARED ${GAUS_LIB_SRC})
set_target_properties(libgaus PROPERTIES OUTPUT_NAME "gaussian")
target_link_libraries(libgaus libbmp24)

add_library(libmed SHARED ${MED_LIB_SRC})
set_target_properties(libmed PROPERTIES OUTPUT_NAME "median")
target_link_libraries(libmed libbmp24)

add_executable(bmp24 ${APP_SRC})
target_link_libraries(bmp24 libbmp24 libgaus libmed)

