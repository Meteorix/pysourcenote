#include "PythonVM.h"

void ExecutePrint(string symbol);
void ExecuteAdd(string& target, string& source);
bool IsSouceAllDigit(string& source);

PyDictObject* m_LocalEnvironment;

void ExecuteCommand(string& command)
{
    string::size_type pos = 0;    
    if ((pos == command.find("print ")) != string::npos)
    {
        ExecutePrint(command.substr(6));
    }
    else if ((pos = command.find(" = ")) != string::npos)
    {
        string target = command.substr(0, pos);
        string source = command.substr(pos + 3);
        ExecuteAdd(target, source);
    }
    else{
        printf("Unknown syntax\n");
    }
}


void ExecutePrint(string symbol)
{
    printf("%s\n", symbol.c_str());
}


void ExecuteAdd(string& target, string& source)
{
    string::size_type pos;
    PyObject* strValue = NULL;
    PyObject* resultValue = NULL;
    
    if (IsSouceAllDigit(source))
    {
        PyObject* intValue = PyInt_Create(atoi(source.c_str()));
        PyObject* key = PyStr_Create(target.c_str());
        PyDict_SetItem((PyObject*)m_LocalEnvironment, key, intValue);
    }
}

bool IsSouceAllDigit(string& source)
{
    char c;
    for (int i = 0; i < source.size(); i ++)
    {
        c = source[i];
        if (!isdigit(c)){
            return false;
        } else {
            return true;
        }
    }
}
