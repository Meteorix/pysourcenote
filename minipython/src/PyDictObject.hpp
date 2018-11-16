#pragma once
#include "PyTypeObject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>


typedef struct tagPyDictObject
{
    PyObject_HEAD;
    std::map<long, PyObject*> dict;
} PyDictObject;


PyObject* PyDict_Create();
PyObject* PyDict_GetItem(PyObject* target, PyObject* key);
PyObject* PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value);
static void dict_print(PyObject* object);

extern PyTypeObject PyDict_Type;
