#include "Complex.h"

// Определение структуры ("объекта")
typedef struct Complex {
    // Поля
    IDouble* x;
    IDouble* y;
    // Методы внутри "интерфейся"
    IComplex interface;
} Complex;

/* Функций доступные только внутри структуры "объект" */
IComplex* additionComplex(IComplex* ring1, IComplex* ring2)
{
    printDubug("IComplex additionComplex\n");
    IDouble* x = NewDouble(ring1->getX(ring1) + ring2->getX(ring2));
    IDouble* y = NewDouble(ring1->getY(ring1) + ring2->getY(ring2));
    IComplex* res = NewComplex(x, y);
    // TODO: чистить память
    return res;
}

IComplex* multiplicationComplex(IComplex* ring1, IComplex* ring2)
{
    double a1 = ring1->getX(ring1);
    double b1 = ring1->getY(ring1);
    double a2 = ring1->getX(ring2);
    double b2 = ring1->getY(ring2);
    IDouble* x = NewDouble(a1*a2 - b1*b2);
    IDouble* y = NewDouble(a1*b2 + b1*a2);
    IComplex* res = NewComplex(x, y);
    // TODO: чистить память
    return res;
}

void freeComplex(Complex* complexObj)
{
    free(complexObj);
}

void deleteComplex(IComplex* interface)
{
    DeleteRing(&(interface->super));
    freeComplex(interface->object);
}

IComplex* copyComplex(IComplex* interface)
{
    printDubug("IComplex copyComplex\n");
    IDouble* x = NewDouble(interface->getX(interface));
    IDouble* y = NewDouble(interface->getY(interface));
    return NewComplex(x, y);
}

double getComlexX(IComplex* interface)
{
    return interface->object->x->getX(interface->object->x);
}

double getComlexY(IComplex* interface)
{
    return interface->object->y->getX(interface->object->y);
}

void initializeComplex(Complex* complexObj)
{
    complexObj->interface.object = complexObj;
    complexObj->interface.getX = getComlexX;
    complexObj->interface.getY = getComlexY;
    // Публичные методы
    IRing* iring = (IRing*)&(complexObj->interface);
    iring->addition = (OperationRing)additionComplex;
    iring->multiplication = (OperationRing)multiplicationComplex;

    IObject* iobject = (IObject*)iring;
    iobject->Copy = (CopyMethod)copyComplex;
    iobject->Delete = (DeleteMethod)deleteComplex;
}

// Если необходимо, то определение ("переопределение") функций ("методов") родетельской структуры ("класса")
/* Комментарий: в случае попытки использования ООП в чистом Си, необходимо для
каждой отличающейся по логике работы структуры реализовывать все методы
методы базовой структуры, которая композируется во все следующие */

// Определение функций ("методов") структуры ("класса")

IComplex* NewComplex(IDouble* x, IDouble* y)
{
    IRing* iring = NewRing();
    Complex* complexObj = (Complex*)calloc(1, sizeof(Complex));
    if (complexObj == NULL)
        return NULL;
    complexObj->interface.super = *iring;
    IObject* iobject = (IObject*)x;
    complexObj->x = (IDouble*)iobject->Copy((IObject*)x);
    complexObj->y = (IDouble*)iobject->Copy((IObject*)y);
    initializeComplex(complexObj);
    return &(complexObj->interface);
}