#ifndef OBJECT_H 
#define OBJECT_H 

// Подключение стандартных библиотек
#include <stdlib.h>

// Подключение наших библиотек
#include "Debug.h"

// Объявление структуры "объект"
typedef struct Object Object;
typedef struct IObject IObject;
typedef IObject*(*CopyMethod)(IObject*);
typedef void(*DeleteMethod)(IObject*);

// Объявление и определение структуры "интерфейс"
typedef struct IObject {
    Object* object;
    CopyMethod Copy;
    DeleteMethod Delete;
} IObject;

// Публичные методы
IObject* NewObject();

#endif