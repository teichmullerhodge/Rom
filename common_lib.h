#ifndef COMMON_LIB_H
#define COMMON_LIB_H

#include <stdio.h>
#include <stdlib.h>



char *read_file_contents(const char *path){


    FILE *filePointer = fopen(path, "rb");
    if(!filePointer){
        perror("Failed to open the file!\n");
        return NULL;
    }

    fseek(filePointer, 0, SEEK_END);
    long fileSize = ftell(filePointer);
    fseek(filePointer, 0, SEEK_SET);

    if(fileSize < 0){
        perror("Failed to determine file size");
        fclose(filePointer);
        return NULL;
    }

    char *buffer = (char *)malloc(fileSize + 1); 
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(filePointer);
        return NULL;
    }

    size_t bytes = fread(buffer, 1, fileSize, filePointer);
    if (bytes < (size_t)fileSize) {
        perror("Failed to read file");
        free(buffer);
        fclose(filePointer);
        return NULL;
    }

    buffer[fileSize] = '\0';        

    fclose(filePointer); //free pointer.
    return buffer;

}

  
#endif