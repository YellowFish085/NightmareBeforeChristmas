#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace glimac;

int main(int argc, char** argv) {
  // Initialize SDL and open a window
  SDLWindowManager windowManager(800, 600, "GLImac");

  // Initialize glew for OpenGL3+ support
  GLenum glewInitError = glewInit();
  if(GLEW_OK != glewInitError) {
    std::cerr << glewGetErrorString(glewInitError) << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

  /*********************************
  * HERE SHOULD COME THE INITIALIZATION CODE
  *********************************/



  // Application loop:
  bool done = false;
  while(!done) {

    // Event loop:
    SDL_Event e;
    while(windowManager.pollEvent(e)) {
      if(e.type == SDL_QUIT) {
       done = true;
      }
   }

    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    // Update the display
    windowManager.swapBuffers();
  }

  return EXIT_SUCCESS;
}







// Shaders


/**
 * Créé un shader et l'ajoute au programme
 **/
static void AddShader(GLuint shaderProgram, const char* shaderContent, GLenum shaderType)
{
  // Création d'un objet shader pour le programme donné
  GLuint shaderObj = glCreateShader(shaderType);

  if (shaderObj == 0) {
    fprintf(stderr, "Erreur lors de la création du shader type %d\n", shaderType);
    exit(0);
  }

  // Récupération du contenu du shader
  const GLchar* content[1];
  content[0] = shaderContent;

  // Récupération de la taille du contenu du shader
  GLint lengths[1];
  lengths[0] = strlen(shaderContent);

  // Le code du shader est mit dans l'objet
  glShaderSource(shaderObj, 1, content, lengths);

  // Compilation du shader
  glCompileShader(shaderObj);

  // Vérification des erreurs
  GLint success;
  glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
  if (!success) {
    GLchar InfoLog[1024];
    glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
    fprintf(stderr, "Erreur pendans la compilation du shader type %d: '%s'\n", shaderType, InfoLog);
    exit(1);
  }

  // On attache le shader au programme
  glAttachShader(shaderProgram, shaderObj);
}


static void CompileShaders()
{
  const char* vsFileName = "shader.vs";
  const char* fsFileName = "shader.fs";

  // Créé un programme
  GLuint shaderProgram = glCreateProgram();

  if (shaderProgram == 0) {
    std::cout << "Erreur lors de la création du programme pour les shaders" << std::endl;
    exit(1);
  }

  // Lecture des shaders
  std::string vs, fs;
  if (!ReadFile(vsFileName, vs)) {
    exit(1);
  };
  if (!ReadFile(fsFileName, fs)) {
    exit(1);
  };

  // Ajout des shaders au programme
  AddShader(shaderProgram, vs.c_str(), GL_VERTEX_SHADER);
  AddShader(shaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

  GLint success = 0;
  GLchar errorLog[1024] = { 0 };

  // Liaison du programme
  glLinkProgram(shaderProgram);

  // Vérification des erreurs
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (success == 0) {
    glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
    fprintf(stderr, "Erreur lors de la liaison du programme : '%s'\n", errorLog);
    exit(1);
  }

  // Validation du programme
  glValidateProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
    fprintf(stderr, "Programme shader invalide: '%s'\n", errorLog);
    exit(1);
  }

  // Utilisation du programme
  glUseProgram(shaderProgram);

  gScaleLocation = glGetUniformLocation(shaderProgram, "gScale");
  assert(gScaleLocation != 0xFFFFFFFF);
}