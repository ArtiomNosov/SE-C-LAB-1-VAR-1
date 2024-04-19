#ifndef INTEGER_H 
#define INTEGER_H 

// Подключение стандартных библиотек

// Подключение наших библиотек
#include "Ring.h"

// Объявление структуры "объект"
typedef struct Integer Integer;
typedef struct IInteger IInteger;

// Объявление и определение структуры "интерфейс"
typedef struct IInteger {
    IRing super;
    int (*getX)(IInteger*);
    Integer* object;
} IInteger;

IInteger* NewInteger(int);

#endif