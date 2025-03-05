#ifndef MODELS_H
#define MODELS_H

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rom_engine.h"
#include "shaders.h"


typedef struct {

    float vertices[9]; // ? (x,y,z), (x,y,z), (x,y,z) in 3D Space.

} Triangle;



void draw_triangle(RomEngine *e){

    e->log_engine(e);

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    glGenVertexArrays(1, &e->VAO);
    glGenBuffers(1, &e->VBO);
    glGenBuffers(1, &e->EBO);

    glBindVertexArray(e->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, e->VBO);  


     // ? The position data of the triangle does not change, is used a lot, 
     // ? and stays the same for every render call so its usage type should best 
     // ? be GL_STATIC_DRAW. If, for instance, one would have a buffer with data that is 
     // ? likely to change frequently, a usage type of GL_DYNAMIC_DRAW 
     // ? ensures the graphics card will place the data in memory that allows for faster writes. 

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);  


    // e->log_engine(e);


}


void draw_rectangle(RomEngine *e){

        e->log_engine(e);

        glGenVertexArrays(1, &e->VAO);
        glBindVertexArray(e->VAO);
    
        float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  // bottom left
           -0.5f,  0.5f, 0.0f   // top left 
        };
        
        unsigned int indices[] = {  // note that we start from 0!
           0, 1, 3,   // first triangle
           1, 2, 3    // second triangle
        };  


        
        glGenBuffers(1, &e->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, e->VBO);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    
        glGenBuffers(1, &e->EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, e->EBO);  
    
         // ? The position data of the triangle does not change, is used a lot, 
         // ? and stays the same for every render call so its usage type should best 
         // ? be GL_STATIC_DRAW. If, for instance, one would have a buffer with data that is 
         // ? likely to change frequently, a usage type of GL_DYNAMIC_DRAW 
         // ? ensures the graphics card will place the data in memory that allows for faster writes. 
    
        
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 
    
        e->log_engine(e);
}

#endif // !MODELS_H