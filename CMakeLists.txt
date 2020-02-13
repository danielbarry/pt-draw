cmake_minimum_required(VERSION 2.4)
project(PTDraw)

add_definitions("-DOPTION_ABI_VERSION=\"10305\"")
set(FLTK_DIR src/fltk)
set(FLTK_LIB_NAME fltk)
add_subdirectory(${FLTK_DIR})
include_directories(${FLTK_DIR})

add_executable(pt-draw-test src/test.c)

add_executable(pt-draw src/draw.cc)
target_link_libraries(pt-draw ${FLTK_LIB_NAME})
