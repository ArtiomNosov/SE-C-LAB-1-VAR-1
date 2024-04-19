#include "Vector.h"

// Определение структуры ("объекта")
typedef struct Vector {
    // Поля
    size_t size;
    IRing** array;
    // Методы внутри "интерфейся"
    IVector interface;
} Vector;

/* Функций доступные только внутри структуры "объект" */
IVector* copyVector(IVector* interface)
{
    IRing* fill = NewRing();
    size_t size = interface->getSize(interface);
    IVector* res = NewVector(size, fill);
    for (size_t i = 0; i < size; i++) {
        IObject* current = (IObject*)interface->object->array[i];
        IRing* previous = res->object->array[i];
        res->object->array[i] = (IRing*)current->Copy(current);
        DeleteRing(previous);
    }
    return res;
}

// Если необходимо, то определение ("переопределение") функций ("методов") родетельской структуры ("класса")
/* Комментарий: в случае попытки использования ООП в чистом Си, необходимо для 
каждой отличающейся по логике работы структуры реализовывать все методы 
методы базовой структуры, которая композируется во все следующие */

size_t getSize(IVector* interface)
{
    printDubug("IVector getSize\n");
    return interface->object->size;
}

IRing* get(IVector* interface, size_t n)
{
    printDubug("IVector get\n");
    return (interface->object->array)[n];
}

IVector* additionVector(IVector* ring1, IVector* ring2)
{
    IVector* res = (IVector*)((IObject*)ring1)->Copy((IObject*)ring1);
    size_t size = res->getSize(res);
    for (size_t i = 0; i < size; i++) {
        IRing* elem1 = ring1->object->array[i];
        IRing* elem2 = ring2->object->array[i];
        IRing* current = elem1->addition(elem1, elem2);
        IRing* previous = res->object->array[i];
        res->object->array[i] = current;
        IObject* object = (IObject*)previous;
        object->Delete(object);
    }
    return res;
}

IRing* scalarProduct(IVector* ring1, IVector* ring2)
{
    IRing* elem1 = ring1->object->array[0];
    IRing* elem2 = ring2->object->array[0];
    IRing* current = elem1->multiplication(elem1, elem2);
    IRing* res = current;
    IRing* resPrevious = res;

    size_t size = ring1->getSize(ring1);
    for (size_t i = 1; i < size; i++) {
        resPrevious = res;
        elem1 = ring1->object->array[i];
        elem2 = ring2->object->array[i];
        current = elem1->multiplication(elem1, elem2);
        res = res->addition(res, current);

        DeleteRing(resPrevious);
        DeleteRing(current);
    }
    return res;
}

// Определение функций ("методов") структуры ("класса")
void freeVector(Vector* vector)
{
    free(vector->array);
    free(vector);
}

void InitializeVector(Vector* vector)
{
    vector->interface.object = vector;
    // Публичные методы
    vector->interface.get = get;
    vector->interface.getSize = getSize;

    vector->interface.addition = additionVector;
    vector->interface.scalarProduct = (ScalarProduct)scalarProduct;
    IObject* iobject = (IObject*)&(vector->interface);
    iobject->Copy = (CopyMethod)copyVector;
}

IVector* NewVector(size_t size, IRing* fill)
{ 
    Vector* vector = (Vector*)calloc(1, sizeof(Vector));
    if (vector == NULL)
        return NULL;
    vector->size = size;
    vector->array = (IRing**)calloc(size, sizeof(IRing*));
    if (vector->array == NULL)
        return NULL;
    for (size_t i = 0; i < size; i++) {
        printDubug("IVector NewVector for %d\n", (int)i);
        IRing* current = (IRing*)((IObject*)fill)->Copy((IObject*)fill);
        (vector->array)[i] = current;
    }
    
    InitializeVector(vector);
    return &(vector->interface);
}

void DeleteVector(IVector* interface)
{
    size_t size = interface->object->size;
    for (size_t i = 0; i < size; i++) {
        IObject* current = (IObject*)interface->object->array[i];
        current->Delete(current);
    }
    freeVector(interface->object);
}