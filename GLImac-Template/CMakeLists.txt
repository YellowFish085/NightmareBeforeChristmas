cmake_minimum_required(VERSION 2.8)

project(NightmareBeforeChristmas)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)
set(ASSIMP_LIBRARY ${CMAKE_SOURCE_DIR}/assimp/lib/libassimp.so.3)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include assimp/include projet/include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${ASSIMP_LIBRARY} projet)

add_subdirectory(glimac)
add_subdirectory(projet)

file(GLOB DEV_DIRECTORIES "dev*")

foreach(DEV ${DEV_DIRECTORIES})
    add_subdirectory(${DEV})
endforeach()
