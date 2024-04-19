#ifndef VECTOR_H 
#define VECTOR_H 

// Подключение стандартных библиотек

// Подключение наших библиотек
#include "Ring.h"

// Объявление структуры "объект"
typedef struct Vector Vector;
typedef struct IVector IVector;
typedef IRing* (*ScalarProduct)(IVector*, IVector*);
typedef IVector* (*AdditionVector)(IVector*, IVector*);

// Объявление и определение структуры "интерфейс"
typedef struct IVector {
    IObject super;
    AdditionVector addition;
    ScalarProduct scalarProduct;
    size_t (*getSize)(IVector*);
    IRing* (*get)(IVector*, size_t);
    Vector* object;
} IVector;

IVector* NewVector(size_t size, IRing* fill);

#endif