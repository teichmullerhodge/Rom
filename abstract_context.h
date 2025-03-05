#ifndef ABSTRACT_CONTEXT_H
#define ABSTRACT_CONTEXT_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define VERSION_MAJOR 4
#define VERSION_MINOR 6

void init_glfw_abstract_context() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
}

#endif // !ABSTRACT_CONTEXT_H