#include <iostream>

#include <projet/Engine.hpp>

int main(int argc, char** argv) {
    Projet::AppEngine* engine = new Projet::AppEngine(argv[0]);
    if (!engine->init("shader.vs.glsl", "shader.fs.glsl")) {
        return EXIT_FAILURE;
    }

    engine->run();

    delete(engine);

    return EXIT_SUCCESS;
}
