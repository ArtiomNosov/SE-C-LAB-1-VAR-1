#ifndef COMPLEX_H 
#define COMPLEX_H 

// Подключение стандартных библиотек

// Подключение наших библиотек
#include "Object.h"
#include "Double.h"

// Объявление структуры "объект"
typedef struct Complex Complex;
typedef struct IComplex IComplex;

// Объявление и определение структуры "интерфейс"
typedef struct IComplex {
    IRing super;
    double (*getX)(IComplex*);
    double (*getY)(IComplex*);
    Complex* object;
} IComplex;

IComplex* NewComplex(IDouble* x, IDouble* y);
#endif