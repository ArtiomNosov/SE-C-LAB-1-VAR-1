extern "C" {
#define DEBUG
#include <stdio.h>
#include "Integer.h"
#include "Double.h"
#include "Vector.h"
#include "Complex.h"

    typedef void(*printFunction)(IObject*);

    void printInteger(IInteger* integer)
    {
        printDubug("test-7\n");
        integer->getX(integer);
        printDubug("test-5\n");
        printf("Integer: %d ", integer->getX(integer));
        // printf("test-6\n");
    }

    void printDouble(IDouble* doubleObj)
    {
        doubleObj->getX(doubleObj);
        printf("Double: %f ", doubleObj->getX(doubleObj));
    }

    void printVector(IVector* vector, printFunction print)
    {
        printf("Vector\n");
        // printf("test-2\n");
        size_t size = vector->getSize(vector);
        for (size_t i = 0; i < size; i++) {
            // printf("test-3\n");
            IObject* current = (IObject*)vector->get(vector, i);
            // printf("test-4\n");
            print(current);
        }
        printf("\n");
    }

    void printComplex(IComplex* complex)
    {
        printf("Complex: %f %f ", complex->getX(complex), complex->getY(complex));
    }

    int main()
    {
        // IObject* object = NewObject();
        // object->Delete(object);
        // IRing* ring = NewRing();
        // DeleteRing(ring);
        IRing* integer1 = (IRing*)NewInteger(1);
        IRing* integer2 = (IRing*)NewInteger(2);
        printf("Integer test sum\n");
        IRing* res = integer1->addition(integer1, integer2);
        printInteger((IInteger*)res);

        printDubug("test-res-1\n");
        int a = ((IInteger*)res)->getX((IInteger*)res);
        printDubug("%d\n", a);
        printDubug("test-res-2\n");

        printDubug("test-copyInteger-1\n");
        printf("Integer test copy\n");
        IInteger* copyInteger = (IInteger*)((IObject*)res)->Copy((IObject*)res);
        int b = copyInteger->getX(copyInteger);
        printDubug("%d\n", b);
        printDubug("test-copyInteger-2\n");

        printDubug("Size of IInteger*: %d\n", (int)sizeof(IInteger*));
        printDubug("Size of IRing*: %d\n", (int)sizeof(IRing*));

        printf("Vector integer test create\n");
        printf("\n");
        IVector* vector = NewVector(10, res);
        printDubug("test-1\n");
        IRing* firstElem = vector->get(vector, 0);
        printDubug("firstElem: %d\n", (int)firstElem);
        printDubug("test-firstElem-1\n");
        printf("Vector integer test addition\n");
        IRing* test = firstElem->addition(firstElem, firstElem);
        printDubug("test-firstElem-3\n");
        int k = ((IInteger*)test)->getX((IInteger*)test);
        // int k = ((IInteger*)firstElem)->getX((IInteger*)firstElem);
        printDubug("test-firstElem-2\n");
        printDubug("Integer %d\n", k);
        printInteger((IInteger*)firstElem);
        printf("\n");
        printVector(vector, (printFunction)printInteger);

        IVector* vector2 = NewVector(10, res);
        printVector(vector2, (printFunction)printInteger);

        IVector* vector3 = vector->addition(vector, vector2);
        printVector(vector3, (printFunction)printInteger);
        printf("Vector integer test scalarProduct\n");
        IRing* ring = vector->scalarProduct(vector, vector2);
        IInteger* integerResult = (IInteger*)ring;
        printInteger(integerResult);

        // Создать double
        IRing* doubleObj1 = (IRing*)NewDouble(0.5);
        printf("\n");
        printDouble((IDouble*)doubleObj1);
        printf("Double test addition\n");
        // Сложить double
        IRing* doubleObj2 = (IRing*)NewDouble(0.5);
        IRing* doubleObj3 = doubleObj2->addition(doubleObj1, doubleObj2);
        printf("\n");
        printDouble((IDouble*)doubleObj3);
        // Умножить double
        printf("Double test multiplication\n");
        IRing* doubleObj4 = doubleObj2->multiplication(doubleObj1, doubleObj2);
        printf("\n");
        printDouble((IDouble*)doubleObj4);
        // Вектор double
        printf("Vector double test create\n");
        IVector* vectorDouble1 = NewVector(2, doubleObj1);
        printf("\n");
        printVector(vectorDouble1, (printFunction)printDouble);
        // Вектор double сложить
        printf("Vector double test addition\n");
        IVector* vectorDouble2 = NewVector(2, doubleObj3);
        printVector(vectorDouble2, (printFunction)printDouble);
        IVector* vectorDouble3 = vectorDouble1->addition(vectorDouble1, vectorDouble2);
        printVector(vectorDouble3, (printFunction)printDouble);
        // Вектор double умножить
        printf("Vector double test scalarProduct\n");
        IRing* iRingVectorDouble4 = vectorDouble1->scalarProduct(vectorDouble1, vectorDouble2);
        printDouble((IDouble*)iRingVectorDouble4);

        // Создать Complex
        printf("Complex create\n");
        printf("\n");
        IRing* complex1 = (IRing*)NewComplex((IDouble*)doubleObj1, (IDouble*)doubleObj2);
        printf("\n");
        printComplex((IComplex*)complex1);
        // Сложить Complex
        printf("Complex addition\n");
        IRing* complex2 = (IRing*)NewComplex((IDouble*)doubleObj2, (IDouble*)doubleObj3);
        IRing* complex3 = (IRing*)complex1->addition(complex1, complex2);
        printf("\n");
        printComplex((IComplex*)complex3);
        // Умножить Complex
        printf("Complex multiplication\n");
        IRing* complex4 = complex1->multiplication(complex1, complex2);
        printf("\n");
        printComplex((IComplex*)complex4);
        // Вектор Complex
        printf("Vector complex create\n");
        IVector* vectorComplex1 = NewVector(2, complex1);
        printf("\n");
        printVector(vectorComplex1, (printFunction)printComplex);
        // Вектор Complex сложить
        printf("Vector complex addition\n");
        IVector* vectorComplex2 = NewVector(2, complex2);
        printVector(vectorComplex2, (printFunction)printComplex);
        IVector* vectorComplex3 = vectorComplex1->addition(vectorComplex1, vectorComplex2);
        printVector(vectorComplex3, (printFunction)printComplex);
        // Вектор Complex умножить
        printf("Vector complex scalarProduct\n");
        IRing* iRingVectorComplex4 = vectorComplex1->scalarProduct(vectorComplex1, vectorComplex2);
        printComplex((IComplex*)iRingVectorComplex4);
        return 0;
    }

}