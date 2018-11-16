#pragma once

#define PyObject_HEAD \
    int refCount; \
    struct tagPyTypeObject *type


#define PyObject_HEAD_INIT(typePtr) \
    0, typePtr


typedef struct tagPyObject
{
    PyObject_HEAD;
} PyObject;
