#include "Double.h"

// Определение структуры ("объекта")
typedef struct Double {
    // Поля
    double x;
    // Методы внутри "интерфейся"
    IDouble interface;
} Double;

/* Функций доступные только внутри структуры "объект" */
IDouble* additionDouble(IDouble* ring1, IDouble* ring2)
{
    printDubug("IDouble additionDouble\n");
    IDouble* res = NewDouble(0);
    res->object->x = ring1->object->x + ring2->object->x;
    return res;
}

IDouble* multiplicationDouble(IDouble* ring1, IDouble* ring2)
{
    IDouble* res = NewDouble(0);
    res->object->x = ring1->object->x * ring2->object->x;
    return res;
}

void freeDouble(Double* doubleObj)
{
    free(doubleObj);
}

void deleteDouble(IDouble* interface)
{
    DeleteRing(&(interface->super));
    freeDouble(interface->object);
}

IDouble* copyDouble(IDouble* interface)
{
    printDubug("IDouble copyDouble\n");
    return NewDouble(interface->object->x);
}

double getDouble(IDouble* interface)
{
    printDubug("IDouble getX\n");
    return interface->object->x;
}

void initializeDouble(Double* doubleObj)
{
    doubleObj->interface.object = doubleObj;
    doubleObj->interface.getX = getDouble;
    // Публичные методы
    IRing* iring = (IRing*)&(doubleObj->interface);
    iring->addition = (OperationRing)additionDouble;
    iring->multiplication = (OperationRing)multiplicationDouble;

    IObject* iobject = (IObject*)iring;
    iobject->Copy = (CopyMethod)copyDouble;
    iobject->Delete = (DeleteMethod)deleteDouble;
}

// Если необходимо, то определение ("переопределение") функций ("методов") родетельской структуры ("класса")
/* Комментарий: в случае попытки использования ООП в чистом Си, необходимо для
каждой отличающейся по логике работы структуры реализовывать все методы
методы базовой структуры, которая композируется во все следующие */

// Определение функций ("методов") структуры ("класса")

IDouble* NewDouble(double x)
{
    IRing* iring = NewRing();
    Double* doubleObj = (Double*)calloc(1, sizeof(Double));
    if (doubleObj == NULL)
        return NULL;
    doubleObj->interface.super = *iring;
    doubleObj->x = x;
    initializeDouble(doubleObj);
    return &(doubleObj->interface);
}