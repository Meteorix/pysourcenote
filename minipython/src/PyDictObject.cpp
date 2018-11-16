#include "PyDictObject.hpp"


PyTypeObject PyDict_Type = {
    PyObject_HEAD_INIT(&PyType_Type),
    "dict",
    dict_print,
    0,
    0,
};


PyObject* PyDict_Create()
{
    PyDictObject* object = new PyDictObject;
    object->refCount = 1;
    object->type = &PyDict_Type;
    return (PyObject*)object;
}


PyObject* PyDict_GetItem(PyObject* target, PyObject* key)
{
    long keyHashValue = (key->type)->hash(key);
    std::map<long, PyObject*>& dict = ((PyDictObject*)target)->dict;
    std::map<long, PyObject*>::iterator it = dict.find(keyHashValue);
    std::map<long, PyObject*>::iterator end = dict.end();
    if (it == end)
    {
        return NULL;
    }
    return it->second;
}


PyObject* PyDict_SetItem(PyObject* target, PyObject* key, PyObject* value)
{
    long keyHashValue = (key->type)->hash(key);
    PyDictObject* dictObject = (PyDictObject*)target;
    (dictObject->dict)[keyHashValue] = value;
    return 0;
}


static void dict_print(PyObject* object)
{
    PyDictObject* dictObject = (PyDictObject*)object;
    std::map<long, PyObject*>& dict = ((PyDictObject*)object)->dict;
    std::map<long, PyObject*>::iterator it = dict.begin();
    std::map<long, PyObject*>::iterator end = dict.end();
    
    printf("{");
    for (; it != end; ++it)
    {
        // print key
        printf("%ld: ", it->first);
        // print value
        PyObject* value = it->second;
        (value->type)->print(value);
        printf(", ");
    }
    printf("}\n");
}
