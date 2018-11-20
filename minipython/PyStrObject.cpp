#include "PyStrObject.h"


PyTypeObject PyString_Type = {
    PyObject_HEAD_INIT(&PyType_Type),
    "str",
    str_print,
    str_add,
    str_hash,
};


PyObject* PyStr_Create(const char* value)
{
    PyStringObject* object = new PyStringObject;
    object->refCount = 1;
    object->type = &PyString_Type;
    object->length = (value == NULL) ? 0 : strlen(value);
    object->hashValue = -1;
    memset(object->value, 0, 50);
    if (value != NULL)
    {
        strcpy(object->value, value);
    }
    return (PyObject*)object;
}


static void str_print(PyObject* object)
{
    printf("%s\n", ((PyStringObject*)object)->value);
}


static PyObject* str_add(PyObject* left, PyObject* right)
{
    PyStringObject* leftStr = (PyStringObject*)left;
    PyStringObject* rightStr = (PyStringObject*)right;
    PyStringObject* result = (PyStringObject*)PyStr_Create(NULL);

    if (result == NULL)
    {
        printf("Memory error when create str");
        exit(1);
    }
    else
    {
        strcpy(result->value, leftStr->value);
        strcat(result->value, rightStr->value);
    }

    // TODO: 数组超长问题
    result->length = leftStr->length + rightStr->length;
    return (PyObject*)result;
}


static long str_hash(PyObject* object)
{
    PyStringObject* strObject = (PyStringObject*)object;
    int len;
    unsigned char* p;
    long x;

    if(strObject->hashValue != -1)
    {
        return strObject->hashValue;
    }
    len = strObject->length;
    p = (unsigned char*)strObject->value;
    x = *p << 7;
    while (--len >= 0)
    {
        x = (1000003 * x) ^ *p++;
    }
    x ^= strObject->length;
    if (x == -1)
    {
        x = -2;
    }
    strObject->hashValue = x;
    return x;
}

