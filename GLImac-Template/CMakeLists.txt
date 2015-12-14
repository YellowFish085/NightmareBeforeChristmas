cmake_minimum_required(VERSION 2.8)

project(NightmareBeforeChristmas)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)
# set(ASSIMP_LIBRARIES ${CMAKE_SOURCE_DIR}/assimp/lib/libassimp.so)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR} glimac/include projet/include third-party/include)

set(ALL_LIBRARIES glimac projet ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} ${ASSIMP_LIBRARIES})

add_subdirectory(glimac)
add_subdirectory(projet)
add_subdirectory(tests)

file(GLOB DEV_DIRECTORIES "dev*")

foreach(DEV ${DEV_DIRECTORIES})
    add_subdirectory(${DEV})
endforeach()
