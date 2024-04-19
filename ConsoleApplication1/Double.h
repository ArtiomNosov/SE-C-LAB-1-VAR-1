#ifndef DOUBLE_H 
#define DOUBLE_H 

// Подключение стандартных библиотек

// Подключение наших библиотек
#include "Ring.h"

// Объявление структуры "объект"
typedef struct Double Double;
typedef struct IDouble IDouble;

// Объявление и определение структуры "интерфейс"
typedef struct IDouble {
    IRing super;
    double (*getX)(IDouble*);
    Double* object;
} IDouble;

IDouble* NewDouble(double x);

#endif