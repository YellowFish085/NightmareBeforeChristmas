#include <iostream>

#include <projet/engine.hpp>

using namespace glimac;

int main(int argc, char** argv) {
    Projet::AppEngine* eng = new Projet::AppEngine(argv[0]);
    if (!eng->init("shader.vs.glsl", "shader.fs.glsl")) {
        return EXIT_FAILURE;
    }

    eng->run();

    // // Application loop:
    // bool done = false;
    // while(!done) {
    //     // Event loop:
    //     SDL_Event e;
    //     while(windowManager.pollEvent(e)) {
    //         if(e.type == SDL_QUIT) {
    //             done = true; // Leave the loop after this iteration
    //         }
    //     }

    //     // Update the display
    //     windowManager.swapBuffers();
    // }

    return EXIT_SUCCESS;
}
