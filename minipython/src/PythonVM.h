#pragma once
#include "PyObject.h"
#include "PyIntObject.h"
#include "PyStrObject.h"
#include "PyDictObject.hpp"
#include <string>
#include <algorithm> 
#include <cctype>
#include <locale>


using std::string;

void ExecuteCommand(string& command);

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}