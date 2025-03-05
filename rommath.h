#ifndef ROMMATH_H
#define ROMMATH_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {

    float x;
    float y;


} Vector2D;

typedef struct {

    float x;
    float y;
    float z;


} Vector3D;


typedef struct {

    float x;
    float y;
    float z;
    float w;

} Vector4D;

enum VecOperation {
    Add,
    Mul,
    Sub,
    Div
};

#define VECTOR_SCALAR(v, axis, op, value) v->axis = v->axis op value 

void scalar2d(Vector2D *v, enum VecOperation operation, float value){
    if(value == 0 && operation == Div){
        perror("Division by zero is not allowed!");
        return;
    }
    switch(operation) {
        case Add:
            VECTOR_SCALAR(v, x, +, value);
            VECTOR_SCALAR(v, y, +, value);            
            break;
        case Mul:
            VECTOR_SCALAR(v, x, *, value);
            VECTOR_SCALAR(v, y, *, value);            
            break;
        case Sub:
            VECTOR_SCALAR(v, x, -, value);
            VECTOR_SCALAR(v, y, -, value);            
            break;
        case Div:
            VECTOR_SCALAR(v, x, /, value);
            VECTOR_SCALAR(v, y, /, value);            
            break;
    }
}

void scalar3d(Vector3D *v, enum VecOperation operation, float value){
    if(value == 0 && operation == Div){
        perror("Division by zero is not allowed!");
        return;
    }
    switch(operation) {
        case Add:
            VECTOR_SCALAR(v, x, +, value);
            VECTOR_SCALAR(v, y, +, value);            
            VECTOR_SCALAR(v, z, +, value);            
            break;
        case Mul:
            VECTOR_SCALAR(v, x, *, value);
            VECTOR_SCALAR(v, y, *, value);            
            VECTOR_SCALAR(v, z, *, value);            
            break;
        case Sub:
            VECTOR_SCALAR(v, x, -, value);
            VECTOR_SCALAR(v, y, -, value);            
            VECTOR_SCALAR(v, z, -, value);            
            break;
        case Div:
            VECTOR_SCALAR(v, x, /, value);
            VECTOR_SCALAR(v, y, /, value);            
            VECTOR_SCALAR(v, z, /, value);            
            break;
    }
}

void scalar4d(Vector4D *v, enum VecOperation operation, float value){
    if(value == 0 && operation == Div){
        perror("Division by zero is not allowed!");
        return;
    }
    switch(operation) {
        case Add:
            VECTOR_SCALAR(v, x, +, value);
            VECTOR_SCALAR(v, y, +, value);            
            VECTOR_SCALAR(v, z, +, value);            
            VECTOR_SCALAR(v, w, +, value);            
            break;
        case Mul:
            VECTOR_SCALAR(v, x, *, value);
            VECTOR_SCALAR(v, y, *, value);            
            VECTOR_SCALAR(v, z, *, value);            
            VECTOR_SCALAR(v, w, *, value);            
            break;
        case Sub:
            VECTOR_SCALAR(v, x, -, value);
            VECTOR_SCALAR(v, y, -, value);            
            VECTOR_SCALAR(v, z, -, value);            
            VECTOR_SCALAR(v, w, -, value);            
            break;
        case Div:
            VECTOR_SCALAR(v, x, /, value);
            VECTOR_SCALAR(v, y, /, value);            
            VECTOR_SCALAR(v, z, /, value);
            VECTOR_SCALAR(v, w, /, value);                        
            break;
    }
}

// ! In those cases function overloading are pretty handy.

#endif