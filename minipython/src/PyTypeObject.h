#pragma once
#include "PyObject.h"

typedef void (*PrintFunc) (PyObject* object);
typedef PyObject* (*AddFunc) (PyObject* left, PyObject* right);
typedef long (*HashFunc) (PyObject* object);


typedef struct tagPyTypeObject
{
    PyObject_HEAD;
    char* name;
    PrintFunc print;
    AddFunc add;
    HashFunc hash;
} PyTypeObject;


extern PyTypeObject PyType_Type;

