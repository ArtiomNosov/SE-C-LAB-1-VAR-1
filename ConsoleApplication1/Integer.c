#include "Integer.h"

// Определение структуры ("объекта")
typedef struct Integer {
    // Поля
    int x;
    // Методы внутри "интерфейся"
    IInteger interface;
} Integer;

/* Функций доступные только внутри структуры "объект" */
IInteger* additionInteger(IInteger* ring1, IInteger* ring2)
{
    printDubug("IInteger additionInteger\n");
    IInteger* res = NewInteger(0);
    res->object->x = ring1->object->x + ring2->object->x;
    return res;
}

IInteger* multiplication(IInteger* ring1, IInteger* ring2)
{
    IInteger* res = NewInteger(0);
    res->object->x = ring1->object->x * ring2->object->x;
    return res;
}

void freeInteger(Integer* integer)
{
    free(integer);
}

void deleteInteger(IInteger* interface)
{
    DeleteRing(&(interface->super));
    freeInteger(interface->object);
}

IInteger* copyInteger(IInteger* interface)
{
    printDubug("IInteger copyInteger\n");
    return NewInteger(interface->object->x);
}

int getX(IInteger* interface)
{
    printDubug("IInteger getX\n");
    return interface->object->x;
}

void initializeInteger(Integer* integer)
{
    integer->interface.object = integer;
    integer->interface.getX = getX;
    // Публичные методы
    IRing* iring = (IRing*)&(integer->interface);
    iring->addition = (OperationRing)additionInteger;
    iring->multiplication = (OperationRing)multiplication;

    IObject* iobject = (IObject*)iring;
    iobject->Copy = (CopyMethod)copyInteger;
    iobject->Delete = (DeleteMethod)deleteInteger;
}

// Если необходимо, то определение ("переопределение") функций ("методов") родетельской структуры ("класса")
/* Комментарий: в случае попытки использования ООП в чистом Си, необходимо для 
каждой отличающейся по логике работы структуры реализовывать все методы 
методы базовой структуры, которая композируется во все следующие */

// Определение функций ("методов") структуры ("класса")

IInteger* NewInteger(int x)
{ 
    IRing* iring = NewRing();
    Integer* integer = (Integer*) calloc(1, sizeof(Integer));
    if (integer == NULL)
        return NULL;
    integer->interface.super = *iring;
    integer->x = x;
    initializeInteger(integer);
    return &(integer->interface);
}