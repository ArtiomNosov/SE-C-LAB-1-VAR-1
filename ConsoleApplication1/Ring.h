#ifndef RING_H 
#define RING_H 

// Подключение стандартных библиотек

// Подключение наших библиотек
#include "Object.h"

// Объявление структуры "объект"
typedef struct Ring Ring;
typedef struct IRing IRing;

typedef IRing* (*OperationRing)(IRing*, IRing*);

// Объявление и определение структуры "интерфейс"
typedef struct IRing {
    IObject super;
    OperationRing addition;
    OperationRing multiplication;
    Ring* object;
} IRing;

IRing* NewRing();

void DeleteRing(IRing* interface);

#endif