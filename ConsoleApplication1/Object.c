#include "Object.h"

// Определение структуры ("объекта")
typedef struct Object {
    // Родительская структура ("класс")
    /*Parent super;*/
    // Поля
    int x;
    // Методы внутри "интерфейся"
    IObject interface;
} Object;

/* Функций доступные только внутри структуры "объект" */

// Если необходимо, то определение ("переопределение") функций ("методов") родетельской структуры ("класса")
/* Комментарий: в случае попытки использования ООП в чистом Си, необходимо для 
каждой отличающейся по логике работы структуры реализовывать все методы 
методы базовой структуры, которая композируется во все следующие */
IObject* copyObject(IObject* interface)
{
    return NewObject();
}

void freeObject(Object* object)
{
    free(object);
}

void deleteObject(IObject* interface)
{
    freeObject(interface->object);
}

// Определение функций ("методов") структуры ("класса")
/* Функций доступные только внутри структуры "объект" */

void InitializeObject(Object* object)
{
    // Публичные методы
    object->interface.object = object;
    object->interface.Copy = copyObject;
    object->interface.Delete = deleteObject;
}

IObject* NewObject()
{ 
    Object* object = (Object*) calloc(1, sizeof(Object));
    InitializeObject(object);
    return &(object->interface);
}