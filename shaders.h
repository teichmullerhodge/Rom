#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h" 
#include "common_lib.h"
#include <stdbool.h>

#define SHADERS_PATH "./shaders/shader.glsl"
#define FRAGMENT_PATH "./shaders/fragment_shader.glsl"




typedef struct Shader {

    unsigned int id;
    const char* shaderSourceCode; // ? contents of a shaderSourceCode file
    const char* fragmentSourceCode; // ? contents of a fragmentSourceCode file

    unsigned int shaderProgram;

    bool(*shaders_compiled)(unsigned int shader, bool printError, bool isShader);
    void(*free_shaders)(struct Shader* s, unsigned int *shadersArray, size_t len);

    void(*use_shader_program)(unsigned int id);
    void(*set_bool)(unsigned int id, const char *name, bool value);
    void(*set_int)(unsigned int id, const char *name, int value);
    void(*set_float)(unsigned int id, const char *name, float value);
    

} Shader;

void use_shader_program(unsigned int id){
    glUseProgram(id);
}

void set_bool(unsigned int id, const char *name, bool value){
    
    glUniform1i(glGetUniformLocation(id, name), (int)value);

}

void set_int(unsigned int id, const char *name, int value){
    
    glUniform1i(glGetUniformLocation(id, name), (int)value);

}

void set_float(unsigned int id, const char *name, float value){
    
    glUniform1f(glGetUniformLocation(id, name), (float)value);

}

void free_shaders(Shader *s, unsigned int *shadersArray, size_t len){
    if(s){
        free((void*)s->shaderSourceCode);
        free((void*)s->fragmentSourceCode);
        free(s);
    }
    for(size_t k = 0; k < len; k++){
        glDeleteShader(shadersArray[k]);
    }
}



bool shaders_compiled(unsigned int shader, bool printError, bool isShader){

    int success;
    char infoLog[512];

    if(isShader){

        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    }
    
    else {
        
        glGetProgramiv(shader, GL_LINK_STATUS, &success);   
    }

    if(!success){
        if(printError && isShader){
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            printf("ERROR::SHADER::VERTER::COMPILATION_FAILED %s\n", infoLog);
            return false;
        }
        if(printError && !isShader){
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
            return false;
        }
        glDeleteShader(shader);  
        return false;
    }

 
    return true;
}



Shader* new_shader(const char* vertexPath, const char* fragmentPath) {

    

    Shader *s = (Shader*)malloc(sizeof(Shader));
    if(s == NULL){
        perror("Failed to allocate memory for shaders");
        return NULL;

    }


    s->shaderSourceCode = read_file_contents(vertexPath);
    s->fragmentSourceCode = read_file_contents(fragmentPath);

    if(!s->shaderSourceCode){
        fprintf(stderr, "Failed to read file: %s\n", vertexPath);
    }
    if(!s->fragmentSourceCode){
        fprintf(stderr, "Failed to read file: %s\n", fragmentPath);
    }



    s->shaders_compiled = shaders_compiled;
    s->free_shaders = free_shaders;
    s->set_bool = set_bool;
    s->set_int = set_int;
    s->set_float = set_float;
        
    return s;
    
}

// ? this is really, really ugly, so the syntax would look like this:
// ? glShaderSource(vertexShader, 1, &((*s)->shaderSourceCode), NULL);    
// ? instead of that, i'm defining this macro ref.

#define ref(x) (*s)
// ? initialize the shaders, returns a boolean indicating a successfull or failure in the initialization.
bool init_shaders(Shader** s, const char *shadersPath, const char *fragmentPath){
    

    ref(s) = new_shader(shadersPath, fragmentPath);
    if(ref(s) == NULL){
        perror("Could not initialize shaders!\n");
        return false;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &(ref(s)->shaderSourceCode), NULL);    
    glCompileShader(vertexShader);

    bool verterShaderCompiled = shaders_compiled(vertexShader, true, true);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &(ref(s)->fragmentSourceCode), NULL);
    glCompileShader(fragmentShader);

    bool fragmentShaderCompiled = shaders_compiled(fragmentShader, true, true);


    ref(s)->shaderProgram = glCreateProgram();
    ref(s)->id = ref(s)->shaderProgram; 
       
    glAttachShader(ref(s)->shaderProgram, vertexShader);
    glAttachShader(ref(s)->shaderProgram, fragmentShader);
    glLinkProgram(ref(s)->shaderProgram);

    bool shaderProgramCompiled = shaders_compiled(ref(s)->shaderProgram, true, false);
    
    if(verterShaderCompiled && fragmentShaderCompiled && shaderProgramCompiled){
        printf("Compilations ok!\n");        
    }

    else {

        printf("Errors in compilation!\n");
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);    
        glDeleteProgram(ref(s)->shaderProgram);
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ref(s)->use_shader_program = use_shader_program;

    return true;

}


#endif