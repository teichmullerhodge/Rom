#ifndef ROM_ENGINE_H
#define ROM_ENGINE_H

#define WIN_WIDTH  1280
#define WIN_HEIGHT 800
#define WIN_TITLE  "Rom Engine"

#include "abstract_context.h"
#include "shaders.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define NUMBER_OF_TEXTURES 64

typedef struct Window {

    GLFWwindow* view;
    int width;
    int height;
    const char *title;
    float RGBA[4]; 

} Window;


 // ^ 1. Vertices
 // * Vertices are the points that define the shape of a 3D object. To draw a triangle, you need three vertices, which represent the three corners 
 // * of the triangle. Each vertex usually has information such as position (X, Y, Z), color, texture coordinates, etc.

 // ^ 2. Buffers (VBO and VAO)
 // * VBO (Vertex Buffer Object): The VBO is a memory buffer that stores vertex data. 
 // * This data is transferred from the CPU to the GPU for efficient rendering. Instead of sending vertex 
 // * data repeatedly to the GPU, you store this data in a VBO, which improves performance.

 // ^ 3.VAO (Vertex Array Object) 
 // * The VAO organizes how vertex data will be read from memory. 
 // * It maintains references to the VBOs and defines how this data will be interpreted by the GPU. 
 // * By configuring the VAO, you tell the GPU which vertex buffers to use and how to interpret the data 
 // * contained in these buffers (e.g., what the positions, colors, etc. are).


// ^ 4. Shaders
// * Shaders are programs executed by the GPU that control the rendering process. There are main types of shaders:
// * Vertex Shader: This shader is responsible for processing the vertices. 
// * It receives data from the vertices (such as positions and colors), manipulates them (for example, transforming the coordinates to screen space) 
// * and passes them to the next stage of the graphics pipeline.
// * Fragment Shader: This shader is responsible for the final color of each pixel (fragment). 
// * It is executed for each fragment generated in the rasterization process (when the geometry of the object is converted to pixels). 
// * The fragment shader determines the final color based on data such as texture and light.

typedef struct RomEngine {

    Window* window;
    Shader* shader;

    unsigned int VAO;
    unsigned int VBO; // ? VBO (Vertex Buffer Object) is a memory buffer to hold the vertices data.
    unsigned int EBO; // ? VAO (Vertex Array Object) handles how the vertices data are read from memory.
    unsigned int texture;
    unsigned int textures[NUMBER_OF_TEXTURES];
    unsigned int texturesCounter;
    bool drawAsWireframe;
    bool shadersInitialized;
    void (*resize_callback)(GLFWwindow* window, int width, int height);
    void (*render_loop)(struct RomEngine* e);
    void (*release)(struct RomEngine* e);
    void (*log_engine)(struct RomEngine* e);

} RomEngine;

void log_textures(RomEngine *e){
    printf("[TEXTURES_ARRAY] \n");
    for(size_t k = 0; k < e->texturesCounter; k++){
        printf("[%ld] -> %d\n", k, e->textures[k]);
    }
}

void log_engine(RomEngine *e){

    printf("[SHADER_PROGRAM] %d\n", e->shader->shaderProgram);
    printf("[VAO] %d\n", e->VAO);
    printf("[VBO] %d\n", e->VBO);
    printf("[EBO] %d\n", e->EBO);
    printf("[TEXTURE] %d\n", e->texture);
    log_textures(e);

}


void resize_callback(GLFWwindow* window, int width, int height){

    glViewport(0, 0, width, height);

}

void process_key_press(Window *w){
    if(glfwGetKey(w->view, GLFW_KEY_ESCAPE) == GLFW_PRESS){     
        printf("Window should close -> True!\n");   
        glfwSetWindowShouldClose(w->view, true);
    }
   
}

void render_loop(RomEngine* engine){
    while(!glfwWindowShouldClose(engine->window->view)){

        process_key_press(engine->window);

        glClearColor(engine->window->RGBA[0], engine->window->RGBA[1], engine->window->RGBA[2], engine->window->RGBA[3]);
        glClear(GL_COLOR_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, engine->textures[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, engine->textures[1]);

        glUseProgram(engine->shader->shaderProgram);

        glBindVertexArray(engine->VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(engine->window->view);
        glfwPollEvents();
    }


}

void release(RomEngine* e){
    glDeleteVertexArrays(1, &e->VAO);
    glDeleteBuffers(1, &e->VBO);
    glDeleteProgram(e->shader->shaderProgram);
    glfwTerminate();

}

// ? initialize the window and the GLAD.
RomEngine init_context(int width, int height, const char *title, float RGBA[3], bool drawAsWireframe){
        
        init_glfw_abstract_context();

        RomEngine context = {0};

        // ^ here we allocate to the window since the init_context returns a RomEngine.
        context.window = (Window *)malloc(sizeof(Window));
        if(context.window == NULL){
        
            perror("Failed to allocate memory for Window");
            glfwTerminate();
            return context;
        
        }

        context.shader = (Shader*)malloc(sizeof(Shader));
        if(context.shader == NULL){
            perror("Failed to allocate memory for context.shader");
            glfwTerminate();
            return context;
        }

        context.window->width = width;
        context.window->height = height;
        context.window->title = title;

        context.window->RGBA[0] = RGBA[0];
        context.window->RGBA[1] = RGBA[1];
        context.window->RGBA[2] = RGBA[2];
        context.window->RGBA[3] = RGBA[3];

        context.VAO = 0;
        context.VBO = 0;
        context.shader->shaderProgram = 0;
    


        context.window->view = glfwCreateWindow(width, height, title, NULL, NULL);
        if(context.window->view == NULL){
            perror("Failed to create GLFW Window.");
            glfwTerminate();
            return context;
        } 


        glfwMakeContextCurrent(context.window->view);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            perror("Failed to initialize GLAD");
            return context;
        }  

        
        // ? set the visible viewport.
        //* We could actually set the 
        //*viewport dimensions at values smaller than GLFW's dimensions; 
        //*then all the OpenGL rendering would be displayed in a smaller window 
        //*and we could for example display other elements outside the OpenGL viewport. 
        glViewport(0, 0, width, height);

        context.drawAsWireframe = drawAsWireframe;
        if(drawAsWireframe){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }

        // ? initialize the methods.
        context.resize_callback = resize_callback;
        glfwSetFramebufferSizeCallback(context.window->view, context.resize_callback);
        context.render_loop = render_loop;
        context.release = release;
        context.log_engine = log_engine;
        context.texture = 0;
        context.texturesCounter = 0;


        return context;
}


#endif 