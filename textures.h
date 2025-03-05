#ifndef TEXTURES_H
#define TEXTURES_H
#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"
#include "rom_engine.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#define CONTAINER_PATH "./assets/container.jpg"
#define SMILEY_PATH "./assets/awesomeface.png"

void load_texture(RomEngine *engine, const char *filePath, unsigned int index, bool usesRGBA, bool flipImage){
    
    glGenTextures(1, &engine->textures[index]);      
    if (engine->textures[index] == 0) {
        fprintf(stderr, "Failed to generate texture ID!\n");
        return;
    }    
    glBindTexture(GL_TEXTURE_2D, engine->textures[index]);  
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, numberOfChannels;

    if(flipImage){
        stbi_set_flip_vertically_on_load(true); 
    }

    unsigned char *data = stbi_load(filePath, &width, &height, &numberOfChannels, 0);
    if(data == NULL){
        perror("Failed loading image data.\n");
        return;
    }

    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    if(usesRGBA){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    }
    else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    }
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    engine->texturesCounter = index + 1;
}

#endif // !TEXTURES_H
