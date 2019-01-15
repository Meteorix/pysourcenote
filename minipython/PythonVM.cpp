#include "PythonVM.h"

void ExecutePrint(string symbol);
void ExecuteAdd(string& target, string& source);
bool IsSouceAllDigit(string& source);
PyObject* GetObjectBySymbol(const string& symbol);


PyDictObject* m_LocalEnvironment = (PyDictObject*)PyDict_Create();



void ExecuteCommand(string& command)
{
    string::size_type pos = 0;    
    if ((pos = command.find("print ")) != string::npos)
    {   
        string target = command.substr(6);
        trim(target);
        ExecutePrint(target);
    }
    else if ((pos = command.find("=")) != string::npos)
    {
        string target = command.substr(0, pos);
        string source = command.substr(pos + 1);
        trim(target);
        trim(source);
        ExecuteAdd(target, source);
    }
    else if ((pos = command.find("__local__")) != string::npos)
    {
        m_LocalEnvironment->type->print((PyObject*)m_LocalEnvironment);
    }
    else
    {   
        string target = command;
        rtrim(target);
        ExecutePrint(target);
    }
}


void ExecutePrint(string symbol)
{
    PyObject* object = GetObjectBySymbol(symbol);
    if (object != NULL)
    {
        object->type->print(object);
    }
}


void ExecuteAdd(string& target, string& source)
{
    string::size_type pos;
    PyObject* key = PyStr_Create(target.c_str());
    
    if (IsSouceAllDigit(source))
    {
        PyObject* intValue = PyInt_Create(atoi(source.c_str()));
        PyDict_SetItem((PyObject*)m_LocalEnvironment, key, intValue);
    }
    else if (source.find("\"") != string::npos)
    {
        PyObject* strValue = PyStr_Create(source.substr(1, source.size() - 2).c_str());
        PyDict_SetItem((PyObject*)m_LocalEnvironment, key, strValue);
    }
    else if ((pos = source.find("+")) != string::npos)
    {
        PyObject* leftObject = GetObjectBySymbol(source.substr(0, pos));
        PyObject* rightObject = GetObjectBySymbol(source.substr(pos + 1));
        PyObject* resultValue = NULL;
        if (leftObject != NULL && rightObject != NULL && leftObject->type == rightObject->type)
        {
            resultValue = (leftObject->type)->add(leftObject, rightObject);
            PyDict_SetItem((PyObject*)m_LocalEnvironment, key, resultValue);
        } 
        else 
        {
            printf("Syntax error!\n");
        }
    }
}


PyObject* GetObjectBySymbol(const string& symbol)
{
    PyObject* key = PyStr_Create(symbol.c_str());
    PyObject* value = PyDict_GetItem((PyObject*)m_LocalEnvironment, key);
    if (value == NULL)
    {
        printf("[Error]: %s is not defined!\n", symbol.c_str());
    }
    return value;
}


bool IsSouceAllDigit(string& source)
{
    char c;
    for (int i = 0; i < source.size(); i ++)
    {
        c = source[i];
        if (!isdigit(c))
            return false;
    }
    return true;
}
