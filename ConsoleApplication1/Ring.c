#include "Ring.h"

// Определение структуры ("объекта")
typedef struct Ring {
    // Поля

    // Методы внутри "интерфейся"
    IRing interface;
} Vector;

/* Функций доступные только внутри структуры "объект" */
// IRing* addition(IRing* ring1, IRing* ring2)
// {
//     return NewRing();
// }

// IRing* multiplication(IRing* ring1, IRing* ring2)
// {
//     return NewRing();
// }

// Если необходимо, то определение ("переопределение") функций ("методов") родетельской структуры ("класса")
/* Комментарий: в случае попытки использования ООП в чистом Си, необходимо для 
каждой отличающейся по логике работы структуры реализовывать все методы 
методы базовой структуры, которая композируется во все следующие */

// Определение функций ("методов") структуры ("класса")
void FreeRing(Ring* ring)
{
    // free(ring);
}

void InitializeRing(Ring* ring)
{
    ring->interface.object = ring;
    // Публичные методы
    ring->interface.addition;
    ring->interface.multiplication;
}

IRing* NewRing()
{ 
    IObject* iobject = NewObject();
    Ring* ring = (Ring*) calloc(1, sizeof(Ring));
    if (ring == NULL)
        return NULL;
    ring->interface.super = *iobject;
    InitializeRing(ring);
    return &(ring->interface);
}

void DeleteRing(IRing* interface)
{
    // interface->super.Delete(&(interface->super));
    // FreeRing(interface->object);
}