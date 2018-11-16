#pragma once
#include "PyTypeObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct tagPyStrObject
{
    PyObject_HEAD;
    int length;
    long hashValue;
    char value[50];
} PyStringObject;


PyObject* PyStr_Create(const char* value);
static void str_print(PyObject* object);
static PyObject* str_add(PyObject* left, PyObject* right);
static long str_hash(PyObject* object);

extern PyTypeObject PyString_Type;
